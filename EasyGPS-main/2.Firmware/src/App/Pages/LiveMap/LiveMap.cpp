#include "LiveMap.h"
#include "App/Config/Config.h"

using namespace Page;

uint16_t LiveMap::mapLevelCurrent = CONFIG_LIVE_MAP_LEVEL_DEFAULT;

/**
 * @brief Construct or destroy the LiveMap object.
 * @return Operation result or status; inspect it before using dependent state.
 */
LiveMap::LiveMap()
{
    memset(&priv, 0, sizeof(priv));
}

/**
 * @brief Release resources owned by the LiveMap object.
 * @return Operation result or status; inspect it before using dependent state.
 */
LiveMap::~LiveMap()
{
}

/**
 * @brief Execute the onCustomAttrConfig operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 */
void LiveMap::onCustomAttrConfig()
{
/**
 * @brief Change the CustomCacheEnable configuration of the object.
 * @param false Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    SetCustomCacheEnable(false);
}

/**
 * @brief Handle the onViewLoad page lifecycle callback.
 */
void LiveMap::onViewLoad()
{
/**
 * @brief Own and retain the tileSize state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    const uint32_t tileSize = 256;

/**
 * @brief Execute the Model.tileConv.SetTileSize operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param tileSize Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Model.tileConv.SetTileSize(tileSize);
    Model.tileConv.SetViewSize(
        CONFIG_LIVE_MAP_VIEW_WIDTH,
        CONFIG_LIVE_MAP_VIEW_HEIGHT);
/**
 * @brief Execute the Model.tileConv.SetFocusPos operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Model.tileConv.SetFocusPos(0, 0);

/**
 * @brief Own and retain the rect state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    TileConv::Rect_t rect;
/**
 * @brief Execute the Model.tileConv.GetTileContainer operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param rect Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    uint32_t tileNum = Model.tileConv.GetTileContainer(&rect);

/**
 * @brief Execute the View.Create operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param _root Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param tileNum Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    View.Create(_root, tileNum);
    lv_slider_set_range(
        View.ui.zoom.slider,
        Model.mapConv.GetLevelMin(),
/**
 * @brief Execute the Model.mapConv.GetLevelMax operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
        Model.mapConv.GetLevelMax());
/**
 * @brief Execute the View.SetMapTile operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param tileSize Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param tileSize Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    View.SetMapTile(tileSize, rect.width / tileSize);

#if CONFIG_LIVE_MAP_DEBUG_ENABLE
    lv_obj_t *contView = lv_obj_create(root);
    lv_obj_center(contView);
    lv_obj_set_size(contView, CONFIG_LIVE_MAP_VIEW_WIDTH, CONFIG_LIVE_MAP_VIEW_HEIGHT);
    lv_obj_set_style_border_color(contView, lv_palette_main(LV_PALETTE_RED), 0);
    lv_obj_set_style_border_width(contView, 1, 0);
#endif

/**
 * @brief Decode a UI or system event and forward it to the responsible model or view.
 * @details Event callbacks execute on the LVGL/UI context; they must remain short and defer blocking work to the corresponding data-processing task.
 * @return Operation result or status; inspect it before using dependent state.
 */
    AttachEvent(lv_scr_act());
/**
 * @brief Decode a UI or system event and forward it to the responsible model or view.
 * @details Event callbacks execute on the LVGL/UI context; they must remain short and defer blocking work to the corresponding data-processing task.
 * @param _root Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    AttachEvent(_root);
/**
 * @brief Decode a UI or system event and forward it to the responsible model or view.
 * @details Event callbacks execute on the LVGL/UI context; they must remain short and defer blocking work to the corresponding data-processing task.
 * @param slider Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    AttachEvent(View.ui.zoom.slider);
/**
 * @brief Decode a UI or system event and forward it to the responsible model or view.
 * @details Event callbacks execute on the LVGL/UI context; they must remain short and defer blocking work to the corresponding data-processing task.
 * @param cont Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    AttachEvent(View.ui.sportInfo.cont);

    lv_slider_set_value(View.ui.zoom.slider, mapLevelCurrent, LV_ANIM_OFF);
/**
 * @brief Execute the Model.mapConv.SetLevel operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param mapLevelCurrent Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Model.mapConv.SetLevel(mapLevelCurrent);
    lv_obj_add_flag(View.ui.map.cont, LV_OBJ_FLAG_HIDDEN);

    /* Point filter */
/**
 * @brief Execute the Model.pointFilter.SetOffsetThreshold operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param CONFIG_TRACK_FILTER_OFFSET_THRESHOLD Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Model.pointFilter.SetOffsetThreshold(CONFIG_TRACK_FILTER_OFFSET_THRESHOLD);
/**
 * @brief Execute the Model.pointFilter.SetOutputPointCallback operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param filter Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param point Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Model.pointFilter.SetOutputPointCallback([](TrackPointFilter *filter, const TrackPointFilter::Point_t *point)
                                             {
        LiveMap* instance = (LiveMap*)filter->userData;
        instance->TrackLineAppendToEnd((int32_t)point->x, (int32_t)point->y); });
    Model.pointFilter.userData = this;

    /* Line filter */
/**
 * @brief Execute the Model.lineFilter.SetOutputPointCallback operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param onTrackLineEvent Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Model.lineFilter.SetOutputPointCallback(onTrackLineEvent);
    Model.lineFilter.userData = this;

}

/**
 * @brief Handle the onViewDidLoad page lifecycle callback.
 */
void LiveMap::onViewDidLoad()
{
}

/**
 * @brief Handle the onViewWillAppear page lifecycle callback.
 */
void LiveMap::onViewWillAppear()
{
    lv_obj_set_style_opa(_root, LV_OPA_COVER, LV_PART_MAIN);
/**
 * @brief Execute the Model.Init operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Model.Init();

/**
 * @brief Own and retain the theme state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    char theme[16];
/**
 * @brief Execute the Model.GetArrowTheme operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param theme Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Model.GetArrowTheme(theme, sizeof(theme));
/**
 * @brief Execute the View.SetArrowTheme operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param theme Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    View.SetArrowTheme(theme);

/**
 * @brief Execute the Model.GetTrackFilterActive operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    priv.isTrackAvtive = Model.GetTrackFilterActive();

/**
 * @brief Execute the Model.SetStatusBarStyle operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param STATUS_BAR_STYLE_BLACK Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Model.SetStatusBarStyle(DataProc::STATUS_BAR_STYLE_BLACK);
/**
 * @brief Refresh the LiveMap state without blocking the scheduler.
 * @details The function consumes the latest cached DataProc/HAL snapshot and updates presentation state; it does not own or free the source data.
 * @return Operation result or status; inspect it before using dependent state.
 */
    SportInfoUpdate();
    lv_obj_clear_flag(View.ui.labelInfo, LV_OBJ_FLAG_HIDDEN);
}

/**
 * @brief Handle the onViewDidAppear page lifecycle callback.
 */
void LiveMap::onViewDidAppear()
{
    priv.timer = lv_timer_create([](lv_timer_t *timer)
                                 {
        LiveMap* instance = (LiveMap*)timer->user_data;
        instance->Update(); },
                                 100,
                                 this);
    priv.lastMapUpdateTime = 0;
    lv_obj_clear_flag(View.ui.map.cont, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(View.ui.labelInfo, LV_OBJ_FLAG_HIDDEN);

    priv.lastTileContOriPoint.x = 0;
    priv.lastTileContOriPoint.y = 0;

/**
 * @brief Execute the Model.GetTrackFilterActive operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    priv.isTrackAvtive = Model.GetTrackFilterActive();
    if (!priv.isTrackAvtive)
    {
/**
 * @brief Execute the Model.pointFilter.SetOutputPointCallback operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param nullptr Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
        Model.pointFilter.SetOutputPointCallback(nullptr);
    }

    lv_group_t *group = lv_group_get_default();
    lv_group_add_obj(group, View.ui.zoom.slider);
    lv_group_set_editing(group, View.ui.zoom.slider);
}

/**
 * @brief Handle the onViewWillDisappear page lifecycle callback.
 */
void LiveMap::onViewWillDisappear()
{
    lv_timer_del(priv.timer);
    lv_obj_add_flag(View.ui.map.cont, LV_OBJ_FLAG_HIDDEN);
    lv_obj_fade_out(_root, 250, 250);
}

/**
 * @brief Handle the onViewDidDisappear page lifecycle callback.
 */
void LiveMap::onViewDidDisappear()
{
/**
 * @brief Execute the Model.Deinit operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Model.Deinit();
}

/**
 * @brief Handle the onViewUnload page lifecycle callback.
 */
void LiveMap::onViewUnload()
{
/**
 * @brief Execute the View.Delete operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    View.Delete();

    lv_obj_remove_event_cb(lv_scr_act(), onEvent); // 移除屏幕手势回调函数
}

/**
 * @brief Handle the onViewDidUnload page lifecycle callback.
 */
void LiveMap::onViewDidUnload()
{
}

/**
 * @brief Decode a UI or system event and forward it to the responsible model or view.
 * @details Event callbacks execute on the LVGL/UI context; they must remain short and defer blocking work to the corresponding data-processing task.
 * @param obj Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void LiveMap::AttachEvent(lv_obj_t *obj)
{
    lv_obj_add_event_cb(obj, onEvent, LV_EVENT_ALL, this);
}

/**
 * @brief Refresh the LiveMap state without blocking the scheduler.
 * @details The function consumes the latest cached DataProc/HAL snapshot and updates presentation state; it does not own or free the source data.
 */
void LiveMap::Update()
{
    if (lv_tick_elaps(priv.lastMapUpdateTime) >= CONFIG_GPS_REFR_PERIOD)
    {
/**
 * @brief Execute the CheckPosition operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
        CheckPosition();
/**
 * @brief Refresh the LiveMap state without blocking the scheduler.
 * @details The function consumes the latest cached DataProc/HAL snapshot and updates presentation state; it does not own or free the source data.
 * @return Operation result or status; inspect it before using dependent state.
 */
        SportInfoUpdate();
        priv.lastMapUpdateTime = lv_tick_get();
    }
    else if (lv_tick_elaps(priv.lastContShowTime) >= 3000)
    {
        lv_obj_add_state(View.ui.zoom.cont, LV_STATE_USER_1);
    }
}

/**
 * @brief Execute the UpdateDelay operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param ms Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void LiveMap::UpdateDelay(uint32_t ms)
{
    priv.lastMapUpdateTime = lv_tick_get() - 1000 + ms;
}

/**
 * @brief Refresh the LiveMap state without blocking the scheduler.
 * @details The function consumes the latest cached DataProc/HAL snapshot and updates presentation state; it does not own or free the source data.
 */
void LiveMap::SportInfoUpdate()
{
    lv_label_set_text_fmt(
        View.ui.sportInfo.labelSpeed,
        "%02d",
        (int)Model.sportStatusInfo.speedKph);

    lv_label_set_text_fmt(
        View.ui.sportInfo.labelTrip,
        "%0.1f km",
        Model.sportStatusInfo.singleDistance / 1000);

/**
 * @brief Own and retain the buf state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    char buf[16];
    lv_label_set_text(
        View.ui.sportInfo.labelTime,
/**
 * @brief Execute the MakeTimeString operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param singleTime Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param buf Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
        DataProc::MakeTimeString(Model.sportStatusInfo.singleTime, buf, sizeof(buf)));
}

/**
 * @brief Execute the CheckPosition operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 */
void LiveMap::CheckPosition()
{
/**
 * @brief Own and retain the refreshMap state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    bool refreshMap = false;

/**
 * @brief Own and retain the gpsInfo state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    HAL::GPS_Info_t gpsInfo;
/**
 * @brief Execute the Model.GetGPS_Info operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param gpsInfo Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Model.GetGPS_Info(&gpsInfo);

    mapLevelCurrent = lv_slider_get_value(View.ui.zoom.slider);
    if (mapLevelCurrent != Model.mapConv.GetLevel())
    {
        refreshMap = true;
/**
 * @brief Execute the Model.mapConv.SetLevel operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param mapLevelCurrent Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
        Model.mapConv.SetLevel(mapLevelCurrent);
        printf("[Update] SetLevel\n");
    }

/**
 * @brief Own and retain the mapY state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    int32_t mapX, mapY;
    Model.mapConv.ConvertMapCoordinate(
        gpsInfo.longitude, gpsInfo.latitude,
        &mapX, &mapY);
/**
 * @brief Execute the Model.tileConv.SetFocusPos operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param mapX Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param mapY Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Model.tileConv.SetFocusPos(mapX, mapY);

    if (GetIsMapTileContChanged())
    {
        refreshMap = true;
        printf("[Update] refreshMap\n");
    }

    if (refreshMap)
    {
/**
 * @brief Own and retain the rect state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        TileConv::Rect_t rect;
/**
 * @brief Execute the Model.tileConv.GetTileContainer operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param rect Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
        Model.tileConv.GetTileContainer(&rect);

        Area_t area =
            {
                .x0 = rect.x,
                .y0 = rect.y,
                .x1 = rect.x + rect.width - 1,
                .y1 = rect.y + rect.height - 1};

        onMapTileContRefresh(&area, mapX, mapY);
    }

/**
 * @brief Refresh the LiveMap state without blocking the scheduler.
 * @details The function consumes the latest cached DataProc/HAL snapshot and updates presentation state; it does not own or free the source data.
 * @param mapX Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param mapY Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param course Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    MapTileContUpdate(mapX, mapY, gpsInfo.course);

    if (priv.isTrackAvtive)
    {
/**
 * @brief Execute the Model.pointFilter.PushPoint operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param mapX Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param mapY Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
        Model.pointFilter.PushPoint(mapX, mapY);
    }
}

/**
 * @brief Execute the onMapTileContRefresh operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param area Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param x Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param y Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void LiveMap::onMapTileContRefresh(const Area_t *area, int32_t x, int32_t y)
{
    LV_LOG_INFO(
        "area: (%d, %d) [%dx%d]",
        area->x0, area->y0,
        area->x1 - area->x0 + 1,
        area->y1 - area->y0 + 1);

/**
 * @brief Convert map or coordinate data between the supported representations.
 * @return Operation result or status; inspect it before using dependent state.
 */
    MapTileContReload();

    if (priv.isTrackAvtive)
    {
/**
 * @brief Execute the TrackLineReload operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param area Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param x Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param y Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
        TrackLineReload(area, x, y);
    }
}

/**
 * @brief Refresh the LiveMap state without blocking the scheduler.
 * @details The function consumes the latest cached DataProc/HAL snapshot and updates presentation state; it does not own or free the source data.
 * @param mapX Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param mapY Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param course Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void LiveMap::MapTileContUpdate(int32_t mapX, int32_t mapY, float course)
{
/**
 * @brief Own and retain the offset state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    TileConv::Point_t offset;
/**
 * @brief Own and retain the curPoint state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    TileConv::Point_t curPoint = {mapX, mapY};
/**
 * @brief Execute the Model.tileConv.GetOffset operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param offset Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param curPoint Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Model.tileConv.GetOffset(&offset, &curPoint);

    /* arrow */
    lv_obj_t *img = View.ui.map.imgArrow;
/**
 * @brief Execute the Model.tileConv.GetFocusOffset operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param offset Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Model.tileConv.GetFocusOffset(&offset);
    lv_coord_t x = offset.x - lv_obj_get_width(img) / 2;
    lv_coord_t y = offset.y - lv_obj_get_height(img) / 2;
/**
 * @brief Execute the View.SetImgArrowStatus operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param x Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param y Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param course Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    View.SetImgArrowStatus(x, y, course);

    /* active line */
    if (priv.isTrackAvtive)
    {
/**
 * @brief Execute the View.SetLineActivePoint operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param x Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param y Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
        View.SetLineActivePoint((lv_coord_t)offset.x, (lv_coord_t)offset.y);
    }

    /* map cont */
/**
 * @brief Execute the Model.tileConv.GetTileContainerOffset operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param offset Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Model.tileConv.GetTileContainerOffset(&offset);

    lv_coord_t baseX = (LV_HOR_RES - CONFIG_LIVE_MAP_VIEW_WIDTH) / 2;
    lv_coord_t baseY = (LV_VER_RES - CONFIG_LIVE_MAP_VIEW_HEIGHT) / 2;
    lv_obj_set_pos(View.ui.map.cont, baseX - offset.x, baseY - offset.y);
}

/**
 * @brief Convert map or coordinate data between the supported representations.
 */
void LiveMap::MapTileContReload()
{
    /* tile src */
    for (uint32_t i = 0; i < View.ui.map.tileNum; i++)
    {
/**
 * @brief Own and retain the pos state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        TileConv::Point_t pos;
/**
 * @brief Execute the Model.tileConv.GetTilePos operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param i Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param pos Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
        Model.tileConv.GetTilePos(i, &pos);

/**
 * @brief Own and retain the path state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        char path[64];
/**
 * @brief Execute the Model.mapConv.ConvertMapPath operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param x Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param y Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param path Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
        Model.mapConv.ConvertMapPath(pos.x, pos.y, path, sizeof(path));

/**
 * @brief Execute the View.SetMapTileSrc operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param i Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param path Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
        View.SetMapTileSrc(i, path);

        printf("[Update] path:%s\n", path);
    }
}

/**
 * @brief Read IsMapTileContChanged from the current object state.
 * @return Operation result or status; inspect it before using dependent state.
 */
bool LiveMap::GetIsMapTileContChanged()
{
/**
 * @brief Own and retain the pos state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    TileConv::Point_t pos;
/**
 * @brief Execute the Model.tileConv.GetTilePos operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param pos Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Model.tileConv.GetTilePos(0, &pos);

    bool ret = (pos.x != priv.lastTileContOriPoint.x || pos.y != priv.lastTileContOriPoint.y);

    priv.lastTileContOriPoint = pos;

/**
 * @brief Own and retain the ret state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    return ret;
}

/**
 * @brief Execute the TrackLineReload operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param area Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param x Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param y Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void LiveMap::TrackLineReload(const Area_t *area, int32_t x, int32_t y)
{
/**
 * @brief Execute the Model.lineFilter.SetClipArea operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param area Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Model.lineFilter.SetClipArea(area);
/**
 * @brief Execute the Model.lineFilter.Reset operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Model.lineFilter.Reset();
/**
 * @brief Execute the Model.TrackReload operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param filter Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param point Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Model.TrackReload([](TrackPointFilter *filter, const TrackPointFilter::Point_t *point)
                      {
        LiveMap* instance = (LiveMap*)filter->userData;
        instance->Model.lineFilter.PushPoint((int32_t)point->x, (int32_t)point->y); }, this);
/**
 * @brief Execute the Model.lineFilter.PushPoint operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param x Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param y Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Model.lineFilter.PushPoint(x, y);
/**
 * @brief Execute the Model.lineFilter.PushEnd operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Model.lineFilter.PushEnd();
}

/**
 * @brief Execute the TrackLineAppend operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param x Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param y Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void LiveMap::TrackLineAppend(int32_t x, int32_t y)
{
/**
 * @brief Own and retain the offset state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    TileConv::Point_t offset;
/**
 * @brief Own and retain the curPoint state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    TileConv::Point_t curPoint = {x, y};
/**
 * @brief Execute the Model.tileConv.GetOffset operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param offset Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param curPoint Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Model.tileConv.GetOffset(&offset, &curPoint);
/**
 * @brief Execute the View.ui.track.lineTrack->append operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param x Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param y Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    View.ui.track.lineTrack->append((lv_coord_t)offset.x, (lv_coord_t)offset.y);
}

/**
 * @brief Execute the TrackLineAppendToEnd operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param x Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param y Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void LiveMap::TrackLineAppendToEnd(int32_t x, int32_t y)
{
/**
 * @brief Own and retain the offset state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    TileConv::Point_t offset;
/**
 * @brief Own and retain the curPoint state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    TileConv::Point_t curPoint = {x, y};
/**
 * @brief Execute the Model.tileConv.GetOffset operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param offset Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param curPoint Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Model.tileConv.GetOffset(&offset, &curPoint);
/**
 * @brief Execute the View.ui.track.lineTrack->append_to_end operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param x Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param y Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    View.ui.track.lineTrack->append_to_end((lv_coord_t)offset.x, (lv_coord_t)offset.y);
}

/**
 * @brief Execute the onTrackLineEvent operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param filter Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param event Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void LiveMap::onTrackLineEvent(TrackLineFilter *filter, TrackLineFilter::Event_t *event)
{
    LiveMap *instance = (LiveMap *)filter->userData;
    lv_poly_line *lineTrack = instance->View.ui.track.lineTrack;

    switch (event->code)
    {
    case TrackLineFilter::EVENT_START_LINE:
        lineTrack->start();
        instance->TrackLineAppend(event->point->x, event->point->y);
        break;
    case TrackLineFilter::EVENT_APPEND_POINT:
        instance->TrackLineAppend(event->point->x, event->point->y);
        break;
    case TrackLineFilter::EVENT_END_LINE:
        if (event->point != nullptr)
        {
            instance->TrackLineAppend(event->point->x, event->point->y);
        }
        lineTrack->stop();
        break;
    case TrackLineFilter::EVENT_RESET:
        lineTrack->reset();
        break;
    default:
        break;
    }
}

/**
 * @brief Decode a UI or system event and forward it to the responsible model or view.
 * @details Event callbacks execute on the LVGL/UI context; they must remain short and defer blocking work to the corresponding data-processing task.
 * @param event Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void LiveMap::onEvent(lv_event_t *event)
{
    LiveMap *instance = (LiveMap *)lv_event_get_user_data(event);
/**
 * @brief Execute the LV_ASSERT_NULL operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param instance Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    LV_ASSERT_NULL(instance);

    lv_obj_t *obj = lv_event_get_current_target(event);
    lv_event_code_t code = lv_event_get_code(event);

    if (code == LV_EVENT_LEAVE)
    {
        instance->_Manager->Pop();
        return;
    }

    if (obj == instance->View.ui.zoom.slider)
    {
        if (code == LV_EVENT_VALUE_CHANGED)
        {
            // int32_t level = lv_slider_get_value(obj);
            // int32_t levelMax = instance->Model.mapConv.GetLevelMax();
            // lv_label_set_text_fmt(instance->View.ui.zoom.labelInfo, "%d/%d", level, levelMax);

            // lv_obj_clear_state(instance->View.ui.zoom.cont, LV_STATE_USER_1);
            // instance->priv.lastContShowTime = lv_tick_get();
            // instance->UpdateDelay(200);

            printf("[Update] Slider Val Change\n");
        }
        else if (code == LV_EVENT_PRESSED)
        {
            instance->_Manager->Pop();
        }
    }

    if (code == LV_EVENT_GESTURE)
    {
        lv_indev_wait_release(lv_indev_get_act());

        // int32_t level = lv_slider_get_value(instance->View.ui.zoom.slider);
        // int32_t levelMax = instance->Model.mapConv.GetLevelMax();

        switch (lv_indev_get_gesture_dir(lv_indev_get_act()))
        {
        case LV_DIR_LEFT:
            lv_slider_set_value(instance->View.ui.zoom.slider, lv_slider_get_value(instance->View.ui.zoom.slider) - 1, LV_ANIM_OFF);

            lv_label_set_text_fmt(instance->View.ui.zoom.labelInfo, "%d/%d", lv_slider_get_value(instance->View.ui.zoom.slider), instance->Model.mapConv.GetLevelMax());

            lv_obj_clear_state(instance->View.ui.zoom.cont, LV_STATE_USER_1);
            instance->priv.lastContShowTime = lv_tick_get();
            instance->UpdateDelay(200);

            printf("[Update] Slider Val Change\n");

            printf("[TOUCH] LEFT:%d\n", lv_slider_get_value(instance->View.ui.zoom.slider));
            break;
        case LV_DIR_RIGHT:
            lv_slider_set_value(instance->View.ui.zoom.slider, lv_slider_get_value(instance->View.ui.zoom.slider) + 1, LV_ANIM_OFF);

            lv_label_set_text_fmt(instance->View.ui.zoom.labelInfo, "%d/%d", lv_slider_get_value(instance->View.ui.zoom.slider), instance->Model.mapConv.GetLevelMax());

            lv_obj_clear_state(instance->View.ui.zoom.cont, LV_STATE_USER_1);
            instance->priv.lastContShowTime = lv_tick_get();
            instance->UpdateDelay(200);

            printf("[Update] Slider Val Change\n");

            printf("[TOUCH] RIGHT:%d\n", lv_slider_get_value(instance->View.ui.zoom.slider));

            break;
        case LV_DIR_TOP:

            break;
        case LV_DIR_BOTTOM:

            break;
        default:
            break;
        }
    }

    if (obj == instance->View.ui.sportInfo.cont)
    {
        if (code == LV_EVENT_PRESSED)
        {
            instance->_Manager->Pop();
        }
    }
}
