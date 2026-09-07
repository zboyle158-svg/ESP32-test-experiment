#pragma once

/** @file ntp.h @brief SNTP 校时任务接口。 */

/** @brief SNTP 同步任务句柄，用于其他模块通知或查询任务。 */
extern TaskHandle_t ntp_sync_task_handle;

/** @brief 配置 SNTP 服务器、时区和系统时间同步参数。 */
void ntp_init(void);
/** @brief FreeRTOS SNTP 同步任务入口。 */
void ntp_sync_task(void *arg);
