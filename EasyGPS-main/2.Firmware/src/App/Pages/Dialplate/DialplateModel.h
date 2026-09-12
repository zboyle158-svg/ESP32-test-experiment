#ifndef __DIALPLATE_MODEL_H
#define __DIALPLATE_MODEL_H

#include "App/Common/DataProc/DataProc.h"

namespace Page
{

class DialplateModel
{
public:
    typedef enum
    {
        REC_START    = DataProc::RECORDER_CMD_START,
        REC_PAUSE    = DataProc::RECORDER_CMD_PAUSE,
        REC_CONTINUE = DataProc::RECORDER_CMD_CONTINUE,
        REC_STOP     = DataProc::RECORDER_CMD_STOP,
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
 * @brief Initialize DialplateModel state and hardware or data resources.
 */
    void Init();
/**
 * @brief Release or reset resources managed by DialplateModel.
 */
    void Deinit();

/**
 * @brief Read GPSReady from the current object state.
 * @return Operation result or status; inspect it before using dependent state.
 */
    bool GetGPSReady();

/**
 * @brief Read Speed from the current object state.
 * @return Operation result or status; inspect it before using dependent state.
 */
    float GetSpeed()
    {
        return sportStatusInfo.speedKph;
    }

/**
 * @brief Read AvgSpeed from the current object state.
 * @return Operation result or status; inspect it before using dependent state.
 */
    float GetAvgSpeed()
    {
        return sportStatusInfo.speedAvgKph;
    }

/**
 * @brief Execute the RecorderCommand operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param cmd Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
    void RecorderCommand(RecCmd_t cmd);
/**
 * @brief Send or play the payload requested by the application.
 * @param music Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
    void PlayMusic(const char* music);
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
    static int onEvent(Account* account, Account::EventParam_t* param);
};

}

#endif
