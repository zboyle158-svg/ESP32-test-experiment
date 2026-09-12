#include "DataProc.h"
#include "../HAL/HAL.h"
#include "App/Config/Config.h"

using namespace DataProc;

/**
 * @brief Own and retain the sysConfig state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
static SysConfig_Info_t sysConfig;

/**
 * @brief Decode a UI or system event and forward it to the responsible model or view.
 * @details Event callbacks execute on the LVGL/UI context; they must remain short and defer blocking work to the corresponding data-processing task.
 * @param account Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param param Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
static int onEvent(Account* account, Account::EventParam_t* param)
{
   if (param->size != sizeof(SysConfig_Info_t))
   {
       return Account::RES_SIZE_MISMATCH;
   }

   SysConfig_Info_t* info = (SysConfig_Info_t*)param->data_p;

   switch (param->event)
   {
   case Account::EVENT_NOTIFY:
   {
       if (info->cmd == SYSCONFIG_CMD_LOAD)
       {
/**
 * @brief Execute the Buzz_SetEnable operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param soundEnable Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
           HAL::Buzz_SetEnable(sysConfig.soundEnable);
       }
       else if (info->cmd == SYSCONFIG_CMD_SAVE)
       {
/**
 * @brief Own and retain the gpsInfo state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
           HAL::GPS_Info_t gpsInfo;
           if(account->Pull("GPS", &gpsInfo, sizeof(gpsInfo)) != Account::RES_OK)
           {
               return Account::RES_UNKNOW;
           }

           if(gpsInfo.isVaild)
           {
               sysConfig.longitude = (float)gpsInfo.longitude;
               sysConfig.latitude = (float)gpsInfo.latitude;
           }
       }
   }
   break;
   case Account::EVENT_SUB_PULL:
   {
       memcpy(info, &sysConfig, sizeof(sysConfig));
   }
   break;
   default:
       return Account::RES_UNSUPPORTED_REQUEST;
   }

    return Account::RES_OK;
}

/**
 * @brief Execute the DATA_PROC_INIT_DEF operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param SysConfig Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
DATA_PROC_INIT_DEF(SysConfig)
{
   account->Subscribe("Storage");
   account->Subscribe("GPS");
   account->SetEventCallback(onEvent);

   memset(&sysConfig, 0, sizeof(sysConfig));

#   define SYSCGF_STRCPY(dest, src) \
do{ \
   strncpy(dest, src, sizeof(dest)); \
   dest[sizeof(dest) - 1] = '\0'; \
}while(0)

   sysConfig.cmd         = SYSCONFIG_CMD_LOAD;
   sysConfig.longitude   = CONFIG_GPS_LONGITUDE_DEFAULT;
   sysConfig.latitude    = CONFIG_GPS_LATITUDE_DEFAULT;
   sysConfig.timeZone    = CONFIG_SYSTEM_TIME_ZONE_DEFAULT;
   sysConfig.soundEnable = CONFIG_SYSTEM_SOUND_ENABLE_DEFAULT;
/**
 * @brief Execute the SYSCGF_STRCPY operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param language Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param CONFIG_SYSTEM_LANGUAGE_DEFAULT Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
   SYSCGF_STRCPY(sysConfig.language, CONFIG_SYSTEM_LANGUAGE_DEFAULT);
/**
 * @brief Execute the SYSCGF_STRCPY operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param arrowTheme Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param CONFIG_ARROW_THEME_DEFAULT Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
   SYSCGF_STRCPY(sysConfig.arrowTheme, CONFIG_ARROW_THEME_DEFAULT);
/**
 * @brief Execute the SYSCGF_STRCPY operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param mapDirPath Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param CONFIG_MAP_DIR_PATH_DEFAULT Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
   SYSCGF_STRCPY(sysConfig.mapDirPath, CONFIG_MAP_DIR_PATH_DEFAULT);
/**
 * @brief Execute the SYSCGF_STRCPY operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param mapExtName Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param CONFIG_MAP_EXT_NAME_DEFAULT Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
   SYSCGF_STRCPY(sysConfig.mapExtName, CONFIG_MAP_EXT_NAME_DEFAULT);
   sysConfig.mapWGS84    = CONFIG_MAP_USE_WGS84_DEFAULT;

/**
 * @brief Execute the STORAGE_VALUE_REG operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param account Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param longitude Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param STORAGE_TYPE_FLOAT Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
   STORAGE_VALUE_REG(account, sysConfig.longitude, STORAGE_TYPE_FLOAT);
/**
 * @brief Execute the STORAGE_VALUE_REG operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param account Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param latitude Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param STORAGE_TYPE_FLOAT Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
   STORAGE_VALUE_REG(account, sysConfig.latitude, STORAGE_TYPE_FLOAT);

/**
 * @brief Execute the STORAGE_VALUE_REG operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param account Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param soundEnable Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param STORAGE_TYPE_INT Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
   STORAGE_VALUE_REG(account, sysConfig.soundEnable, STORAGE_TYPE_INT);
/**
 * @brief Execute the STORAGE_VALUE_REG operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param account Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param timeZone Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param STORAGE_TYPE_INT Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
   STORAGE_VALUE_REG(account, sysConfig.timeZone, STORAGE_TYPE_INT);
/**
 * @brief Execute the STORAGE_VALUE_REG operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param account Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param language Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param STORAGE_TYPE_STRING Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
   STORAGE_VALUE_REG(account, sysConfig.language, STORAGE_TYPE_STRING);
/**
 * @brief Execute the STORAGE_VALUE_REG operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param account Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param arrowTheme Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param STORAGE_TYPE_STRING Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
   STORAGE_VALUE_REG(account, sysConfig.arrowTheme, STORAGE_TYPE_STRING);
/**
 * @brief Execute the STORAGE_VALUE_REG operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param account Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param mapDirPath Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param STORAGE_TYPE_STRING Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
   STORAGE_VALUE_REG(account, sysConfig.mapDirPath, STORAGE_TYPE_STRING);
/**
 * @brief Execute the STORAGE_VALUE_REG operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param account Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param mapExtName Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param STORAGE_TYPE_STRING Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
   STORAGE_VALUE_REG(account, sysConfig.mapExtName, STORAGE_TYPE_STRING);
/**
 * @brief Execute the STORAGE_VALUE_REG operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param account Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param mapWGS84 Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param STORAGE_TYPE_INT Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
   STORAGE_VALUE_REG(account, sysConfig.mapWGS84, STORAGE_TYPE_INT);
}
