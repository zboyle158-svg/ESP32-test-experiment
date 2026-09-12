#include "BaiduErnieBot.h"

/* 百度文心一言 */
/**
 * @brief Execute the getResponse operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param inputText Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
String BaiduErnieBot::getResponse(String inputText)
{
/**
 * @brief Own and retain the http_client state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    HTTPClient http_client;

/**
 * @brief Own and retain the URL state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    String URL = apiErnieBotUrl + _token;

    http_client.begin(URL);
    http_client.addHeader("Content-Type", "application/json");

    http_client.setTimeout(20000); // 20s的超时时间

    // String payload = "{\"messages\":[{\"role\":\"user\",\"content\":\"请用一句话回答我，严格规定在二十个字以内。\"},{\"role\":\"assistant\",\"content\":\"好的。\"},{\"role\":\"user\",\"content\":\"" + inputText + "\"}]}";
/**
 * @brief Own and retain the payload state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    String payload = "{\"messages\":[{\"role\":\"user\",\"content\":\"" + inputText + "\"}],\"system\":\"你是生活助手机器人，要求回答严格控制在64字内！\"}";

/**
 * @brief Execute the http_client.POST operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param payload Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    int httpResponseCode = http_client.POST(payload);

    if (httpResponseCode == HTTP_CODE_OK)
    {
/**
 * @brief Execute the http_client.getString operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
        String response = http_client.getString();
        http_client.end();

        // _LOG("\r\n%s\r\n", response.c_str());

        // Parse JSON response
/**
 * @brief Execute the doc operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
        DynamicJsonDocument doc(2048);
        deserializeJson(doc, response);

        // authentication 鉴权
/**
 * @brief Own and retain the responseErr state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        String responseErr = doc["error_code"];
        printf("[ASR] Err: %s\n", responseErr);
        if (strcmp(responseErr.c_str(), "110") == 0 || strcmp(responseErr.c_str(), "111") == 0)
        {
            gainToken();
            return "token失效了，已尝试重新获取，请试试看吧！";
        }

/**
 * @brief Own and retain the outPutText state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        String outPutText = doc["result"];

        _LOG("\r\n%s\r\n", outPutText.c_str());

/**
 * @brief Own and retain the outPutText state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        return outPutText;
    }
    else
    {
        _LOG("[HTTP] GET... failed, error: %s\n", http_client.errorToString(httpResponseCode).c_str());
        http_client.end();

        return "<error>";
    }
}

/* 获取Token */
/**
 * @brief Execute the gainToken operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 */
void BaiduErnieBot::gainToken(void)
{
    // param
/**
 * @brief Own and retain the http_client state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    HTTPClient http_client;
/**
 * @brief Own and retain the prefs state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    Preferences prefs;
/**
 * @brief Own and retain the response state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    String response;

    // 注意，要把下面网址中的your_apikey和your_secretkey替换成自己的API Key和Secret Key
    // http_client.begin("https://aip.baidubce.com/oauth/2.0/token?grant_type=client_credentials&client_id=your_apikey&client_secret=your_secretkey");
    http_client.begin("https://aip.baidubce.com/oauth/2.0/token?grant_type=client_credentials&client_id=Psp49YQ4FFrzrqbiHK7xxxxx&client_secret=BPx8GurbpL640iq4O9xj1soySTzxxxxx");
    http_client.addHeader("Content-Type", "application/json");

    // GET
/**
 * @brief Own and retain the httpResponseCode state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    int httpResponseCode;
/**
 * @brief Execute the http_client.GET operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    httpResponseCode = http_client.GET();

    if (httpResponseCode == HTTP_CODE_OK)
    {
/**
 * @brief Execute the http_client.getString operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
        response = http_client.getString();
        http_client.end();

        // Parse JSON response
/**
 * @brief Execute the doc operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
        DynamicJsonDocument doc(2048);
        deserializeJson(doc, response);

        // access_token
/**
 * @brief Own and retain the token state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        String token = doc["access_token"];
        _LOG("[GPT] Token: %s\n", token.c_str());

        // Storage
        prefs.begin("SaAPI");
        prefs.putString("BaiduBot", token);
        _LOG("[Storage] BaiduBotToken: %s\n", prefs.getString("BaiduBot").c_str());
        prefs.end();

        // refresh local token 更新本地token
        _token = token;
    }
    else
    {
        _LOG("[HTTP] GET... failed, error: %s\n", http_client.errorToString(httpResponseCode).c_str());
        http_client.end();
    }
}

/* 从flash中获取token到本地 */
/**
 * @brief Execute the getToken operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 */
void BaiduErnieBot::getToken(void)
{
    // param
/**
 * @brief Own and retain the prefs state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    Preferences prefs;
    prefs.begin("SaAPI");
/**
 * @brief Execute the prefs.getString operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    _token = prefs.getString("BaiduBot");

    _LOG("[Storage] getBaiduBotToken: %s\n", _token.c_str());
    prefs.end();
}
