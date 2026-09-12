#include "HAL.h"
#include "ChappieCore/ChappieCore.h"
#include "App/App.h"


/**
 * @brief Own and retain the Chappie state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
extern ChappieCore Chappie;

/* 上一次操作时间(ms) */
/**
 * @brief Own and retain the Power_LastHandleTime state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
static uint32_t Power_LastHandleTime = 0;

/* 自动关机时间(秒) */
/**
 * @brief Own and retain the Power_AutoLowPowerTimeout state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
static uint16_t Power_AutoLowPowerTimeout = 60;

/* 自动关机功能使能 */
/**
 * @brief Own and retain the Power_AutoLowPowerEnable state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
static bool Power_AutoLowPowerEnable = false;

/**
 * @brief Own and retain the Power_IsShutdown state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
static bool Power_IsShutdown = false;

/**
 * @brief Own and retain the Power_ADCValue state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
static volatile uint16_t Power_ADCValue = 0;

/**
 * @brief Own and retain the Power_EventCallback state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
static HAL::Power_CallbackFunction_t Power_EventCallback = nullptr;

#define BATT_MAX_VOLTAGE 4200
#define BATT_MIN_VOLTAGE 3300
#define BATT_FULL_CHARGE_VOLTAGE 4100
/**
 * @brief  电源初始化
 * @param  无
 * @retval 无
 */
/**
 * @brief Execute the Power_Init operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 */
