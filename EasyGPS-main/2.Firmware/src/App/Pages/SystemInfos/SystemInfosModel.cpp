#include "SystemInfosModel.h"
#include <stdio.h>

using namespace Page;

/**
 * @brief Initialize SystemInfosModel state and hardware or data resources.
 */
void SystemInfosModel::Init()
{
/**
 * @brief Execute the Account operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param this Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    account = new Account("SystemInfosModel", DataProc::Center(), 0, this);

    account->Subscribe("SportStatus");
    account->Subscribe("GPS");
    account->Subscribe("MAG");
    account->Subscribe("IMU");
    account->Subscribe("Clock");
    account->Subscribe("Power");
    account->Subscribe("Storage");
    account->Subscribe("StatusBar");
}

/**
 * @brief Release or reset resources managed by SystemInfosModel.
 */
void SystemInfosModel::Deinit()
{
    if (account)
    {
/**
 * @brief Own and retain the account state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        delete account;
        account = nullptr;
    }
}

void SystemInfosModel::GetSportInfo(
    float *trip,
    char *time, uint32_t len,
    float *maxSpd)
{
/**
 * @brief Own and retain the sport state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    HAL::SportStatus_Info_t sport = {0};
    account->Pull("SportStatus", &sport, sizeof(sport));
    *trip = sport.totalDistance / 1000;
/**
 * @brief Execute the MakeTimeString operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param totalTime Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param time Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param len Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    DataProc::MakeTimeString(sport.totalTime, time, len);
    *maxSpd = sport.speedMaxKph;
}

void SystemInfosModel::GetGPSInfo(
    float *lat,
    float *lng,
    float *alt,
    char *utc, uint32_t len,
    float *course,
    float *speed)
{
/**
 * @brief Own and retain the gps state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    HAL::GPS_Info_t gps = {0};
    account->Pull("GPS", &gps, sizeof(gps));
    *lat = (float)gps.latitude;
    *lng = (float)gps.longitude;
    *alt = gps.altitude;
    snprintf(
        utc, len,
        "%d-%d-%d\n%02d:%02d:%02d",
        gps.clock.year,
        gps.clock.month,
        gps.clock.day,
        gps.clock.hour,
        gps.clock.minute,
        gps.clock.second);
    *course = gps.course;
    *speed = gps.speed;
}

void SystemInfosModel::GetMAGInfo(
    float *dir,
    int *x,
    int *y,
    int *z)
{
/**
 * @brief Own and retain the mag state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    HAL::MAG_Info_t mag = {0};

    account->Pull("MAG", &mag, sizeof(mag));

    *dir = mag.deg;
    *x = mag.x;
    *y = mag.y;
    *z = mag.z;
}

void SystemInfosModel::GetIMUInfo(
    int *step,
    char *info, uint32_t len)
{
/**
 * @brief Own and retain the imu state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    HAL::IMU_Info_t imu = {0};

    account->Pull("IMU", &imu, sizeof(imu));
    *step = imu.steps;
    snprintf(
        info,
        len,
        "%d\n%d\n%d\n%d\n%d\n%d",
        imu.ax,
        imu.ay,
        imu.az,
        imu.gx,
        imu.gy,
        imu.gz);
}

void SystemInfosModel::GetRTCInfo(
    char *dateTime, uint32_t len)
{
/**
 * @brief Own and retain the clock state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    HAL::Clock_Info_t clock = {0};
    account->Pull("Clock", &clock, sizeof(clock));
    snprintf(
        dateTime,
        len,
        "%d-%d-%d\n%02d:%02d:%02d",
        clock.year,
        clock.month,
        clock.day,
        clock.hour,
        clock.minute,
        clock.second);
}

void SystemInfosModel::GetBatteryInfo(
    int *usage,
    float *voltage,
    char *state, uint32_t len)
{
/**
 * @brief Own and retain the power state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    HAL::Power_Info_t power = {0};
    account->Pull("Power", &power, sizeof(power));
    *usage = power.usage;
    *voltage = (float)power.voltage / 1000.0;
    strncpy(state, power.isCharging ? "CHARGE" : "DISCHARGE", len);
    state[len - 1] = '\0';
}

void SystemInfosModel::GetStorageInfo(
    bool *detect,
    const char **type,
    char *usage, uint32_t len)
{
/**
 * @brief Own and retain the info state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    DataProc::Storage_Basic_Info_t info = {0};
    account->Pull("Storage", &info, sizeof(info));
    *detect = info.isDetect;
    *type = info.type;
    snprintf(
        usage, len,
        "%0.1f GB",
        info.totalSizeMB / 1024.0f);
}

/**
 * @brief Change the StatusBarStyle configuration of the object.
 * @param style Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void SystemInfosModel::SetStatusBarStyle(DataProc::StatusBar_Style_t style)
{
/**
 * @brief Own and retain the info state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    DataProc::StatusBar_Info_t info;
/**
 * @brief Execute the DATA_PROC_INIT_STRUCT operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param info Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    DATA_PROC_INIT_STRUCT(info);

    info.cmd = DataProc::STATUS_BAR_CMD_SET_STYLE;
    info.param.style = style;

    account->Notify("StatusBar", &info, sizeof(info));
}

/**
 * @brief Change the StatusBarAppear configuration of the object.
 * @param en Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void SystemInfosModel::SetStatusBarAppear(bool en)
{
/**
 * @brief Own and retain the info state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    DataProc::StatusBar_Info_t info;
/**
 * @brief Execute the DATA_PROC_INIT_STRUCT operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param info Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    DATA_PROC_INIT_STRUCT(info);
    info.cmd = DataProc::STATUS_BAR_CMD_APPEAR;
    info.param.appear = en;
    account->Notify("StatusBar", &info, sizeof(info));
}
