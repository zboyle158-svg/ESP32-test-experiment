#include "SystemInfos.h"
#include "App/Version.h"
#include "HardwareSerial.h"

using namespace Page;

/**
 * @brief Construct or destroy the SystemInfos object.
 * @return Operation result or status; inspect it before using dependent state.
 */
SystemInfos::SystemInfos()
{
}

/**
 * @brief Release resources owned by the SystemInfos object.
 * @return Operation result or status; inspect it before using dependent state.
 */
SystemInfos::~SystemInfos()
{
}

/**
 * @brief Execute the onCustomAttrConfig operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 */
void SystemInfos::onCustomAttrConfig()
{
/**
 * @brief Execute the LV_LOG_USER operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    LV_LOG_USER("onCustomAttrConfig");
}

/**
 * @brief Handle the onViewLoad page lifecycle callback.
 */
void SystemInfos::onViewLoad()
{
/**
 * @brief Execute the LV_LOG_USER operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    LV_LOG_USER("onViewLoad");
    Serial.println("[SystemInfos] onViewLoad!");

/**
 * @brief Execute the Model.Init operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Model.Init();
/**
 * @brief Execute the View.Create operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param _root Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    View.Create(_root);
/**
 * @brief Decode a UI or system event and forward it to the responsible model or view.
 * @details Event callbacks execute on the LVGL/UI context; they must remain short and defer blocking work to the corresponding data-processing task.
 * @param _root Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    AttachEvent(_root);

    SystemInfosView::item_t *item_grp = ((SystemInfosView::item_t *)&View.ui);

    for (int i = 0; i < sizeof(View.ui) / sizeof(SystemInfosView::item_t); i++)
    {
/**
 * @brief Decode a UI or system event and forward it to the responsible model or view.
 * @details Event callbacks execute on the LVGL/UI context; they must remain short and defer blocking work to the corresponding data-processing task.
 * @param icon Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
        AttachEvent(item_grp[i].icon);
    }
}

/**
 * @brief Handle the onViewDidLoad page lifecycle callback.
 */
void SystemInfos::onViewDidLoad()
{
/**
 * @brief Execute the LV_LOG_USER operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    LV_LOG_USER("onViewDidLoad");
}

/**
 * @brief Handle the onViewWillAppear page lifecycle callback.
 */
void SystemInfos::onViewWillAppear()
{
/**
 * @brief Execute the LV_LOG_USER operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    LV_LOG_USER("onViewWillAppear");

/**
 * @brief Execute the Model.SetStatusBarStyle operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param STATUS_BAR_STYLE_BLACK Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Model.SetStatusBarStyle(DataProc::STATUS_BAR_STYLE_BLACK);
/**
 * @brief Execute the Model.SetStatusBarAppear operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param true Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Model.SetStatusBarAppear(true);
    
    timer = lv_timer_create(onTimerUpdate, 1000, this);
    lv_timer_ready(timer); // 就是无视倒计时，直接给一个触发标志位，就是马上跑一遍回调函数

/**
 * @brief Execute the View.SetScrollToY operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param _root Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param LV_VER_RES Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param LV_ANIM_OFF Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    View.SetScrollToY(_root, -LV_VER_RES, LV_ANIM_OFF);
    lv_obj_set_style_opa(_root, LV_OPA_TRANSP, 0);
    lv_obj_fade_in(_root, 250, 0);
}

/**
 * @brief Handle the onViewDidAppear page lifecycle callback.
 */
void SystemInfos::onViewDidAppear()
{
/**
 * @brief Execute the LV_LOG_USER operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    LV_LOG_USER("onViewDidAppear");
    lv_group_t *group = lv_group_get_default();
/**
 * @brief Execute the LV_ASSERT_NULL operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param group Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    LV_ASSERT_NULL(group);
/**
 * @brief Execute the View.onFocus operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param group Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    View.onFocus(group);
}

/**
 * @brief Handle the onViewWillDisappear page lifecycle callback.
 */
void SystemInfos::onViewWillDisappear()
{
/**
 * @brief Execute the LV_LOG_USER operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    LV_LOG_USER("onViewWillDisappear");
    lv_group_t *group = lv_group_get_default();
/**
 * @brief Execute the LV_ASSERT_NULL operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param group Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    LV_ASSERT_NULL(group);
    lv_group_focus_obj(nullptr);
    lv_group_remove_all_objs(group);
    lv_group_set_focus_cb(lv_group_get_default(), nullptr);
    lv_obj_fade_out(_root, 250, 0);
}

/**
 * @brief Handle the onViewDidDisappear page lifecycle callback.
 */
void SystemInfos::onViewDidDisappear()
{
/**
 * @brief Execute the LV_LOG_USER operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    LV_LOG_USER("onViewDidDisappear");

    lv_timer_del(timer);
}

/**
 * @brief Handle the onViewUnload page lifecycle callback.
 */
void SystemInfos::onViewUnload()
{
/**
 * @brief Execute the LV_LOG_USER operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    LV_LOG_USER("onViewUnload");

/**
 * @brief Execute the View.Delete operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    View.Delete();
/**
 * @brief Execute the Model.Deinit operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Model.Deinit();
}

/**
 * @brief Handle the onViewDidUnload page lifecycle callback.
 */
void SystemInfos::onViewDidUnload()
{
/**
 * @brief Execute the LV_LOG_USER operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    LV_LOG_USER("onViewDidUnload");
}

/**
 * @brief Decode a UI or system event and forward it to the responsible model or view.
 * @details Event callbacks execute on the LVGL/UI context; they must remain short and defer blocking work to the corresponding data-processing task.
 * @param obj Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void SystemInfos::AttachEvent(lv_obj_t *obj)
{
    lv_obj_add_event_cb(obj, onEvent, LV_EVENT_ALL, this);
}

/**
 * @brief Refresh the SystemInfos state without blocking the scheduler.
 * @details The function consumes the latest cached DataProc/HAL snapshot and updates presentation state; it does not own or free the source data.
 */
void SystemInfos::Update()
{
/**
 * @brief Own and retain the buf state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    char buf[64] = {0};

    /* Sport */
/**
 * @brief Own and retain the trip state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    float trip = 0;
/**
 * @brief Own and retain the maxSpd state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    float maxSpd = 0;
    // Model.GetSportInfo(&trip, buf, sizeof(buf), &maxSpd);
/**
 * @brief Execute the View.SetSport operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param trip Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param buf Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param maxSpd Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    View.SetSport(trip, buf, maxSpd);

    /* GPS */
/**
 * @brief Own and retain the lat state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    float lat = 0;
/**
 * @brief Own and retain the lng state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    float lng = 0;
/**
 * @brief Own and retain the alt state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    float alt = 0;
/**
 * @brief Own and retain the course state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    float course = 0;
/**
 * @brief Own and retain the speed state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    float speed = 0;
/**
 * @brief Execute the Model.GetGPSInfo operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param lat Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param lng Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param alt Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param buf Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param course Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param speed Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Model.GetGPSInfo(&lat, &lng, &alt, buf, sizeof(buf), &course, &speed);
/**
 * @brief Execute the View.SetGPS operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param lat Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param lng Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param alt Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param buf Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param course Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param speed Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    View.SetGPS(lat, lng, alt, buf, course, speed);

    /* MAG */
/**
 * @brief Own and retain the dir state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    float dir = 0;
/**
 * @brief Own and retain the x state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    int x = 0;
/**
 * @brief Own and retain the y state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    int y = 0;
/**
 * @brief Own and retain the z state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    int z = 0;
/**
 * @brief Execute the Model.GetMAGInfo operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param dir Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param x Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param y Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param z Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Model.GetMAGInfo(&dir, &x, &y, &z);
/**
 * @brief Execute the View.SetMAG operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param dir Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param x Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param y Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param z Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    View.SetMAG(dir, x, y, z);

    /* IMU */
/**
 * @brief Own and retain the steps state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    int steps = 0;
/**
 * @brief Execute the Model.GetIMUInfo operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param steps Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param buf Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Model.GetIMUInfo(&steps, buf, sizeof(buf));
/**
 * @brief Execute the View.SetIMU operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param steps Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param buf Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    View.SetIMU(steps, buf);

    /* RTC */
/**
 * @brief Execute the Model.GetRTCInfo operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param buf Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Model.GetRTCInfo(buf, sizeof(buf));
/**
 * @brief Execute the View.SetRTC operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param buf Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    View.SetRTC(buf);

    /* Power */
/**
 * @brief Own and retain the usage state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    int usage = 0;
/**
 * @brief Own and retain the voltage state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    float voltage = 0;
/**
 * @brief Execute the Model.GetBatteryInfo operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param usage Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param voltage Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param buf Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Model.GetBatteryInfo(&usage, &voltage, buf, sizeof(buf));
/**
 * @brief Execute the View.SetBattery operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param usage Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param voltage Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param buf Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    View.SetBattery(usage, voltage, buf);

    /* Storage */
/**
 * @brief Own and retain the detect state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    bool detect = 0;
    const char *type = "-";
/**
 * @brief Execute the Model.GetStorageInfo operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param detect Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param type Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param buf Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Model.GetStorageInfo(&detect, &type, buf, sizeof(buf));
    View.SetStorage(
        detect ? "OK" : "ERROR",
        buf,
        type,
        VERSION_FILESYSTEM);

    /* System */
/**
 * @brief Execute the MakeTimeString operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param buf Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    DataProc::MakeTimeString(lv_tick_get(), buf, sizeof(buf));
    View.SetSystem(
        VERSION_FIRMWARE_NAME " " VERSION_SOFTWARE,
        VERSION_AUTHOR_NAME,
        VERSION_LVGL,
        buf,
        VERSION_COMPILER,
        VERSION_BUILD_TIME);
}

/**
 * @brief Refresh the SystemInfos state without blocking the scheduler.
 * @details The function consumes the latest cached DataProc/HAL snapshot and updates presentation state; it does not own or free the source data.
 * @param timer Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void SystemInfos::onTimerUpdate(lv_timer_t *timer)
{
    SystemInfos *instance = (SystemInfos *)timer->user_data;

    instance->Update();
}

/**
 * @brief Decode a UI or system event and forward it to the responsible model or view.
 * @details Event callbacks execute on the LVGL/UI context; they must remain short and defer blocking work to the corresponding data-processing task.
 * @param event Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void SystemInfos::onEvent(lv_event_t *event)
{
    SystemInfos *instance = (SystemInfos *)lv_event_get_user_data(event);
/**
 * @brief Execute the LV_ASSERT_NULL operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param instance Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    LV_ASSERT_NULL(instance);

    lv_obj_t *obj = lv_event_get_current_target(event);
    lv_event_code_t code = lv_event_get_code(event);

    if (code == LV_EVENT_PRESSED)
    {
        if (lv_obj_has_state(obj, LV_STATE_FOCUSED))
        {
            instance->_Manager->Pop();
        }
    }

    if (obj == instance->_root)
    {
        if (code == LV_EVENT_LEAVE)
        {
            instance->_Manager->Pop();
        }
    }
}
