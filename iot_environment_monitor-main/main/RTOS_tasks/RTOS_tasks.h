/**
 * @file RTOS_tasks.h
 * @brief 环境监测应用层 FreeRTOS 任务接口。
 * @details 任务之间使用 task notification 同步，传感器结果由聚合任务提供给 UI。
 */
#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

/**
 * @file RTOS_tasks.h
 * @brief 环境监测系统 FreeRTOS 任务的统一声明。
 *
 * 任务之间主要通过 FreeRTOS 任务通知同步：采集任务等待通知后读取
 * 传感器，数据聚合任务周期性触发采集并刷新历史曲线，界面任务负责
 * 将最新数据提交给 LVGL。任务句柄在此集中导出，便于模块间解耦。
 */

extern TaskHandle_t bat_adc_task_handle;
extern TaskHandle_t stcc4_task_handle;
extern TaskHandle_t spg4x_task_handle;
extern TaskHandle_t weather_task_handle;

/** @brief SGP40/SGP4x VOC/NOx 传感器采集任务。 */
void sgp4x_task(void *arg);
/** @brief STCC4 二氧化碳、温度和湿度采集任务。 */
void stcc4_task(void *arg);
/** @brief 状态栏初始化及周期刷新任务。 */
void status_bar_init_task(void *pvParameter);
/** @brief 电池电量采集及充电阈值控制任务。 */
void bat_adc_task(void *arg);
/** @brief 聚合传感器数据并维护分钟、小时、天历史数据。 */
void get_data_task(void *arg);
/** @brief 天气数据请求和天气界面更新任务。 */
void weather_task(void *arg);
