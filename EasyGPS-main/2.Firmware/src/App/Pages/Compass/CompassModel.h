#ifndef __COMPASS_MODEL_H
#define __COMPASS_MODEL_H

#include "App/Common/DataProc/DataProc.h"
#include "lvgl.h"

namespace Page
{

    class CompassModel
    {
    public:
        void GetMAGInfo(
            int *dir,
            int *x,
            int *y,
            int *z,
            bool *isCalibrated);

/**
 * @brief Change the MAGCalibration configuration of the object.
 */
        void SetMAGCalibration(void);

    public:
/**
 * @brief Initialize CompassModel state and hardware or data resources.
 */
        void Init();
/**
 * @brief Release or reset resources managed by CompassModel.
 */
        void Deinit();

/**
 * @brief Change the StatusBarStyle configuration of the object.
 * @param style Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
        void SetStatusBarStyle(DataProc::StatusBar_Style_t style);

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
