#include "DataProc.h"
#include "../HAL/HAL.h"

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

    if (param->size != sizeof(HAL::MAG_Info_t))
    {
        return Account::RES_SIZE_MISMATCH;
    }

    if (param->event == Account::EVENT_SUB_PULL)
    {
        HAL::MAG_Info_t *info = (HAL::MAG_Info_t *)param->data_p;

/**
 * @brief Execute the MAG_GetInfo operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param info Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
        HAL::MAG_GetInfo(info);

        printf("[DP] MAG PULL\r\n");
    }
    else if (param->event == Account::EVENT_NOTIFY)
    {
        HAL::MAG_Info_t *info = (HAL::MAG_Info_t *)param->data_p;

        if (info->isCalibrated)
/**
 * @brief Execute the MAG_SetCalibration operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
            HAL::MAG_SetCalibration(); // 进行MAG校准

        printf("[DP] MAG NOTOFIY\r\n");
    }

    return Account::RES_OK;
}

/**
 * @brief Execute the DATA_PROC_INIT_DEF operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param MAG Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
DATA_PROC_INIT_DEF(MAG)
{
    account->SetEventCallback(onEvent);

    // HAL::MAG_SetCommitCallback([](void *info, void *userData)
    //                            {
    //    Account* account = (Account*)userData;
    //    return account->Commit(info, sizeof(HAL::MAG_Info_t)); },
    //                            account);
}
