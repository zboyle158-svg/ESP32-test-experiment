#include "HAL.h"
#include "ChappieCore/ChappieCore.h"

/**
 * @brief Own and retain the Chappie state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
extern ChappieCore Chappie;

/**
 * @brief Execute the Clock_Init operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 */
void HAL::Clock_Init()
{
    // ...
}

/**
 * @brief Execute the Clock_GetInfo operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param info Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void HAL::Clock_GetInfo(Clock_Info_t *info)
{
    // Get RTC time
/**
 * @brief Own and retain the timeStruct state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    I2C_BM8563_TimeTypeDef timeStruct;

    // Get RTC Date
/**
 * @brief Own and retain the dateStruct state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    I2C_BM8563_DateTypeDef dateStruct;

/**
 * @brief Execute the Chappie.Rtc.getTime operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param timeStruct Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Chappie.Rtc.getTime(&timeStruct);
/**
 * @brief Execute the Chappie.Rtc.getDate operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param dateStruct Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Chappie.Rtc.getDate(&dateStruct);

    info->year = dateStruct.year;
    info->month = dateStruct.month;
    info->day = dateStruct.date;
    info->week = dateStruct.weekDay;
    info->hour = timeStruct.hours;
    info->minute = timeStruct.minutes;
    info->second = timeStruct.seconds;
    info->millisecond = 0;
}

/**
 * @brief Execute the Clock_SetInfo operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param info Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void HAL::Clock_SetInfo(const Clock_Info_t *info)
{
    // Set RTC time
/**
 * @brief Own and retain the timeStruct state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    I2C_BM8563_TimeTypeDef timeStruct;
    timeStruct.hours = info->hour;
    timeStruct.minutes = info->minute;
    timeStruct.seconds = info->second;
/**
 * @brief Execute the Chappie.Rtc.setTime operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param timeStruct Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Chappie.Rtc.setTime(&timeStruct);

    // Set RTC Date
/**
 * @brief Own and retain the dateStruct state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    I2C_BM8563_DateTypeDef dateStruct;
    dateStruct.month = info->month;
    dateStruct.date = info->day;
    dateStruct.year = info->year;
/**
 * @brief Execute the Chappie.Rtc.setDate operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param dateStruct Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Chappie.Rtc.setDate(&dateStruct);
}

/**
 * @brief Execute the Clock_GetWeekString operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param week Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
const char *HAL::Clock_GetWeekString(uint8_t week)
{
    const char *week_str[] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};
    return week < 7 ? week_str[week] : "";
}
