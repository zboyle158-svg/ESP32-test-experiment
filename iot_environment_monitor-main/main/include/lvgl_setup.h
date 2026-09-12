#pragma once

/** @file lvgl_setup.h @brief LVGL display and GT911 touch initialization. */
#include "rgb_lcd.h"
#include "gui_guider.h"
#include "events_init.h"
#include "custom.h"
#include "lvgl.h"
#include "esp_lcd_touch_gt911.h"
#include "esp_lcd_touch.h"
#include "esp_log.h"
#include "esp_err.h"
#include "driver/i2c_master.h"
#include "esp_timer.h"
#include <sys/lock.h>

/** @brief LVGL 显示对象，由 lvgl_init 创建并供刷新回调使用。 */
extern lv_display_t *display;

/** @brief Initialize LVGL, display buffers, and generated UI screens. */
/** @brief 初始化 LVGL 核心、RGB 显示驱动、缓冲区和后台任务。 */
void lvgl_init(void);
/** @brief Initialize the GT911 touch controller and input device. */
/** @brief 初始化 GT911 触摸控制器并注册 LVGL 输入设备。 */
void lvgl_touch_init(void);
