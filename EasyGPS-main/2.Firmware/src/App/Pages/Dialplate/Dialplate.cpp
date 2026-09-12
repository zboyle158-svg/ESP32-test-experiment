#include "Dialplate.h"
#include "HardwareSerial.h"
using namespace Page;

/**
 * @brief Construct or destroy the Dialplate object.
 * @return Operation result or status; inspect it before using dependent state.
 */
Dialplate::Dialplate()
/**
 * @brief Execute the recState operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param RECORD_STATE_READY Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    : recState(RECORD_STATE_READY) // 记录当前列表的运行状态
      ,
      lastFocus(nullptr) 
{
}

/**
 * @brief Release resources owned by the Dialplate object.
 * @return Operation result or status; inspect it before using dependent state.
 */
Dialplate::~Dialplate()
{
}

/**
 * @brief Execute the onCustomAttrConfig operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 */
void Dialplate::onCustomAttrConfig()
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
void Dialplate::onViewLoad() // 该页面page的UI加载初始化
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

/**
 * @brief Decode a UI or system event and forward it to the responsible model or view.
 * @details Event callbacks execute on the LVGL/UI context; they must remain short and defer blocking work to the corresponding data-processing task.
 * @return Operation result or status; inspect it before using dependent state.
 */
    AttachEvent(lv_scr_act());
/**
 * @brief Decode a UI or system event and forward it to the responsible model or view.
 * @details Event callbacks execute on the LVGL/UI context; they must remain short and defer blocking work to the corresponding data-processing task.
 * @param btnMap Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    AttachEvent(View.ui.btnCont.btnMap); // 添加事件回调 // 三个button
/**
 * @brief Decode a UI or system event and forward it to the responsible model or view.
 * @details Event callbacks execute on the LVGL/UI context; they must remain short and defer blocking work to the corresponding data-processing task.
 * @param btnRec Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    AttachEvent(View.ui.btnCont.btnRec);
/**
 * @brief Decode a UI or system event and forward it to the responsible model or view.
 * @details Event callbacks execute on the LVGL/UI context; they must remain short and defer blocking work to the corresponding data-processing task.
 * @param btnMenu Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    AttachEvent(View.ui.btnCont.btnMenu);
}

/**
 * @brief Handle the onViewDidLoad page lifecycle callback.
 */
void Dialplate::onViewDidLoad() // 该页面page的UI结束加载初始化
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
void Dialplate::onViewWillAppear() // 该页面page的UI开始出场动画
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

    lv_group_add_obj(group, View.ui.btnCont.btnMap); // lv_group_add_obj用于向组对象中添加控件，这样组对象就可以管理该控件的交互和事件处理
    lv_group_add_obj(group, View.ui.btnCont.btnRec);
    lv_group_add_obj(group, View.ui.btnCont.btnMenu);

    // if (lastFocus)
    // {
    //     lv_group_focus_obj(lastFocus); // lv_group_focus_obj用于设置组对象中的焦点控件 // 相当于选择吧，选择这个按钮时，会出现某些变化
    // }
    // else
    // {
    //     lv_group_focus_obj(View.ui.btnCont.btnMap); // lastFocus==NULL的时候，刚刚开机时，聚焦在中间的播放键（是播放键吧，记录键？hh
    // }

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
 * @brief Refresh the Dialplate state without blocking the scheduler.
 * @details The function consumes the latest cached DataProc/HAL snapshot and updates presentation state; it does not own or free the source data.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Update(); // 刷新，第一次加载界面，需要刷新一下，不然数值不显示会卡一下才显示

/**
 * @brief Execute the View.AppearAnimStart operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    View.AppearAnimStart(); // 开始加载进入该page的动画，出场动画
}

/**
 * @brief Handle the onViewDidAppear page lifecycle callback.
 */
