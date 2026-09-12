#include "DataProc.h"
#include "App/Utils/Filters/Filters.h"
#include "../HAL/HAL.h"

/**
 * @brief Process the periodic timer or FreeRTOS task callback.
 * @param account Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
static void onTimer(Account* account)
{
/**
 * @brief Own and retain the lastStatus state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
   static bool lastStatus = false;

//    HAL::Power_Info_t power;
//    HAL::Power_GetInfo(&power);
//    if (power.isCharging != lastStatus)
//    {
//        DataProc::MusicPlayer_Info_t info;
//        DATA_PROC_INIT_STRUCT(info);
//        info.music = power.isCharging ? "BattChargeStart" : "BattChargeEnd";
//        account->Notify("MusicPlayer", &info, sizeof(info));

//        lastStatus = power.isCharging;
//    }
}

/**
 * @brief Decode a UI or system event and forward it to the responsible model or view.
 * @details Event callbacks execute on the LVGL/UI context; they must remain short and defer blocking work to the corresponding data-processing task.
 * @param account Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param param Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
static int onEvent(Account* account, Account::EventParam_t* param)
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

   if (param->size != sizeof(HAL::Power_Info_t))
   {
       return Account::RES_SIZE_MISMATCH;
   }

   if (param->event == Account::EVENT_SUB_PULL)
   {
/**
 * @brief Own and retain the powerInfo state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
       HAL::Power_Info_t powerInfo;
/**
 * @brief Execute the Power_GetInfo operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param powerInfo Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
       HAL::Power_GetInfo(&powerInfo);

       memcpy(param->data_p, &powerInfo, param->size);

    //    printf("[DP] PowerPULL\r\n");
   }
   else if (param->event == Account::EVENT_NOTIFY)
   {
       HAL::Power_Info_t *info = (HAL::Power_Info_t *)param->data_p;

/**
 * @brief Execute the Power_SetAutoLowPowerEnable operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param isAutoPowerOff Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
       HAL::Power_SetAutoLowPowerEnable(info->isAutoPowerOff);

    //    printf("[DP] PowerNOTOFIY\r\n");
   }



    return Account::RES_OK;
}

/**
 * @brief Execute the DATA_PROC_INIT_DEF operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param Power Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
DATA_PROC_INIT_DEF(Power)
{
//    account->Subscribe("MusicPlayer");
   account->SetEventCallback(onEvent);
//    account->SetTimerPeriod(500);
}
