/**
 * @file HAL_Def.h
 * @brief Stable value types exchanged across the HAL/DataProc boundary.
 *
 * @details A HAL implementation may change sensor libraries, bus timing or
 * GPIO details, while these application-facing structures remain stable.
 */
#ifndef __HAL_DEF_H
#define __HAL_DEF_H

#include <stdint.h>

namespace HAL
{

    /* Clock */
    typedef struct
    {
/**
 * @brief Own and retain the year state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        uint16_t year;
/**
 * @brief Own and retain the month state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        uint8_t month;
/**
 * @brief Own and retain the day state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        uint8_t day;
/**
 * @brief Own and retain the week state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        uint8_t week;
/**
 * @brief Own and retain the hour state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        uint8_t hour;
/**
 * @brief Own and retain the minute state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        uint8_t minute;
/**
 * @brief Own and retain the second state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        uint8_t second;
/**
 * @brief Own and retain the millisecond state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        uint16_t millisecond;
/**
 * @brief Own and retain the Clock_Info_t state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    } Clock_Info_t;

    /* GPS */
    typedef struct
    {
/**
 * @brief Own and retain the longitude state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        double longitude;
/**
 * @brief Own and retain the latitude state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        double latitude;
/**
 * @brief Own and retain the altitude state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        float altitude;
/**
 * @brief Own and retain the course state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        float course;
/**
 * @brief Own and retain the speed state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        float speed;
/**
 * @brief Own and retain the satellites state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        int16_t satellites;
/**
 * @brief Own and retain the isVaild state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        bool isVaild;
/**
 * @brief Own and retain the clock state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        Clock_Info_t clock;
/**
 * @brief Own and retain the GPS_Info_t state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    } GPS_Info_t;

    /* MAG */
    typedef struct
    {
/**
 * @brief Own and retain the deg state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        int16_t deg;
/**
 * @brief Own and retain the x state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        int16_t x;
/**
 * @brief Own and retain the y state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        int16_t y;
/**
 * @brief Own and retain the z state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        int16_t z;
/**
 * @brief Own and retain the isCalibrated state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        bool isCalibrated;
/**
 * @brief Own and retain the MAG_Info_t state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    } MAG_Info_t;

    /* IMU */
    typedef struct
    {
/**
 * @brief Own and retain the ax state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        int16_t ax;
/**
 * @brief Own and retain the ay state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        int16_t ay;
/**
 * @brief Own and retain the az state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        int16_t az;
/**
 * @brief Own and retain the gx state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        int16_t gx;
/**
 * @brief Own and retain the gy state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        int16_t gy;
/**
 * @brief Own and retain the gz state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        int16_t gz;
/**
 * @brief Own and retain the steps state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        int16_t steps;
/**
 * @brief Own and retain the IMU_Info_t state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    } IMU_Info_t;

    /* SportStatus */
    typedef struct
    {
/**
 * @brief Own and retain the lastTick state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        uint32_t lastTick;

/**
 * @brief Own and retain the weight state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        float weight;

/**
 * @brief Own and retain the speedKph state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        float speedKph;
/**
 * @brief Own and retain the speedMaxKph state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        float speedMaxKph;
/**
 * @brief Own and retain the speedAvgKph state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        float speedAvgKph;

        union
        {
/**
 * @brief Own and retain the totalTimeUINT32 state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
            uint32_t totalTimeUINT32[2];
/**
 * @brief Own and retain the totalTime state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
            uint64_t totalTime;
        };

/**
 * @brief Own and retain the totalDistance state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        float totalDistance;

        union
        {
/**
 * @brief Own and retain the singleTimeUINT32 state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
            uint32_t singleTimeUINT32[2];
/**
 * @brief Own and retain the singleTime state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
            uint64_t singleTime;
        };

/**
 * @brief Own and retain the singleDistance state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        float singleDistance;
/**
 * @brief Own and retain the singleCalorie state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        float singleCalorie;

/**
 * @brief Own and retain the SportStatus_Info_t state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    } SportStatus_Info_t;

    /* Power */
    typedef struct
    {
/**
 * @brief Own and retain the voltage state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        uint16_t voltage;
/**
 * @brief Own and retain the usage state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        uint8_t usage;
/**
 * @brief Own and retain the isCharging state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        bool isCharging;
/**
 * @brief Own and retain the isAutoPowerOff state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        bool isAutoPowerOff;
/**
 * @brief Own and retain the Power_Info_t state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    } Power_Info_t;

    /* WiFi */
    typedef struct
    {
        /* pull */
        char *name;
        char *IP;
        char *gateWay;
        char *Mac;
/**
 * @brief Own and retain the isConnected state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        bool isConnected;

        /* notify */
/**
 * @brief Own and retain the isAPEnabled state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        bool isAPEnabled;
/**
 * @brief Own and retain the isWiFiEnabled state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        bool isWiFiEnabled;

/**
 * @brief Own and retain the WiFi_Info_t state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    } WiFi_Info_t;

    /* BLE */
    typedef struct
    {
        /* pull */
        char *name;
/**
 * @brief Own and retain the isConnected state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        bool isConnected;

        /* notify */
/**
 * @brief Own and retain the MouseClick state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        uint16_t MouseClick; // Data
/**
 * @brief Own and retain the MouseVal state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        uint8_t MouseVal[4]; // Data
/**
 * @brief Own and retain the KeyVal state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        uint8_t KeyVal[2];   // Data
/**
 * @brief Own and retain the isEnabled state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        bool isEnabled;      // Cmd
/**
 * @brief Own and retain the DC state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        uint8_t DC;          // Data->0 / Cmd->1

/**
 * @brief Own and retain the BLE_Info_t state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    } BLE_Info_t;

    /* SmartAssistant */
    typedef struct
    {
        /* pull */
        char *inputText;
        char *outputText;
/**
 * @brief Own and retain the isRunning state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        bool isRunning;
/**
 * @brief Own and retain the isListening state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        bool isListening;
        /* notify */
        // ...

/**
 * @brief Own and retain the Saa_Info_t state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    } Saa_Info_t;
}

#endif