void Dialplate::onViewDidAppear() // 该页面page的UI结束出场动画
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
void Dialplate::onViewWillDisappear() // 该页面page的UI开始退场动画
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
    // lastFocus = lv_group_get_focused(group);
    lv_group_remove_all_objs(group);
    
    lv_timer_del(timer);
}

/**
 * @brief Handle the onViewDidDisappear page lifecycle callback.
 */
void Dialplate::onViewDidDisappear() // 该页面page的UI结束退场动画
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
void Dialplate::onViewUnload()
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
void Dialplate::onViewDidUnload()
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
void Dialplate::AttachEvent(lv_obj_t *obj)
{
    lv_obj_add_event_cb(obj, onEvent, LV_EVENT_ALL, this); // 这里也把this指针交给了onEvent->user_data，方便回调
}

/**
 * @brief Refresh the Dialplate state without blocking the scheduler.
 * @details The function consumes the latest cached DataProc/HAL snapshot and updates presentation state; it does not own or free the source data.
 */
void Dialplate::Update()
{
/**
 * @brief Own and retain the buf state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    char buf[16];
    lv_label_set_text_fmt(View.ui.topInfo.labelSpeed, "%02d", (int)Model.GetSpeed());

    lv_label_set_text_fmt(View.ui.bottomInfo.labelInfoGrp[0].lableValue, "%0.1f km/h", Model.GetAvgSpeed());
    lv_label_set_text(
        View.ui.bottomInfo.labelInfoGrp[1].lableValue,
/**
 * @brief Execute the MakeTimeString operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param singleTime Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param buf Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
        DataProc::MakeTimeString(Model.sportStatusInfo.singleTime, buf, sizeof(buf)));
    lv_label_set_text_fmt(
        View.ui.bottomInfo.labelInfoGrp[2].lableValue,
        "%0.1f km",
        Model.sportStatusInfo.singleDistance / 1000);
    lv_label_set_text_fmt(
        View.ui.bottomInfo.labelInfoGrp[3].lableValue,
        "%d k",
        int(Model.sportStatusInfo.singleCalorie));
}

/**
 * @brief Refresh the Dialplate state without blocking the scheduler.
 * @details The function consumes the latest cached DataProc/HAL snapshot and updates presentation state; it does not own or free the source data.
 * @param timer Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void Dialplate::onTimerUpdate(lv_timer_t *timer)
{
    Dialplate *instance = (Dialplate *)timer->user_data;

    instance->Update();
}

/**
 * @brief Execute the onBtnClicked operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param btn Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void Dialplate::onBtnClicked(lv_obj_t *btn) // 另外两粒button的回调
{
    if (btn == View.ui.btnCont.btnMap)
    {
        if (lv_obj_has_state(btn, LV_STATE_FOCUSED))
        {
            // _Manager->Pop(); // 将Pages/LiveMap从池中推到栈顶，同时调用了SwitchTo,切换页面到Pages/LiveMap
            _Manager->Push("Pages/LiveMap"); // "Pages/LiveMap"
        }                    
    }
    else if (btn == View.ui.btnCont.btnMenu)
    {
        _Manager->Push("Pages/SystemInfos");
    }
}

/**
 * @brief Execute the onRecord operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param longPress Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void Dialplate::onRecord(bool longPress) // Rec_button的回调
{
    switch (recState)
    {
    case RECORD_STATE_READY:
        if (longPress)
        {
            if (!Model.GetGPSReady())
            {
/**
 * @brief Execute the LV_LOG_WARN operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param ready Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
                LV_LOG_WARN("GPS has not ready, can't start record");
                // Model.PlayMusic("Error");
                // return;
            }

            // Model.PlayMusic("Connect");
/**
 * @brief Execute the Model.RecorderCommand operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param REC_START Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
            Model.RecorderCommand(Model.REC_START);
/**
 * @brief Change the BtnRecImgSrc configuration of the object.
 * @return Operation result or status; inspect it before using dependent state.
 */
            SetBtnRecImgSrc("pause");
            recState = RECORD_STATE_RUN;
        }
        break;
    case RECORD_STATE_RUN:
        if (!longPress)
        {
            // Model.PlayMusic("UnstableConnect");
/**
 * @brief Execute the Model.RecorderCommand operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param REC_PAUSE Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
            Model.RecorderCommand(Model.REC_PAUSE);
/**
 * @brief Change the BtnRecImgSrc configuration of the object.
 * @return Operation result or status; inspect it before using dependent state.
 */
            SetBtnRecImgSrc("start");
            recState = RECORD_STATE_PAUSE;
        }
        break;
    case RECORD_STATE_PAUSE:
        if (longPress)
        {
            // Model.PlayMusic("NoOperationWarning");
/**
 * @brief Change the BtnRecImgSrc configuration of the object.
 * @return Operation result or status; inspect it before using dependent state.
 */
            SetBtnRecImgSrc("stop");
/**
 * @brief Execute the Model.RecorderCommand operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param REC_READY_STOP Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
            Model.RecorderCommand(Model.REC_READY_STOP);
            recState = RECORD_STATE_STOP;
        }
        else
        {
            // Model.PlayMusic("Connect");
/**
 * @brief Execute the Model.RecorderCommand operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param REC_CONTINUE Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
            Model.RecorderCommand(Model.REC_CONTINUE);
/**
 * @brief Change the BtnRecImgSrc configuration of the object.
 * @return Operation result or status; inspect it before using dependent state.
 */
            SetBtnRecImgSrc("pause");
            recState = RECORD_STATE_RUN;
        }
        break;
    case RECORD_STATE_STOP:
        if (longPress)
        {
            // Model.PlayMusic("Disconnect");
/**
 * @brief Execute the Model.RecorderCommand operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param REC_STOP Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
            Model.RecorderCommand(Model.REC_STOP);
/**
 * @brief Change the BtnRecImgSrc configuration of the object.
 * @return Operation result or status; inspect it before using dependent state.
 */
            SetBtnRecImgSrc("start");
            recState = RECORD_STATE_READY;
        }
        else
        {
            // Model.PlayMusic("Connect");
/**
 * @brief Execute the Model.RecorderCommand operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param REC_CONTINUE Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
            Model.RecorderCommand(Model.REC_CONTINUE);
/**
 * @brief Change the BtnRecImgSrc configuration of the object.
 * @return Operation result or status; inspect it before using dependent state.
 */
            SetBtnRecImgSrc("pause");
            recState = RECORD_STATE_RUN;
        }
        break;
    default:
        break;
    }
}

