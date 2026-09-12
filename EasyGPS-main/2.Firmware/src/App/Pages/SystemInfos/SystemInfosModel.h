#ifndef __SYSTEM_INFOS_MODEL_H
#define __SYSTEM_INFOS_MODEL_H

#include "App/Common/DataProc/DataProc.h"

namespace Page
{

class SystemInfosModel
{
public:
/**
 * @brief Initialize SystemInfosModel state and hardware or data resources.
 */
    void Init();
/**
 * @brief Release or reset resources managed by SystemInfosModel.
 */
    void Deinit();

    void GetSportInfo(
        float* trip,
        char* time, uint32_t len,
        float* maxSpd
    );

    void GetGPSInfo(
        float* lat,
        float* lng,
        float* alt,
        char* utc, uint32_t len,
        float* course,
        float* speed
    );

    void GetMAGInfo(
        float* dir,
        int* x,
        int* y,
        int* z
    );

    void GetIMUInfo(
        int* step,
        char* info, uint32_t len
    );

    void GetRTCInfo(
        char* dateTime, uint32_t len
    );

    void GetBatteryInfo(
        int* usage,
        float* voltage,
        char* state, uint32_t len
    );

    void GetStorageInfo(
        bool* detect,
        const char** type,
        char* size, uint32_t len
    );

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

};

}

#endif
