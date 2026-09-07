#pragma once
#include "esp_wifi.h"
#include "esp_netif.h"

/** @file wifi.h @brief Wi-Fi STA 模式管理和扫描接口。 */

/** @brief 用户输入的 Wi-Fi 凭据，字段长度与 ESP-IDF STA 配置兼容。 */
typedef struct
{
    uint8_t ssid[32];
    uint8_t password[64];
} user_wifi_cfg;

/** @brief 以字符串形式保存 IPv4 地址、掩码和网关。 */
typedef struct 
{
    char ip[16];
    char netmask[16];
    char gw[16];
} wifi_ip_info_t;


/** @brief Wi-Fi 连接状态机状态。 */
enum WIFISTATUS{
    WIFI_DISCONNECTED,
    WIFI_CONNECTING,
    WIFI_CONNECTED,
    WIFI_FAILED,
    WIFI_SCANNING,
};

extern wifi_ap_record_t ap_info[16];
extern volatile uint8_t wifi_sta_status;
extern volatile uint8_t wifi_pwr_status; // 0: wifi off, 1: wifi on

/** @brief 初始化 NVS、事件循环、TCP/IP 栈和扫描任务。 */
void wifi_init(void);
/** @brief 初始化并启动 Wi-Fi STA。 */
void wifi_start(void);
/** @brief 断开 STA 并停止 Wi-Fi 驱动。 */
void wifi_stop(void);
/** @brief 异步启动 Wi-Fi 扫描。 */
void wifi_scan(void);
/** @brief 异步连接指定 AP。 @param cfg Wi-Fi 凭据。 */
void wifi_connect(user_wifi_cfg *cfg);
/** @brief 断开当前 Wi-Fi 连接。 */
void wifi_disconnect(void);
/** @brief 获取当前 STA 的 IPv4 网络参数字符串。 */
void wifi_get_ip_info_str(wifi_ip_info_t* wifi_ip_info);
/** @brief 读取 NVS 中保存的 AP 并发起连接。 @return 是否找到有效配置。 */
bool wifi_connect_to_saved_ap(void);
/** @brief 判断 STA 是否已获得连接状态。 */
bool is_wifi_connected(void);
/** @brief 注册 Wi-Fi 和 IP 事件回调。 */
void wifi_event_init(void);
