#include "lvgl_setup.h"

/** @brief LVGL 模块日志标签。 */
#define TAG "lvgl_setup"

/** @brief RGB565 每个像素占用的字节数。 */
#define PIXEL_SIZE 2
/** @brief 当前显示面板使用的 LVGL 颜色格式。 */
#define LV_COLOR_FORMAT LV_COLOR_FORMAT_RGB565
/** @brief 非帧缓冲模式下单个绘图缓冲区包含的行数。 */
#define LVGL_DRAW_BUF_LINES 50
/** @brief LVGL 系统节拍定时器周期，单位为毫秒。 */
#define LVGL_TICK_PERIOD_MS 1
/** @brief LVGL 服务任务栈大小，单位为字节。 */
#define LVGL_TASK_STACK_SIZE (16 * 1024)
/** @brief LVGL 服务任务优先级。 */
#define LVGL_TASK_PRIORITY 2

// LVGL library is not thread-safe, this example will call LVGL APIs from different tasks, so use a mutex to protect it
/** @brief 保护 LVGL API 的递归锁；所有任务访问界面对象前必须持有该锁。 */
_lock_t lvgl_api_lock;

/** @brief LVGL 显示对象句柄，初始化后由界面和刷新回调共享。 */
lv_display_t *display = NULL;
/** @brief SquareLine 生成的界面对象集合。 */
extern i2c_master_bus_handle_t bus_handle;
lv_ui guider_ui;

/**
 * @brief 从 GT911 读取一次触摸坐标并转换为 LVGL 输入状态。
 * @param[in] indev LVGL 输入设备对象。
 * @param[out] data 本次采样得到的坐标和按键状态。
 * @note 由 LVGL 输入设备线程调用，不应在中断服务函数中直接调用。
 */
static void lvgl_touch_cb(lv_indev_t *indev, lv_indev_data_t *data)
{
    uint16_t touchpad_x[1] = {0};
    uint16_t touchpad_y[1] = {0};
    uint8_t touchpad_cnt = 0;

    esp_lcd_touch_handle_t touch_pad = lv_indev_get_user_data(indev);
    esp_lcd_touch_read_data(touch_pad);
    /* Get coordinates */
    bool touchpad_pressed = esp_lcd_touch_get_coordinates(touch_pad, touchpad_x, touchpad_y, NULL, &touchpad_cnt, 1);

    if (touchpad_pressed && touchpad_cnt > 0)
    {
        data->point.x = touchpad_x[0];
        data->point.y = touchpad_y[0];
        data->state = LV_INDEV_STATE_PRESSED;
    }
    else
    {
        data->state = LV_INDEV_STATE_RELEASED;
    }
}

/**
 * @brief RGB LCD VSYNC 到来时通知 LVGL 当前帧已经可以继续提交。
 * @param[in] panel LCD 面板句柄（由驱动提供）。
 * @param[in] event_data VSYNC 事件数据，当前实现不使用。
 * @param[in] user_ctx LVGL 显示对象指针。
 * @return false 表示不要求高优先级任务切换。
 */
static bool notify_lvgl_flush_ready(esp_lcd_panel_handle_t panel, const esp_lcd_rgb_panel_event_data_t *event_data, void *user_ctx)
{
    lv_display_t *disp = (lv_display_t *)user_ctx;
    lv_display_flush_ready(disp);
    return false;
}

/**
 * @brief 将 LVGL 渲染出的像素区域提交给 RGB LCD 驱动。
 * @param[in] disp LVGL 显示对象。
 * @param[in] area 待刷新的矩形区域，坐标包含边界。
 * @param[in] px_map RGB565 像素缓冲区。
 * @note 该回调可能在 LVGL 任务中执行，不能在此处阻塞等待应用任务。
 */
static void lvgl_flush_cb(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map)
{
    esp_lcd_panel_handle_t panel_handle = lv_display_get_user_data(disp);
    int offsetx1 = area->x1;
    int offsetx2 = area->x2;
    int offsety1 = area->y1;
    int offsety2 = area->y2;
    // pass the draw buffer to the driver
    esp_lcd_panel_draw_bitmap(panel_handle, offsetx1, offsety1, offsetx2 + 1, offsety2 + 1, px_map);
}

/**
 * @brief 周期性增加 LVGL 内部时基。
 * @param[in] arg esp_timer 回调参数，当前未使用。
 */
static void increase_lvgl_tick(void *arg)
{
    /* Tell LVGL how many milliseconds has elapsed */
    lv_tick_inc(LVGL_TICK_PERIOD_MS);
}

/**
 * @brief LVGL 后台服务任务，负责执行定时器和动画处理。
 * @param[in] arg FreeRTOS 任务参数，当前未使用。
 * @note 任务独占 LVGL 锁后调用 lv_timer_handler，每 10 ms 调度一次。
 */
