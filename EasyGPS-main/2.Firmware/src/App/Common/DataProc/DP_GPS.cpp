#include "DataProc.h"
#include "../HAL/HAL.h"
#include "App/Config/Config.h"

typedef enum
{
    GPS_STATUS_DISCONNECT,
    GPS_STATUS_UNSTABLE,
    GPS_STATUS_CONNECT,
/**
 * @brief Own and retain the GPS_Status_t state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
} GPS_Status_t;

/**
 * @brief Process the periodic timer or FreeRTOS task callback.
 * @param account Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
static void onTimer(Account* account)
{
/**
 * @brief Own and retain the gpsInfo state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
   HAL::GPS_Info_t gpsInfo;
/**
 * @brief Execute the GPS_GetInfo operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param gpsInfo Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
   HAL::GPS_GetInfo(&gpsInfo);

/**
 * @brief Own and retain the satellites state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
   int satellites = gpsInfo.satellites;

/**
 * @brief Own and retain the nowStatus state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
   static GPS_Status_t nowStatus = GPS_STATUS_DISCONNECT;
/**
 * @brief Own and retain the lastStatus state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
   static GPS_Status_t lastStatus = GPS_STATUS_DISCONNECT;

   if (satellites > 7)
   {
       nowStatus = GPS_STATUS_CONNECT;
   }
   else if (satellites < 5 && satellites >= 3)
   {
       nowStatus = GPS_STATUS_UNSTABLE;
   }
   else if (satellites == 0)
   {
       nowStatus = GPS_STATUS_DISCONNECT;
   }

   if (nowStatus != lastStatus)
   {
       const char* music[] =
       {
           "Disconnect",
           "UnstableConnect",
           "Connect"
       };

/**
 * @brief Own and retain the info state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
       DataProc::MusicPlayer_Info_t info;
/**
 * @brief Execute the DATA_PROC_INIT_STRUCT operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param info Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
       DATA_PROC_INIT_STRUCT(info);
       info.music = music[nowStatus];
    //    account->Notify("MusicPlayer", &info, sizeof(info));
       lastStatus = nowStatus;
   }

   if (satellites >= 3)
   {
       account->Commit(&gpsInfo, sizeof(gpsInfo));
       account->Publish();
   }
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

   if (param->event != Account::EVENT_SUB_PULL)
   {
       return Account::RES_UNSUPPORTED_REQUEST;
   }

   if (param->size != sizeof(HAL::GPS_Info_t))
   {
       return Account::RES_SIZE_MISMATCH;
   }

/**
 * @brief Execute the GPS_GetInfo operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param data_p Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
   HAL::GPS_GetInfo((HAL::GPS_Info_t*)param->data_p);

    return Account::RES_OK;
}

/**
 * @brief Execute the DATA_PROC_INIT_DEF operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param GPS Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
DATA_PROC_INIT_DEF(GPS)
{
//    account->Subscribe("MusicPlayer");

   account->SetEventCallback(onEvent);
   account->SetTimerPeriod(CONFIG_GPS_REFR_PERIOD);
}
