#include "HAL.h"
#include "ChappieCore/ChappieCore.h"

/**
 * @brief Own and retain the Chappie state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
extern ChappieCore Chappie;
/**
 * @brief Own and retain the CommitFunc state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
static HAL::CommitFunc_t CommitFunc = nullptr;
static void *UserData = nullptr;

/**
 * @brief Own and retain the Mag_x state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
static int Mag_x = 0, Mag_y = 0, Mag_z = 0, Mag_deg = 0; // MAG数据
/**
 * @brief Own and retain the Mag_isCalibrated state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
static bool Mag_isCalibrated = false;                    // MAG数据是否矫正

/**
 * @brief Execute the MAG_Init operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
bool HAL::MAG_Init()
{
    // ...
    return 0;
}

/**
 * @brief Execute the MAG_SetCommitCallback operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param func Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param userData Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void HAL::MAG_SetCommitCallback(CommitFunc_t func, void *userData)
{
    CommitFunc = func;
    UserData = userData;
}

/**
 * @brief Execute the MAG_SetCalibration operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 */
void HAL::MAG_SetCalibration(void)
{
    if (Mag_isCalibrated)
        return;

    _LOG("[HAL] MAG CALIBRATING. Keep moving your sensor...\n");
/**
 * @brief Execute the Chappie.Mag.calibrate operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Chappie.Mag.calibrate();
    Mag_isCalibrated = true;
    _LOG("[HAL] MAG CALIBRATION is FINISH!\n");
    // Chappie.Mag.setCalibrationOffsets(Chappie.Mag.getCalibrationOffset(0), Chappie.Mag.getCalibrationOffset(1), Chappie.Mag.getCalibrationOffset(2));
    // Chappie.Mag.setCalibrationScales(Chappie.Mag.getCalibrationScale(0), Chappie.Mag.getCalibrationScale(1), Chappie.Mag.getCalibrationScale(2));
    _LOG("DONE. Copy the lines below and paste it into your projects sketch.);\n");
    _LOG("compass.setCalibrationOffsets(%.2f, %.2f, %.2f);\n", Chappie.Mag.getCalibrationOffset(0), Chappie.Mag.getCalibrationOffset(1), Chappie.Mag.getCalibrationOffset(2));
    _LOG("compass.setCalibrationScales(%.2f, %.2f, %.2f);\n", Chappie.Mag.getCalibrationScale(0), Chappie.Mag.getCalibrationScale(1), Chappie.Mag.getCalibrationScale(2));
}

/**
 * @brief Refresh the HAL_MAG state without blocking the scheduler.
 * @details The function consumes the latest cached DataProc/HAL snapshot and updates presentation state; it does not own or free the source data.
 */
void HAL::MAG_Update()
{
/**
 * @brief Execute the Chappie.Mag.read operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Chappie.Mag.read();
/**
 * @brief Execute the Chappie.Mag.getAzimuth operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Mag_deg = Chappie.Mag.getAzimuth();

/**
 * @brief Execute the Chappie.Mag.getX operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Mag_x = Chappie.Mag.getX();
/**
 * @brief Execute the Chappie.Mag.getY operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Mag_y = Chappie.Mag.getY();
/**
 * @brief Execute the Chappie.Mag.getZ operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Mag_z = Chappie.Mag.getZ();


    // _LOG("[MAG] x:%d, y:%d, z:%d\r\n", Mag_x, Mag_y, Mag_z);

    if (CommitFunc)
    {
/**
 * @brief Own and retain the magInfo state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        MAG_Info_t magInfo;
        magInfo.x = Mag_x;
        magInfo.y = Mag_y;
        magInfo.z = Mag_z;
        magInfo.deg = Mag_deg;
        magInfo.isCalibrated = Mag_isCalibrated;

/**
 * @brief Execute the CommitFunc operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param magInfo Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param UserData Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
        CommitFunc(&magInfo, UserData);
    }
}

/**
 * @brief Execute the MAG_GetInfo operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param info Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void HAL::MAG_GetInfo(HAL::MAG_Info_t *info)
{
    info->x = Mag_x;
    info->y = Mag_y;
    info->z = Mag_z;
    info->deg = Mag_deg;
    info->isCalibrated = Mag_isCalibrated;
}
