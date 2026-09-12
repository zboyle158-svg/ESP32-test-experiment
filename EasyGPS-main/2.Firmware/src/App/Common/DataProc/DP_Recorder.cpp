#include <stdio.h>
#include "DataProc.h"
#include "App/Utils/GPX/GPX.h"
#include "App/Config/Config.h"
#include "App/Version.h"

using namespace DataProc;

#define RECORDER_GPX_TIME_FMT "%d-%02d-%02dT%02d:%02d:%02dZ"
#define RECORDER_GPX_FILE_NAME "/" CONFIG_TRACK_RECORD_FILE_DIR_NAME "/TRK_%d%02d%02d_%02d%02d%02d.gpx"
#define RECORDER_GPX_META_NAME VERSION_FIRMWARE_NAME " " VERSION_SOFTWARE
#define RECORDER_GPX_META_DESC VERSION_PROJECT_LINK

typedef struct
{
/**
 * @brief Own and retain the gpx state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    GPX gpx;
/**
 * @brief Own and retain the recInfo state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    Recorder_Info_t recInfo;
/**
 * @brief Own and retain the file state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    lv_fs_file_t file;
/**
 * @brief Own and retain the active state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    bool active;
    Account *account;
/**
 * @brief Own and retain the Recorder_t state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
} Recorder_t;

/**
 * @brief Execute the Recorder_FileWriteString operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param file_p Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param str Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
static lv_fs_res_t Recorder_FileWriteString(lv_fs_file_t *file_p, const char *str)
{
/**
 * @brief Execute the LV_LOG_USER operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param str Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    LV_LOG_USER(str);

    lv_fs_res_t res = lv_fs_write(
        file_p,
        str,
        (uint32_t)strlen(str),
        nullptr);

/**
 * @brief Own and retain the res state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    return res;
    return 0;
}

static int Recorder_GetTimeConv(
    Recorder_t *recorder,
    const char *format,
    char *buf,
    uint32_t size)
{
/**
 * @brief Own and retain the clock state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    HAL::Clock_Info_t clock;
/**
 * @brief Own and retain the retval state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    int retval = -1;
    if (recorder->account->Pull("Clock", &clock, sizeof(clock)) == Account::RES_OK)
    {
        retval = snprintf(
            buf,
            size,
            format,
            clock.year,
            clock.month,
            clock.day,
            clock.hour,
            clock.minute,
            clock.second);

        printf("[DP] RecorderGetClock: retval = %d!\r\n", retval);
    }

/**
 * @brief Own and retain the retval state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    return retval;
}

/**
 * @brief Execute the Recorder_RecPoint operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param recorder Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param gpsInfo Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
static void Recorder_RecPoint(Recorder_t *recorder, HAL::GPS_Info_t *gpsInfo)
{
/**
 * @brief Execute the LV_LOG_USER operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    LV_LOG_USER("Track recording...");

/**
 * @brief Own and retain the timeBuf state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    char timeBuf[64];
    int ret = Recorder_GetTimeConv(
        recorder,
        RECORDER_GPX_TIME_FMT,
        timeBuf,
        sizeof(timeBuf));

    if (ret < 0)
    {
/**
 * @brief Execute the LV_LOG_WARN operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
        LV_LOG_WARN("cant't get time");
        printf("[DP] RecorderGetClock: cant't get time\r\n");
        return;
    }

    recorder->gpx.setEle(String(gpsInfo->altitude, 2));
    recorder->gpx.setTime(timeBuf);

    String gpxStr = recorder->gpx.getPt(
        GPX_TRKPT,
        String(gpsInfo->longitude, 6),
/**
 * @brief Execute the String operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param latitude Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
        String(gpsInfo->latitude, 6));

/**
 * @brief Execute the Recorder_FileWriteString operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Recorder_FileWriteString(&(recorder->file), gpxStr.c_str());
}

/**
 * @brief Execute the Recorder_RecStart operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param recorder Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param time Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
static void Recorder_RecStart(Recorder_t *recorder, uint16_t time)
{
/**
 * @brief Execute the LV_LOG_USER operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    LV_LOG_USER("Track record start");

/**
 * @brief Own and retain the filepath state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    char filepath[128];
    int ret = Recorder_GetTimeConv(
        recorder,
        RECORDER_GPX_FILE_NAME,
/**
 * @brief Execute the sizeof operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
        filepath, sizeof(filepath));

    if (ret < 0)
    {
/**
 * @brief Execute the LV_LOG_WARN operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
        LV_LOG_WARN("cant't get time");
        printf("[DP] RecorderGetClock: cant't get time\r\n");
        return;
    }

    lv_fs_res_t res = lv_fs_open(&(recorder->file), filepath, LV_FS_MODE_WR | LV_FS_MODE_RD);

    if (res == LV_FS_RES_OK)
    {
/**
 * @brief Execute the LV_LOG_USER operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param filepath Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
        LV_LOG_USER("Track file %s open success", filepath);
        printf("[DP] Recorder: Track file %s open success\r\n", filepath);

        GPX *gpx = &(recorder->gpx);
        lv_fs_file_t *file_p = &(recorder->file);

        gpx->setMetaName(RECORDER_GPX_META_NAME);
        gpx->setMetaDesc(RECORDER_GPX_META_DESC);
        gpx->setName(filepath);
        gpx->setDesc("");

/**
 * @brief Execute the Recorder_FileWriteString operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param file_p Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
        Recorder_FileWriteString(file_p, gpx->getOpen().c_str());
/**
 * @brief Execute the Recorder_FileWriteString operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param file_p Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
        Recorder_FileWriteString(file_p, gpx->getMetaData().c_str());
/**
 * @brief Execute the Recorder_FileWriteString operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param file_p Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
        Recorder_FileWriteString(file_p, gpx->getTrakOpen().c_str());
/**
 * @brief Execute the Recorder_FileWriteString operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param file_p Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
        Recorder_FileWriteString(file_p, gpx->getInfo().c_str());
/**
 * @brief Execute the Recorder_FileWriteString operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param file_p Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
        Recorder_FileWriteString(file_p, gpx->getTrakSegOpen().c_str());

        recorder->active = true;
    }
    else
    {
/**
 * @brief Execute the LV_LOG_ERROR operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
        LV_LOG_ERROR("Track file open error");
        printf("[DP] Recorder: Track file open error: %d!\r\n", res);
        printf("[DP] Track file name: %s\r\n", filepath);
    }
}

/**
 * @brief Execute the Recorder_RecStop operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param recorder Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
static void Recorder_RecStop(Recorder_t *recorder)
{
    recorder->active = false;
    GPX *gpx = &(recorder->gpx);
    lv_fs_file_t *file_p = &(recorder->file);

/**
 * @brief Execute the Recorder_FileWriteString operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param file_p Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Recorder_FileWriteString(file_p, gpx->getTrakSegClose().c_str());
    ;
/**
 * @brief Execute the Recorder_FileWriteString operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param file_p Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Recorder_FileWriteString(file_p, gpx->getTrakClose().c_str());
/**
 * @brief Execute the Recorder_FileWriteString operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param file_p Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Recorder_FileWriteString(file_p, gpx->getClose().c_str());
    lv_fs_close(file_p);

/**
 * @brief Execute the LV_LOG_USER operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    LV_LOG_USER("Track record end");
    printf("[DP] Recorder: Track record end\r\n");
}

/**
 * @brief Execute the onNotify operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param recorder Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param info Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
static int onNotify(Recorder_t *recorder, Recorder_Info_t *info)
{
    switch (info->cmd)
    {
    case RECORDER_CMD_START:
/**
 * @brief Execute the Recorder_RecStart operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param recorder Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param time Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
        Recorder_RecStart(recorder, info->time);
        break;
    case RECORDER_CMD_PAUSE:
        recorder->active = false;
/**
 * @brief Execute the LV_LOG_USER operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
        LV_LOG_USER("Track record pause");
        break;
    case RECORDER_CMD_CONTINUE:
/**
 * @brief Execute the LV_LOG_USER operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
        LV_LOG_USER("Track record continue");
        recorder->active = true;
        break;
    case RECORDER_CMD_STOP:
/**
 * @brief Execute the Recorder_RecStop operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param recorder Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
        Recorder_RecStop(recorder);
        break;
    }

/**
 * @brief Own and retain the tfInfo state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    TrackFilter_Info_t tfInfo;
/**
 * @brief Execute the DATA_PROC_INIT_STRUCT operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param tfInfo Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    DATA_PROC_INIT_STRUCT(tfInfo);
    tfInfo.cmd = (TrackFilter_Cmd_t)info->cmd;

    return recorder->account->Notify("TrackFilter", &tfInfo, sizeof(tfInfo));
    return 0;
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
/**
 * @brief Own and retain the res state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    Account::ResCode_t res = Account::RES_UNKNOW;
    Recorder_t *recorder = (Recorder_t *)account->UserData;
    ;

    switch (param->event)
    {
    case Account::EVENT_PUB_PUBLISH:
        if (param->size == sizeof(HAL::GPS_Info_t))
        {
            if (recorder->active)
            {
/**
 * @brief Execute the Recorder_RecPoint operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param recorder Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param data_p Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
                Recorder_RecPoint(recorder, (HAL::GPS_Info_t *)param->data_p);
            }
            res = Account::RES_OK;
        }
        else
        {
            res = Account::RES_SIZE_MISMATCH;
        }
        break;

    case Account::EVENT_SUB_PULL:
        if (param->size == sizeof(Recorder_Info_t))
        {
            memcpy(param->data_p, &(recorder->recInfo), param->size);
        }
        else
        {
            res = Account::RES_SIZE_MISMATCH;
        }
        break;

    case Account::EVENT_NOTIFY:
        if (param->size == sizeof(Recorder_Info_t))
        {
            onNotify(recorder, (Recorder_Info_t *)param->data_p);
            res = Account::RES_OK;
        }
        else
        {
            res = Account::RES_SIZE_MISMATCH;
        }
        break;

    default:
        break;
    }

/**
 * @brief Own and retain the res state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    return res;
}

/**
 * @brief Execute the DATA_PROC_INIT_DEF operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param Recorder Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
DATA_PROC_INIT_DEF(Recorder)
{
/**
 * @brief Own and retain the recorder state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    static Recorder_t recorder;
    memset(&recorder.recInfo, 0, sizeof(recorder.recInfo));
    memset(&recorder.file, 0, sizeof(recorder.file));
    recorder.active = false;
    recorder.account = account;
    account->UserData = &recorder;

    account->Subscribe("GPS");
    account->Subscribe("Clock");
    account->Subscribe("TrackFilter");
    account->SetEventCallback(onEvent);
}
