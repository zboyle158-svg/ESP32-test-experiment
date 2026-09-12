#include "DataProc.h"
#include "../HAL/HAL.h"
#include "App/Config/Config.h"

/**
 * @brief Process the periodic timer or FreeRTOS task callback.
 * @param account Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
static void onTimer(Account *account)
{
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

    if (param->size != sizeof(HAL::WiFi_Info_t))
    {
        return Account::RES_SIZE_MISMATCH;
    }

    if (param->event == Account::EVENT_SUB_PULL)
    {
        HAL::WiFi_Info_t *info = (HAL::WiFi_Info_t *)param->data_p;
/**
 * @brief Execute the WiFi_GetInfo operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param info Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
        HAL::WiFi_GetInfo(info);
        printf("[DP] WiFiPULL\r\n");
    }
    else if (param->event == Account::EVENT_NOTIFY)
    {
        HAL::WiFi_Info_t *info = (HAL::WiFi_Info_t *)param->data_p;

/**
 * @brief Execute the WiFi_APSetEnable operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param isAPEnabled Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
        HAL::WiFi_APSetEnable(info->isAPEnabled);
/**
 * @brief Execute the WiFi_STASetEnable operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param isWiFiEnabled Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
        HAL::WiFi_STASetEnable(info->isWiFiEnabled);

        printf("[DP] WiFiNOTOFIY\r\n");
    }

    return Account::RES_OK;
}

/**
 * @brief Execute the DATA_PROC_INIT_DEF operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param WiFi Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
DATA_PROC_INIT_DEF(WiFi)
{
    account->SetEventCallback(onEvent);
}
