#include "SmartAssistantModel.h"

using namespace Page;

/**
 * @brief Initialize SmartAssistantModel state and hardware or data resources.
 */
void SmartAssistantModel::Init()
{
/**
 * @brief Execute the Account operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param this Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    account = new Account("SmartAssistantModel", DataProc::Center(), 0, this); // 创建一个账户，注意这里把this传给了userdata

    account->Subscribe("StatusBar");
    account->Subscribe("SmartAssistant");

    account->SetEventCallback(onEvent); // 设置回调函数，好忙啊
}

/**
 * @brief Release or reset resources managed by SmartAssistantModel.
 */
void SmartAssistantModel::Deinit() // 恢复缺省
{
    if (account)
    {
/**
 * @brief Own and retain the account state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        delete account; // 删除类
        account = nullptr;
    }
}

/**
 * @brief Decode a UI or system event and forward it to the responsible model or view.
 * @details Event callbacks execute on the LVGL/UI context; they must remain short and defer blocking work to the corresponding data-processing task.
 * @param account Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param param Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
int SmartAssistantModel::onEvent(Account *account, Account::EventParam_t *param)
{
    if (param->event != Account::EVENT_PUB_PUBLISH) // 如果发行人/出版社没有发布数据
    {
        return Account::RES_UNSUPPORTED_REQUEST; // 则返回不支持请求
    }

    if (strcmp(param->tran->ID, "StatusBar") != 0)
    {
        return Account::RES_PARAM_ERROR;
    }

    SmartAssistantModel *instance = (SmartAssistantModel *)account->UserData;

    return Account::RES_OK;
}

/**
 * @brief Change the StatusBarStyle configuration of the object.
 * @param style Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void SmartAssistantModel::SetStatusBarStyle(DataProc::StatusBar_Style_t style)
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
 * @brief Change the SmartAssistantBegin configuration of the object.
 * @param en Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void SmartAssistantModel::SetSmartAssistantBegin(bool en)
{
/**
 * @brief Own and retain the info state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    HAL::Saa_Info_t info = {0};

    account->Notify("SmartAssistant", &info, sizeof(info)); // 通知

    printf("[Model] SetSmartAssistantBegin\r\n");
}

void SmartAssistantModel::GetSmartAssistantInfo(
    char *inputText, char *outputText, bool *isRunning, bool *isListening)
{
/**
 * @brief Own and retain the info state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    HAL::Saa_Info_t info = {0};
    account->Pull("SmartAssistant", &info, sizeof(info));

    snprintf(inputText, 128, "%s", info.inputText);
    snprintf(outputText, 256, "%s", info.outputText);

    *isRunning = info.isRunning ? true : false;
    *isListening = info.isListening ? true : false;

    printf("[Model] GetSmartAssistantInfo\r\n");
}
