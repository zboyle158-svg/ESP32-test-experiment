#ifndef __LIVEMAP_PRESENTER_H
#define __LIVEMAP_PRESENTER_H

#include "LiveMapView.h"
#include "LiveMapModel.h"

namespace Page
{

class LiveMap : public PageBase
{
public:
/**
 * @brief Construct or destroy the LiveMap object.
 * @return Operation result or status; inspect it before using dependent state.
 */
    LiveMap();
/**
 * @brief Release resources owned by the LiveMap object.
 * @return Operation result or status; inspect it before using dependent state.
 */
    virtual ~LiveMap();

/**
 * @brief Execute the onCustomAttrConfig operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    virtual void onCustomAttrConfig();
/**
 * @brief Handle the onViewLoad page lifecycle callback.
 * @return Operation result or status; inspect it before using dependent state.
 */
    virtual void onViewLoad();
/**
 * @brief Handle the onViewDidLoad page lifecycle callback.
 * @return Operation result or status; inspect it before using dependent state.
 */
    virtual void onViewDidLoad();
/**
 * @brief Handle the onViewWillAppear page lifecycle callback.
 * @return Operation result or status; inspect it before using dependent state.
 */
    virtual void onViewWillAppear();
/**
 * @brief Handle the onViewDidAppear page lifecycle callback.
 * @return Operation result or status; inspect it before using dependent state.
 */
    virtual void onViewDidAppear();
/**
 * @brief Handle the onViewWillDisappear page lifecycle callback.
 * @return Operation result or status; inspect it before using dependent state.
 */
    virtual void onViewWillDisappear();
/**
 * @brief Handle the onViewDidDisappear page lifecycle callback.
 * @return Operation result or status; inspect it before using dependent state.
 */
    virtual void onViewDidDisappear();
/**
 * @brief Handle the onViewUnload page lifecycle callback.
 * @return Operation result or status; inspect it before using dependent state.
 */
    virtual void onViewUnload();
/**
 * @brief Handle the onViewDidUnload page lifecycle callback.
 * @return Operation result or status; inspect it before using dependent state.
 */
    virtual void onViewDidUnload();

private:
/**
 * @brief Own and retain the View state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    LiveMapView View;
/**
 * @brief Own and retain the Model state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    LiveMapModel Model;

    struct
    {
/**
 * @brief Own and retain the lastMapUpdateTime state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        uint32_t lastMapUpdateTime;
/**
 * @brief Own and retain the lastContShowTime state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        uint32_t lastContShowTime;
/**
 * @brief Own and retain the timer state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        lv_timer_t* timer;
/**
 * @brief Own and retain the lastTileContOriPoint state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        TileConv::Point_t lastTileContOriPoint;
/**
 * @brief Own and retain the isTrackAvtive state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        bool isTrackAvtive;
/**
 * @brief Own and retain the priv state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    } priv;

/**
 * @brief Own and retain the mapLevelCurrent state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    static uint16_t mapLevelCurrent;

private:
    typedef  TrackLineFilter::Area_t Area_t;

private:
/**
 * @brief Refresh the LiveMap state without blocking the scheduler.
 * @details The function consumes the latest cached DataProc/HAL snapshot and updates presentation state; it does not own or free the source data.
 */
    void Update();
/**
 * @brief Execute the UpdateDelay operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param ms Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
    void UpdateDelay(uint32_t ms);
/**
 * @brief Execute the CheckPosition operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 */
    void CheckPosition();

    /* SportInfo */
/**
 * @brief Refresh the LiveMap state without blocking the scheduler.
 * @details The function consumes the latest cached DataProc/HAL snapshot and updates presentation state; it does not own or free the source data.
 */
    void SportInfoUpdate();

    /* MapTileCont */
/**
 * @brief Read IsMapTileContChanged from the current object state.
 * @return Operation result or status; inspect it before using dependent state.
 */
    bool GetIsMapTileContChanged();
/**
 * @brief Execute the onMapTileContRefresh operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param area Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param x Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param y Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
    void onMapTileContRefresh(const Area_t* area, int32_t x, int32_t y);
/**
 * @brief Refresh the LiveMap state without blocking the scheduler.
 * @details The function consumes the latest cached DataProc/HAL snapshot and updates presentation state; it does not own or free the source data.
 * @param mapX Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param mapY Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param course Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
    void MapTileContUpdate(int32_t mapX, int32_t mapY, float course);
/**
 * @brief Convert map or coordinate data between the supported representations.
 */
    void MapTileContReload();
    
    /* TrackLine */
/**
 * @brief Execute the TrackLineReload operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param area Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param x Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param y Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
    void TrackLineReload(const Area_t* area, int32_t x, int32_t y);
/**
 * @brief Execute the TrackLineAppend operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param x Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param y Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
    void TrackLineAppend(int32_t x, int32_t y);
/**
 * @brief Execute the TrackLineAppendToEnd operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param x Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param y Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
    void TrackLineAppendToEnd(int32_t x, int32_t y);
/**
 * @brief Execute the onTrackLineEvent operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param filter Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param event Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
    static void onTrackLineEvent(TrackLineFilter* filter, TrackLineFilter::Event_t* event);
    
/**
 * @brief Decode a UI or system event and forward it to the responsible model or view.
 * @details Event callbacks execute on the LVGL/UI context; they must remain short and defer blocking work to the corresponding data-processing task.
 * @param obj Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
    void AttachEvent(lv_obj_t* obj);
/**
 * @brief Decode a UI or system event and forward it to the responsible model or view.
 * @details Event callbacks execute on the LVGL/UI context; they must remain short and defer blocking work to the corresponding data-processing task.
 * @param event Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
    static void onEvent(lv_event_t* event);
};

}

#endif
