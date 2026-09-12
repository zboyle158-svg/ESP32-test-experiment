#pragma once

/**
 * @file bat_adc.h
 * @brief 电池 ADC 采样与容量估算接口。
 * @details 组件内部使用 ADC 电池估算器，并考虑硬件分压电阻。
 */

/** @file bat_adc.h @brief 电池 ADC 采样与电量换算接口。 */

/** @brief 初始化 ADC 通道、校准参数及电池分压采样链路。 */
void bat_adc_init(void);

/** @brief 初始化 ADC 通道、衰减、校准器和电池分压参数。 */
/**
 * @brief 读取电池电量百分比。
 * @param[out] bat_level 输出电量百分比；调用者必须传入有效指针。
 */
void bat_adc_get_battery_level(float *bat_level);

/** @brief 输出经过校准的电池容量百分比；调用前必须完成初始化。 */
