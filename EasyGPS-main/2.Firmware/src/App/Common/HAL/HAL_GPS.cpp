#include "HAL.h"
#include "ChappieCore/ChappieCore.h"

/**
 * @brief Own and retain the Chappie state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
extern ChappieCore Chappie;

/**
 * @brief Execute the GPS_Init operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 */
void HAL::GPS_Init()
{
    // ...
}

/**
 * @brief Refresh the HAL_GPS state without blocking the scheduler.
 * @details The function consumes the latest cached DataProc/HAL snapshot and updates presentation state; it does not own or free the source data.
 */
void HAL::GPS_Update()
{
#if CONFIG_GPS_BUF_OVERLOAD_CHK && !GPS_USE_TRANSPARENT
/**
 * @brief Execute the GPS_SERIAL.available operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    int available = GPS_SERIAL.available();
/**
 * @brief Execute the DEBUG_SERIAL.printf operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param available Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param available Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    DEBUG_SERIAL.printf("GPS: Buffer available = %d", available);
    if (available >= SERIAL_RX_BUFFER_SIZE / 2)
    {
/**
 * @brief Execute the DEBUG_SERIAL.print operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
        DEBUG_SERIAL.print(", maybe overload!");
    }
/**
 * @brief Execute the DEBUG_SERIAL.println operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    DEBUG_SERIAL.println();
#endif

    while (GPS_SERIAL.available() > 0)
    {
/**
 * @brief Execute the GPS_SERIAL.read operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
        char c = GPS_SERIAL.read();

        // 转发GPS的原始数据
        // printf("%c", c);

#if GPS_USE_TRANSPARENT
/**
 * @brief Execute the DEBUG_SERIAL.write operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param c Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
        DEBUG_SERIAL.write(c);
#endif
/**
 * @brief Execute the Chappie.Gps.encode operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param c Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
        Chappie.Gps.encode(c);
    }

    // test
    if (Chappie.Gps.location.isValid())
    {
        __IntervalExecute(FastLED.showColor(CRGB::Green), 1000);
    }
    else
    {
        __IntervalExecute(FastLED.showColor(CRGB::OrangeRed), 1000);
    }

    if (Chappie.Gps.satellites.isValid())
    {
/**
 * @brief Execute the Chappie.Gps.satellites.value operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
        uint16_t satellites = Chappie.Gps.satellites.value();

        if (satellites >= 1 && satellites < 3)
        {
            __IntervalExecute(FastLED.showColor(CRGB::RosyBrown), 1000);
        }
        else if (satellites >= 3 && satellites < 5)
        {
            __IntervalExecute(FastLED.showColor(CRGB::PowderBlue), 1000);
        }
        else if (satellites >= 7)
        {
            __IntervalExecute(FastLED.showColor(CRGB::Snow), 1000);
        }
    }
    // else
    // {
    //     __IntervalExecute(FastLED.showColor(CRGB::OrangeRed), 1000);
    // }

#if GPS_USE_TRANSPARENT
    while (DEBUG_SERIAL.available() > 0)
    {
/**
 * @brief Execute the GPS_SERIAL.write operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
        GPS_SERIAL.write(DEBUG_SERIAL.read());
    }
#endif
}

/**
 * @brief Execute the GPS_GetInfo operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param info Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
bool HAL::GPS_GetInfo(GPS_Info_t *info)
{
    memset(info, 0, sizeof(GPS_Info_t));

/**
 * @brief Execute the Chappie.Gps.location.isValid operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    info->isVaild = Chappie.Gps.location.isValid();
/**
 * @brief Execute the Chappie.Gps.location.lng operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    info->longitude = Chappie.Gps.location.lng();
/**
 * @brief Execute the Chappie.Gps.location.lat operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    info->latitude = Chappie.Gps.location.lat();
/**
 * @brief Execute the Chappie.Gps.altitude.meters operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    info->altitude = Chappie.Gps.altitude.meters();
/**
 * @brief Execute the Chappie.Gps.speed.kmph operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    info->speed = Chappie.Gps.speed.kmph();
/**
 * @brief Execute the Chappie.Gps.course.deg operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    info->course = Chappie.Gps.course.deg();

/**
 * @brief Execute the Chappie.Gps.date.year operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    info->clock.year = Chappie.Gps.date.year();
/**
 * @brief Execute the Chappie.Gps.date.month operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    info->clock.month = Chappie.Gps.date.month();
/**
 * @brief Execute the Chappie.Gps.date.day operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    info->clock.day = Chappie.Gps.date.day();
/**
 * @brief Execute the Chappie.Gps.time.hour operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    info->clock.hour = Chappie.Gps.time.hour();
/**
 * @brief Execute the Chappie.Gps.time.minute operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    info->clock.minute = Chappie.Gps.time.minute();
/**
 * @brief Execute the Chappie.Gps.time.second operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    info->clock.second = Chappie.Gps.time.second();
/**
 * @brief Execute the Chappie.Gps.satellites.value operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    info->satellites = Chappie.Gps.satellites.value();

    // info->isVaild = true;
    // info->longitude = 10;
    // info->latitude = 20;
    // info->altitude = 30;
    // info->speed = 10;
    // info->course = 10;

    // info->clock.year = 2024;
    // info->clock.month = 4;
    // info->clock.day = 1;
    // info->clock.hour = 6;
    // info->clock.minute = 6;
    // info->clock.second = 6;
    // info->satellites = 9;

    return info->isVaild;
}

/**
 * @brief Execute the GPS_LocationIsValid operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
bool HAL::GPS_LocationIsValid()
{
    return Chappie.Gps.location.isValid();
}

/**
 * @brief Execute the GPS_GetDistanceOffset operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param info Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param preLong Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param preLat Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
double HAL::GPS_GetDistanceOffset(GPS_Info_t *info, double preLong, double preLat)
{
    return Chappie.Gps.distanceBetween(info->latitude, info->longitude, preLat, preLong);
}
