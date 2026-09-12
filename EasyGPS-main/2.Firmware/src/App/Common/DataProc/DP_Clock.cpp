#include "DataProc.h"
#include "../HAL/HAL.h"
#include "lvgl.h"

/**
 * @brief Read Tick from the current object state.
 * @return Operation result or status; inspect it before using dependent state.
 */
uint32_t DataProc::GetTick()
{
    return lv_tick_get();
}

/**
 * @brief Read TickElaps from the current object state.
 * @param prevTick Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
uint32_t DataProc::GetTickElaps(uint32_t prevTick)
{
    return lv_tick_elaps(prevTick);
}

/**
 * @brief Execute the MakeTimeString operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param ms Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param buf Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param len Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
const char* DataProc::MakeTimeString(uint64_t ms, char* buf, uint16_t len)
{
/**
 * @brief Own and retain the ss state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
   uint64_t ss = ms / 1000;
/**
 * @brief Own and retain the mm state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
   uint64_t mm = ss / 60;
   uint32_t hh = (uint32_t)(mm / 60);

   lv_snprintf(
       buf, len,
       "%d:%02d:%02d",
       hh,
       (uint32_t)(mm % 60),
       (uint32_t)(ss % 60)
   );

/**
 * @brief Own and retain the buf state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    return buf;
}

/**
 * @brief Execute the Clock_Calibrate operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param account Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param gpsInfo Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
static bool Clock_Calibrate(Account* account, HAL::GPS_Info_t* gpsInfo)
{
/**
 * @brief Own and retain the retval state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    bool retval = false;
   if(gpsInfo->isVaild)
   {
/**
 * @brief Own and retain the clock state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
       HAL::Clock_Info_t clock;
       if (account->Pull("TzConv", &clock, sizeof(clock)) == Account::RES_OK)
       {
/**
 * @brief Execute the Clock_SetInfo operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param clock Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
           HAL::Clock_SetInfo(&clock);
           retval = true;
       }
   }
/**
 * @brief Own and retain the retval state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    return retval;
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
   if (param->event == Account::EVENT_PUB_PUBLISH)
   {
       if (param->size == sizeof(HAL::GPS_Info_t))
       {
        //    if (Clock_Calibrate(account, (HAL::GPS_Info_t*)param->data_p))
        //    {
        //        account->Unsubscribe("GPS");
        //    }
       }
       
       return Account::RES_OK;
   }

   if (param->event != Account::EVENT_SUB_PULL)
   {
       return Account::RES_UNSUPPORTED_REQUEST;
   }

   if (param->size != sizeof(HAL::Clock_Info_t))
   {
       return Account::RES_SIZE_MISMATCH;
   }

   HAL::Clock_Info_t* info = (HAL::Clock_Info_t*)param->data_p;
/**
 * @brief Execute the Clock_GetInfo operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param info Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
   HAL::Clock_GetInfo(info);

    return Account::RES_OK;
}

/**
 * @brief Execute the DATA_PROC_INIT_DEF operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param Clock Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
DATA_PROC_INIT_DEF(Clock)
{
//    account->Subscribe("TzConv");
   account->Subscribe("GPS");
   account->SetEventCallback(onEvent);
}
