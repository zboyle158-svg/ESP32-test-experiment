#pragma once

#include "esp_log.h"
#include "nvs_flash.h"
#include "nvs.h"

#define DEFAULT_OTA_URL "https://raw.gitcode.com/VRxiaojie/testOTA/raw/main/version.json"

/** @brief 电源设置：低功耗开关和充电截止百分比。 */
typedef struct {
    uint8_t power_save_mode; // 省电模式
    uint8_t charge_limit;    // 电量百分比上限
} power_settings_t;


extern power_settings_t power_settings;

/** @brief MQTT 连接参数和周期上传配置。 */
typedef struct
{
    char uri[64];
    uint32_t port;
    char username[64];
    char password[64];
    uint8_t upload_interval;
    uint8_t auto_conn;
} mqtt_user_config_t;

extern mqtt_user_config_t mqtt_user_config;

/** @brief OTA 版本信息地址和固件下载地址。 */
typedef struct
{
    char info_url[128];
    char newest_version[32];
    char download_url[256];
} ota_settings_t;

extern ota_settings_t ota_settings;

/** @brief 和风天气 API 密钥、主机和城市配置。 */
typedef struct {
    char api_key[64];
    char api_host[64];     // 和风天气API主机地址
    char city[32];         // 城市 支持拼音
} weather_config_t;
extern weather_config_t weather_config;

extern uint8_t wifi_auto_connect;

/** @brief NVS 异步读取操作选择。 */
typedef enum
{
    NVS_READ_PWR,
    NVS_READ_MQTT,
    NVS_READ_OTA,
    NVS_READ_WEATHER,
    NVS_READ_WIFI
} nvs_read_idx_t;

/** @brief NVS 异步写入操作选择。 */
typedef enum
{
    NVS_WRITE_PWR,
    NVS_WRITE_MQTT,
    NVS_WRITE_OTA,
    NVS_WRITE_WEATHER,
    NVS_WRITE_WIFI
} nvs_write_idx_t;

extern volatile nvs_read_idx_t nvs_read_idx;
extern volatile nvs_write_idx_t nvs_write_idx;

/** @brief 初始化 NVS 分区，必要时擦除并重建。 */
void nvs_init(void);
/** @brief 创建任务读取指定类别的持久化设置。 @param idx 设置类别。 */
void nvs_read(nvs_read_idx_t idx);
/** @brief 更新内存配置并创建任务写入 NVS。 @param idx 设置类别。 @param arg 对应配置结构体指针。 */
void nvs_write(nvs_write_idx_t idx, void* arg);
