#ifndef __SETTINGS_MODEL_H
#define __SETTINGS_MODEL_H

#include "App/Common/DataProc/DataProc.h"
#include "lvgl.h"

namespace Page
{

    class SettingsModel
    {
    public:
        typedef enum
        {
            REC_START = DataProc::RECORDER_CMD_START,
            REC_PAUSE = DataProc::RECORDER_CMD_PAUSE,
            REC_CONTINUE = DataProc::RECORDER_CMD_CONTINUE,
            REC_STOP = DataProc::RECORDER_CMD_STOP,
            REC_READY_STOP
/**
 * @brief Own and retain the RecCmd_t state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        } RecCmd_t;

    public:
/**
 * @brief Own and retain the sportStatusInfo state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        HAL::SportStatus_Info_t sportStatusInfo;

    public:
/**
 * @brief Initialize SettingsModel state and hardware or data resources.
 */
        void Init();
/**
 * @brief Release or reset resources managed by SettingsModel.
 */
        void Deinit();

/**
 * @brief Send or play the payload requested by the application.
 * @param music Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
        void PlayMusic(const char *music);
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

/**
 * @brief Read WiFiInfo from the current object state.
 * @param name Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param IP Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param gateWay Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param Mac Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param isConnected Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param isAPEnable Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param isWiFiEnable Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
        void GetWiFiInfo(char *name, char *IP, char *gateWay, char *Mac, bool *isConnected, bool *isAPEnable, bool *isWiFiEnable);
/**
 * @brief Change the APEnable configuration of the object.
 * @param en Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
        void SetAPEnable(bool en);
/**
 * @brief Change the WiFiEnable configuration of the object.
 * @param en Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
        void SetWiFiEnable(bool en);

/**
 * @brief Read BLEInfo from the current object state.
 * @param name Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param isConnected Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param isEnabled Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
        void GetBLEInfo(char *name, bool *isConnected, bool *isEnabled);
/**
 * @brief Change the BLEEnable configuration of the object.
 * @param en Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
        void SetBLEEnable(bool en);

/**
 * @brief Change the DisplayBrightness configuration of the object.
 * @param val Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
        void SetDisplayBrightness(uint16_t val);
/**
 * @brief Read DisplayBrightness from the current object state.
 * @param val Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
        void GetDisplayBrightness(uint16_t *val);

/**
 * @brief Read PowAutoOff from the current object state.
 * @param en Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
        void GetPowAutoOff(bool *en);
/**
 * @brief Change the PowAutoOff configuration of the object.
 * @param en Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
        void SetPowAutoOff(bool en);

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
