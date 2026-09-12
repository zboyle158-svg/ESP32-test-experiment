#include "DataProc.h"
#include "App/Utils/Filters/Filters.h"
#include "../HAL/HAL.h"
#include "App/Config/Config.h"

#define CALORIC_CORFFICIENT 0.5f

using namespace DataProc;

/**
 * @brief Own and retain the sportStatus state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
static HAL::SportStatus_Info_t sportStatus;

/**
 * @brief Execute the SportStatus_GetDistanceOffset operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param gpsInfo Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
static double SportStatus_GetDistanceOffset(HAL::GPS_Info_t* gpsInfo)
{
/**
 * @brief Own and retain the isFirst state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
   static bool isFirst = true;
/**
 * @brief Own and retain the preLongitude state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
   static double preLongitude;
/**
 * @brief Own and retain the preLatitude state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
   static double preLatitude;

/**
 * @brief Own and retain the offset state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    double offset = 0.0f;

   if (!isFirst)
   {
/**
 * @brief Execute the GPS_GetDistanceOffset operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param gpsInfo Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param preLongitude Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param preLatitude Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
       offset = HAL::GPS_GetDistanceOffset(gpsInfo, preLongitude, preLatitude);
   }
   else
   {
       isFirst = false;
   }

   preLongitude = gpsInfo->longitude;
   preLatitude = gpsInfo->latitude;

/**
 * @brief Own and retain the offset state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    return offset;
}

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
   if(account->Pull("GPS", &gpsInfo, sizeof(gpsInfo)) != Account::RES_OK)
   {
       return;
   }

/**
 * @brief Read TickElaps from the current object state.
 * @param lastTick Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
   uint32_t timeElaps = DataProc::GetTickElaps(sportStatus.lastTick);

/**
 * @brief Own and retain the speedKph state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
   float speedKph = 0.0f;
   bool isSignalInterruption = (gpsInfo.isVaild && (gpsInfo.satellites == 0));

   if (gpsInfo.satellites >= 3)
   {
/**
 * @brief Own and retain the spd state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
       float spd = gpsInfo.speed;
       speedKph = spd > 1 ? spd : 0;
   }

   if (speedKph > 0.0f || isSignalInterruption)
   {
       sportStatus.singleTime += timeElaps;
       sportStatus.totalTime += timeElaps;

       if (speedKph > 0.0f)
       {
           float dist = (float)SportStatus_GetDistanceOffset(&gpsInfo);

           sportStatus.singleDistance += dist;
           sportStatus.totalDistance += dist;

/**
 * @brief Own and retain the meterPerSec state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
           float meterPerSec = sportStatus.singleDistance * 1000 / sportStatus.singleTime;
           sportStatus.speedAvgKph = meterPerSec * 3.6f;

           if (speedKph > sportStatus.speedMaxKph)
           {
               sportStatus.speedMaxKph = speedKph;
           }

/**
 * @brief Own and retain the calorie state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
           float calorie = speedKph * sportStatus.weight * CALORIC_CORFFICIENT * timeElaps / 1000 / 3600;
           sportStatus.singleCalorie += calorie;
       }
   }

   sportStatus.speedKph = speedKph;

/**
 * @brief Read Tick from the current object state.
 * @return Operation result or status; inspect it before using dependent state.
 */
   sportStatus.lastTick = DataProc::GetTick();
   account->Commit(&sportStatus, sizeof(sportStatus));
   account->Publish();
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

   if (param->size != sizeof(sportStatus))
   {
       return Account::RES_SIZE_MISMATCH;
   }

   memcpy(param->data_p, &sportStatus, param->size);
    return Account::RES_OK;
}

/**
 * @brief Execute the DATA_PROC_INIT_DEF operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param SportStatus Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
DATA_PROC_INIT_DEF(SportStatus)
{
   memset(&sportStatus, 0, sizeof(sportStatus));
   sportStatus.weight = CONFIG_WEIGHT_DEFAULT;

   account->Subscribe("GPS");
   account->Subscribe("Storage");

/**
 * @brief Execute the STORAGE_VALUE_REG operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param account Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param totalDistance Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param STORAGE_TYPE_FLOAT Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
   STORAGE_VALUE_REG(account, sportStatus.totalDistance, STORAGE_TYPE_FLOAT);
/**
 * @brief Execute the STORAGE_VALUE_REG operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param account Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param totalTimeUINT32 Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param STORAGE_TYPE_INT Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
   STORAGE_VALUE_REG(account, sportStatus.totalTimeUINT32[0], STORAGE_TYPE_INT);
/**
 * @brief Execute the STORAGE_VALUE_REG operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param account Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param totalTimeUINT32 Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param STORAGE_TYPE_INT Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
   STORAGE_VALUE_REG(account, sportStatus.totalTimeUINT32[1], STORAGE_TYPE_INT);
/**
 * @brief Execute the STORAGE_VALUE_REG operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param account Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param speedMaxKph Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param STORAGE_TYPE_FLOAT Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
   STORAGE_VALUE_REG(account, sportStatus.speedMaxKph, STORAGE_TYPE_FLOAT);
/**
 * @brief Execute the STORAGE_VALUE_REG operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param account Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param weight Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param STORAGE_TYPE_FLOAT Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
   STORAGE_VALUE_REG(account, sportStatus.weight, STORAGE_TYPE_FLOAT);

/**
 * @brief Read Tick from the current object state.
 * @return Operation result or status; inspect it before using dependent state.
 */
   sportStatus.lastTick = DataProc::GetTick();

   account->SetEventCallback(onEvent);
   account->SetTimerPeriod(500);
}
