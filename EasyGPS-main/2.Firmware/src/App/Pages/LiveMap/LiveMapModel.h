#ifndef __LIVEMAP_MODEL_H
#define __LIVEMAP_MODEL_H

#include "lvgl.h"
#include "App/Utils/MapConv/MapConv.h"
#include "App/Utils/TileConv/TileConv.h"
#include "App/Utils/TrackFilter/TrackFilter.h"
#include "App/Common/DataProc/DataProc.h"
#include <vector>

namespace Page
{

class LiveMapModel
{
public:
/**
 * @brief Construct or destroy the LiveMapModel object.
 * @return Operation result or status; inspect it before using dependent state.
 */
    LiveMapModel();
    ~LiveMapModel() {}
/**
 * @brief Initialize LiveMapModel state and hardware or data resources.
 */
    void Init();
/**
 * @brief Release or reset resources managed by LiveMapModel.
 */
    void Deinit();
/**
 * @brief Read GPS_Info from the current object state.
 * @param info Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
    void GetGPS_Info(HAL::GPS_Info_t* info);
/**
 * @brief Read ArrowTheme from the current object state.
 * @param buf Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param size Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
    void GetArrowTheme(char* buf, uint32_t size);
/**
 * @brief Read TrackFilterActive from the current object state.
 * @return Operation result or status; inspect it before using dependent state.
 */
    bool GetTrackFilterActive();
/**
 * @brief Execute the TrackReload operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param callback Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param userData Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
    void TrackReload(TrackPointFilter::Callback_t callback, void* userData);
/**
 * @brief Change the StatusBarStyle configuration of the object.
 * @param style Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
    void SetStatusBarStyle(DataProc::StatusBar_Style_t style);

public:
/**
 * @brief Own and retain the mapConv state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    MapConv mapConv;
/**
 * @brief Own and retain the tileConv state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    TileConv tileConv;
/**
 * @brief Own and retain the pointFilter state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    TrackPointFilter pointFilter;
/**
 * @brief Own and retain the lineFilter state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    TrackLineFilter lineFilter;
/**
 * @brief Own and retain the sportStatusInfo state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    HAL::SportStatus_Info_t sportStatusInfo;

private:
/**
 * @brief Own and retain the account state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    Account* account;

private:
/**
 * @brief Decode a UI or system event and forward it to the responsible model or view.
 * @details Event callbacks execute on the LVGL/UI context; they must remain short and defer blocking work to the corresponding data-processing task.
 * @param account Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param param Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    static int onEvent(Account* account, Account::EventParam_t* param);

private:
};

}

#endif
