#include "power_management.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define TAG "AW32001"
/** @brief 电源管理芯片中断任务使用的任务句柄。 */
extern TaskHandle_t update_battery_task;

/** @brief AW32001 GPIO 中断处理任务句柄。 */
TaskHandle_t aw32001_interrupt_task_handle = NULL;

/**
 * @brief AW32001 充电状态 GPIO 中断服务函数。
 * @param[in] arg GPIO 驱动传递的用户参数，当前未使用。
 * @note ISR 中只发送任务通知，避免在中断上下文执行 I2C 访问。
 */
void aw32001_isr_handler(void *arg)
{
    xTaskNotifyGive(aw32001_interrupt_task_handle);
}

/**
 * @brief 读取 AW32001 状态并向电池任务转发电源变化事件。
 * @param[in] arg FreeRTOS 任务参数，当前未使用。
 */
void aw32001_interrupt_task(void *arg)
{
    aw32001_read_sys_status(&pwr_sys_status);
    while (1)
    {
        // 等待中断事件发生
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        aw32001_read_sys_status(&pwr_sys_status);
        switch (pwr_sys_status.chg_stat)
        {
        case AW32001_CHG_STAT_NOT_CHARGING:
            // ESP_LOGW(TAG, "AW32001 Interrupt: Charge Status = NOT CHARGING");
            break;
        case AW32001_CHG_STAT_PRE_CHARGE:
            // ESP_LOGW(TAG, "AW32001 Interrupt: Charge Status = PRE CHARGE");
            break;
        case AW32001_CHG_STAT_FAST_CHARGE:
            // ESP_LOGW(TAG, "AW32001 Interrupt: Charge Status = FAST CHARGE");
            break;
        case AW32001_CHG_STAT_CHARGE_DONE:
            // ESP_LOGW(TAG, "AW32001 Interrupt: Charge Status = CHARGE DONE");
            break;
        }
        switch (pwr_sys_status.pg_stat)
        {
        case true:
            if (update_battery_task)
            {
                xTaskNotifyGive(update_battery_task);
            }

            // ESP_LOGW(TAG, "AW32001 Interrupt: Power Source = USB POWER");
            break;
        case false:
            if (update_battery_task)
            {
                xTaskNotifyGive(update_battery_task);
            }
            // ESP_LOGW(TAG, "AW32001 Interrupt: Power Source = BATTERY POWER");
            break;
        }
    }
}

/**
 * @brief 配置 AW32001 中断 GPIO 并创建状态处理任务。
 * @details GPIO5 下降沿表示充电器或电源路径状态变化；重复调用不会重复创建任务。
 */
void aw32001_interrupt_init()
{
    gpio_config_t io_conf = {};
    io_conf.intr_type = GPIO_INTR_NEGEDGE; // 下降沿产生中断
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pull_up_en = 0;
    io_conf.pin_bit_mask = 1ULL << 5;
    gpio_config(&io_conf);
    gpio_install_isr_service(0);
    gpio_isr_handler_add(GPIO_NUM_5, aw32001_isr_handler, NULL);
    if (aw32001_interrupt_task_handle != NULL)
    {
        ESP_LOGW(TAG, "AW32001 interrupt task already created");
        return;
    }
    xTaskCreateWithCaps(aw32001_interrupt_task, "aw32001_interrupt_task", 8 * 1024, NULL, 6, &aw32001_interrupt_task_handle, MALLOC_CAP_SPIRAM);
}