void HAL::Power_Init()
{
    /* 设置自动关机 */
/**
 * @brief Execute the Power_SetAutoLowPowerTimeout operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Power_SetAutoLowPowerTimeout(60);
/**
 * @brief Refresh the HAL_Power state without blocking the scheduler.
 * @details The function consumes the latest cached DataProc/HAL snapshot and updates presentation state; it does not own or free the source data.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Power_HandleTimeUpdate();
/**
 * @brief Execute the Power_SetAutoLowPowerEnable operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param true Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Power_SetAutoLowPowerEnable(true);
}

/**
 * @brief Refresh the HAL_Power state without blocking the scheduler.
 * @details The function consumes the latest cached DataProc/HAL snapshot and updates presentation state; it does not own or free the source data.
 */
static void Power_ADC_TrigUpdate()
{
    // Power_ADCValue = Chappie.Pow.readBatMilliVoltRaw();
    // _LOG("[Power] VoltageRaw: %d\r\n", Chappie.Pow.readBatMilliVoltRaw());
    _LOG("[Power] Voltage: %.2f V\r\n", Chappie.Pow.readBatVoltage());
    // _LOG("[Power] Percentage: %d\r\n", Chappie.Pow.readBatPercentage());
}

/**
 * @brief  更新操作时间
 * @param  无
 * @retval 无
 */
/**
 * @brief Refresh the HAL_Power state without blocking the scheduler.
 * @details The function consumes the latest cached DataProc/HAL snapshot and updates presentation state; it does not own or free the source data.
 */
void HAL::Power_HandleTimeUpdate()
{
/**
 * @brief Execute the millis operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Power_LastHandleTime = millis();
}

/**
 * @brief  设置自动关机时间
 * @param  sec:时间(秒)
 * @retval 无
 */
/**
 * @brief Execute the Power_SetAutoLowPowerTimeout operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param sec Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void HAL::Power_SetAutoLowPowerTimeout(uint16_t sec)
{
    Power_AutoLowPowerTimeout = sec;
}

/**
 * @brief  获取自动关机时间
 * @param  无
 * @retval sec:时间(秒)
 */
/**
 * @brief Execute the Power_GetAutoLowPowerTimeout operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
uint16_t HAL::Power_GetAutoLowPowerTimeout()
{
/**
 * @brief Own and retain the Power_AutoLowPowerTimeout state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    return Power_AutoLowPowerTimeout;
}

/**
 * @brief  设置自动关机功能使能
 * @param  en:使能
 * @retval 无
 */
/**
 * @brief Execute the Power_SetAutoLowPowerEnable operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param en Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void HAL::Power_SetAutoLowPowerEnable(bool en)
{
    Power_AutoLowPowerEnable = en;
/**
 * @brief Refresh the HAL_Power state without blocking the scheduler.
 * @details The function consumes the latest cached DataProc/HAL snapshot and updates presentation state; it does not own or free the source data.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Power_HandleTimeUpdate();
}

/**
 * @brief  执行关机
 * @param  无
 * @retval 无
 */
/**
 * @brief Execute the Power_Shutdown operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 */
void HAL::Power_Shutdown()
{
/**
 * @brief Execute the Backlight_SetGradual operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Backlight_SetGradual(10, 500);

    /* 关机反悔 */
    for (uint8_t i = 0; i < 50; i++)
    {
        if (Chappie.Tp.isTouched())
        {
/**
 * @brief Refresh the HAL_Power state without blocking the scheduler.
 * @details The function consumes the latest cached DataProc/HAL snapshot and updates presentation state; it does not own or free the source data.
 * @return Operation result or status; inspect it before using dependent state.
 */
            Power_HandleTimeUpdate();
            break;
        }
        delay(100);
    }

    if (millis() - Power_LastHandleTime < (Power_AutoLowPowerTimeout * 1000))
    {
/**
 * @brief Execute the Backlight_SetGradual operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
        Backlight_SetGradual(127, 500);
        return;
    }

    /* 执行关机 */

/**
 * @brief Execute the App_Uninit operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    App_Uninit();

/**
 * @brief Execute the Chappie.Gps.disable operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Chappie.Gps.disable();

/**
 * @brief Execute the Chappie.Imu.sleep operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param true Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Chappie.Imu.sleep(true);
/**
 * @brief Execute the Chappie.Env.sleep operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param true Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Chappie.Env.sleep(true);
/**
 * @brief Execute the Chappie.Mag.sleep operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param true Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Chappie.Mag.sleep(true);

/**
 * @brief Execute the Chappie.Speaker.disable operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Chappie.Speaker.disable();
/**
 * @brief Execute the Chappie.Speaker.end operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Chappie.Speaker.end();
    
/**
 * @brief Execute the Chappie.Mic.sleep operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Chappie.Mic.sleep();
/**
 * @brief Execute the Chappie.Mic.end operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Chappie.Mic.end();

/**
 * @brief Execute the Chappie.Lcd.sleep operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Chappie.Lcd.sleep();
/**
 * @brief Execute the Chappie.Tp.disable operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Chappie.Tp.disable();

    FastLED.showColor(CRGB::Black);

    // Chappie.Buzz.play(Melody::Message);

    Power_IsShutdown = true;
    _LOG("[Power] the device is sleep!\r\n");

    delay(500);

    // Todo: ESP32低功耗API
    esp_deep_sleep_start();
}

/**
 * @brief  自动关机监控
 * @param  无
 * @retval 无
 */
/**
 * @brief Refresh the HAL_Power state without blocking the scheduler.
 * @details The function consumes the latest cached DataProc/HAL snapshot and updates presentation state; it does not own or free the source data.
 */
void HAL::Power_Update()
{
    __IntervalExecute(Power_ADC_TrigUpdate(), 2000);

    // Todo: update Power_LastHandleTime
    if (Chappie.Tp.isTouched())
/**
 * @brief Refresh the HAL_Power state without blocking the scheduler.
 * @details The function consumes the latest cached DataProc/HAL snapshot and updates presentation state; it does not own or free the source data.
 * @return Operation result or status; inspect it before using dependent state.
 */
        Power_HandleTimeUpdate();

    if (!Power_AutoLowPowerEnable)
        return;

    if (Power_AutoLowPowerTimeout == 0)
        return;

    if (millis() - Power_LastHandleTime >= (Power_AutoLowPowerTimeout * 1000))
    {
/**
 * @brief Execute the Power_Shutdown operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
        Power_Shutdown();
    }
}

/**
 * @brief Execute the Power_EventMonitor operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 */
void HAL::Power_EventMonitor()
{
    // if (Power.ShutdownReq)
    // {
    //     if (Power.EventCallback)
    //     {
    //         Power.EventCallback();
    //     }
    //     Backlight_SetGradual(0, 500);
    //     digitalWrite(CONFIG_POWER_EN_PIN, LOW);
    //     Serial.println("Power: OFF");
    //     Power.ShutdownReq = false;
    // }
}

/**
 * @brief Execute the Power_GetInfo operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param info Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void HAL::Power_GetInfo(Power_Info_t *info)
{
    int voltage = (int)(Chappie.Pow.readBatVoltage() * 1000);
    __LimitValue(voltage, BATT_MIN_VOLTAGE, BATT_MAX_VOLTAGE);

/**
 * @brief Execute the Chappie.Pow.readBatPercentage operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    int usage = Chappie.Pow.readBatPercentage();
    __LimitValue(usage, 0, 100);

    info->usage = usage;
    info->isCharging = ((usage == 100) ? true : false);
    info->voltage = voltage;
    info->isAutoPowerOff = Power_AutoLowPowerEnable;
}

/**
 * @brief Execute the Power_SetEventCallback operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param callback Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void HAL::Power_SetEventCallback(Power_CallbackFunction_t callback)
{
    Power_EventCallback = callback;
}
