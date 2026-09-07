#pragma once

#include "esp_log.h"
#include "esp_event.h"
#include "mqtt_client.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs_helper.h"
#include "wifi.h"

/** @file mqtt_user.h @brief MQTT 配置、连接和数据发布接口。 */

/** @brief ESP-IDF MQTT 客户端句柄，由 MQTT 模块创建和维护。 */
extern esp_mqtt_client_handle_t client;
/** @brief MQTT 当前状态，具体枚举值由实现和事件回调定义。 */
extern volatile uint8_t mqtt_status;

/** @brief 根据 NVS 配置创建并启动 MQTT 客户端。 */
void mqtt_start(void);
/** @brief 停止 MQTT 客户端并释放相关运行资源。 */
void mqtt_stop(void);
/** @brief 获取 MQTT 当前连接状态。 @return 状态值。 */
uint8_t mqtt_get_status();
