#include "Compass.h"

using namespace Page;

/**
 * @brief Construct or destroy the Compass object.
 * @return Operation result or status; inspect it before using dependent state.
 */
Compass::Compass()
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
 * @brief Release resources owned by the Compass object.
 * @return Operation result or status; inspect it before using dependent state.
 */
Compass::~Compass()
{
}

/**
 * @brief Execute the onCustomAttrConfig operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 */
void Compass::onCustomAttrConfig()
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
void Compass::onViewLoad()
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
void Compass::onViewDidLoad()
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
void Compass::onViewWillAppear()
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

/**
 * @brief Execute the Model.SetStatusBarStyle operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param STATUS_BAR_STYLE_TRANSP Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Model.SetStatusBarStyle(DataProc::STATUS_BAR_STYLE_TRANSP); // transparent 透明的清澈的

/**
 * @brief Refresh the Compass state without blocking the scheduler.
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
void Compass::onViewDidAppear()
{
/**
 * @brief Execute the LV_LOG_USER operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    LV_LOG_USER("onViewDidAppear");
    timer = lv_timer_create(onTimerUpdate, 100, this); // 这里设置一个1s的定时器，软定时器，用于在onTimerUpdate里update
}

/**
 * @brief Handle the onViewWillDisappear page lifecycle callback.
 */
void Compass::onViewWillDisappear()
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
void Compass::onViewDidDisappear()
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
void Compass::onViewUnload()
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
void Compass::onViewDidUnload()
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
void Compass::AttachEvent(lv_obj_t *obj)
{
    lv_obj_add_event_cb(obj, onEvent, LV_EVENT_ALL, this);
}

/**
 * @brief Refresh the Compass state without blocking the scheduler.
 * @details The function consumes the latest cached DataProc/HAL snapshot and updates presentation state; it does not own or free the source data.
 */
void Compass::Update()
{
/**
 * @brief Execute the LV_LOG_USER operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    LV_LOG_USER("Hi!\n");

    /* MAG */
/**
 * @brief Own and retain the angleLast state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    static int16_t angleLast = 0;
/**
 * @brief Own and retain the angle state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    int angle = 0;
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
 * @brief Own and retain the isCalibrated state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    bool isCalibrated = false;

/**
 * @brief Execute the Model.GetMAGInfo operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param angle Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param x Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param y Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param z Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param isCalibrated Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Model.GetMAGInfo(&angle, &x, &y, &z, &isCalibrated);

    // 如果校准成功
    if (isCalibrated)
    {
        lv_obj_move_background(View.ui.btnCont.cont);
        if (angleLast < angle)
        {
/**
 * @brief Own and retain the tmp state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
            int16_t tmp = angle - angleLast;

            if (tmp < 180)
            {
/**
 * @brief Own and retain the cnt state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
                int16_t cnt = tmp / 10;
                if (tmp == 0)
                    tmp++;
                angleLast += cnt;
            }
            else
            {
                tmp = 180 + 179 - angle + angleLast;
/**
 * @brief Own and retain the cnt state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
                int16_t cnt = tmp / 10;
                if (tmp == 0)
                    tmp++;
                angleLast -= cnt;
            }
        }
        else
        {
/**
 * @brief Own and retain the tmp state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
            int16_t tmp = angleLast - angle;
            if (tmp < 180)
            {
/**
 * @brief Own and retain the cnt state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
                int16_t cnt = tmp / 10;
                angleLast -= cnt;
            }
            else
            {
                tmp = 180 + 179 + angle - angleLast;
/**
 * @brief Own and retain the cnt state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
                int16_t cnt = tmp / 10;
                if (tmp == 0)
                    tmp++;
                angleLast += cnt;
            }
        }

        if (angleLast > 180)
            angleLast = -179 + (angleLast - 180);
        if (angleLast < -179)
            angleLast = 180 - (-179 - angleLast);

        lv_img_set_angle(View.ui.mainCont.img,  angleLast * 10);

/**
 * @brief Own and retain the tmp state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        uint8_t tmp = 0;
        if (angleLast < 157)
            tmp = 0;
        else if (angleLast < 112)
            tmp = 1;
        else if (angleLast < 67)
            tmp = 2;
        else if (angleLast < 22)
            tmp = 3;
        else if (angleLast < -22)
            tmp = 4;
        else if (angleLast < -67)
            tmp = 5;
        else if (angleLast < -112)
            tmp = 6;
        else if (angleLast < -157)
            tmp = 7;
        else
            tmp = 7;

/**
 * @brief Own and retain the angle_t state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        int16_t angle_t = angleLast;
        if (angle_t < 0)
            angle_t += 360;
        angle_t = -angle_t + 360;

        lv_label_set_text_fmt(View.ui.mainCont.label[label_angle], rotation_ch[tmp], angle_t);
    }
}

/**
 * @brief Refresh the Compass state without blocking the scheduler.
 * @details The function consumes the latest cached DataProc/HAL snapshot and updates presentation state; it does not own or free the source data.
 * @param timer Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void Compass::onTimerUpdate(lv_timer_t *timer)
{
    Compass *instance = (Compass *)timer->user_data;

    instance->Update();
}

/**
 * @brief Decode a UI or system event and forward it to the responsible model or view.
 * @details Event callbacks execute on the LVGL/UI context; they must remain short and defer blocking work to the corresponding data-processing task.
 * @param event Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void Compass::onEvent(lv_event_t *event)
{
    Compass *instance = (Compass *)lv_event_get_user_data(event);
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
            lv_label_set_text_fmt(instance->View.ui.btnCont.label, "%s", "开始校准");
            instance->View.AppearAnimClick();
            instance->Model.SetMAGCalibration();
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
