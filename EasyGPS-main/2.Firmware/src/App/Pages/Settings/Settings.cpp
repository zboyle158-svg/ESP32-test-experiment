#include "Settings.h"

using namespace Page;

/**
 * @brief Construct or destroy the Settings object.
 * @return Operation result or status; inspect it before using dependent state.
 */
Settings::Settings()
/**
 * @brief Execute the timer operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param nullptr Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    : timer(nullptr)
{
}

/**
 * @brief Release resources owned by the Settings object.
 * @return Operation result or status; inspect it before using dependent state.
 */
Settings::~Settings()
{
}

/**
 * @brief Execute the onCustomAttrConfig operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 */
void Settings::onCustomAttrConfig()
{
/**
 * @brief Execute the LV_LOG_USER operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    LV_LOG_USER("onCustomAttrConfig");
/**
 * @brief Change the CustomCacheEnable configuration of the object.
 * @param false Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    SetCustomCacheEnable(false);
/**
 * @brief Change the CustomLoadAnimType configuration of the object.
 * @param LOAD_ANIM_NONE Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    SetCustomLoadAnimType(PageManager::LOAD_ANIM_NONE); // 设置当前的动画样式（？
}

/**
 * @brief Handle the onViewLoad page lifecycle callback.
 */
void Settings::onViewLoad() // 该页面page的UI加载初始化
{
/**
 * @brief Execute the LV_LOG_USER operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    LV_LOG_USER("onViewLoad");
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
    View.Create(_root); // 创建画布 // _root相当于全局画布，所有的控件都基于_root

    /* Update the buttons position manually for first */
    lv_event_send(View.ui.menuCont.cont, LV_EVENT_SCROLL, NULL);
    /* Be sure the fist button is in the middle */
    lv_obj_scroll_to_view(lv_obj_get_child(View.ui.menuCont.cont, 1), LV_ANIM_ON);

/**
 * @brief Decode a UI or system event and forward it to the responsible model or view.
 * @details Event callbacks execute on the LVGL/UI context; they must remain short and defer blocking work to the corresponding data-processing task.
 * @return Operation result or status; inspect it before using dependent state.
 */
    AttachEvent(lv_scr_act());
    lv_obj_add_event_cb(lv_obj_get_child(View.ui.wifiInfo.swAP, -1), (lv_event_cb_t)WiFiSwitchHandler, LV_EVENT_CLICKED, this);
    lv_obj_add_event_cb(lv_obj_get_child(View.ui.wifiInfo.swSTA, -1), (lv_event_cb_t)WiFiSwitchHandler, LV_EVENT_CLICKED, this);

    lv_obj_add_event_cb(lv_obj_get_child(View.ui.bleInfo.sw, -1), (lv_event_cb_t)BLESwitchHandler, LV_EVENT_CLICKED, this);

    lv_obj_add_event_cb(lv_obj_get_child(View.ui.displayInfo.brig, -1), (lv_event_cb_t)DisplaySliderHandler, LV_EVENT_VALUE_CHANGED, this);

    lv_obj_add_event_cb(lv_obj_get_child(View.ui.powInfo.swAutoPowOff, -1), (lv_event_cb_t)PowerSwitchHandler, LV_EVENT_CLICKED, this);
}

/**
 * @brief Handle the onViewDidLoad page lifecycle callback.
 */
void Settings::onViewDidLoad() // 该页面page的UI结束加载初始化
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
void Settings::onViewWillAppear() // 该页面page的UI开始出场动画
{
/**
 * @brief Execute the LV_LOG_USER operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    LV_LOG_USER("onViewWillAppear");

    // lv_indev_wait_release(lv_indev_get_act());  // lv_indev_get_act获取当前活动的输入设备 // lv_indev_wait_release等待当前输入设备的释放
    lv_group_t *group = lv_group_get_default(); // 用于获取LittlevGL中默认的组对象
/**
 * @brief Execute the LV_ASSERT_NULL operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param group Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    LV_ASSERT_NULL(group);

    // lv_group_set_wrap(group, false); // lv_group_set_wrap设置组对象的循环模式，以便在焦点移动时确定是否循环到组的开头，这对于导航控件和处理焦点移动时的行为非常有用

/**
 * @brief Execute the Model.SetStatusBarStyle operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param STATUS_BAR_STYLE_TRANSP Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Model.SetStatusBarStyle(DataProc::STATUS_BAR_STYLE_TRANSP); // 设置状态栏的样式（？
/**
 * @brief Execute the Model.SetStatusBarAppear operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param true Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Model.SetStatusBarAppear(true);
/**
 * @brief Refresh the Settings state without blocking the scheduler.
 * @details The function consumes the latest cached DataProc/HAL snapshot and updates presentation state; it does not own or free the source data.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Update(); // 刷新，第一次加载界面，需要刷新一下，不然数值不显示会卡一下才显示

    lv_obj_fade_in(_root, 350, 0);

    // View.AppearAnimStart(); // 开始加载进入该page的动画，出场动画
}

/**
 * @brief Handle the onViewDidAppear page lifecycle callback.
 */
void Settings::onViewDidAppear() // 该页面page的UI结束出场动画
{
/**
 * @brief Execute the LV_LOG_USER operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    LV_LOG_USER("onViewDidAppear");

    timer = lv_timer_create(onTimerUpdate, 1000, this); // 这里设置一个1s的定时器，软定时器，用于在onTimerUpdate里update
}

/**
 * @brief Handle the onViewWillDisappear page lifecycle callback.
 */
void Settings::onViewWillDisappear() // 该页面page的UI开始退场动画
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

    lv_group_remove_all_objs(group);

    lv_timer_del(timer);
}

/**
 * @brief Handle the onViewDidDisappear page lifecycle callback.
 */
void Settings::onViewDidDisappear() // 该页面page的UI结束退场动画
{
/**
 * @brief Execute the LV_LOG_USER operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    LV_LOG_USER("onViewDidDisappear");
}

/**
 * @brief Handle the onViewUnload page lifecycle callback.
 */
void Settings::onViewUnload()
{
/**
 * @brief Execute the LV_LOG_USER operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    LV_LOG_USER("onViewUnload");

/**
 * @brief Execute the Model.Deinit operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Model.Deinit();
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
void Settings::onViewDidUnload()
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
void Settings::AttachEvent(lv_obj_t *obj)
{
    lv_obj_add_event_cb(obj, onEvent, LV_EVENT_ALL, this);
}

/**
 * @brief Refresh the Settings state without blocking the scheduler.
 * @details The function consumes the latest cached DataProc/HAL snapshot and updates presentation state; it does not own or free the source data.
 */
void Settings::Update()
{
    /* WiFi */
/**
 * @brief Own and retain the WiFiname state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    char WiFiname[20] = {0};
/**
 * @brief Own and retain the WiFiIP state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    char WiFiIP[20] = {0};
/**
 * @brief Own and retain the WiFiGatWay state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    char WiFiGatWay[20] = {0};
/**
 * @brief Own and retain the WiFiMac state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    char WiFiMac[20] = {0};
/**
 * @brief Own and retain the isWiFiConnected state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    bool isWiFiConnected = false;
/**
 * @brief Own and retain the isWiFiEnabled state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    bool isWiFiEnabled = false;
/**
 * @brief Own and retain the isAPEnabled state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    bool isAPEnabled = false;
/**
 * @brief Execute the Model.GetWiFiInfo operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param WiFiname Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param WiFiIP Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param WiFiGatWay Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param WiFiMac Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param isWiFiConnected Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param isAPEnabled Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param isWiFiEnabled Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Model.GetWiFiInfo(WiFiname, WiFiIP, WiFiGatWay, WiFiMac, &isWiFiConnected, &isAPEnabled, &isWiFiEnabled);
    // printf("[test] ip:%s\r\n", WiFiIP);
/**
 * @brief Refresh the Settings state without blocking the scheduler.
 * @details The function consumes the latest cached DataProc/HAL snapshot and updates presentation state; it does not own or free the source data.
 * @param labelName Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param WiFiname Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Content_Update(View.ui.wifiInfo.labelName, WiFiname);
/**
 * @brief Refresh the Settings state without blocking the scheduler.
 * @details The function consumes the latest cached DataProc/HAL snapshot and updates presentation state; it does not own or free the source data.
 * @param labelConnect Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Content_Update(View.ui.wifiInfo.labelConnect, isWiFiConnected ? "Connected" : "DisConnected");
/**
 * @brief Refresh the Settings state without blocking the scheduler.
 * @details The function consumes the latest cached DataProc/HAL snapshot and updates presentation state; it does not own or free the source data.
 * @param labelIP Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param WiFiIP Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Content_Update(View.ui.wifiInfo.labelIP, WiFiIP);
/**
 * @brief Refresh the Settings state without blocking the scheduler.
 * @details The function consumes the latest cached DataProc/HAL snapshot and updates presentation state; it does not own or free the source data.
 * @param swAP Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param isAPEnabled Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Switch_Update(View.ui.wifiInfo.swAP, isAPEnabled);
/**
 * @brief Refresh the Settings state without blocking the scheduler.
 * @details The function consumes the latest cached DataProc/HAL snapshot and updates presentation state; it does not own or free the source data.
 * @param swSTA Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param isWiFiEnabled Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Switch_Update(View.ui.wifiInfo.swSTA, isWiFiEnabled);

    /* BLEKeyboard */
/**
 * @brief Own and retain the BLEName state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    char BLEName[20] = {0};
/**
 * @brief Own and retain the isBLEConnected state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    bool isBLEConnected = false;
/**
 * @brief Own and retain the isBLEEnabled state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    bool isBLEEnabled = false;
/**
 * @brief Execute the Model.GetBLEInfo operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param BLEName Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param isBLEConnected Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param isBLEEnabled Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Model.GetBLEInfo(BLEName, &isBLEConnected, &isBLEEnabled);
/**
 * @brief Refresh the Settings state without blocking the scheduler.
 * @details The function consumes the latest cached DataProc/HAL snapshot and updates presentation state; it does not own or free the source data.
 * @param labelName Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param BLEName Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Content_Update(View.ui.bleInfo.labelName, BLEName);
/**
 * @brief Refresh the Settings state without blocking the scheduler.
 * @details The function consumes the latest cached DataProc/HAL snapshot and updates presentation state; it does not own or free the source data.
 * @param labelConnect Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Content_Update(View.ui.bleInfo.labelConnect, isBLEConnected ? "Connected" : "DisConnected");
/**
 * @brief Refresh the Settings state without blocking the scheduler.
 * @details The function consumes the latest cached DataProc/HAL snapshot and updates presentation state; it does not own or free the source data.
 * @param sw Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param isBLEEnabled Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Switch_Update(View.ui.bleInfo.sw, isBLEEnabled);

    /* Backlight */
/**
 * @brief Own and retain the Brightness state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    uint16_t Brightness = 255;
/**
 * @brief Execute the Model.GetDisplayBrightness operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param Brightness Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Model.GetDisplayBrightness(&Brightness);
/**
 * @brief Refresh the Settings state without blocking the scheduler.
 * @details The function consumes the latest cached DataProc/HAL snapshot and updates presentation state; it does not own or free the source data.
 * @param brig Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param Brightness Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Slider_Update(View.ui.displayInfo.brig, Brightness);

    /* Power */
/**
 * @brief Own and retain the isAutoPowOff state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    bool isAutoPowOff = false;
/**
 * @brief Execute the Model.GetPowAutoOff operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param isAutoPowOff Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Model.GetPowAutoOff(&isAutoPowOff);
/**
 * @brief Refresh the Settings state without blocking the scheduler.
 * @details The function consumes the latest cached DataProc/HAL snapshot and updates presentation state; it does not own or free the source data.
 * @param swAutoPowOff Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param isAutoPowOff Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Switch_Update(View.ui.powInfo.swAutoPowOff, isAutoPowOff);
}

/**
 * @brief Refresh the Settings state without blocking the scheduler.
 * @details The function consumes the latest cached DataProc/HAL snapshot and updates presentation state; it does not own or free the source data.
 * @param timer Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void Settings::onTimerUpdate(lv_timer_t *timer)
{
    Settings *instance = (Settings *)timer->user_data;

    instance->Update();
}

/**
 * @brief Refresh the Settings state without blocking the scheduler.
 * @details The function consumes the latest cached DataProc/HAL snapshot and updates presentation state; it does not own or free the source data.
 * @param obj Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param text Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void Settings::Content_Update(lv_obj_t *obj, const char *text)
{
    lv_label_set_text_fmt(lv_obj_get_child(obj, -1), "%s", text);
}

/**
 * @brief Refresh the Settings state without blocking the scheduler.
 * @details The function consumes the latest cached DataProc/HAL snapshot and updates presentation state; it does not own or free the source data.
 * @param obj Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param isChecked Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void Settings::Switch_Update(lv_obj_t *obj, bool isChecked)
{
    if (isChecked)
        lv_obj_add_state(lv_obj_get_child(obj, -1), LV_STATE_CHECKED);
    else
        lv_obj_clear_state(lv_obj_get_child(obj, -1), LV_STATE_CHECKED);
}

/**
 * @brief Refresh the Settings state without blocking the scheduler.
 * @details The function consumes the latest cached DataProc/HAL snapshot and updates presentation state; it does not own or free the source data.
 * @param obj Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param val Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void Settings::Slider_Update(lv_obj_t *obj, int32_t val)
{
    lv_slider_set_value(lv_obj_get_child(obj, -1), val, LV_ANIM_OFF);
}

/**
 * @brief Decode a UI or system event and forward it to the responsible model or view.
 * @details Event callbacks execute on the LVGL/UI context; they must remain short and defer blocking work to the corresponding data-processing task.
 * @param event Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void Settings::onEvent(lv_event_t *event)
{
    Settings *instance = (Settings *)lv_event_get_user_data(event); // 获得this指针
/**
 * @brief Execute the LV_ASSERT_NULL operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param instance Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    LV_ASSERT_NULL(instance);

    lv_obj_t *obj = lv_event_get_current_target(event); // lv_event_get_current_target用于获取当前正在处理事件的目标对象
    lv_event_code_t code = lv_event_get_code(event);    // lv_event_get_code就是获取短按长按双击之类的枚举

    if (code == LV_EVENT_SHORT_CLICKED)
    {
    }

    if (code == LV_EVENT_GESTURE)
    {
        lv_indev_wait_release(lv_indev_get_act());

        switch (lv_indev_get_gesture_dir(lv_indev_get_act()))
        {
        case LV_DIR_LEFT:
            instance->_Manager->Pop();
            break;
        case LV_DIR_RIGHT:
            instance->_Manager->Pop();
            break;
        case LV_DIR_TOP:

            break;
        case LV_DIR_BOTTOM:

            break;
        default:
            break;
        }
    }
}

/**
 * @brief Decode a UI or system event and forward it to the responsible model or view.
 * @details Event callbacks execute on the LVGL/UI context; they must remain short and defer blocking work to the corresponding data-processing task.
 * @param event Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void Settings::WiFiSwitchHandler(lv_event_t *event)
{
    Settings *instance = (Settings *)lv_event_get_user_data(event); // 获得this指针
/**
 * @brief Execute the LV_ASSERT_NULL operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param instance Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    LV_ASSERT_NULL(instance);

    lv_obj_t *obj = lv_event_get_current_target(event); // lv_event_get_current_target用于获取当前正在处理事件的目标对象
    lv_event_code_t code = lv_event_get_code(event);

    if (code == LV_EVENT_VALUE_CHANGED || LV_EVENT_CLICKED)
    {
        if (obj == lv_obj_get_child(instance->View.ui.wifiInfo.swAP, -1))
        {
            if (lv_obj_has_state(obj, LV_STATE_CHECKED))
            {
                instance->Model.SetAPEnable(true);
            }
            else
            {
                instance->Model.SetAPEnable(false);
            }
        }

        if (obj == lv_obj_get_child(instance->View.ui.wifiInfo.swSTA, -1))
        {
            if (lv_obj_has_state(obj, LV_STATE_CHECKED))
            {
                instance->Model.SetWiFiEnable(true);
            }
            else
            {
                instance->Model.SetWiFiEnable(false);
            }
        }
    }
}

/**
 * @brief Decode a UI or system event and forward it to the responsible model or view.
 * @details Event callbacks execute on the LVGL/UI context; they must remain short and defer blocking work to the corresponding data-processing task.
 * @param event Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void Settings::BLESwitchHandler(lv_event_t *event)
{
    Settings *instance = (Settings *)lv_event_get_user_data(event); // 获得this指针
/**
 * @brief Execute the LV_ASSERT_NULL operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param instance Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    LV_ASSERT_NULL(instance);

    lv_obj_t *obj = lv_event_get_current_target(event); // lv_event_get_current_target用于获取当前正在处理事件的目标对象
    lv_event_code_t code = lv_event_get_code(event);

    if (code == LV_EVENT_VALUE_CHANGED || LV_EVENT_CLICKED)
    {
        if (obj == lv_obj_get_child(instance->View.ui.bleInfo.sw , -1))
        {
            if (lv_obj_has_state(obj, LV_STATE_CHECKED))
            {
                instance->Model.SetBLEEnable(true);
            }
            else
            {
                instance->Model.SetBLEEnable(false);
            }
        }
    }
}

/**
 * @brief Decode a UI or system event and forward it to the responsible model or view.
 * @details Event callbacks execute on the LVGL/UI context; they must remain short and defer blocking work to the corresponding data-processing task.
 * @param event Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void Settings::DisplaySliderHandler(lv_event_t *event)
{
    Settings *instance = (Settings *)lv_event_get_user_data(event); // 获得this指针
/**
 * @brief Execute the LV_ASSERT_NULL operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param instance Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    LV_ASSERT_NULL(instance);

    lv_obj_t *obj = lv_event_get_current_target(event); // lv_event_get_current_target用于获取当前正在处理事件的目标对象
    lv_event_code_t code = lv_event_get_code(event);

    if (code == LV_EVENT_VALUE_CHANGED)
    {
        lv_indev_wait_release(lv_indev_get_act());

        if (obj == lv_obj_get_child(instance->View.ui.displayInfo.brig, -1))
        {
            instance->Model.SetDisplayBrightness(lv_slider_get_value(obj));
        }
    }
}

/**
 * @brief Decode a UI or system event and forward it to the responsible model or view.
 * @details Event callbacks execute on the LVGL/UI context; they must remain short and defer blocking work to the corresponding data-processing task.
 * @param event Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void Settings::PowerSwitchHandler(lv_event_t *event)
{
    Settings *instance = (Settings *)lv_event_get_user_data(event); // 获得this指针
/**
 * @brief Execute the LV_ASSERT_NULL operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param instance Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    LV_ASSERT_NULL(instance);

    lv_obj_t *obj = lv_event_get_current_target(event); // lv_event_get_current_target用于获取当前正在处理事件的目标对象
    lv_event_code_t code = lv_event_get_code(event);

    if (code == LV_EVENT_VALUE_CHANGED || LV_EVENT_CLICKED)
    {
        if (obj == lv_obj_get_child(instance->View.ui.powInfo.swAutoPowOff, -1))
        {
            if (lv_obj_has_state(obj, LV_STATE_CHECKED))
            {
                instance->Model.SetPowAutoOff(true);
            }
            else
            {
                instance->Model.SetPowAutoOff(false);
            }
        }
    }
}
