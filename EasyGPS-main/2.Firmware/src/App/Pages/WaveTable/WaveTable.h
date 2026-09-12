#ifndef __WAVETABLE_PRESENTER_H
#define __WAVETABLE_PRESENTER_H

#include "WaveTableView.h"
#include "WaveTableModel.h"

namespace Page
{

    class WaveTable : public PageBase
    {
    public:
/**
 * @brief Construct or destroy the WaveTable object.
 * @return Operation result or status; inspect it before using dependent state.
 */
        WaveTable();
/**
 * @brief Release resources owned by the WaveTable object.
 * @return Operation result or status; inspect it before using dependent state.
 */
        virtual ~WaveTable();

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
 * @brief Refresh the WaveTable state without blocking the scheduler.
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
 * @brief Refresh the WaveTable state without blocking the scheduler.
 * @details The function consumes the latest cached DataProc/HAL snapshot and updates presentation state; it does not own or free the source data.
 * @param timer Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
        static void onTimerUpdate(lv_timer_t *timer);
/**
 * @brief Execute the scrollEventCallback operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param e Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
        static void scrollEventCallback(lv_event_t *e);
/**
 * @brief Decode a UI or system event and forward it to the responsible model or view.
 * @details Event callbacks execute on the LVGL/UI context; they must remain short and defer blocking work to the corresponding data-processing task.
 * @param event Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
        static void onEvent(lv_event_t *event);

    private:
/**
 * @brief Own and retain the View state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        WaveTableView View;
/**
 * @brief Own and retain the Model state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        WaveTableModel Model;
        lv_timer_t *timer;
    };

}

#endif
