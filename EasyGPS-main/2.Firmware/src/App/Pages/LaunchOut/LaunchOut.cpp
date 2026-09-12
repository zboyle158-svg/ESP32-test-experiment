#include "LaunchOut.h"

using namespace Page;

/**
 * @brief Construct or destroy the LaunchOut object.
 * @return Operation result or status; inspect it before using dependent state.
 */
LaunchOut::LaunchOut()
{
}

/**
 * @brief Release resources owned by the LaunchOut object.
 * @return Operation result or status; inspect it before using dependent state.
 */
LaunchOut::~LaunchOut()
{
}

/**
 * @brief Execute the onCustomAttrConfig operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 */
void LaunchOut::onCustomAttrConfig()
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
    SetCustomCacheEnable(false);                        // 设置是否手动管理缓存
/**
 * @brief Change the CustomLoadAnimType configuration of the object.
 * @param LOAD_ANIM_NONE Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    SetCustomLoadAnimType(PageManager::LOAD_ANIM_NONE); // 设置自定义动画属性
}

/**
 * @brief Handle the onViewLoad page lifecycle callback.
 */
void LaunchOut::onViewLoad()
{
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
    lv_timer_t *timer = lv_timer_create(onTimer, 2500, this);
    lv_timer_set_repeat_count(timer, 1);
}

/**
 * @brief Handle the onViewDidLoad page lifecycle callback.
 */
void LaunchOut::onViewDidLoad()
{
}

/**
 * @brief Handle the onViewWillAppear page lifecycle callback.
 */
void LaunchOut::onViewWillAppear()
{
/**
 * @brief Execute the Model.PlayMusic operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Model.PlayMusic("Startup");
    lv_anim_timeline_set_reverse(View.ui.anim_timeline, false);
    lv_anim_timeline_start(View.ui.anim_timeline);
}

/**
 * @brief Handle the onViewDidAppear page lifecycle callback.
 */
void LaunchOut::onViewDidAppear()
{
    lv_obj_fade_out(_root, 500, 2000);
}

/**
 * @brief Handle the onViewWillDisappear page lifecycle callback.
 */
void LaunchOut::onViewWillDisappear()
{
}

/**
 * @brief Handle the onViewDidDisappear page lifecycle callback.
 */
void LaunchOut::onViewDidDisappear()
{
    // Model.SetStatusBarAppear(true);
}

/**
 * @brief Handle the onViewUnload page lifecycle callback.
 */
void LaunchOut::onViewUnload()
{
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
void LaunchOut::onViewDidUnload()
{
}

/**
 * @brief Process the periodic timer or FreeRTOS task callback.
 * @param timer Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void LaunchOut::onTimer(lv_timer_t *timer)
{                                                        // 2.5s定时，然后执行这个函数，实现页面跳转
    LaunchOut *instance = (LaunchOut *)timer->user_data; // 实例等于this //在onViewLoad里将this指针给了timer->user_data

    instance->_Manager->Replace("Pages/WaveTable"); //"Pages/Dialplate" "Pages/_Template"// 这个地方实现了启动界面后跳转到Dialplate界面
}

/**
 * @brief Decode a UI or system event and forward it to the responsible model or view.
 * @details Event callbacks execute on the LVGL/UI context; they must remain short and defer blocking work to the corresponding data-processing task.
 * @param event Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void LaunchOut::onEvent(lv_event_t *event)
{
    LaunchOut *instance = (LaunchOut *)lv_event_get_user_data(event);
/**
 * @brief Execute the LV_ASSERT_NULL operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param instance Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    LV_ASSERT_NULL(instance);

    lv_obj_t *obj = lv_event_get_current_target(event);
    lv_event_code_t code = lv_event_get_code(event);

    if (obj == instance->_root)
    {
        if (code == LV_EVENT_LEAVE)
        {
            // instance->Manager->Pop();
        }
    }
}
