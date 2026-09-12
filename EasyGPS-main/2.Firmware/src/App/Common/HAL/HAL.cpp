#include "HAL.h"

/**
 * @brief Task to handle hal timer
 *
 * @param param
 */
/**
 * @brief FreeRTOS worker that periodically services the HAL scheduler.
 * @param param Unused FreeRTOS task parameter.
 *
 * @details Individual module intervals are enforced inside HAL_Update(). The
 * short outer delay prevents this low-level coordination task from starving
 * LVGL, WiFi and application tasks.
 */
/**
 * @brief Execute the task_hal_update_handler operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param param Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
static void task_hal_update_handler(void *param)
{
    while (1)
    {
/**
 * @brief Refresh the HAL state without blocking the scheduler.
 * @details The function consumes the latest cached DataProc/HAL snapshot and updates presentation state; it does not own or free the source data.
 * @return Operation result or status; inspect it before using dependent state.
 */
        HAL::HAL_Update();
        delay(10);
    }
    vTaskDelete(NULL);
}

/**
 * @brief Initialise HAL modules and launch the HAL FreeRTOS task.
 *
 * @warning The task stack is fixed at `1024 * 5`; new HAL features with large
 * local buffers should be measured for stack use before being enabled.
 */
/**
 * @brief Initialize HAL state and hardware or data resources.
 */
void HAL::HAL_Init(void)
{
    // Buzz_init();
    // Audio_Init();
/**
 * @brief Execute the Power_Init operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Power_Init();

    xTaskCreate(task_hal_update_handler, "Hal", 1024 * 5, nullptr, 5, nullptr);
}

/**
 * @brief Service due hardware updates without blocking the user interface.
 *
 * @details `__IntervalExecute` turns the task's $10\text{ ms}$ loop into
 * independent update periods. Do not put long delays or network transactions
 * directly in this function.
 */
/**
 * @brief Refresh the HAL state without blocking the scheduler.
 * @details The function consumes the latest cached DataProc/HAL snapshot and updates presentation state; it does not own or free the source data.
 */
void HAL::HAL_Update(void)
{
    __IntervalExecute(HAL::IMU_Update(), 200);
    __IntervalExecute(HAL::MAG_Update(), 50);
    __IntervalExecute(HAL::Power_Update(), 500);
    __IntervalExecute(HAL::WiFi_Update(), 100);
    __IntervalExecute(HAL::GPS_Update(), 500);
    // __IntervalExecute(HAL::ENV_Update(), 100);
}
