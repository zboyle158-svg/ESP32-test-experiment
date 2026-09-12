#include "DataProc.h"
#include "../HAL/HAL.h"
#include "App/Utils/StorageService/StorageService.h"
#include "App/Utils/MapConv/MapConv.h"
#include "App/Config/Config.h"
#include <stdlib.h>

using namespace DataProc;

#define MAP_LEVEL_MIN    0
#define MAP_LEVEL_MAX    19

/**
 * @brief Execute the storageService operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param CONFIG_SYSTEM_SAVE_FILE_PATH Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
static StorageService storageService(CONFIG_SYSTEM_SAVE_FILE_PATH, 4096);

/**
 * @brief Convert map or coordinate data between the supported representations.
 * @param dirName Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param min Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param max Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
static bool MapConvGetRange(const char* dirName, int16_t* min, int16_t* max)
{
/**
 * @brief Own and retain the retval state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    bool retval = false;
/**
 * @brief Own and retain the dir state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
   lv_fs_dir_t dir;

   if (lv_fs_dir_open(&dir, dirName) == LV_FS_RES_OK)
   {
/**
 * @brief Execute the LV_LOG_USER operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param dirName Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
       LV_LOG_USER("%s open success", dirName);

/**
 * @brief Own and retain the levelMin state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
       int16_t levelMin = MAP_LEVEL_MAX;
/**
 * @brief Own and retain the levelMax state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
       int16_t levelMax = MAP_LEVEL_MIN;

/**
 * @brief Own and retain the name state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
       char name[128];
       while (1)
       {
           lv_fs_res_t res = lv_fs_dir_read(&dir, name);

           if (name[0] == '\0' || res != LV_FS_RES_OK)
           {
               break;
           }

           if (name[0] == '/')
           {
               retval = true;
/**
 * @brief Execute the atoi operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
               int level = atoi(name + 1);

               if (level < MAP_LEVEL_MIN || level > MAP_LEVEL_MAX)
               {
/**
 * @brief Execute the LV_LOG_ERROR operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param level Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param level Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
                   LV_LOG_ERROR("Error level = %d", level);
                   retval = false;
                   break;
               }

               if (level < levelMin)
               {
                   levelMin = level;
               }

               if (level > levelMax)
               {
                   levelMax = level;
               }
           }
       }

       if (retval)
       {
           *min = levelMin;
           *max = levelMax;
       }

       lv_fs_dir_close(&dir);
   }
   else
   {
/**
 * @brief Execute the LV_LOG_ERROR operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param dirName Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
       LV_LOG_ERROR("%s open faild", dirName);
   }
/**
 * @brief Own and retain the retval state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    return retval;
}

/**
 * @brief Execute the onLoad operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param account Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
static bool onLoad(Account* account)
{
/**
 * @brief Execute the storageService.LoadFile operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
   bool success = storageService.LoadFile();

   if (!success)
   {
/**
 * @brief Execute the LV_LOG_WARN operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
       LV_LOG_WARN("Load " CONFIG_SYSTEM_SAVE_FILE_PATH " error");
   }

/**
 * @brief Own and retain the sysConfig state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
   SysConfig_Info_t sysConfig;
   if (account->Pull("SysConfig", &sysConfig, sizeof(sysConfig)) != Account::RES_OK)
   {
/**
 * @brief Execute the LV_LOG_ERROR operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
       LV_LOG_ERROR("Pull SysConfig failed!");
/**
 * @brief Own and retain the false state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
       return false;
   }

/**
 * @brief Change the DirPath configuration of the object.
 * @param mapDirPath Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
   MapConv::SetDirPath(sysConfig.mapDirPath);
/**
 * @brief Change the ExtName configuration of the object.
 * @param mapExtName Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
   MapConv::SetExtName(sysConfig.mapExtName);
/**
 * @brief Change the CoordTransformEnable configuration of the object.
 * @param mapWGS84 Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
   MapConv::SetCoordTransformEnable(!sysConfig.mapWGS84);

/**
 * @brief Own and retain the levelMax state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
   int16_t levelMin, levelMax;
   if (MapConvGetRange(sysConfig.mapDirPath, &levelMin, &levelMax))
   {
/**
 * @brief Change the LevelRange configuration of the object.
 * @param levelMin Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param levelMax Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
       MapConv::SetLevelRange(levelMin, levelMax);
   }
   else
   {
/**
 * @brief Execute the LV_LOG_ERROR operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
       LV_LOG_ERROR("Get map level range failed!");
   }

   LV_LOG_USER(
       "Map path: %s, WGS84: %d, level min = %d, max = %d",
       sysConfig.mapDirPath,
       sysConfig.mapWGS84,
       MapConv::GetLevelMin(),
/**
 * @brief Read LevelMax from the current object state.
 * @return Operation result or status; inspect it before using dependent state.
 */
       MapConv::GetLevelMax()
   );
