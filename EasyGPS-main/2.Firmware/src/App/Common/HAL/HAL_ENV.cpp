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
 * @brief Execute the ENV_Init operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 */
void HAL::ENV_Init(void)
{
    // ...
}

/**
 * @brief Execute the ENV_SetCommitCallback operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param func Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param userData Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void HAL::ENV_SetCommitCallback(CommitFunc_t func, void *userData)
{
    CommitFunc = func;
    UserData = userData;
}

/**
 * @brief Refresh the HAL_ENV state without blocking the scheduler.
 * @details The function consumes the latest cached DataProc/HAL snapshot and updates presentation state; it does not own or free the source data.
 */
void HAL::ENV_Update(void)
{
/**
 * @brief Own and retain the magInfo state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    MAG_Info_t magInfo = {0};

    magInfo.x = (int32_t)(Chappie.Env.readPressure());
    magInfo.y = (int32_t)(Chappie.Env.readAltitude());
    magInfo.z = (int32_t)(Chappie.Env.readTemperature());
    // Serial.printf("%d,%d,%d\n", mag.m.x, mag.m.y, mag.m.z);

    if (CommitFunc)
    {
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