static void lvgl_port_task(void *arg)
{
    ESP_LOGI(TAG, "Starting LVGL task");
    while (1)
    {
        _lock_acquire(&lvgl_api_lock);
        lv_timer_handler();
        _lock_release(&lvgl_api_lock);
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

/**
 * @brief 初始化 LVGL、显示缓冲区、VSYNC 回调和 LVGL 服务任务。
 * @details 创建 RGB565 显示对象，并将 ESP LCD 面板绑定为 LVGL 的刷新后端；最后加载生成的 UI。
 * @note 必须在 rgb_lcd_init() 完成且 panel_handle 有效后调用。
 */
void lvgl_init(void)
{
    ESP_LOGI(TAG, "Initialize LVGL library");
    lv_init();
    // create a lvgl display
    display = lv_display_create(LCD_H_RES, LCD_V_RES);
    // associate the rgb panel handle to the display
    lv_display_set_user_data(display, panel_handle);
    // set color depth
    lv_display_set_color_format(display, LV_COLOR_FORMAT);
    // create draw buffers
    void *buf1 = NULL;
    void *buf2 = NULL;

    // 分配LVGL绘图缓冲区 （这里使用双缓冲）
#if CONFIG_USE_DOUBLE_FB
    ESP_LOGI(TAG, "Use frame buffers as LVGL draw buffers");
    ESP_ERROR_CHECK(esp_lcd_rgb_panel_get_frame_buffer(panel_handle, 2, &buf1, &buf2));
    // set LVGL draw buffers and direct mode
    lv_display_set_buffers(display, buf1, buf2, LCD_H_RES * LCD_V_RES * PIXEL_SIZE, LV_DISPLAY_RENDER_MODE_FULL);
#else
    ESP_LOGI(TAG, "Allocate LVGL draw buffers");
    //  it's recommended to allocate the draw buffer from internal memory, for better performance
    size_t draw_buffer_sz = LCD_H_RES * LVGL_DRAW_BUF_LINES * PIXEL_SIZE;
    buf1 = heap_caps_malloc(draw_buffer_sz, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
    assert(buf1);
    // set LVGL draw buffers and partial mode
    lv_display_set_buffers(display, buf1, buf2, draw_buffer_sz, LV_DISPLAY_RENDER_MODE_PARTIAL);
#endif // CONFIG_USE_DOUBLE_FB

    // set the callback which can copy the rendered image to an area of the display
    lv_display_set_flush_cb(display, lvgl_flush_cb);

    ESP_LOGI(TAG, "Register event callbacks");
    esp_lcd_rgb_panel_event_callbacks_t cbs = {
        .on_vsync = notify_lvgl_flush_ready,
    };
    ESP_ERROR_CHECK(esp_lcd_rgb_panel_register_event_callbacks(panel_handle, &cbs, display));

    ESP_LOGI(TAG, "Install LVGL tick timer");
    // Tick interface for LVGL (using esp_timer to generate 2ms periodic event)
    const esp_timer_create_args_t lvgl_tick_timer_args = {
        .callback = &increase_lvgl_tick,
        .name = "lvgl_tick"};
    esp_timer_handle_t lvgl_tick_timer = NULL;
    ESP_ERROR_CHECK(esp_timer_create(&lvgl_tick_timer_args, &lvgl_tick_timer));
    ESP_ERROR_CHECK(esp_timer_start_periodic(lvgl_tick_timer, LVGL_TICK_PERIOD_MS * 1000));

    ESP_LOGI(TAG, "Create LVGL task");
    xTaskCreatePinnedToCoreWithCaps(lvgl_port_task, "LVGL", LVGL_TASK_STACK_SIZE,
                            NULL, LVGL_TASK_PRIORITY, NULL, 1, MALLOC_CAP_SPIRAM);

    _lock_acquire(&lvgl_api_lock);
    events_init(&guider_ui);
    setup_ui(&guider_ui);
    _lock_release(&lvgl_api_lock);
}

/**
 * @brief 初始化 GT911 触摸控制器并注册为 LVGL 指针输入设备。
 * @details 触摸控制器通过公共 I2C 总线访问，坐标范围与 LCD 分辨率一致。
 * @note 必须在 lvgl_init() 和 I2C 总线初始化后调用。
 */
void lvgl_touch_init()
{
    ESP_LOGI(TAG, "Initialize GT911 touch panel");
    esp_lcd_panel_io_handle_t tp_io_handle = NULL;
    esp_lcd_panel_io_i2c_config_t io_config = ESP_LCD_TOUCH_IO_I2C_GT911_CONFIG();
    io_config.scl_speed_hz = CONFIG_I2C_MASTER_FREQUENCY;
    // 地址 0x5D (ESP_LCD_TOUCH_IO_I2C_GT911_ADDRESS) 或 0x14  (ESP_LCD_TOUCH_IO_I2C_GT911_ADDRESS_BACKUP)
    esp_lcd_touch_io_gt911_config_t tp_gt911_config = {
        .dev_addr = io_config.dev_addr,
    };
    // 配置触摸参数
    esp_lcd_touch_config_t tp_cfg = {
        .x_max = LCD_H_RES,
        .y_max = LCD_V_RES,
        .rst_gpio_num = CONFIG_GT911_RST_GPIO,
        .int_gpio_num = CONFIG_GT911_INT_GPIO,
        .levels = {
            .reset = 0,
            .interrupt = 0,
        },
        .flags = {
            .swap_xy = 0,
            .mirror_x = 0,
            .mirror_y = 0,
        },
        .driver_data = &tp_gt911_config,
    };

    // 将GT911挂载到I2C总线上
    esp_lcd_new_panel_io_i2c(bus_handle, &io_config, &tp_io_handle);

    // 为屏幕创建触摸设备
    esp_lcd_touch_handle_t tp = NULL;
    esp_lcd_touch_new_i2c_gt911(tp_io_handle, &tp_cfg, &tp);
    // 检查GT911是否初始化成功
    if (tp == NULL)
    {
        ESP_LOGE(TAG, "Failed to initialize GT911 touch panel");
        return;
    }
    else
    {
        ESP_LOGI(TAG, "GT911 initialized successfully");
    }
    // 初始化LVGL输入设备 参考示例 spi_lcd_touch
    ESP_LOGI(TAG, "Initialize input device for LVGL");
    static lv_indev_t *indev;
    indev = lv_indev_create(); // Input device driver (Touch)
    lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
    lv_indev_set_display(indev, display);
    lv_indev_set_user_data(indev, tp);
    lv_indev_set_read_cb(indev, lvgl_touch_cb);
    ESP_LOGI(TAG, "Touch panel initialized successfully");
}
