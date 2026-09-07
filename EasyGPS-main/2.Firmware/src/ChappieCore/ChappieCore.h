#ifndef _CHAPPIECORE_H_
#define _CHAPPIECORE_H_

/* Core */
#include <Arduino.h>
#include "Wire.h"

/* Part */
#include "CTP/ChappieCTP.hpp"
#include "IMU/ChappieIMU.hpp"
#include "Power/ChappiePower.hpp"
#include "SD/ChappieSD.hpp"
#include "ENV/ChappieENV.hpp"
#include "Utility/BM8563/I2C_BM8563.h"
#include "Lvgl/ChappieLvgl.hpp"
#include "Buzzer/EmmaBuzzer.hpp"
#include "Button/EmmaButton.hpp"
#include "Mic/EmmaMicPDM.hpp"
#include "Speaker/EmmaSpeaker.hpp"
#include "RGBLED/EmmaRGBLED.hpp"
#include "MAG/ChappieMAG.hpp"
#include "WiFi/ConfigWiFi.h"
#include "BLE/ChappieBLE.hpp"
#include "GPS/ChappieGPS.hpp"
#include "SmartAssistantAPI/SmartAssistantAPI.hpp"

/* Config */
#include "ChappieCore_config.h"

/**
 * @brief Board support package for the EasyGPS custom hardware.
 *
 * @details This class owns the concrete peripheral drivers.  Higher layers
 * should obtain measurements through HAL rather than operating these members
 * directly.  The exception is board-startup code, where `begin()` establishes
 * the hardware dependency order.
 */
class ChappieCore
{
private:
public:
    /** @brief Initialise every board peripheral and the LVGL ports. */
    void begin(uint32_t delayTime = 100);

    /** @brief Initialise physical peripherals in their required order. */
    void init();

    /** @brief Write the firmware logo to the serial debug output. */
    void printLOGO();

public:
    const std::string Logo = R"(
  ___ _  _  __  ____ ____ __ ____ 
 / __) )( \/ _\(  _ (  _ (  |  __)
( (__) __ (    \) __/) __/)( ) _) 
 \___)_)(_|_/\_(__) (__) (__|____)
)";

    const std::string EasyGPS = R"(
  ____  __  ___  _  _  ____  ____ ___
 |  __)/ _\( __\( \/ )/ ___)(  _ ( __\
  ) _)/ /_)_\ \  \  /( (_/ | ) __/\ \
 |____)_/\_\___/ (__) \____/(__) \___/
)";

    /** @brief ST7789 display driver configured for this PCB. */
    LGFX_ChappieCore Lcd;

    /** @brief I2C capacitive-touch driver. */
    ChappieCTP Tp;

    /** @brief Inertial measurement unit driver. */
    ChappieIMU Imu;

    /** @brief Removable SD-card filesystem driver. */
    ChappieSD Sd;

    /** @brief Battery ADC and power-control driver. */
    ChappiePower Pow;

    /** @brief LVGL display/input/filesystem adaptation layer. */
    ChappieLvgl lvgl;

    /** @brief BM8563 real-time clock on the shared I2C bus. */
    I2C_BM8563 Rtc = I2C_BM8563(I2C_BM8563_DEFAULT_ADDRESS, Wire);

    /** @brief BMP280 environmental sensor driver. */
    ChappieENV Env;

    /** @brief QMC5883L magnetometer driver. */
    ChappieMAG Mag;

    /** @brief GPS NMEA parser and UART transport wrapper. */
    ChappieGPS Gps;

    EmmaButton Button;

    EmmaSpeaker Speaker;

    EmmaMicPDM Mic;

    EmmaBuzzer Buzz;

    EmmaRGBLED RGBLed = EmmaRGBLED();

    /** @brief WiFi station, captive-portal configuration and NTP helper. */
    ConfigWiFi Wf;

    /** @brief Speech-recognition, TTS and cloud-LLM integration facade. */
    SmartAssistantAPI saa;

#if CHAPPIE_CORE_USE_BLE
    ChappieBLE Ble;
#endif
};

/**
 * @brief Define the way to format logout
 *
 */
#define _LOG(format, args...) printf(format, ##args)

#endif
