#include "DataProc.h"
#include "../HAL/HAL.h"

/**
 * @brief Execute the DATA_PROC_INIT_DEF operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param IMU Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
DATA_PROC_INIT_DEF(IMU)
{
/**
 * @brief Execute the IMU_SetCommitCallback operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param info Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param userData Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
   HAL::IMU_SetCommitCallback([](void* info, void* userData){
       Account* account = (Account*)userData;
       return account->Commit(info, sizeof(HAL::IMU_Info_t));
   }, account);
}
