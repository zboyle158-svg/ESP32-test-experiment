#ifndef __LAUNCHOUT_MODEL_H
#define __LAUNCHOUT_MODEL_H

#include "App/Common/DataProc/DataProc.h"
#include "App/Common/HAL/HAL.h"

namespace Page
{

class LaunchOutModel
{
public:
/**
 * @brief Initialize LaunchOutModel state and hardware or data resources.
 */
    void Init();
/**
 * @brief Release or reset resources managed by LaunchOutModel.
 */
    void Deinit();
/**
 * @brief Send or play the payload requested by the application.
 * @param music Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
    void PlayMusic(const char* music);
/**
 * @brief Change the EncoderEnable configuration of the object.
 * @param en Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
    void SetEncoderEnable(bool en)
    {
/**
 * @brief Execute the Encoder_SetEnable operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param en Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
        HAL::Encoder_SetEnable(en);
    }
/**
 * @brief Change the StatusBarAppear configuration of the object.
 * @param en Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
    void SetStatusBarAppear(bool en);

private:
/**
 * @brief Own and retain the account state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    Account* account;
};

}

#endif
