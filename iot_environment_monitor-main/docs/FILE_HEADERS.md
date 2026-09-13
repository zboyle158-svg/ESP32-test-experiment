# 文件级说明索引

本文档与源码文件顶部的 Doxygen 注释配套，逐文件说明用途和使用方法。源码中的 `@file` 注释回答“这个文件是什么”，本文回答“项目中什么时候调用它”。

## 应用入口与任务

| 文件 | 作用 | 使用方法 |
|---|---|---|
| `main/main.c` | 系统入口、I2C 总线和任务创建 | ESP-IDF 自动调用 `app_main()` |
| `main/lvgl_setup.c/.h` | LVGL、RGB LCD、GT911 初始化 | `app_main()` 依次调用 `lvgl_init()`、`lvgl_touch_init()` |
| `main/ntp.c/.h` | SNTP 校时任务 | Wi-Fi 启动后由 `ntp_sync_task` 运行 |
| `main/wifi_event_callback.c` | Wi-Fi/IP 事件回调 | 由 `wifi_event_init()` 注册，禁止直接阻塞 |
| `main/power_event_callback.c` | 电源芯片中断处理 | 由电源管理组件注册 GPIO 中断 |
| `main/RTOS_tasks/RTOS_tasks.h` | 所有任务函数和句柄声明 | 由 `main.c` 和各任务源文件包含 |
| `main/RTOS_tasks/stcc4_task.c` | STCC4 采样任务 | 创建后等待通知，结果写入 `stcc4` |
| `main/RTOS_tasks/sgp4x_task.c` | SGP4x/VOC 采样任务 | 创建后等待通知，结果写入 `voc_index` |
| `main/RTOS_tasks/get_data_task.c` | 5 秒采样触发和历史缓存 | 通知传感器任务并更新图表窗口 |
| `main/RTOS_tasks/bat_adc_task.c` | 电池采样与充电滞回控制 | 周期运行并通知状态栏 |
| `main/RTOS_tasks/status_bar_task.c` | 时间、电量、Wi-Fi 状态栏 | `status_bar_init_task()` 创建子任务 |
| `main/RTOS_tasks/weather_task.c` | 天气 HTTP 请求和界面更新 | 网络在线时运行，更新天气页面 |

## 硬件组件

| 文件/目录 | 作用 | 使用方法 |
|---|---|---|
| `components/stcc4` | STCC4 I2C 协议驱动 | 初始化后调用测量、读取、睡眠 API |
| `components/sgp4x` | SGP4x 驱动和 Sensirion 算法 | 创建句柄后读取原始 VOC 信号 |
| `components/bat_adc` | ADC 电池电压换算 | `bat_adc_init()` 后调用读取函数 |
| `components/rgb_lcd` | RGB LCD 面板和时序 | `rgb_lcd_init()` 创建 `panel_handle` |
| `components/backlight` | LEDC 背光 PWM | 设置占空比控制亮度 |
| `components/power_management` | AW32001 充放电和状态寄存器 | I2C 初始化后读写寄存器或调用控制 API |
| `components/lpm` | 低功耗策略 | 在系统初始化阶段调用 `lpm_init()` |

## 网络与存储

| 文件/目录 | 作用 | 使用方法 |
|---|---|---|
| `components/wifi` | STA 连接、扫描、断线状态 | `wifi_init()` 后调用连接/扫描 API |
| `components/mqtt_user` | MQTT 客户端和数据发布 | 读取 NVS 配置后调用 `mqtt_start()` |
| `components/weather` | HTTP 天气请求和 JSON 解析 | `weather_get()` 返回天气结构体 |
| `components/ota` | HTTPS OTA 升级 | 提供版本 URL 和下载 URL 后启动升级 |
| `components/nvs_helper` | 配置持久化 | 使用 `nvs_read()`/`nvs_write()` 选择配置类别 |

## 用户界面

| 文件/目录 | 作用 | 使用方法 |
|---|---|---|
| `main/ui/data_chart.c/.h` | 历史数组和图表刷新任务 | 聚合任务写缓存，UI 任务读缓存 |
| `main/ui/status_bar.c/.h` | 状态栏控件更新接口 | 只调用 `status_bar_set_*` 函数 |
| `main/ui/custom` | 手写 UI 事件和主题扩展 | 在生成 UI 初始化后调用 |
| `main/ui/generated` | SquareLine/LVGL 生成的屏幕、事件、字体、图片 | 只调用生成接口，不直接修改；重新导出会覆盖改动 |

## 构建与配置文件

`CMakeLists.txt` 注册工程，`main/CMakeLists.txt` 收集源文件和组件依赖，`components/*/CMakeLists.txt` 定义组件边界；`sdkconfig*` 保存芯片和功能配置，`Kconfig.projbuild` 定义自定义菜单，`partitions.csv` 定义 Flash 分区，`dependencies.lock` 固定第三方版本。

## 调用约束

* 传感器和网络协议只能在对应任务或组件中执行，不能塞入 LVGL 回调。
* 调用 LVGL API 前获取 `lvgl_api_lock`。
* I2C 总线由 `main.c` 创建一次，组件不得重复创建总线。
* 生成目录只读使用；业务修改放在 `ui/custom`。
