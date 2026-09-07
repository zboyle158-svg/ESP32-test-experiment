#pragma once

/** @file bat_adc.h @brief 电池 ADC 采样与电量换算接口。 */

/** @brief 初始化 ADC 通道、校准参数及电池分压采样链路。 */
void bat_adc_init(void);
/**
 * @brief 读取电池电量百分比。
 * @param[out] bat_level 输出电量百分比；调用者必须传入有效指针。
 */
void bat_adc_get_battery_level(float *bat_level);
