#include <stdio.h>
#include "wifi.h"
#include "esp_event.h"
#include "nvs_flash.h"
#include "esp_log.h"
#include "esp_err.h"
#include <string.h>

/** @brief Wi-Fi 模块日志标签。 */
#define TAG "wifi"

/** @brief Wi-Fi 扫描任务句柄。 */
TaskHandle_t wifi_scan_task_handle = NULL;

/** @brief 扫描结果缓存，最多保存 16 个接入点。 */
wifi_ap_record_t ap_info[16];

/** @brief STA 网络接口句柄。 */
esp_netif_t *sta_netif = NULL;

/** @brief 当前 Wi-Fi STA 连接状态。 */
volatile uint8_t wifi_sta_status = WIFI_DISCONNECTED;
/** @brief Wi-Fi 电源状态标志，供低功耗逻辑读取。 */
volatile uint8_t wifi_pwr_status = 0; 

void wifi_connect_task(void *args);

/** @brief 等待通知并执行异步 Wi-Fi 扫描。 */
void wifi_scan_task(void *args)
{
    if (sta_netif == NULL)
    {
        sta_netif = esp_netif_create_default_wifi_sta();
        assert(sta_netif);
    }

    while (1)
    {
        // 使用任务通知接收
        if (ulTaskNotifyTake(pdTRUE, portMAX_DELAY) == 1)
        {
            vTaskDelay(pdMS_TO_TICKS(50)); 
            // 开始扫描
            ESP_ERROR_CHECK(esp_wifi_scan_start(NULL, false)); // false: 异步扫描，扫描完成后会触发 WIFI_EVENT_SCAN_DONE 事件
            ESP_LOGI(TAG, "Started wifi scan");
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

/** @brief 初始化并启动 ESP-IDF Wi-Fi STA 驱动。 */
void wifi_start()
{
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_start());
}

/** @brief 断开当前连接并停止 Wi-Fi 驱动。 */
void wifi_stop()
{
    if (is_wifi_connected())
    {
        ESP_ERROR_CHECK(esp_wifi_disconnect());
    }
    ESP_ERROR_CHECK(esp_wifi_stop());
}

/** @brief 主动断开当前 Wi-Fi 连接。 */
void wifi_disconnect(void)
{
    ESP_ERROR_CHECK(esp_wifi_disconnect());
}

/** @brief 通知扫描任务开始一次扫描。 */
void wifi_scan()
{
    if (wifi_scan_task_handle != NULL)
    {
        // 通知任务开始扫描
        xTaskNotifyGive(wifi_scan_task_handle);
        ESP_LOGI(TAG, "Notified wifi_scan_task to start scanning");
    }
    else
    {
        ESP_LOGE(TAG, "wifi_scan_task_handle is NULL");
    }
}

/** @brief 使用指定 SSID/密码异步连接 Wi-Fi。 */
void wifi_connect(user_wifi_cfg *cfg)
{
    if(is_wifi_connected())
    {
        ESP_ERROR_CHECK(esp_wifi_disconnect());
    }
    
    BaseType_t xReturned = xTaskCreate(wifi_connect_task, "wifi_connect_task", 8 * 1024, (void *)cfg, 6, NULL);
    if (xReturned != pdPASS)
    {
        ESP_LOGE(TAG, "Failed to create wifi_connect_task");
    }
}

/** @brief 读取并连接 ESP-IDF 保存的上次 AP 配置。 */
bool wifi_connect_to_saved_ap(void)
{
    wifi_start();
    if(is_wifi_connected())
    {
        ESP_ERROR_CHECK(esp_wifi_disconnect());
    }
    // 连接到上次连接的wifi
    wifi_config_t wifi_config = {};
    ESP_ERROR_CHECK(esp_wifi_get_config(WIFI_IF_STA, &wifi_config));
    if (strlen((const char *)wifi_config.sta.ssid) == 0)
    {
        ESP_LOGW(TAG, "No saved WiFi configuration found");
        return false;
    }
    ESP_LOGI(TAG, "Connecting to saved WiFi: %s", wifi_config.sta.ssid);
    BaseType_t xReturned = xTaskCreate(wifi_connect_task, "wifi_connect_task", 8 * 1024, (void *)&wifi_config.sta, 6, NULL);
    if (xReturned != pdPASS)
    {
        ESP_LOGE(TAG, "Failed to create wifi_connect_task");
    }
    return true;
}

/** @brief 初始化 NVS、网络接口、默认事件循环和 Wi-Fi 扫描任务。 */
void wifi_init()
{
    // 初始化wifi前需要初始化NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    ESP_ERROR_CHECK(esp_netif_init()); // 初始化TCP/IP栈
    // 创建wifi扫描任务
    BaseType_t xReturned = xTaskCreate(wifi_scan_task, "wifi_scan_task", 8 * 1024, NULL, 15, &wifi_scan_task_handle);
    if (xReturned != pdPASS)
    {
        ESP_LOGE(TAG, "Failed to create wifi_scan_task");
    }
}

/** @brief 将 STA 接口的 IP、掩码和网关格式化为字符串。 */
void wifi_get_ip_info_str(wifi_ip_info_t *wifi_ip_info)
{
    if (sta_netif != NULL)
    {
        esp_netif_ip_info_t *netif_ip_info = malloc(sizeof(esp_netif_ip_info_t));
        esp_netif_get_ip_info(sta_netif, netif_ip_info);
        sprintf(wifi_ip_info->ip, IPSTR, IP2STR(&netif_ip_info->ip));
        sprintf(wifi_ip_info->netmask, IPSTR, IP2STR(&netif_ip_info->netmask));
        sprintf(wifi_ip_info->gw, IPSTR, IP2STR(&netif_ip_info->gw));
        free(netif_ip_info);
    }
}

/** @brief 判断当前 STA 是否处于已连接状态。 */
bool is_wifi_connected(void)
{
    return wifi_sta_status == WIFI_CONNECTED ? true : false;
}
