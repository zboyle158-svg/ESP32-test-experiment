#include "RTOS_tasks.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "stcc4.h"

#define TAG "sensor_stcc4"
extern i2c_master_bus_handle_t bus_handle;

TaskHandle_t stcc4_task_handle = NULL;

STCC4_t stcc4 = {0};
/**
 * @brief Initializes STCC4 and publishes CO2, temperature, and humidity.
 *
 * Sensor access is notification-driven so the I2C bus is used only when a
 * new data point is required by the data aggregation task.
 */
/** @brief STCC4 采样任务：等待通知并更新 CO2、温度和湿度共享数据。 */
void stcc4_task(void *arg)
{
    if (i2c_master_probe(bus_handle, STCC4_I2C_ADDR_64, 1000) == ESP_OK)
    {
        ESP_LOGI(TAG, "STCC4 found at address 0x%02X", STCC4_I2C_ADDR_64);
        ESP_ERROR_CHECK(stcc4_i2c_init(bus_handle));
    }
    else
    {
        ESP_LOGE(TAG, "STCC4 not found!");
        vTaskDelete(NULL);
    }
    while (1)
    {
        stcc4_exit_sleep_mode();                      // step 1 退出睡眠模式
        ESP_ERROR_CHECK(stcc4_measure_single_shot()); // step 2 触发单次测量
        ESP_ERROR_CHECK(stcc4_read_measurement(&stcc4.co2Concentration, &stcc4.temperature,
                                               &stcc4.relativeHumidity, &stcc4.sensorStatus)); // step 3 读取测量值
        ESP_ERROR_CHECK(stcc4_enter_sleep_mode());                                             // step 4 进入睡眠模式，节省功耗
        ESP_LOGI(TAG, "[single shot] CO2 Concentration: %d ppm, Temperature: %.2f C, Relative Humidity: %.2f %%, Sensor Status: 0x%04X",
                 stcc4.co2Concentration, stcc4.temperature, stcc4.relativeHumidity, stcc4.sensorStatus);
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
    }
}
