#include "BLEKeyboardModel.h"

using namespace Page;

/**
 * @brief Initialize BLEKeyboardModel state and hardware or data resources.
 */
void BLEKeyboardModel::Init()
{
/**
 * @brief Execute the Account operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param this Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    account = new Account("BLEKeyboardModel", DataProc::Center(), 0, this); // 创建一个账户，注意这里把this传给了userdata

    account->Subscribe("StatusBar");
    account->Subscribe("BLE");

    account->SetEventCallback(onEvent); // 设置回调函数，好忙啊
}

/**
 * @brief Release or reset resources managed by BLEKeyboardModel.
 */
void BLEKeyboardModel::Deinit() // 恢复缺省
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
int BLEKeyboardModel::onEvent(Account *account, Account::EventParam_t *param)
{
    if (param->event != Account::EVENT_PUB_PUBLISH) // 如果发行人/出版社没有发布数据
    {
        return Account::RES_UNSUPPORTED_REQUEST; // 则返回不支持请求
    }

    if (strcmp(param->tran->ID, "StatusBar") != 0)
    {
        return Account::RES_PARAM_ERROR;
    }

    BLEKeyboardModel *instance = (BLEKeyboardModel *)account->UserData;

    return Account::RES_OK;
}

/**
 * @brief Read BLEInfo from the current object state.
 * @param name Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param isConnected Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param isEnabled Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void BLEKeyboardModel::GetBLEInfo(char *name, bool *isConnected, bool *isEnabled)
{
/**
 * @brief Own and retain the ble state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    HAL::BLE_Info_t ble = {0};
    account->Pull("BLE", &ble, sizeof(ble));

    snprintf(name, 20, "%s", ble.name);

    *isConnected = ble.isConnected ? true : false;
    *isEnabled = ble.isEnabled ? true : false;

    // printf("[Model] GetBLEInfo\n");
}

/**
 * @brief Send or play the payload requested by the application.
 * @param KeyVal Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void BLEKeyboardModel::SendBLEKeyboardValue(uint8_t *KeyVal)
{
/**
 * @brief Own and retain the ble state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    HAL::BLE_Info_t ble = {0};

    ble.DC = false;
    ble.KeyVal[0] = KeyVal[0];
    ble.KeyVal[1] = KeyVal[1];

    account->Notify("BLE", &ble, sizeof(ble));

    // printf("[Model] SendBLEValue\n");
}
/**
 * @brief Send or play the payload requested by the application.
 * @param MouseVal Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void BLEKeyboardModel::SendBLEMouseMoveValue(uint8_t *MouseVal)
{
/**
 * @brief Own and retain the ble state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    HAL::BLE_Info_t ble = {0};

    ble.DC = false;
    ble.MouseVal[0] = MouseVal[0];
    ble.MouseVal[1] = MouseVal[1];
    ble.MouseVal[2] = MouseVal[2];
    ble.MouseVal[3] = MouseVal[3];

    account->Notify("BLE", &ble, sizeof(ble));

    // printf("[Model] SendBLEMouseValue\n");
}

/**
 * @brief Send or play the payload requested by the application.
 * @param MouseClick Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void BLEKeyboardModel::SendBLEMouseClickValue(uint16_t MouseClick)
{
/**
 * @brief Own and retain the ble state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    HAL::BLE_Info_t ble = {0};

    ble.DC = false;
    ble.MouseClick = MouseClick;

    account->Notify("BLE", &ble, sizeof(ble));
    // printf("[Model] SendBLEMouseClickValue\n");
}

/**
 * @brief Change the StatusBarStyle configuration of the object.
 * @param style Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void BLEKeyboardModel::SetStatusBarStyle(DataProc::StatusBar_Style_t style)
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
void BLEKeyboardModel::SetStatusBarAppear(bool en)
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
