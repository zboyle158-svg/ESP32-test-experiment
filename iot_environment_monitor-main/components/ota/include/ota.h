#pragma once

#include <stdint.h>

/**
 * @file ota.h
 * @brief OTA 固件升级状态和控制接口。
 * @details OTA 下载到下一个应用分区，校验成功后设置启动分区并重启。
 */

/** @brief OTA workflow states. */
enum {
    OTA_STATUS_IDLE = 0,
    OTA_STATUS_CHECKING_UPDATE,
    OTA_STATUS_NO_UPDATE,
    OTA_STATUS_FOUND_UPDATE,
    OTA_STATUS_DOWNLOADING,
    OTA_STATUS_FAILED
};

/** @brief 当前 OTA 流程状态，由 OTA 任务和 UI 读取。 */
extern volatile uint8_t ota_status;

/** @brief 创建 OTA 下载任务并开始固件下载。 */
void ota_start(void);
/** @brief 创建版本检查任务，异步比较远程版本与当前版本。 */
void ota_check_for_update(void);
/** @brief 将当前运行固件版本号复制到调用者缓冲区。 */
void ota_get_current_version(char ota_version[]);
/** @brief 返回 $0$ 到 $100$ 的固件下载进度百分比。 */
double ota_get_download_progress(void);
