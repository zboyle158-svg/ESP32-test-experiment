#include "HAL.h"
#include "ChappieCore/ChappieCore.h"

/**
 * @brief Own and retain the Chappie state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
extern ChappieCore Chappie;

/**
 * @brief Execute the SmartAssistant_Init operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
bool HAL::SmartAssistant_Init()
{
    // ...
    return 0;
}

/**
 * @brief  启动智能助手对话
 * @param  en
 * @retval 无
 */
/**
 * @brief Execute the SmartAssistant_SetBegin operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param en Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void HAL::SmartAssistant_SetBegin(bool en)
{
    if (!en)
        return;

/**
 * @brief Execute the Chappie.saa.begin operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Chappie.saa.begin();

}

/**
 * @brief  获取智能助手的信息
 * @param  无
 * @retval 无
 */
/**
 * @brief Execute the SmartAssistant_GetInfo operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param info Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void HAL::SmartAssistant_GetInfo(HAL::Saa_Info_t *info)
{
/**
 * @brief Execute the Chappie.saa.getInputText operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    info->inputText = Chappie.saa.getInputText();
/**
 * @brief Execute the Chappie.saa.getOutputText operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    info->outputText = Chappie.saa.getOutputText();
/**
 * @brief Execute the Chappie.saa.isRunning operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    info->isRunning = Chappie.saa.isRunning();
/**
 * @brief Execute the Chappie.saa.isListening operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    info->isListening = Chappie.saa.isListening();
}
