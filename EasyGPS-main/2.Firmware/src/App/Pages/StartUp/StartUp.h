#ifndef __STARTUP_PRESENTER_H
#define __STARTUP_PRESENTER_H

#include "StartUpView.h"
#include "StartUpModel.h"

namespace Page
{

class Startup : public PageBase
{
public:

public:
/**
 * @brief Execute the Startup operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Startup();
/**
 * @brief Execute the ~Startup operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    virtual ~Startup();

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
 * @brief Process the periodic timer or FreeRTOS task callback.
 * @param timer Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
    static void onTimer(lv_timer_t* timer);
/**
 * @brief Decode a UI or system event and forward it to the responsible model or view.
 * @details Event callbacks execute on the LVGL/UI context; they must remain short and defer blocking work to the corresponding data-processing task.
 * @param event Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
    static void onEvent(lv_event_t* event);

private:
/**
 * @brief Own and retain the View state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    StartupView View;
/**
 * @brief Own and retain the Model state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    StartupModel Model;
};

}

#endif
