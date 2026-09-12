#pragma once

/**
 * @file backlight.h
 * @brief LCD 背光 PWM 控制接口。
 * @details 背光由 ESP-IDF LEDC 低速定时器输出 PWM，占空比范围为 $0\%$ 到 $100\%$。
 */

#include "sdkconfig.h"
#include <stdint.h>

/** @file backlight.h @brief LCD 背光 PWM 控制接口。 */

/** @brief 当前背光占空比，范围由驱动配置决定，通常为 0~100。 */
extern volatile uint8_t backlight_duty;

/** @brief 上述变量由驱动维护，供低功耗唤醒后恢复亮度。 */

/** @brief 初始化背光 GPIO、LEDC 定时器和 PWM 通道。 */
void lcd_backlight_init(void);

/** @brief 初始化背光 GPIO、LEDC 定时器和 PWM 通道。 */
/** @brief 设置 LCD 背光 PWM 占空比。 @param duty 目标占空比。 */
void lcd_backlight_set_duty(uint8_t duty);

/**
 * @brief 设置 LCD 背光 PWM 占空比。
 * @param duty 目标占空比，超过 $100$ 时限制为 $100$。
 */
/** @brief 读取当前 LCD 背光 PWM 占空比。 @param[out] duty 输出占空比指针。 */
void lcd_backlight_get_duty(uint8_t *duty);

/** @brief 将当前硬件 PWM 占空比写入调用者提供的变量。 */
