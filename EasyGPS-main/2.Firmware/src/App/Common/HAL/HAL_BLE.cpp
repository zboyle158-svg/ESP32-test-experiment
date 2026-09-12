#include "HAL.h"
#include "ChappieCore/ChappieCore.h"

/**
 * @brief Own and retain the Chappie state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
extern ChappieCore Chappie;

/**
 * @brief  BLE初始化
 * @param  无
 * @retval 无
 */
/**
 * @brief Execute the BLE_Init operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 */
void HAL::BLE_Init()
{
    // ...
}

/**
 * @brief Refresh the HAL_BLE state without blocking the scheduler.
 * @details The function consumes the latest cached DataProc/HAL snapshot and updates presentation state; it does not own or free the source data.
 */
void HAL::BLE_Update(void)
{
    // ...
}

/**
 * @brief Execute the BLE_SetBegin operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 */
void HAL::BLE_SetBegin(void)
{
/**
 * @brief Execute the Chappie.Ble.begin operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Chappie.Ble.begin();
}

/**
 * @brief Execute the BLE_SetSleep operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 */
void HAL::BLE_SetSleep(void)
{
/**
 * @brief Execute the Chappie.Ble.sleep operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Chappie.Ble.sleep();
}

/**
 * @brief Execute the BLE_SetKeyboardValue operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param c Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void HAL::BLE_SetKeyboardValue(uint8_t *c)
{
    printf("[BLE] c[0]: %d, c[1]: %d\n", c[0], c[1]);
/**
 * @brief Execute the Chappie.Ble.write operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param c Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    uint16_t Ret = Chappie.Ble.write(c);

    printf("[BLE] Ret: %d\n", Ret);
}

/**
 * @brief Execute the BLE_SetMouseMoveValue operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param c Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void HAL::BLE_SetMouseMoveValue(uint8_t *c)
{
    printf("[BLE] c[0]: %d, c[1]: %d, c[2]: %d, c[3]: %d\n", c[0], c[1], c[2], c[3]);
/**
 * @brief Execute the Chappie.Ble.move operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param c Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Chappie.Ble.move(c);
}

/**
 * @brief Execute the BLE_SetMouseClickValue operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param b Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void HAL::BLE_SetMouseClickValue(uint16_t b)
{
    printf("[BLE] b: %d\n", b);
/**
 * @brief Execute the Chappie.Ble.click operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param b Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Chappie.Ble.click(b);
}

/**
 * @brief Execute the BLE_GetInfo operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param info Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void HAL::BLE_GetInfo(HAL::BLE_Info_t *info)
{
/**
 * @brief Execute the Chappie.Ble.GetName operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    info->name = Chappie.Ble.GetName();
/**
 * @brief Execute the Chappie.Ble.isConnected operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    info->isConnected = Chappie.Ble.isConnected();
/**
 * @brief Execute the Chappie.Ble.isEnabled operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    info->isEnabled = Chappie.Ble.isEnabled();
}
