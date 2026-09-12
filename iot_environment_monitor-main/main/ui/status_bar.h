#pragma once
#include <stdbool.h>

/** @file status_bar.h @brief Status bar API. */

/** @brief Create status bar widgets. */
/** @brief 创建状态栏控件。 */
void status_bar_create(void);
/** @brief 更新状态栏时间文本。 */
void status_bar_set_time(const char *time_str);
/** @brief 更新 Wi-Fi 图标状态。 */
void status_bar_set_wifi_state(bool connected);
/** @brief 更新电池百分比和图标。 */
void status_bar_set_battery_level(float level);
/** @brief 更新充电图标状态。 */
void status_bar_set_charge_state(bool charging);
/** @brief 显示状态栏。 */
void status_bar_show(bool need_api_lock);
/** @brief 隐藏状态栏。 */
void status_bar_hide(bool need_api_lock);
