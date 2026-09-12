/**
 * @file ChappieCore.cpp
 * @brief EasyGPS board-support-package initialisation sequence.
 *
 * @details This translation unit is the only place that decides the startup
 * order of the physical devices. Keep the order conservative: buses and
 * power must exist before dependent sensors, and the LVGL adapter is created
 * only after the display and touch objects are ready.
 */
#include "ChappieCore.h"

/**
 * @brief Init Chappie Core
 *
 * @param delayTime Delay ms before init
 */
/**
 * @brief Execute the begin operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param delayTime Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void ChappieCore::begin(uint32_t delayTime)
{
    /* Hold a second */
    delay(delayTime);

    /* Initialise physical devices before exposing the UI to the scheduler. */
    init();

    /* Init lvgl */
    lvgl.init(&Lcd, &Tp);

    /* print Logo */
    printLOGO();
    _LOG("[ChappieCore] Hi!\r\n");
    _LOG("[ChappieCore] version: %s\r\n", VERSION_SOFTWARE);
    _LOG("[ChappieCore] author: Forairaaaaa\r\n");
    _LOG("[ChappieCore] https://github.com/Forairaaaaa/Chappie-Core\r\n");
}

/**
 * @brief Initialize ChappieCore state and hardware or data resources.
 */
void ChappieCore::init()
{
    /* Init power contrl */
/**
 * @brief Execute the Pow.init operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Pow.init();
    _LOG("[Power] Voltage:%.2f V\r\n", Pow.readBatVoltage());
    _LOG("[Power] BatPercentage:%d\r\n", Pow.readBatPercentage());

    /* Init RGB led */
    FastLED.showColor(CRGB::Pink, 128);

    /* Init Gps */
/**
 * @brief Execute the Gps.init operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Gps.init();

    /* Init Serial */
    Serial.begin(115200);

#if CHAPPIE_CORE_USE_BLE
    /* Init BLE */
#endif

    /* Init lcd */
/**
 * @brief Execute the Lcd.init operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Lcd.init();
/**
 * @brief Execute the Lcd.setFont operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param efontCN_12 Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Lcd.setFont(&fonts::efontCN_12);
    /* Print Logo in a cool way */
/**
 * @brief Execute the Lcd.setCursor operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Lcd.setCursor(0, 0);
    for (char c : EasyGPS)
    {
/**
 * @brief Execute the Lcd.printf operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param c Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
        Lcd.printf("%c", c);
        delay(3);
    }
/**
 * @brief Execute the Lcd.printf operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param VERSION_SOFTWARE Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Lcd.printf("\n ChappieBSP %s :)\n -Author: Forairaaaaa\n", VERSION_SOFTWARE);
    delay(100);
/**
 * @brief Execute the Lcd.printf operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param FIRMWARE_NAME Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Lcd.printf(" Project: %s\n -Powerby @kkl\n", FIRMWARE_NAME);
    delay(100);
/**
 * @brief Execute the Lcd.printf operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Lcd.printf(" " __DATE__ "-" __TIME__ "\n");
    delay(100);
/**
 * @brief Execute the Lcd.printf operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Lcd.printf(" Please put the equipment in a stable place!\n");
/**
 * @brief Execute the Lcd.setTextColor operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param x00c957 Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Lcd.setTextColor(0x00c957);
/**
 * @brief Execute the Lcd.printf operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Lcd.printf(" 请把设备放在平稳的地方进行初始化!\n");

    /* Init I2C */
    Wire.begin(5, 4);
    Wire.setClock(400000);

    /* Init IMU */
/**
 * @brief Execute the Imu.init operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Imu.init();

    /* Init touchpad */
/**
 * @brief Execute the Tp.init operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param Wire Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Tp.init(&Wire);

    /* Init RTC */
/**
 * @brief Execute the Rtc.begin operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Rtc.begin();

    /* Init BMP280 */
/**
 * @brief Execute the Env.init operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Env.init();

    /* Init qmc5883l */
/**
 * @brief Execute the Mag.init operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Mag.init();

    /* Init SD card */
/**
 * @brief Execute the Sd.init operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Sd.init();

    /* Init WiFi */
/**
 * @brief Execute the Wf.Init operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Wf.Init();

    /* Init BLE */
#if CHAPPIE_CORE_USE_BLE
/**
 * @brief Execute the Ble.init operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Ble.init();
#endif

    /* Init SmartAssistant */
    saa.init(&Mic, &Speaker);

    /* Fire up */
    // Speaker.setVolume(100);
    // Speaker.tone(9000, 300);

    /* Play tone */
    // Buzz.play(Melody::StartUp);

    FastLED.showColor(CRGB::Black);
}

/**
 * @brief Print logo on serial port
 *
 */
/**
 * @brief Execute the printLOGO operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 */
void ChappieCore::printLOGO()
{

    /* Print out LOGO */
    _LOG(Logo.c_str());
    _LOG("\r\n");
}
