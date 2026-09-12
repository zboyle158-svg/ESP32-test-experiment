#include "SmartAssistant.h"

using namespace Page;

/**
 * @brief Construct or destroy the SmartAssistant object.
 * @return Operation result or status; inspect it before using dependent state.
 */
SmartAssistant::SmartAssistant()
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
 * @brief Release resources owned by the SmartAssistant object.
 * @return Operation result or status; inspect it before using dependent state.
 */
SmartAssistant::~SmartAssistant()
{
}

/**
 * @brief Execute the onCustomAttrConfig operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 */
void SmartAssistant::onCustomAttrConfig()
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
void SmartAssistant::onViewLoad()
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
    View.Create(_root);

/**
 * @brief Decode a UI or system event and forward it to the responsible model or view.
 * @details Event callbacks execute on the LVGL/UI context; they must remain short and defer blocking work to the corresponding data-processing task.
 * @return Operation result or status; inspect it before using dependent state.
 */
    AttachEvent(lv_scr_act());
/**
 * @brief Decode a UI or system event and forward it to the responsible model or view.
 * @details Event callbacks execute on the LVGL/UI context; they must remain short and defer blocking work to the corresponding data-processing task.
 * @param btn Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    AttachEvent(View.ui.btnCont.btn); // 添加事件回调
}

/**
 * @brief Handle the onViewDidLoad page lifecycle callback.
 */
void SmartAssistant::onViewDidLoad()
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
void SmartAssistant::onViewWillAppear()
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

    lv_group_set_wrap(group, false); // lv_group_set_wrap设置组对象的循环模式，以便在焦点移动时确定是否循环到组的开头，这对于导航控件和处理焦点移动时的行为非常有用

/**
 * @brief Execute the Model.SetStatusBarStyle operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param STATUS_BAR_STYLE_TRANSP Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Model.SetStatusBarStyle(DataProc::STATUS_BAR_STYLE_TRANSP); // transparent 透明的清澈的

/**
 * @brief Refresh the SmartAssistant state without blocking the scheduler.
 * @details The function consumes the latest cached DataProc/HAL snapshot and updates presentation state; it does not own or free the source data.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Update(); // 刷新，第一次加载界面，需要刷新一下，不然数值不显示会卡一下才显示

    lv_obj_fade_in(_root, 350, 0);
/**
 * @brief Execute the View.AppearAnimStart operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    View.AppearAnimStart(); // 开始加载进入该page的动画，出场动画 // 填flase是动画正着放，true是反着放
}

/**
 * @brief Handle the onViewDidAppear page lifecycle callback.
 */
void SmartAssistant::onViewDidAppear()
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
void SmartAssistant::onViewWillDisappear()
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

    lv_timer_del(timer); // 删除该页面的软定时器
}

/**
 * @brief Handle the onViewDidDisappear page lifecycle callback.
 */
void SmartAssistant::onViewDidDisappear()
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
void SmartAssistant::onViewUnload()
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
    View.Delete(); // 删除该页面的UI指针，释放容器的内存
/**
 * @brief Execute the Model.Deinit operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Model.Deinit();

    lv_obj_remove_event_cb(lv_scr_act(), onEvent); // 移除屏幕手势回调函数
}

/**
 * @brief Handle the onViewDidUnload page lifecycle callback.
 */
void SmartAssistant::onViewDidUnload()
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
void SmartAssistant::AttachEvent(lv_obj_t *obj)
{
    lv_obj_add_event_cb(obj, onEvent, LV_EVENT_ALL, this);
}

/**
 * @brief Refresh the SmartAssistant state without blocking the scheduler.
 * @details The function consumes the latest cached DataProc/HAL snapshot and updates presentation state; it does not own or free the source data.
 */
void SmartAssistant::Update()
{
    // LV_LOG_USER("Hi!\n");
/**
 * @brief Own and retain the SaaInputText state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    char SaaInputText[128] = {0};
/**
 * @brief Own and retain the SaaOutputText state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    char SaaOutputText[256] = {0};
/**
 * @brief Own and retain the SaaIsRunning state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    bool SaaIsRunning = false;
/**
 * @brief Own and retain the SaaIsListening state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    bool SaaIsListening = false;

/**
 * @brief Execute the Model.GetSmartAssistantInfo operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param SaaInputText Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param SaaOutputText Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param SaaIsRunning Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param SaaIsListening Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Model.GetSmartAssistantInfo(SaaInputText, SaaOutputText, &SaaIsRunning, &SaaIsListening);
    if (SaaIsRunning == true)
    {
        if (strcmp(SaaInputText, "none") == 0)
            // lv_label_set_text(View.ui.labelCont.inputText, "Q: ..");
            lv_label_set_text(View.ui.labelCont.inputText, "Q: 请你按下按钮对着麦克风提问吧.");
        else
        {
            lv_label_set_text_fmt(View.ui.labelCont.inputText, "Q: %s", SaaInputText);
        }

        if (strcmp(SaaOutputText, "none") == 0)
            // lv_label_set_text(View.ui.labelCont.outputText, "A: ..");
            lv_label_set_text(View.ui.labelCont.outputText, "A: 还没有得到回答呢.");
        else
        {
            lv_label_set_text_fmt(View.ui.labelCont.outputText, "A: %s", SaaOutputText);
        }

        if (SaaIsListening)
            lv_label_set_text_fmt(View.ui.labelCont.label, "%s", "I'M LISTENING...");
        else
            lv_label_set_text_fmt(View.ui.labelCont.label, "%s", "THINKING...");
    }
    else if (SaaIsRunning == false)
    {
        lv_label_set_text_fmt(View.ui.labelCont.label, "%s", "CLICK IT!");

        // 将按键使能，可以再次点击
        lv_obj_clear_state(View.ui.btnCont.btn, LV_STATE_DISABLED);
        // lv_label_set_text(View.ui.labelCont.inputText, "Q: ..");
        // lv_label_set_text(View.ui.labelCont.outputText, "A: ..");
    }
}

/**
 * @brief Refresh the SmartAssistant state without blocking the scheduler.
 * @details The function consumes the latest cached DataProc/HAL snapshot and updates presentation state; it does not own or free the source data.
 * @param timer Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void SmartAssistant::onTimerUpdate(lv_timer_t *timer)
{
    SmartAssistant *instance = (SmartAssistant *)timer->user_data;

    instance->Update();
}

/**
 * @brief Decode a UI or system event and forward it to the responsible model or view.
 * @details Event callbacks execute on the LVGL/UI context; they must remain short and defer blocking work to the corresponding data-processing task.
 * @param event Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void SmartAssistant::onEvent(lv_event_t *event)
{
    SmartAssistant *instance = (SmartAssistant *)lv_event_get_user_data(event);
/**
 * @brief Execute the LV_ASSERT_NULL operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param instance Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    LV_ASSERT_NULL(instance);

    lv_obj_t *obj = lv_event_get_current_target(event);
    lv_event_code_t code = lv_event_get_code(event);

    if (code == LV_EVENT_SHORT_CLICKED)
    {
        if (obj == instance->View.ui.btnCont.btn)
        {

            instance->Model.SetSmartAssistantBegin(true);

            lv_label_set_text_fmt(instance->View.ui.labelCont.label, "%s", "I'M LISTENING...");
            instance->View.AppearAnimClick();

            // 将按钮锁定，防止多次点击
            lv_obj_add_state(instance->View.ui.btnCont.btn, LV_STATE_DISABLED);
        }
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
