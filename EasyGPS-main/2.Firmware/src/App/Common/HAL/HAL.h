/*
 * MIT License
 * Copyright (c) 2021 _VIFEXTech
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#ifndef __HAL_H
#define __HAL_H

#include <stdint.h>
#include "HAL_Def.h"
#include "CommonMacro.h"

/**
 * @namespace HAL
 * @brief Hardware abstraction API exposed to data-processing and page layers.
 *
 * @details Implementations read `Chappie` drivers and publish plain data
 * structures declared in HAL_Def.h.  This boundary keeps UI code independent
 * from I2C, UART, SPI and device-library details.
 */
namespace HAL
{
    /** @brief Callback invoked when a driver has fresh data to commit. */
    typedef bool (*CommitFunc_t)(void *info, void *userData);

    /** @brief Initialise HAL state and start the periodic FreeRTOS task. */
    void HAL_Init(void);
    /** @brief Run scheduled peripheral updates; called by the HAL task. */
    void HAL_Update(void);

    /* Backlight */
/**
 * @brief Execute the Backlight_Init operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 */
    void Backlight_Init();
/**
 * @brief Execute the Backlight_GetValue operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    uint16_t Backlight_GetValue();
/**
 * @brief Execute the Backlight_SetValue operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param val Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
    void Backlight_SetValue(int16_t val);
/**
 * @brief Execute the Backlight_SetGradual operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param target Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param time Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
    void Backlight_SetGradual(uint16_t target, uint16_t time = 500);
/**
 * @brief Execute the Backlight_ForceLit operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param en Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
    void Backlight_ForceLit(bool en);

    /* Display */
/**
 * @brief Execute the Display_Init operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 */
    void Display_Init();
/**
 * @brief Execute the Display_DumpCrashInfo operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param info Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
    void Display_DumpCrashInfo(const char *info);
/**
 * @brief Execute the Display_SetAddrWindow operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param x0 Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param y0 Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param x1 Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param y1 Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
    void Display_SetAddrWindow(int16_t x0, int16_t y0, int16_t x1, int16_t y1);
/**
 * @brief Execute the Display_SendPixels operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param pixels Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param len Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
    void Display_SendPixels(const uint16_t *pixels, uint32_t len);

    typedef void (*Display_CallbackFunc_t)(void);
/**
 * @brief Execute the Display_SetSendFinishCallback operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param func Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
    void Display_SetSendFinishCallback(Display_CallbackFunc_t func);

    /* FaultHandle */
/**
 * @brief Execute the FaultHandle_Init operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 */
    void FaultHandle_Init();

    /* I2C */
/**
 * @brief Execute the I2C_Scan operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    int I2C_Scan();

    /* IMU */
/**
 * @brief Execute the IMU_Init operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 */
    void IMU_Init(void);
/**
 * @brief Execute the IMU_SetCommitCallback operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param func Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param userData Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
    void IMU_SetCommitCallback(CommitFunc_t func, void *userData);
/**
 * @brief Refresh the HAL state without blocking the scheduler.
 * @details The function consumes the latest cached DataProc/HAL snapshot and updates presentation state; it does not own or free the source data.
 */
    void IMU_Update();

    /* MAG */
/**
 * @brief Execute the MAG_Init operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    bool MAG_Init();
/**
 * @brief Execute the MAG_SetCommitCallback operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param func Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param userData Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
    void MAG_SetCommitCallback(CommitFunc_t func, void *userData);
/**
 * @brief Refresh the HAL state without blocking the scheduler.
 * @details The function consumes the latest cached DataProc/HAL snapshot and updates presentation state; it does not own or free the source data.
 */
    void MAG_Update();
/**
 * @brief Execute the MAG_GetInfo operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param info Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
    void MAG_GetInfo(MAG_Info_t *info);
/**
 * @brief Execute the MAG_SetCalibration operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 */
    void MAG_SetCalibration(void);

    /* SD */
    bool SD_Init();
    void SD_Update();
    bool SD_GetReady();
    float SD_GetCardSizeMB();
    const char *SD_GetTypeName();
    typedef void (*SD_CallbackFunction_t)(bool insert);
    void SD_SetEventCallback(SD_CallbackFunction_t callback);

