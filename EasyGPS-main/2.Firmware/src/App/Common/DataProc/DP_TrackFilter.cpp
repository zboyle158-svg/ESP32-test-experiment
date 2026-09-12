#include "DataProc.h"
#include "App/Utils/MapConv/MapConv.h"
#include "App/Utils/TrackFilter/TrackFilter.h"
#include "App/Utils/PointContainer/PointContainer.h"
#include "App/Config/Config.h"

#include <vector>

using namespace DataProc;

typedef struct
{
/**
 * @brief Own and retain the mapConv state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
   MapConv mapConv;
/**
 * @brief Own and retain the pointFilter state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
   TrackPointFilter pointFilter;
/**
 * @brief Own and retain the pointContainer state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
   PointContainer* pointContainer;
/**
 * @brief Own and retain the isStarted state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
   bool isStarted;
/**
 * @brief Own and retain the isActive state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
   bool isActive;
/**
 * @brief Own and retain the TrackFilter_t state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
} TrackFilter_t;

/**
 * @brief Own and retain the trackFilter state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
static TrackFilter_t trackFilter;

/**
 * @brief Execute the onNotify operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param account Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param info Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
static void onNotify(Account* account, TrackFilter_Info_t* info)
{
   switch (info->cmd)
   {
   case TRACK_FILTER_CMD_START:
       trackFilter.pointContainer = new PointContainer;
       trackFilter.pointFilter.Reset();
       trackFilter.isActive = true;
       trackFilter.isStarted = true;
/**
 * @brief Execute the LV_LOG_USER operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
       LV_LOG_USER("Track filter start");
       break;
   case TRACK_FILTER_CMD_PAUSE:
       trackFilter.isActive = false;
/**
 * @brief Execute the LV_LOG_USER operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
       LV_LOG_USER("Track filter pause");
       break;
   case TRACK_FILTER_CMD_CONTINUE:
       trackFilter.isActive = true;
/**
 * @brief Execute the LV_LOG_USER operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
       LV_LOG_USER("Track filter continue");
       break;
   case TRACK_FILTER_CMD_STOP:
   {
       trackFilter.isStarted = false;
       trackFilter.isActive = false;

       if (trackFilter.pointContainer)
       {
           delete trackFilter.pointContainer;
           trackFilter.pointContainer = nullptr;
       }

/**
 * @brief Own and retain the sum state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
       uint32_t sum = 0, output = 0;
       trackFilter.pointFilter.GetCounts(&sum, &output);
       LV_LOG_USER(
           "Track filter stop, filted(%d%%): sum = %d, output = %d",
           sum ? (100 - output * 100 / sum) : 0,
           sum,
           output
       );
       break;
   }
   default:
       break;
   }
}

/**
 * @brief Execute the onPublish operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param account Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param gps Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
static void onPublish(Account* account, HAL::GPS_Info_t* gps)
{
/**
 * @brief Own and retain the mapY state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
   int32_t mapX, mapY;
   trackFilter.mapConv.ConvertMapCoordinate(
       gps->longitude,
       gps->latitude,
       &mapX,
       &mapY
   );

   if (trackFilter.pointFilter.PushPoint(mapX, mapY))
   {
       trackFilter.pointContainer->PushPoint(mapX, mapY);
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
   if (param->event == Account::EVENT_PUB_PUBLISH
/**
 * @brief Execute the sizeof operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
           && param->size == sizeof(HAL::GPS_Info_t))
   {
       if (trackFilter.isActive)
       {
           onPublish(account, (HAL::GPS_Info_t*)param->data_p);
       }

       return Account::RES_OK;
   }

   if (param->size != sizeof(TrackFilter_Info_t))
   {
       return Account::RES_SIZE_MISMATCH;
   }

   switch (param->event)
   {
   case Account::EVENT_SUB_PULL:
   {
       TrackFilter_Info_t* info = (TrackFilter_Info_t*)param->data_p;
       info->pointCont = trackFilter.pointContainer;
       info->level = (uint8_t)trackFilter.mapConv.GetLevel();
       info->isActive = trackFilter.isStarted;
       break;
   }
   case Account::EVENT_NOTIFY:
       onNotify(account, (TrackFilter_Info_t*)param->data_p);
       break;

   default:
       break;
   }

    return Account::RES_OK;
}

/**
 * @brief Execute the DATA_PROC_INIT_DEF operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param TrackFilter Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
DATA_PROC_INIT_DEF(TrackFilter)
{
   account->Subscribe("GPS");
   account->SetEventCallback(onEvent);

   trackFilter.pointContainer = nullptr;
   trackFilter.isActive = false;
   trackFilter.isStarted = false;

   trackFilter.mapConv.SetLevel(CONFIG_LIVE_MAP_LEVEL_DEFAULT);

   trackFilter.pointFilter.SetOffsetThreshold(CONFIG_TRACK_FILTER_OFFSET_THRESHOLD);
}
