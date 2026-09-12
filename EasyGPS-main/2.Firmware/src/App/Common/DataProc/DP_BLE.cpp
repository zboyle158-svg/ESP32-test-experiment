#include "DataProc.h"
#include "../HAL/HAL.h"
#include "App/Config/Config.h"

using namespace DataProc;

/**
 * @brief Process the periodic timer or FreeRTOS task callback.
 * @param account Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
static void onTimer(Account *account)
{
}

/**
 * @brief Execute the onNotify operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param account Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param info Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
static void onNotify(Account *account, HAL::BLE_Info_t *info)
{
    switch (info->DC)
    {
    // Cmd
    case true:
    {
        if (info->isEnabled)
/**
 * @brief Execute the BLE_SetBegin operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
            HAL::BLE_SetBegin();
        else
/**
 * @brief Execute the BLE_SetSleep operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
            HAL::BLE_SetSleep();
        break;
    }
    // Data
    case false:
    {
        if (info->KeyVal[0] | info->KeyVal[1])
/**
 * @brief Execute the BLE_SetKeyboardValue operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param KeyVal Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
            HAL::BLE_SetKeyboardValue(info->KeyVal);

        if (info->MouseVal[0] | info->MouseVal[1] | info->MouseVal[2] | info->MouseVal[3])
/**
 * @brief Execute the BLE_SetMouseMoveValue operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param MouseVal Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
            HAL::BLE_SetMouseMoveValue(info->MouseVal);

        if (info->MouseClick)
/**
 * @brief Execute the BLE_SetMouseClickValue operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param MouseClick Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
            HAL::BLE_SetMouseClickValue(info->MouseClick);
        break;
    }

    default:
        break;
    }
}

/**
 * @brief Decode a UI or system event and forward it to the responsible model or view.
 * @details Event callbacks execute on the LVGL/UI context; they must remain short and defer blocking work to the corresponding data-processing task.
 * @param account Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param param Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
static int onEvent(Account *account, Account::EventParam_t *param)
{

    if (param->event == Account::EVENT_TIMER)
    {
        onTimer(account);
        return Account::RES_OK;
    }

    if (param->event != Account::EVENT_SUB_PULL && param->event != Account::EVENT_NOTIFY)
    {
        return Account::RES_UNSUPPORTED_REQUEST;
    }

    if (param->size != sizeof(HAL::BLE_Info_t))
    {
        return Account::RES_SIZE_MISMATCH;
    }

    switch (param->event)
    {
    case Account::EVENT_SUB_PULL:
    {
        HAL::BLE_Info_t *info = (HAL::BLE_Info_t *)param->data_p;
/**
 * @brief Execute the BLE_GetInfo operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param info Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
        HAL::BLE_GetInfo(info);
        printf("[DP] BLE PULL\r\n");
        break;
    }
    case Account::EVENT_NOTIFY:
    {
        onNotify(account, (HAL::BLE_Info_t *)param->data_p);
        printf("[DP] BLE NOTOFIY\r\n");
        break;
    }
    default:
        break;
    }

    return Account::RES_OK;
}

/**
 * @brief Execute the DATA_PROC_INIT_DEF operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param BLE Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
DATA_PROC_INIT_DEF(BLE)
{
    account->SetEventCallback(onEvent);
}
