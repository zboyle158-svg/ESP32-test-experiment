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
 * @brief Execute the IMU_Init operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 */
void HAL::IMU_Init(void)
{
    // ...
}

/**
 * @brief Execute the IMU_SetCommitCallback operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param func Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param userData Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void HAL::IMU_SetCommitCallback(CommitFunc_t func, void *userData)
{
    CommitFunc = func;
    UserData = userData;
}

/**
 * @brief Refresh the HAL_IMU state without blocking the scheduler.
 * @details The function consumes the latest cached DataProc/HAL snapshot and updates presentation state; it does not own or free the source data.
 */
void HAL::IMU_Update()
{
/**
 * @brief Own and retain the imuInfo state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    IMU_Info_t imuInfo = {0};
    // float data[3] = {0};
    Chappie.Imu.getMotion6(
        &imuInfo.ax, &imuInfo.ay, &imuInfo.az,
        &imuInfo.gx, &imuInfo.gy, &imuInfo.gz);

    // Chappie.Imu.getYawPitchRoll(data[0], data[1], data[2]); // 使用此函数会闪退重启

    // imuInfo.ax = (int16_t)data[0];
    // imuInfo.ay = (int16_t)data[1];
    // imuInfo.az = (int16_t)data[2];

    //    Serial.printf(
    //        "ax = %d, ay = %d, az = %d, gx = %d, gy = %d, gz = %d\r\n",
    //        imuInfo.ax, imuInfo.ay, imuInfo.az, imuInfo.gx, imuInfo.gy, imuInfo.gz
    //    );

    // imuInfo.steps = Chappie.Imu.dmpGetSampleStepSizeMS();

    if (CommitFunc)
    {
/**
 * @brief Execute the CommitFunc operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param imuInfo Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param UserData Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
        CommitFunc(&imuInfo, UserData);
    }
}
