#include "SettingsModel.h"

using namespace Page;

/**
 * @brief Initialize SettingsModel state and hardware or data resources.
 */
void SettingsModel::Init()
{
/**
 * @brief Execute the Account operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param this Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    account = new Account("SettingsModel", DataProc::Center(), 0, this); // 创建一个账户，注意这里把this传给了userdata
    account->Subscribe("StatusBar");
    account->Subscribe("WiFi");
    account->Subscribe("BLE");
    account->Subscribe("Backlight");
    // account->Subscribe("MusicPlayer");
    account->Subscribe("Power");
    account->SetEventCallback(onEvent); // 设置回调函数，好忙啊
}

/**
 * @brief Release or reset resources managed by SettingsModel.
 */
void SettingsModel::Deinit() // 恢复缺省
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

void SettingsModel::GetWiFiInfo(
    char *name, char *IP, char *gateWay, char *Mac, bool *isConnected, bool *isAPEnabled, bool *isWiFiEnabled)
{
/**
 * @brief Own and retain the wifi state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    HAL::WiFi_Info_t wifi = {0};
    account->Pull("WiFi", &wifi, sizeof(wifi));

    snprintf(name, 20, "%s", wifi.name);
    snprintf(IP, 20, "%s", wifi.IP);
    snprintf(gateWay, 20, "%s", wifi.gateWay);
    snprintf(Mac, 20, "%s", wifi.Mac);

    *isAPEnabled = wifi.isAPEnabled ? true : false;

    *isWiFiEnabled = wifi.isWiFiEnabled ? true : false;

    *isConnected = wifi.isConnected ? true : false;

    printf("[Model] GetWiFiInfo\r\n");
}

/**
 * @brief Change the APEnable configuration of the object.
 * @param en Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void SettingsModel::SetAPEnable(bool en)
{
/**
 * @brief Own and retain the info state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    HAL::WiFi_Info_t info = {0};
    info.isAPEnabled = en;

    if (en)
        info.isWiFiEnabled = !en; // AP开，STA关

    account->Notify("WiFi", &info, sizeof(info)); // 通知
    printf("[Model] SetAPEnable\r\n");
}

/**
 * @brief Change the WiFiEnable configuration of the object.
 * @param en Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void SettingsModel::SetWiFiEnable(bool en)
{
/**
 * @brief Own and retain the info state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    HAL::WiFi_Info_t info = {0};
    info.isWiFiEnabled = en;

    if (en)
        info.isAPEnabled = !en; // STA开，AP关

    account->Notify("WiFi", &info, sizeof(info)); // 通知
    printf("[Model] SetWiFiEnable\r\n");
}

/**
 * @brief Read BLEInfo from the current object state.
 * @param name Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param isConnected Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param isEnabled Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void SettingsModel::GetBLEInfo(char *name, bool *isConnected, bool *isEnabled)
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

    printf("[Model] GetBLEInfo\r\n");
}

/**
 * @brief Change the BLEEnable configuration of the object.
 * @param en Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void SettingsModel::SetBLEEnable(bool en)
{
/**
 * @brief Own and retain the info state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    HAL::BLE_Info_t info = {0};
    info.DC = true; // Cmd
    info.isEnabled = en;

    account->Notify("BLE", &info, sizeof(info)); // 通知
    if (en)
        printf("[Model] SetBLEEnable!\n");
    else
        printf("[Model] SetBLESleep!\n");
}

/**
 * @brief Read DisplayBrightness from the current object state.
 * @param val Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void SettingsModel::GetDisplayBrightness(uint16_t *val)
{
/**
 * @brief Own and retain the info state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    uint16_t info = 0;
    account->Pull("Backlight", &info, sizeof(info));

    *val = info;

    printf("[Model] GetDisplayBrightness\r\n");
}

/**
 * @brief Change the DisplayBrightness configuration of the object.
 * @param val Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void SettingsModel::SetDisplayBrightness(uint16_t val)
{
/**
 * @brief Own and retain the info state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    uint16_t info = val;

    account->Notify("Backlight", &info, sizeof(info)); // 通知

    printf("[Model] SetDisplayBrightness\r\n");
}

/**
 * @brief Read PowAutoOff from the current object state.
 * @param en Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void SettingsModel::GetPowAutoOff(bool *en)
{
/**
 * @brief Own and retain the power state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    HAL::Power_Info_t power = {0};

    account->Pull("Power", &power, sizeof(power));

    *en = power.isAutoPowerOff;
}

/**
 * @brief Change the PowAutoOff configuration of the object.
 * @param en Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void SettingsModel::SetPowAutoOff(bool en)
{
/**
 * @brief Own and retain the info state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    HAL::Power_Info_t info = {0};

    info.isAutoPowerOff = en;

    account->Notify("Power", &info, sizeof(info)); // 通知
}

/**
 * @brief Decode a UI or system event and forward it to the responsible model or view.
 * @details Event callbacks execute on the LVGL/UI context; they must remain short and defer blocking work to the corresponding data-processing task.
 * @param account Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param param Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
int SettingsModel::onEvent(Account *account, Account::EventParam_t *param)
{
    // ...
    return Account::RES_OK;
}

/**
 * @brief Send or play the payload requested by the application.
 * @param music Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void SettingsModel::PlayMusic(const char *music)
{
/**
 * @brief Own and retain the info state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    DataProc::MusicPlayer_Info_t info;
/**
 * @brief Execute the DATA_PROC_INIT_STRUCT operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param info Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    DATA_PROC_INIT_STRUCT(info); // 这里搞了个宏定义，就是用memset把这个info给初始化为0

    info.music = music;
    account->Notify("MusicPlayer", &info, sizeof(info)); // 通知
}

/**
 * @brief Change the StatusBarStyle configuration of the object.
 * @param style Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void SettingsModel::SetStatusBarStyle(DataProc::StatusBar_Style_t style)
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
void SettingsModel::SetStatusBarAppear(bool en)
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
