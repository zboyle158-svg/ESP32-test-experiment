#ifndef __BLEKEYBOARD_MODEL_H
#define __BLEKEYBOARD_MODEL_H

#include "App/Common/DataProc/DataProc.h"
#include "lvgl.h"

namespace Page
{

    class BLEKeyboardModel
    {
    public:
    public:
/**
 * @brief Initialize BLEKeyboardModel state and hardware or data resources.
 */
        void Init();
/**
 * @brief Release or reset resources managed by BLEKeyboardModel.
 */
        void Deinit();

/**
 * @brief Read BLEInfo from the current object state.
 * @param name Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param isConnected Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param isEnabled Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
        void GetBLEInfo(char *name, bool *isConnected, bool *isEnabled);
/**
 * @brief Send or play the payload requested by the application.
 * @param KeyVal Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
        void SendBLEKeyboardValue(uint8_t *KeyVal);
/**
 * @brief Send or play the payload requested by the application.
 * @param MouseVal Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
        void SendBLEMouseMoveValue(uint8_t *MouseVal);
/**
 * @brief Send or play the payload requested by the application.
 * @param MouseClick Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
        void SendBLEMouseClickValue(uint16_t MouseClick);

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
