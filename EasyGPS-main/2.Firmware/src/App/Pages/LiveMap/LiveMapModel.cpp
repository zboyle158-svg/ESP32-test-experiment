#include "LiveMapModel.h"
#include "App/Config/Config.h"
#include "App/Utils/PointContainer/PointContainer.h"

using namespace Page;

/**
 * @brief Construct or destroy the LiveMapModel object.
 * @return Operation result or status; inspect it before using dependent state.
 */
LiveMapModel::LiveMapModel()
{

}

/**
 * @brief Initialize LiveMapModel state and hardware or data resources.
 */
void LiveMapModel::Init()
{
/**
 * @brief Execute the Account operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param this Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    account = new Account("LiveMapModel", DataProc::Center(), 0, this);
    account->Subscribe("GPS");
    account->Subscribe("SportStatus");
    account->Subscribe("TrackFilter");
    account->Subscribe("SysConfig");
    account->Subscribe("StatusBar");
    account->SetEventCallback(onEvent);
}

/**
 * @brief Release or reset resources managed by LiveMapModel.
 */
void LiveMapModel::Deinit()
{
    if (account)
    {
/**
 * @brief Own and retain the account state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        delete account;
        account = nullptr;
    }
}

/**
 * @brief Read GPS_Info from the current object state.
 * @param info Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void LiveMapModel::GetGPS_Info(HAL::GPS_Info_t* info)
{
    memset(info, 0, sizeof(HAL::GPS_Info_t));
    if(account->Pull("GPS", info, sizeof(HAL::GPS_Info_t)) != Account::RES_OK)
    {
        return;
    }

    /* Use default location */
    if (!info->isVaild)
    {
/**
 * @brief Own and retain the sysConfig state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        DataProc::SysConfig_Info_t sysConfig;
        if(account->Pull("SysConfig", &sysConfig, sizeof(sysConfig)) == Account::RES_OK)
        {
            info->longitude = sysConfig.longitude;
            info->latitude = sysConfig.latitude;
            
            printf("[Model] SysConfigLongitude:%.2f\n", sysConfig.longitude);
            printf("[Model] SysConfiglatitude:%.2f\n", sysConfig.latitude);
        }
    }
}

/**
 * @brief Read ArrowTheme from the current object state.
 * @param buf Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param size Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void LiveMapModel::GetArrowTheme(char* buf, uint32_t size)
{
/**
 * @brief Own and retain the sysConfig state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    DataProc::SysConfig_Info_t sysConfig;
    if(account->Pull("SysConfig", &sysConfig, sizeof(sysConfig)) != Account::RES_OK)
    {
        buf[0] = '\0';
        return;
    }
    strncpy(buf, sysConfig.arrowTheme, size);
    buf[size - 1] = '\0';
}

/**
 * @brief Read TrackFilterActive from the current object state.
 * @return Operation result or status; inspect it before using dependent state.
 */
bool LiveMapModel::GetTrackFilterActive()
{
/**
 * @brief Own and retain the info state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    DataProc::TrackFilter_Info_t info;
    if(account->Pull("TrackFilter", &info, sizeof(info)) != Account::RES_OK)
    {
/**
 * @brief Own and retain the false state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        return false;
    }

    return info.isActive;
}

/**
 * @brief Decode a UI or system event and forward it to the responsible model or view.
 * @details Event callbacks execute on the LVGL/UI context; they must remain short and defer blocking work to the corresponding data-processing task.
 * @param account Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param param Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
int LiveMapModel::onEvent(Account* account, Account::EventParam_t* param)
{
    if (param->event != Account::EVENT_PUB_PUBLISH)
    {
        return Account::RES_UNSUPPORTED_REQUEST;
    }

    if (strcmp(param->tran->ID, "SportStatus") != 0
/**
 * @brief Execute the sizeof operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
            || param->size != sizeof(HAL::SportStatus_Info_t))
    {
        return Account::RES_PARAM_ERROR;
    }

    LiveMapModel* instance = (LiveMapModel*)account->UserData;
    memcpy(&(instance->sportStatusInfo), param->data_p, param->size);

    return Account::RES_OK;
}

/**
 * @brief Execute the TrackReload operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param callback Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param userData Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void LiveMapModel::TrackReload(TrackPointFilter::Callback_t callback, void* userData)
{
/**
 * @brief Own and retain the info state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    DataProc::TrackFilter_Info_t info;
    if(account->Pull("TrackFilter", &info, sizeof(info)) != Account::RES_OK)
    {
        return;
    }

    if (!info.isActive || info.pointCont == nullptr)
    {
        return;
    }

    PointContainer* pointContainer = (PointContainer*)info.pointCont;

    pointContainer->PopStart();
    pointFilter.Reset();

/**
 * @brief Own and retain the ptFilter state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    TrackPointFilter ptFilter;

    ptFilter.SetOffsetThreshold(CONFIG_TRACK_FILTER_OFFSET_THRESHOLD);
    ptFilter.SetOutputPointCallback(callback);
    ptFilter.SetSecondFilterModeEnable(true);
    ptFilter.userData = userData;

/**
 * @brief Own and retain the pointY state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    int32_t pointX, pointY;
    while (pointContainer->PopPoint(&pointX, &pointY))
    {
/**
 * @brief Own and retain the mapY state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        int32_t mapX, mapY;
        mapConv.ConvertMapLevelPos(
            &mapX, &mapY,
            pointX, pointY,
            info.level
        );

        ptFilter.PushPoint(mapX, mapY);
    }
    ptFilter.PushEnd();
}

/**
 * @brief Change the StatusBarStyle configuration of the object.
 * @param style Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void LiveMapModel::SetStatusBarStyle(DataProc::StatusBar_Style_t style)
{
/**
 * @brief Own and retain the info state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    DataProc::StatusBar_Info_t info;
/**
 * @brief Execute the DATA_PROC_INIT_STRUCT operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param info Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    DATA_PROC_INIT_STRUCT(info);

    info.cmd = DataProc::STATUS_BAR_CMD_SET_STYLE;
    info.param.style = style;

    account->Notify("StatusBar", &info, sizeof(info));
}
