#ifndef __DIALPLATE_PRESENTER_H
#define __DIALPLATE_PRESENTER_H

#include "DialplateView.h"
#include "DialplateModel.h"

namespace Page
{

    class Dialplate : public PageBase // public继承
    {
    public:
/**
 * @brief Construct or destroy the Dialplate object.
 * @return Operation result or status; inspect it before using dependent state.
 */
        Dialplate();          // 构造函数
/**
 * @brief Release resources owned by the Dialplate object.
 * @return Operation result or status; inspect it before using dependent state.
 */
        virtual ~Dialplate(); // 析构函数

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
        typedef enum
        {
            RECORD_STATE_READY,
            RECORD_STATE_RUN,
            RECORD_STATE_PAUSE,
            RECORD_STATE_STOP
/**
 * @brief Own and retain the RecordState_t state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        } RecordState_t;

    private:
/**
 * @brief Refresh the Dialplate state without blocking the scheduler.
 * @details The function consumes the latest cached DataProc/HAL snapshot and updates presentation state; it does not own or free the source data.
 */
        void Update();
/**
 * @brief Decode a UI or system event and forward it to the responsible model or view.
 * @details Event callbacks execute on the LVGL/UI context; they must remain short and defer blocking work to the corresponding data-processing task.
 * @param obj Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
        void AttachEvent(lv_obj_t *obj);
/**
 * @brief Refresh the Dialplate state without blocking the scheduler.
 * @details The function consumes the latest cached DataProc/HAL snapshot and updates presentation state; it does not own or free the source data.
 * @param timer Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
        static void onTimerUpdate(lv_timer_t *timer);
/**
 * @brief Decode a UI or system event and forward it to the responsible model or view.
 * @details Event callbacks execute on the LVGL/UI context; they must remain short and defer blocking work to the corresponding data-processing task.
 * @param event Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
        static void onEvent(lv_event_t *event);
/**
 * @brief Execute the onBtnClicked operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param btn Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
        void onBtnClicked(lv_obj_t *btn);
/**
 * @brief Execute the onRecord operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param longPress Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
        void onRecord(bool longPress);
/**
 * @brief Change the BtnRecImgSrc configuration of the object.
 * @param srcName Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
        void SetBtnRecImgSrc(const char *srcName);

    private:
/**
 * @brief Own and retain the View state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        DialplateView View;
/**
 * @brief Own and retain the Model state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        DialplateModel Model;
        lv_timer_t *timer;
/**
 * @brief Own and retain the recState state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        RecordState_t recState;
        lv_obj_t *lastFocus;
    };

}

#endif