/**
 * @brief Execute the LV_LOG_USER operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param mapExtName Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
   LV_LOG_USER("Map ext name: *.%s", sysConfig.mapExtName);
#if CONFIG_MAP_PNG_DECODE_ENABLE
/**
 * @brief Execute the LV_LOG_USER operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
   LV_LOG_USER("Map PNG decoder enable");
#endif

/**
 * @brief Own and retain the success state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
   return success;
		return 0;
}

/**
 * @brief Execute the onNotify operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param account Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param info Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
static void onNotify(Account* account, Storage_Info_t* info)
{
/**
 * @brief Own and retain the isLoadSuccess state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
   static bool isLoadSuccess = false;

   switch (info->cmd)
   {
   case STORAGE_CMD_LOAD:
/**
 * @brief Execute the onLoad operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param account Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
       isLoadSuccess = onLoad(account);
       break;
   case STORAGE_CMD_SAVE:
       storageService.SaveFile();
       if (isLoadSuccess)
       {
/**
 * @brief Execute the LV_LOG_USER operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param CONFIG_SYSTEM_SAVE_FILE_BACKUP_PATH Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
           LV_LOG_USER("Saving backup file: " CONFIG_SYSTEM_SAVE_FILE_BACKUP_PATH);
           storageService.SaveFile(CONFIG_SYSTEM_SAVE_FILE_BACKUP_PATH);
       }
       break;
   case STORAGE_CMD_ADD:
       storageService.Add(
           info->key,
           info->value,
           info->size,
           (StorageService::DataType_t)info->type
       );
       break;
   case STORAGE_CMD_REMOVE:
       storageService.Remove(info->key);
       break;
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
static int onEvent(Account* account, Account::EventParam_t* param)
{
   if (param->event == Account::EVENT_SUB_PULL)
   {
       if (param->size != sizeof(Storage_Basic_Info_t))
       {
           return Account::RES_SIZE_MISMATCH;
       }

       Storage_Basic_Info_t* info = (Storage_Basic_Info_t*)param->data_p;
/**
 * @brief Execute the SD_GetReady operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
       info->isDetect = HAL::SD_GetReady();
/**
 * @brief Execute the SD_GetCardSizeMB operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
       info->totalSizeMB = HAL::SD_GetCardSizeMB();
       info->freeSizeMB = 0.0f;
/**
 * @brief Execute the SD_GetTypeName operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
       info->type = HAL::SD_GetTypeName();
       return Account::RES_OK;
   }

   if (param->event != Account::EVENT_NOTIFY)
   {
       return Account::RES_UNSUPPORTED_REQUEST;
   }

   if (param->size != sizeof(Storage_Info_t))
   {
       return Account::RES_SIZE_MISMATCH;
   }

   Storage_Info_t* info = (Storage_Info_t*)param->data_p;
   onNotify(account, info);

    return Account::RES_OK;
}


/**
 * @brief Execute the onSDEvent operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param insert Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
static void onSDEvent(bool insert)
{
   if(insert)
   {
/**
 * @brief Own and retain the info state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
       DataProc::Storage_Info_t info;
/**
 * @brief Execute the DATA_PROC_INIT_STRUCT operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param info Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
       DATA_PROC_INIT_STRUCT(info);
       info.cmd = DataProc::STORAGE_CMD_LOAD;
/**
 * @brief Execute the Center operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param info Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
       DataProc::Center()->AccountMain.Notify("Storage", &info, sizeof(info));
   }
}

/**
 * @brief Execute the DATA_PROC_INIT_DEF operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param Storage Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
DATA_PROC_INIT_DEF(Storage)
{
   account->SetEventCallback(onEvent);
   account->Subscribe("SysConfig");
/**
 * @brief Execute the SD_SetEventCallback operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param onSDEvent Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
   HAL::SD_SetEventCallback(onSDEvent);
}
