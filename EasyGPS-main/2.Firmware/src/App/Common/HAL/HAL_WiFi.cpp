#include "HAL.h"
#include "ChappieCore/ChappieCore.h"

/**
 * @brief Own and retain the Chappie state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
extern ChappieCore Chappie;

/**
 * @brief  WiFi初始化
 * @param  无
 * @retval 无
 */
/**
 * @brief Execute the WiFi_Init operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 */
void HAL::WiFi_Init()
{
    // ...
}

/**
 * @brief Refresh the HAL_WiFi state without blocking the scheduler.
 * @details The function consumes the latest cached DataProc/HAL snapshot and updates presentation state; it does not own or free the source data.
 */
void HAL::WiFi_Update(void)
{
    // ...
    if (Chappie.Wf.OnAP)
    {
/**
 * @brief Execute the Chappie.Wf.WiFiloop operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
        Chappie.Wf.WiFiloop();
    }
    else if (Chappie.Wf.isConnected())
    {
        // ...todo
        __IntervalExecute(Chappie.Wf.NtpTimeCorr(), 5000);
    }
    else if (Chappie.Wf.wifiEnabled && !Chappie.Wf.isConnected())
    {
        // ...todo
        // __IntervalExecute(Chappie.Wf.enableWiFi(), 500);
        __IntervalExecute(_LOG("[WiFi] is connecting...\n"), 2000);
    }

}
/**
 * @brief Execute the WiFi_APSetEnable operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param en Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void HAL::WiFi_APSetEnable(bool en)
{
    if (en)
    {
/**
 * @brief Execute the Chappie.Wf.APMode operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
        Chappie.Wf.APMode();
    }
    else
    {
/**
 * @brief Execute the Chappie.Wf.APClose operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
        Chappie.Wf.APClose();
    }
}
/**
 * @brief Execute the WiFi_STASetEnable operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param en Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void HAL::WiFi_STASetEnable(bool en)
{
    if (en)
    {
/**
 * @brief Execute the Chappie.Wf.enableWiFi operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
        Chappie.Wf.enableWiFi();
    }
    else
    {
/**
 * @brief Execute the Chappie.Wf.disableWiFi operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
        Chappie.Wf.disableWiFi();
    }
}
/**
 * @brief Execute the WiFi_GetInfo operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param info Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void HAL::WiFi_GetInfo(HAL::WiFi_Info_t *info)
{
/**
 * @brief Execute the Chappie.Wf.WiFiN operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    info->name = Chappie.Wf.WiFiN();
/**
 * @brief Execute the Chappie.Wf.LocalIP operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    info->IP = Chappie.Wf.LocalIP();
/**
 * @brief Execute the Chappie.Wf.GateWay operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    info->gateWay = Chappie.Wf.GateWay();
/**
 * @brief Execute the Chappie.Wf.WiFiMac operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    info->Mac = Chappie.Wf.WiFiMac();
/**
 * @brief Execute the Chappie.Wf.isConnected operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    info->isConnected = Chappie.Wf.isConnected();
    info->isAPEnabled = Chappie.Wf.OnAP;
/**
 * @brief Execute the Chappie.Wf.isWiFiEnabled operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    info->isWiFiEnabled = Chappie.Wf.isWiFiEnabled();
}
