#include "configwifi.h"

/**
 * @brief Own and retain the prefs state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
Preferences prefs;
/**
 * @brief Own and retain the dnsServer state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
DNSServer dnsServer;  // 创建dnsServer实例
/**
 * @brief Execute the server operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
WebServer server(80); // 开启web服务, 创建TCP SERVER,参数: 端口号,最大连接数
/**
 * @brief Execute the apIP operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
IPAddress apIP(192, 168, 4, 1);
/**
 * @brief Own and retain the DNS_PORT state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
const byte DNS_PORT = 53; // 设置DNS端口号
/**
 * @brief Execute the I2C_BM8563 operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param I2C_BM8563_DEFAULT_ADDRESS Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param Wire Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
I2C_BM8563 Rtc = I2C_BM8563(I2C_BM8563_DEFAULT_ADDRESS, Wire);

/**
 * @brief Release resources owned by the ConfigWiFi object.
 * @return Operation result or status; inspect it before using dependent state.
 */
ConfigWiFi::~ConfigWiFi() {}
/**
 * @brief Construct or destroy the ConfigWiFi object.
 * @param false Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
ConfigWiFi::ConfigWiFi() : wifiEnabled(false) {}

/**
 * @brief Execute the InitWiFi operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 */
void InitWiFi()
{
    prefs.begin("WiFiAP");                   // 在Preferences中命名空间和键名均为字符串，并且长度不大于15个字节 大于可能无法打开命名空间
/**
 * @brief Execute the prefs.getString operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    WiFi_Name = prefs.getString("WiFiName"); // wifi名字
/**
 * @brief Execute the prefs.getString operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    WiFi_Pass = prefs.getString("WiFiPass"); // wifi密码
    WiFi_LOG("WiFi N:%s WiFi P:%s\r\n", WiFi_Name, WiFi_Pass);
    prefs.end();
}
/**
 * @brief Execute the FunctionRoot operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 */
void FunctionRoot()
{
    server.send(200, "text/html", ROOT_HTML);
}
/**
 * @brief Execute the setWiFi operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param w Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param p Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void setWiFi(String w, String p)
{
    prefs.begin("WiFiAP");
    prefs.putString("WiFiName", w); // 默认值
    prefs.putString("WiFiPass", p); // 默认值
/**
 * @brief Execute the prefs.getString operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    WiFi_Name = prefs.getString("WiFiName");
/**
 * @brief Execute the prefs.getString operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    WiFi_Pass = prefs.getString("WiFiPass");
    WiFi_LOG("WiFi N:%s \nWiFi P:%s \n", WiFi_Name, WiFi_Pass);
    prefs.end();
}
/**
 * @brief Execute the handleConfigWifi operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 */
void handleConfigWifi() // 返回http状态
{
    if (server.hasArg("ssid") && server.hasArg("password")) // 判断是否有账号参数
    {
/**
 * @brief Execute the server.arg operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
        WiFi_Name = server.arg("ssid");     // 获取html表单输入框name名为"ssid"的内容
/**
 * @brief Execute the server.arg operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
        WiFi_Pass = server.arg("password"); // 获取html表单输入框name名为"pwd"的内容
        setWiFi(WiFi_Name, WiFi_Pass);
        server.send(200, "text", "ture");
    }
    else
    {                                                                                 // 没有参数
        server.send(200, "text/html", "<meta charset='UTF-8'>error, not found ssid"); // 返回错误页面
        return;
    }
    server.send(200, "text/html", "<meta charset='UTF-8'>SSID：" + WiFi_Name + "<br />password:" + WiFi_Pass + "<br />已取得WiFi信息,正在尝试连接,请手动关闭此页面。"); // 返回保存成功页面
    // WiFi.softAPdisconnect(true);     //参数设置为true，设备将直接关闭接入点模式，即关闭设备所建立的WiFi网络。
    // server.close();                  //关闭web服务
    // WiFi.softAPdisconnect();         //在不输入参数的情况下调用该函数,将关闭接入点模式,并将当前配置的AP热点网络名和密码设置为空值.
}
/**
 * @brief Execute the scanWiFi operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 */
void scanWiFi()
{
    WiFi.disconnect();
/**
 * @brief Own and retain the req_json state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    static String req_json = "";
    int n = WiFi.scanNetworks();
/**
 * @brief Own and retain the m state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    int m = 0;
    if (n > 0)
    {
        req_json = "{\"req\":[";
        for (int i = 0; i < n; i++)
        {
            if ((int)WiFi.RSSI(i) >= -200)
                //  if (1) {
                m++;
            String a = "{\"ssid\":\"" + (String)WiFi.SSID(i) + "\"," + "\"encryptionType\":\"" + WiFi.encryptionType(i) + "\"," + "\"rssi\":" + (int)WiFi.RSSI(i) + "},";
            if (a.length() > 15)
                req_json += a;
        }
    }
    req_json.remove(req_json.length() - 1);
    req_json += "]}";
    server.send(200, "text/json;charset=UTF-8", req_json);
    WiFi_LOG("req_json:%s\n", req_json.c_str());
}
/**
 * @brief Execute the APMode operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 */
void ConfigWiFi::APMode()
{
    if (WiFi.status() == WL_CONNECTED)
    {
        WiFi.mode(WIFI_OFF);
    }
    WiFi.mode(WIFI_AP);                                         // 配置为AP模式
    WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0)); // 设置AP热点IP和子网掩码
    WiFi.softAP(AP_SSID);
    dnsServer.start(DNS_PORT, "*", apIP); // 判断将所有地址映射到esp32的ip上是否成功
/**
 * @brief Execute the MDNS.begin operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    MDNS.begin("Hugokkl");
    // 必须添加第二个参数HTTP_GET，以下面这种格式去写，否则无法强制门户
    server.on("/", HTTP_GET, FunctionRoot);     //  当浏览器请求服务器根目录(网站首页)时调用自定义函数handleRoot处理，设置主页回调函数，必须添加第二个参数HTTP_GET，否则无法强制门户
    server.on("/configwifi", handleConfigWifi); //  当浏览器请求服务器/configwifi(表单字段)目录时调用自定义函数handleConfigWifi处
    server.on("/scanWiFi", scanWiFi);
    server.onNotFound(FunctionRoot); // 当浏览器请求的网络资源无法在服务器找到时调用自定义函数handleNotFound处理
    server.begin();                  // 启动TCP SERVER
    OnAP = true;

    // return true;
}
/**
 * @brief Execute the WiFiN operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
char *ConfigWiFi::WiFiN()
{
    return (char *)WiFi_Name.c_str();
}
/**
 * @brief Initialize ConfigWiFi state and hardware or data resources.
 */
void ConfigWiFi::Init()
{
    WiFi.hostname(HOST_NAME);
/**
 * @brief Execute the InitWiFi operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    InitWiFi();
    WiFi.mode(WIFI_STA);
}
/**
 * @brief Execute the APClose operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
bool ConfigWiFi::APClose()
{
    server.close();
    dnsServer.stop();
    WiFi.softAPdisconnect(true);
    WiFi.mode(WIFI_STA);
    OnAP = false;
/**
 * @brief Own and retain the true state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    return true;
}

/**
 * @brief Change the enableWiFi configuration of the object.
 */
void ConfigWiFi::enableWiFi()
{
    if (isConnected())
    {
        WiFi_LOG("[WiFi] WiFi已经是启用状态\r\n");
        return;
    }
    else
    {
        wifiEnabled = true;
        WiFi.mode(WIFI_STA);
        WiFi.begin(WiFi_Name.c_str(), WiFi_Pass.c_str());
    }
}

/**
 * @brief Change the disableWiFi configuration of the object.
 */
void ConfigWiFi::disableWiFi()
{
    if (wifiEnabled)
    {
        wifiEnabled = false;
        WiFi.disconnect(); // 断开 WiFi 连接
        WiFi.mode(WIFI_AP);
    }
    else
    {
        WiFi_LOG("[WiFi] WiFi已经是禁用状态\r\n");
    }
}
/**
 * @brief Change the enableIPv6 configuration of the object.
 * @return Operation result or status; inspect it before using dependent state.
 */
bool ConfigWiFi::enableIPv6()
{
    return WiFi.enableIpV6();
}
bool ConfigWiFi::isWiFiEnabled() const
{
/**
 * @brief Own and retain the wifiEnabled state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    return wifiEnabled;
}
bool ConfigWiFi::isConnected() const
{
    return (WiFi.status() == WL_CONNECTED);
}
/**
 * @brief Execute the LocalIP operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
char *ConfigWiFi::LocalIP()
{
    // return (WiFi.status() == WL_CONNECTED) ? (WiFi.localIP().toString()) : "0.0.0.0";
    if (WiFi.status() == WL_CONNECTED)
    {
        printf("LocalIP:%s\r\n", WiFi.localIP().toString().c_str());
        String res = WiFi.localIP().toString();
        return (char *)res.c_str();
    }
    else
    {
        return (char *)"none";
    }
}
/**
 * @brief Execute the GateWay operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
char *ConfigWiFi::GateWay()
{
    // printf("GYIP:%s",WiFi.gatewayIP().toString().c_str());
    // return (WiFi.status() == WL_CONNECTED) ? WiFi.gatewayIP().toString() : "0.0.0.0";
    if (WiFi.status() == WL_CONNECTED)
    {
        String res = WiFi.gatewayIP().toString();
        return (char *)res.c_str();
    }
    else
    {
        return (char *)"none";
    }
}
/**
 * @brief Execute the WiFiMac operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
char *ConfigWiFi::WiFiMac()
{
    // return (WiFi.status() == WL_CONNECTED) ? (char *)(WiFi.macAddress().c_str()) : "None";
    if (WiFi.status() == WL_CONNECTED)
    {
        String res = WiFi.macAddress();
        return (char *)res.c_str();
    }
    else
    {
        return (char *)"none";
    }
}

/**
 * @brief Execute the WiFiloop operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 */
void ConfigWiFi::WiFiloop()
{
    if (OnAP)
    {
        server.handleClient();
        dnsServer.processNextRequest();
        delay(10);
    }
}

/**
 * @brief Read IPv6 from the current object state.
 * @return Operation result or status; inspect it before using dependent state.
 */
String ConfigWiFi::GetIPv6()
{
    return (WiFi.status() == WL_CONNECTED) ? (WiFi.localIPv6().toString()) : "0:0:0:0";
}
/**
 * @brief Execute the NtpTimeCorr operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 */
void ConfigWiFi::NtpTimeCorr()
{
/**
 * @brief Own and retain the timeInfo state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    static struct tm timeInfo;
    if (AutoTime)
    {
        if (isConnected())
        {
            configTime(8 * 3600, 0, ntpServer);
            if (getLocalTime(&timeInfo))
            {
                // Set RTC time
/**
 * @brief Own and retain the timeStruct state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
                I2C_BM8563_TimeTypeDef timeStruct;
                timeStruct.hours = timeInfo.tm_hour;
                timeStruct.minutes = timeInfo.tm_min;
                timeStruct.seconds = timeInfo.tm_sec;
/**
 * @brief Execute the Rtc.setTime operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param timeStruct Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
                Rtc.setTime(&timeStruct);

                // Set RTC Date
/**
 * @brief Own and retain the dateStruct state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
                I2C_BM8563_DateTypeDef dateStruct;
                dateStruct.weekDay = timeInfo.tm_wday;
                dateStruct.month = timeInfo.tm_mon + 1;
                dateStruct.date = timeInfo.tm_mday;
                dateStruct.year = timeInfo.tm_year + 1900;
/**
 * @brief Execute the Rtc.setDate operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param dateStruct Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
                Rtc.setDate(&dateStruct);
            }
        }
    }
}
