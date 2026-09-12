#include "HAL.h"
#include "App/Config/Config.h"
#include "ChappieCore/ChappieCore.h"

/**
 * @brief Own and retain the Chappie state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
extern ChappieCore Chappie;

/**
 * @brief Own and retain the SD_IsReady state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
static bool SD_IsReady = false;
/**
 * @brief Own and retain the SD_CardSize state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
static uint32_t SD_CardSize = 0;

/**
 * @brief Own and retain the SD_EventCallback state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
static HAL::SD_CallbackFunction_t SD_EventCallback = nullptr;

/*
 * User provided date time callback function.
 * See SdFile::dateTimeCallback() for usage.
 */
static void SD_GetDateTime(uint16_t *date, uint16_t *time)
{
    // User gets date and time from GPS or real-time
    // clock in real callback function
/**
 * @brief Own and retain the clock state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    HAL::Clock_Info_t clock;
/**
 * @brief Execute the Clock_GetInfo operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param clock Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    HAL::Clock_GetInfo(&clock);

    // return date using FAT_DATE macro to format fields
    // *date = FAT_DATE(clock.year, clock.month, clock.day);

    // return time using FAT_TIME macro to format fields
    // *time = FAT_TIME(clock.hour, clock.minute, clock.second);
}

static bool SD_CheckDir(const char *path)
{
/**
 * @brief Own and retain the retval state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    bool retval = true;
    if (!SD.exists(path))
    {
        printf("SD: Auto create path \"%s\"...", path);
        retval = SD.mkdir(path);
        printf(retval ? "success" : "failed");
    }
/**
 * @brief Own and retain the retval state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    return retval;
}

/**
 * @brief Execute the SD_Init operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
bool HAL::SD_Init()
{
    // ...
/**
 * @brief Own and retain the retval state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    bool retval = true;

/**
 * @brief Execute the Chappie.Sd.init operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    retval = Chappie.Sd.init();
    
/**
 * @brief Own and retain the retval state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    return retval;
}

/**
 * @brief Execute the SD_GetReady operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
bool HAL::SD_GetReady()
{
/**
 * @brief Execute the Chappie.Sd.isInited operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    SD_IsReady = Chappie.Sd.isInited();

/**
 * @brief Own and retain the SD_IsReady state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    return SD_IsReady;
}

/**
 * @brief Execute the SD_GetCardSizeMB operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
float HAL::SD_GetCardSizeMB()
{
#define CONV_MB(size) (size / 1048576.0f)
    return CONV_MB(SD.cardSize());
}

/**
 * @brief Execute the SD_GetTypeName operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
const char *HAL::SD_GetTypeName()
{
    const char *type = "Unknown";

    SD_CardSize = SD.cardSize();

    if (!SD_CardSize)
    {
/**
 * @brief Own and retain the failed state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        goto failed;
    }

    switch (SD.cardType())
    {
    case CARD_MMC:
        type = "SD1";
        break;

    case CARD_SD:
        type = "SD2";
        break;

    case CARD_SDHC:
        type = (SD_CardSize < 70000000) ? "SDHC" : "SDXC";
        break;

    default:
        break;
    }

failed:
/**
 * @brief Own and retain the type state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    return type;
}

static void SD_Check(bool isInsert)
{
    if (isInsert)
    {
/**
 * @brief Execute the SD_Init operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
        bool ret = HAL::SD_Init();

        if (ret && SD_EventCallback)
        {
            SD_EventCallback(true);
        }

/**
 * @brief Execute the Audio_PlayMusic operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
        HAL::Audio_PlayMusic(ret ? "DeviceInsert" : "Error");
    }
    else
    {
        SD_IsReady = false;

        if (SD_EventCallback)
        {
            SD_EventCallback(false);
            SD_CardSize = 0;
        }

/**
 * @brief Execute the Audio_PlayMusic operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
        HAL::Audio_PlayMusic("DevicePullout");
    }
}

/**
 * @brief Execute the SD_SetEventCallback operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param callback Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void HAL::SD_SetEventCallback(SD_CallbackFunction_t callback)
{
    SD_EventCallback = callback;
}

/**
 * @brief Refresh the HAL_SD state without blocking the scheduler.
 * @details The function consumes the latest cached DataProc/HAL snapshot and updates presentation state; it does not own or free the source data.
 */
void HAL::SD_Update()
{
    // bool isInsert = (digitalRead(CONFIG_SD_CD_PIN) == LOW);
/**
 * @brief Own and retain the isInsert state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    bool isInsert = 0;
    __ValueMonitor(isInsert, SD_Check(isInsert));
}
