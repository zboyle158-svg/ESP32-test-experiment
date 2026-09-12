#include "DataProc.h"
#include "../HAL/HAL.h"
#include "App/Utils/Time/Time.h"
#include "App/Config/Config.h"

using namespace DataProc;

/**
 * @brief Decode a UI or system event and forward it to the responsible model or view.
 * @details Event callbacks execute on the LVGL/UI context; they must remain short and defer blocking work to the corresponding data-processing task.
 * @param account Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param param Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
static int onEvent(Account* account, Account::EventParam_t* param)
{
   if (param->event != Account::EVENT_SUB_PULL)
   {
       return Account::RES_UNSUPPORTED_REQUEST;
   }

   if (param->size != sizeof(HAL::Clock_Info_t))
   {
       return Account::RES_SIZE_MISMATCH;
   }

/**
 * @brief Own and retain the gps state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
   HAL::GPS_Info_t gps;
   if (account->Pull("GPS", &gps, sizeof(gps)) != Account::RES_OK)
   {
       return Account::RES_UNKNOW;
   }

/**
 * @brief Own and retain the sysCfg state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
   DataProc::SysConfig_Info_t sysCfg;
   if (account->Pull("SysConfig", &sysCfg, sizeof(sysCfg)) != Account::RES_OK)
   {
       return Account::RES_UNKNOW;
   }

   setTime(
       gps.clock.hour,
       gps.clock.minute,
       gps.clock.second,
       gps.clock.day,
       gps.clock.month,
       gps.clock.year
   );
   adjustTime(sysCfg.timeZone * SECS_PER_HOUR);

   HAL::Clock_Info_t* info = (HAL::Clock_Info_t*)param->data_p;
/**
 * @brief Execute the year operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
   info->year = year();
/**
 * @brief Execute the month operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
   info->month = month();
/**
 * @brief Execute the day operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
   info->day = day();
/**
 * @brief Execute the hour operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
   info->hour = hour();
/**
 * @brief Execute the minute operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
   info->minute = minute();
/**
 * @brief Execute the second operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
   info->second = second();

    return Account::RES_OK;
}

/**
 * @brief Execute the DATA_PROC_INIT_DEF operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param TzConv Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
DATA_PROC_INIT_DEF(TzConv)
{
   account->Subscribe("GPS");
   account->Subscribe("SysConfig");
   account->SetEventCallback(onEvent);
}
