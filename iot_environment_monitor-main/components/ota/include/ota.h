#pragma once

#include <stdint.h>

/** @file ota.h @brief OTA update state and control API. */

/** @brief OTA workflow states. */
enum {
    OTA_STATUS_IDLE = 0,
    OTA_STATUS_CHECKING_UPDATE,
    OTA_STATUS_NO_UPDATE,
    OTA_STATUS_FOUND_UPDATE,
    OTA_STATUS_DOWNLOADING,
    OTA_STATUS_FAILED
};

/** @brief Current OTA workflow state. */
extern volatile uint8_t ota_status;

/** @brief Start OTA services or worker tasks. */
void ota_start(void);
/** @brief Asynchronously check the remote firmware version. */
void ota_check_for_update(void);
/** @brief Copy the running firmware version to the caller buffer. */
void ota_get_current_version(char ota_version[]);
/** @brief Return firmware download progress in percent. */
double ota_get_download_progress(void);
