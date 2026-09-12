#include "WaveTable.h"

using namespace Page;

/**
 * @brief Construct or destroy the WaveTable object.
 * @return Operation result or status; inspect it before using dependent state.
 */
WaveTable::WaveTable()
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
 * @brief Release resources owned by the WaveTable object.
 * @return Operation result or status; inspect it before using dependent state.
 */
WaveTable::~WaveTable()
{
}

/**
 * @brief Execute the onCustomAttrConfig operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 */
void WaveTable::onCustomAttrConfig()
{
/**
 * @brief Execute the LV_LOG_USER operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    LV_LOG_USER("onCustomAttrConfig");
    // SetCustomCacheEnable(true);
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
void WaveTable::onViewLoad()
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

    lv_obj_add_event_cb(View.ui.cont, scrollEventCallback, LV_EVENT_SCROLL, NULL); // 滚动界面时使用回调函数
    /* Update the buttons position manually for first */
    lv_event_send(View.ui.cont, LV_EVENT_SCROLL, NULL);
    /* Be sure the fist button is in the middle */
    lv_obj_scroll_to_view(lv_obj_get_child(View.ui.cont, 1), LV_ANIM_ON);

/**
 * @brief Decode a UI or system event and forward it to the responsible model or view.
 * @details Event callbacks execute on the LVGL/UI context; they must remain short and defer blocking work to the corresponding data-processing task.
 * @param btn Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    AttachEvent(View.ui.btnA.btn); // 添加事件回调
/**
 * @brief Decode a UI or system event and forward it to the responsible model or view.
 * @details Event callbacks execute on the LVGL/UI context; they must remain short and defer blocking work to the corresponding data-processing task.
 * @param btn Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    AttachEvent(View.ui.btnB.btn); // 添加事件回调 
/**
 * @brief Decode a UI or system event and forward it to the responsible model or view.
 * @details Event callbacks execute on the LVGL/UI context; they must remain short and defer blocking work to the corresponding data-processing task.
 * @param btn Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    AttachEvent(View.ui.btnC.btn); // 添加事件回调
/**
 * @brief Decode a UI or system event and forward it to the responsible model or view.
 * @details Event callbacks execute on the LVGL/UI context; they must remain short and defer blocking work to the corresponding data-processing task.
 * @param btn Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    AttachEvent(View.ui.btnD.btn); // 添加事件回调
/**
 * @brief Decode a UI or system event and forward it to the responsible model or view.
 * @details Event callbacks execute on the LVGL/UI context; they must remain short and defer blocking work to the corresponding data-processing task.
 * @param btn Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    AttachEvent(View.ui.btnE.btn); // 添加事件回调
/**
 * @brief Decode a UI or system event and forward it to the responsible model or view.
 * @details Event callbacks execute on the LVGL/UI context; they must remain short and defer blocking work to the corresponding data-processing task.
 * @param btn Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    AttachEvent(View.ui.btnF.btn); // 添加事件回调
/**
 * @brief Decode a UI or system event and forward it to the responsible model or view.
 * @details Event callbacks execute on the LVGL/UI context; they must remain short and defer blocking work to the corresponding data-processing task.
 * @param btn Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    AttachEvent(View.ui.btnG.btn); // 添加事件回调
}

/**
 * @brief Handle the onViewDidLoad page lifecycle callback.
 */
void WaveTable::onViewDidLoad()
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
void WaveTable::onViewWillAppear()
{
/**
 * @brief Execute the LV_LOG_USER operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    LV_LOG_USER("onViewWillAppear");

    lv_group_t *group = lv_group_get_default(); // 用于获取LittlevGL中默认的组对象
/**
 * @brief Execute the LV_ASSERT_NULL operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param group Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    LV_ASSERT_NULL(group);

    lv_group_focus_obj(View.ui.cont);
    // lv_group_set_wrap(group, false); // lv_group_set_wrap设置组对象的循环模式，以便在焦点移动时确定是否循环到组的开头，这对于导航控件和处理焦点移动时的行为非常有用

/**
 * @brief Execute the Model.SetStatusBarAppear operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param false Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Model.SetStatusBarAppear(false);

/**
 * @brief Execute the Model.SetStatusBarStyle operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param STATUS_BAR_STYLE_TRANSP Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Model.SetStatusBarStyle(DataProc::STATUS_BAR_STYLE_TRANSP); // transparent 透明的清澈的
    
/**
 * @brief Refresh the WaveTable state without blocking the scheduler.
 * @details The function consumes the latest cached DataProc/HAL snapshot and updates presentation state; it does not own or free the source data.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Update(); // 刷新，第一次加载界面，需要刷新一下，不然数值不显示会卡一下才显示

    lv_obj_fade_in(_root, 350, 0);

    // View.AppearAnimStart(); // 开始加载进入该page的动画，出场动画 // 填flase是动画正着放，true是反着放
}

/**
 * @brief Handle the onViewDidAppear page lifecycle callback.
 */
void WaveTable::onViewDidAppear()
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
void WaveTable::onViewWillDisappear()
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

    lv_obj_fade_out(_root, 350, 0);
}

/**
 * @brief Handle the onViewDidDisappear page lifecycle callback.
 */
void WaveTable::onViewDidDisappear()
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
void WaveTable::onViewUnload()
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
}

/**
 * @brief Handle the onViewDidUnload page lifecycle callback.
 */