    /* Power */
/**
 * @brief Execute the Power_Init operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 */
    void Power_Init();
/**
 * @brief Refresh the HAL state without blocking the scheduler.
 * @details The function consumes the latest cached DataProc/HAL snapshot and updates presentation state; it does not own or free the source data.
 */
    void Power_HandleTimeUpdate();
/**
 * @brief Execute the Power_SetAutoLowPowerTimeout operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param sec Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
    void Power_SetAutoLowPowerTimeout(uint16_t sec);
/**
 * @brief Execute the Power_GetAutoLowPowerTimeout operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    uint16_t Power_GetAutoLowPowerTimeout();
/**
 * @brief Execute the Power_SetAutoLowPowerEnable operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param en Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
    void Power_SetAutoLowPowerEnable(bool en);
/**
 * @brief Execute the Power_Shutdown operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 */
    void Power_Shutdown();
/**
 * @brief Refresh the HAL state without blocking the scheduler.
 * @details The function consumes the latest cached DataProc/HAL snapshot and updates presentation state; it does not own or free the source data.
 */
    void Power_Update();
/**
 * @brief Execute the Power_EventMonitor operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 */
    void Power_EventMonitor();
/**
 * @brief Execute the Power_GetInfo operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param info Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
    void Power_GetInfo(Power_Info_t *info);
    typedef void (*Power_CallbackFunction_t)(void);
/**
 * @brief Execute the Power_SetEventCallback operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param callback Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
    void Power_SetEventCallback(Power_CallbackFunction_t callback);

    /* Clock */
/**
 * @brief Execute the Clock_Init operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 */
    void Clock_Init();
/**
 * @brief Execute the Clock_GetInfo operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param info Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
    void Clock_GetInfo(Clock_Info_t *info);
/**
 * @brief Execute the Clock_SetInfo operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param info Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
    void Clock_SetInfo(const Clock_Info_t *info);
/**
 * @brief Execute the Clock_GetWeekString operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param week Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    const char *Clock_GetWeekString(uint8_t week);

    /* GPS */
/**
 * @brief Execute the GPS_Init operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 */
    void GPS_Init();
/**
 * @brief Refresh the HAL state without blocking the scheduler.
 * @details The function consumes the latest cached DataProc/HAL snapshot and updates presentation state; it does not own or free the source data.
 */
    void GPS_Update();
/**
 * @brief Execute the GPS_GetInfo operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param info Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    bool GPS_GetInfo(GPS_Info_t *info);
/**
 * @brief Execute the GPS_LocationIsValid operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    bool GPS_LocationIsValid();
/**
 * @brief Execute the GPS_GetDistanceOffset operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param info Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param preLong Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param preLat Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    double GPS_GetDistanceOffset(GPS_Info_t *info, double preLong, double preLat);

    /* Buzzer */
/**
 * @brief Execute the Buzz_init operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 */
    void Buzz_init();
/**
 * @brief Execute the Buzz_SetEnable operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param en Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
    void Buzz_SetEnable(bool en);
/**
 * @brief Execute the Buzz_Tone operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param freq Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param duration Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
    void Buzz_Tone(uint32_t freq, int32_t duration = -1);

    /* Encoder */
/**
 * @brief Execute the Encoder_Init operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 */
    void Encoder_Init();
/**
 * @brief Refresh the HAL state without blocking the scheduler.
 * @details The function consumes the latest cached DataProc/HAL snapshot and updates presentation state; it does not own or free the source data.
 */
    void Encoder_Update();
/**
 * @brief Execute the Encoder_GetDiff operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    int32_t Encoder_GetDiff();
/**
 * @brief Execute the Encoder_GetIsPush operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    bool Encoder_GetIsPush();
/**
 * @brief Execute the Encoder_SetEnable operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param en Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
    void Encoder_SetEnable(bool en);

    /* Audio */
/**
 * @brief Execute the Audio_Init operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 */
    void Audio_Init();
/**
 * @brief Refresh the HAL state without blocking the scheduler.
 * @details The function consumes the latest cached DataProc/HAL snapshot and updates presentation state; it does not own or free the source data.
 */
    void Audio_Update();
/**
 * @brief Execute the Audio_PlayMusic operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param name Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    bool Audio_PlayMusic(const char *name);

    /* Memory */
/**
 * @brief Execute the Memory_DumpInfo operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 */
    void Memory_DumpInfo();

    /* ENV */
/**
 * @brief Execute the ENV_Init operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 */
    void ENV_Init(void);
/**
 * @brief Execute the ENV_SetCommitCallback operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param func Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param userData Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
    void ENV_SetCommitCallback(CommitFunc_t func, void *userData);
/**
 * @brief Refresh the HAL state without blocking the scheduler.
 * @details The function consumes the latest cached DataProc/HAL snapshot and updates presentation state; it does not own or free the source data.
 */
    void ENV_Update(void);

    /* WiFi */
    void WiFi_Init(void);
    void WiFi_Update(void);
    void WiFi_APSetEnable(bool en);
    void WiFi_STASetEnable(bool en);
    void WiFi_GetInfo(WiFi_Info_t *info);

    /* BLE */
/**
 * @brief Execute the BLE_Init operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 */
    void BLE_Init(void);
/**
 * @brief Refresh the HAL state without blocking the scheduler.
 * @details The function consumes the latest cached DataProc/HAL snapshot and updates presentation state; it does not own or free the source data.
 */
    void BLE_Update(void);
/**
 * @brief Execute the BLE_SetBegin operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 */
    void BLE_SetBegin(void);
/**
 * @brief Execute the BLE_SetSleep operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 */
    void BLE_SetSleep(void);
/**
 * @brief Execute the BLE_GetInfo operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param info Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
    void BLE_GetInfo(HAL::BLE_Info_t *info);
/**
 * @brief Execute the BLE_SetKeyboardValue operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param c Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
    void BLE_SetKeyboardValue(uint8_t *c);
/**
 * @brief Execute the BLE_SetMouseMoveValue operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param c Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
    void BLE_SetMouseMoveValue(uint8_t *c);
/**
 * @brief Execute the BLE_SetMouseClickValue operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param b Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
    void BLE_SetMouseClickValue(uint16_t b);

    /* SmartAssistant */
/**
 * @brief Execute the SmartAssistant_Init operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    bool SmartAssistant_Init();
/**
 * @brief Execute the SmartAssistant_SetBegin operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param en Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
    void SmartAssistant_SetBegin(bool en);
/**
 * @brief Execute the SmartAssistant_GetInfo operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param info Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
    void SmartAssistant_GetInfo(HAL::Saa_Info_t *info);
}

#endif
