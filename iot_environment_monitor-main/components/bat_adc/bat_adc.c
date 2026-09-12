#include <stdio.h>
#include "bat_adc.h"
#include "esp_log.h"
#include "adc_battery_estimation.h"

#define TAG "bat_adc"
#define ADC_UNIT (ADC_UNIT_1)
#define ADC_BITWIDTH (ADC_BITWIDTH_12)
#define ADC_ATTEN (ADC_ATTEN_DB_2_5)
#define ADC_CHANNEL (ADC_CHANNEL_3)
#define RESISTOR_UPPER (330)
#define RESISTOR_LOWER (110)

adc_battery_estimation_handle_t adc_battery_estimation_handle = NULL;
/** @brief 初始化 ADC 电池容量估算器和电阻分压参数。 */
void bat_adc_init()
{
    adc_battery_estimation_t config = {
        .internal = {
            .adc_unit = ADC_UNIT,
            .adc_bitwidth = ADC_BITWIDTH,
            .adc_atten = ADC_ATTEN,
        },
        .adc_channel = ADC_CHANNEL,
        .lower_resistor = RESISTOR_LOWER,
        .upper_resistor = RESISTOR_UPPER,
    };
    adc_battery_estimation_handle = adc_battery_estimation_create(&config);
}

/** @brief 读取校准后的电池容量百分比。 @param[out] bat_level 输出容量指针。 */
void bat_adc_get_battery_level(float *bat_level)
{
    if (adc_battery_estimation_handle == NULL) {
        ESP_LOGE(TAG, "Battery ADC estimation handle not initialized");
        return;
    }
    adc_battery_estimation_get_capacity(adc_battery_estimation_handle, bat_level);
}