void WaveTable::onViewDidUnload()
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
void WaveTable::AttachEvent(lv_obj_t *obj)
{
    lv_obj_add_event_cb(obj, onEvent, LV_EVENT_ALL, this);
}

/**
 * @brief Refresh the WaveTable state without blocking the scheduler.
 * @details The function consumes the latest cached DataProc/HAL snapshot and updates presentation state; it does not own or free the source data.
 */
void WaveTable::Update()
{
/**
 * @brief Execute the LV_LOG_USER operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    LV_LOG_USER("Hi!\n");
}

/**
 * @brief Refresh the WaveTable state without blocking the scheduler.
 * @details The function consumes the latest cached DataProc/HAL snapshot and updates presentation state; it does not own or free the source data.
 * @param timer Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void WaveTable::onTimerUpdate(lv_timer_t *timer)
{
    WaveTable *instance = (WaveTable *)timer->user_data;

    instance->Update();
}

/**
 * @brief Execute the scrollEventCallback operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param e Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void WaveTable::scrollEventCallback(lv_event_t *e)
{
    lv_obj_t *cont = lv_event_get_target(e);

/**
 * @brief Own and retain the cont_a state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    lv_area_t cont_a;
    lv_obj_get_coords(cont, &cont_a); // 获得画布坐标
    lv_coord_t cont_y_center = cont_a.y1 + lv_area_get_height(&cont_a) / 2;

    lv_coord_t r = lv_obj_get_height(cont) * 7 / 10; // 计算半径
/**
 * @brief Own and retain the i state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    uint32_t i;
    uint32_t child_cnt = lv_obj_get_child_cnt(cont); // 获得画布子对象的个数
    for (i = 0; i < child_cnt; i++)
    {
        lv_obj_t *child = lv_obj_get_child(cont, i); // 获得画布子对象
/**
 * @brief Own and retain the child_a state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        lv_area_t child_a;
        lv_obj_get_coords(child, &child_a); // 获得子对象坐标

        lv_coord_t child_y_center = child_a.y1 + lv_area_get_height(&child_a) / 2;

/**
 * @brief Own and retain the diff_y state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        lv_coord_t diff_y = child_y_center - cont_y_center;
/**
 * @brief Execute the LV_ABS operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param diff_y Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
        diff_y = LV_ABS(diff_y); // 求绝对值

        /*Get the x of diff_y on a circle.*/
/**
 * @brief Own and retain the x state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        lv_coord_t x;
        /*If diff_y is out of the circle use the last point of the circle (the radius)*/
        if (diff_y >= r)
        {
            x = r;
        }
        else
        {
            /*Use Pythagoras theorem to get x from radius and y*/
/**
 * @brief Own and retain the x_sqr state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
            uint32_t x_sqr = r * r - diff_y * diff_y;
/**
 * @brief Own and retain the res state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
            lv_sqrt_res_t res;
            lv_sqrt(x_sqr, &res, 0x8000); /*Use lvgl's built in sqrt root function*/
            x = r - res.i;
        }

        /*Translate the item by the calculated X coordinate*/
        lv_obj_set_style_translate_x(child, x, 0); // 移动子对象

        /*Use some opacity with larger translations*/
        // lv_opa_t opa = lv_map(x, 0, r, LV_OPA_TRANSP, LV_OPA_COVER); // 根据移动的程度修改子对象的透明度
        // lv_obj_set_style_opa(child, LV_OPA_COVER - opa, 0);
    }
}

/**
 * @brief Decode a UI or system event and forward it to the responsible model or view.
 * @details Event callbacks execute on the LVGL/UI context; they must remain short and defer blocking work to the corresponding data-processing task.
 * @param event Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void WaveTable::onEvent(lv_event_t *event)
{
    WaveTable *instance = (WaveTable *)lv_event_get_user_data(event);
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
        if (obj == instance->View.ui.btnA.btn)
        {
            if (lv_obj_has_state(obj, LV_STATE_FOCUSED))
            {
                instance->_Manager->Push("Pages/SystemInfos"); //"Pages/Dialplate"
            }
        }
        else if (obj == instance->View.ui.btnB.btn)
        {
            if (lv_obj_has_state(obj, LV_STATE_FOCUSED))
            {
                instance->_Manager->Push("Pages/Dialplate"); //"Pages/Dialplate"
            }
        }
        else if (obj == instance->View.ui.btnC.btn)
        {
            if (lv_obj_has_state(obj, LV_STATE_FOCUSED))
            {
                instance->_Manager->Push("Pages/Settings"); //"Pages/Dialplate"
            }
        }
        else if (obj == instance->View.ui.btnD.btn)
        {
            if (lv_obj_has_state(obj, LV_STATE_FOCUSED))
            {
                instance->_Manager->Push("Pages/Popcat"); 
            }
        }
        else if (obj == instance->View.ui.btnE.btn)
        {
            if (lv_obj_has_state(obj, LV_STATE_FOCUSED))
            {
                instance->_Manager->Push("Pages/SmartAssistant");
            }
        }
        else if (obj == instance->View.ui.btnF.btn)
        {
            if (lv_obj_has_state(obj, LV_STATE_FOCUSED))
            {
                instance->_Manager->Push("Pages/Compass");
            }
        }
        else if (obj == instance->View.ui.btnG.btn)
        {
            if (lv_obj_has_state(obj, LV_STATE_FOCUSED))
            {
                instance->_Manager->Push("Pages/BLEKeyboard");
            }
        }
    }
}
