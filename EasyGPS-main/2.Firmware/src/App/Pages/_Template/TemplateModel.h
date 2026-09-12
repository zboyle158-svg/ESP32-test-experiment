#ifndef __TEMPLATE_MODEL_H
#define __TEMPLATE_MODEL_H

#include "App/Common/DataProc/DataProc.h"
#include "lvgl.h"

namespace Page
{

class TemplateModel
{
public:
/**
 * @brief Own and retain the TickSave state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    uint32_t TickSave;
/**
 * @brief Read Data from the current object state.
 * @return Operation result or status; inspect it before using dependent state.
 */
    uint32_t GetData();
public:
/**
 * @brief Initialize TemplateModel state and hardware or data resources.
 */
    void Init();
/**
 * @brief Release or reset resources managed by TemplateModel.
 */
    void Deinit();

/**
 * @brief Change the StatusBarStyle configuration of the object.
 * @param style Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
    void SetStatusBarStyle(DataProc::StatusBar_Style_t style);
/**
 * @brief Change the StatusBarAppear configuration of the object.
 * @param en Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
    void SetStatusBarAppear(bool en);

private:
    Account *account;

private:
/**
 * @brief Decode a UI or system event and forward it to the responsible model or view.
 * @details Event callbacks execute on the LVGL/UI context; they must remain short and defer blocking work to the corresponding data-processing task.
 * @param account Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param param Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    static int onEvent(Account *account, Account::EventParam_t *param);
};

}

#endif
