#include "esp_sntp.h"
#include "esp_log.h"
#include "esp_err.h"
#include "esp_netif_sntp.h"
#include "ntp.h"
#include "time.h"
#include "wifi.h"

/** @brief NTP 同步任务句柄，用于 IP 获取事件通知立即同步时间。 */
TaskHandle_t ntp_sync_task_handle = NULL;

/**
 * @brief 配置中国标准时区并初始化 SNTP 客户端。
 * @details 使用中国科学院和阿里云公共时间服务器作为主备服务器。
 * @note 只应初始化一次；重复调用前需先停止已有 SNTP 服务。
 */
void ntp_init()
{
    // 设置时区为中国标准时间
    setenv("TZ", "CST-8", 1);
    tzset();
    // 初始化SNTP
    esp_sntp_config_t config = ESP_NETIF_SNTP_DEFAULT_CONFIG_MULTIPLE(2,
                                                                      ESP_SNTP_SERVER_LIST("ntp.ntsc.ac.cn", "ntp1.aliyun.com"));
    esp_netif_sntp_init(&config);
}

/**
 * @brief NTP 周期同步任务。
 * @param[in] arg FreeRTOS 任务参数，当前未使用。
 * @details 任务启动时初始化 SNTP，之后等待 IP 事件通知或最长 30 分钟，再在 Wi-Fi 已连接时等待同步完成。
 */
void ntp_sync_task(void *arg)
{
    ntp_init();
    while (1)
    {
        ulTaskNotifyTake(pdTRUE, pdMS_TO_TICKS(30 * 60 * 1000));
        if (wifi_sta_status == WIFI_CONNECTED)
        {
            if (esp_netif_sntp_sync_wait(pdMS_TO_TICKS(10000)) != ESP_OK)
            {
                ESP_LOGW("NTP", "Failed to update system time within 10s timeout");
            }
            else
            {
                ESP_LOGI("NTP", "System time updated");
            }
        }
    }
}