/**
 * @brief Change the BtnRecImgSrc configuration of the object.
 * @param srcName Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void Dialplate::SetBtnRecImgSrc(const char *srcName) // 设置Rec_button的图标，区分start和stop两种状态（？是两种吧，反正没差
{
    lv_obj_set_style_bg_img_src(View.ui.btnCont.btnRec, ResourcePool::GetImage(srcName), 0); // lv_obj_set_style_bg_img_src用于设置对象的背景图像样式。通过这个函数，可以为指定的对象设置背景图像的来源，即指定要显示的图像。
}

/**
 * @brief Decode a UI or system event and forward it to the responsible model or view.
 * @details Event callbacks execute on the LVGL/UI context; they must remain short and defer blocking work to the corresponding data-processing task.
 * @param event Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void Dialplate::onEvent(lv_event_t *event)
{
    Dialplate *instance = (Dialplate *)lv_event_get_user_data(event); // 获得this指针
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
        instance->onBtnClicked(obj);
    }

    if (obj == instance->View.ui.btnCont.btnRec)
    {
        if (code == LV_EVENT_SHORT_CLICKED) // 区分长短按
        {
            // instance->_Manager->Push("Pages/Popcat");
            instance->onRecord(false);
        }
        else if (code == LV_EVENT_LONG_PRESSED)
        {
            instance->onRecord(true);
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
