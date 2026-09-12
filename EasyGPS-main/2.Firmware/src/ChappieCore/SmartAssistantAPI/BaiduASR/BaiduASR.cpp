#include "BaiduASR.h"

/* 百度在线语音识别 */
/**
 * @brief Execute the getRecognitionResult operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param rawData Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param len Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
String BaiduASR::getRecognitionResult(int16_t *rawData, uint32_t len)
{
/**
 * @brief Own and retain the http_client state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    HTTPClient http_client;

    _LOG("[ASR] Start recognition!\r\n");

    // String length(len);

    memset(_payLoad, '\0', strlen(_payLoad)); // 将数组清空
    strcat(_payLoad, "{");
    strcat(_payLoad, "\"format\":\"pcm\",");
    strcat(_payLoad, "\"rate\":16000,");       // 采样率，只有16000、8000两个固定采样率
    strcat(_payLoad, "\"dev_pid\":80001,");    // 1537(标准版) // 80001(极速版)                                                                // 中文普通话
    strcat(_payLoad, "\"channel\":1,");        // 只有单声道，填1
    strcat(_payLoad, "\"cuid\":\"hugozkl\","); // 识别码，可以写任意字符，但最好唯一
    strcat(_payLoad, "\"token\":\"");          // token，这里需要修改成自己申请到的token
    strcat(_payLoad, _token.c_str());
    strcat(_payLoad, "\",");
    strcat(_payLoad, "\"len\":"); // 数据长度，如果传输的数据长度改变了，记得修改该值，该值是ADC采集的数据字节数，不是base64编码后的长度
    strcat(_payLoad, String(len).c_str());
    strcat(_payLoad, ",");
    strcat(_payLoad, "\"speech\":\"");
    strcat(_payLoad, base64::encode((uint8_t *)rawData, len).c_str()); // base64编码数据
    strcat(_payLoad, "\"");
    strcat(_payLoad, "}");

    // HTTP POST
/**
 * @brief Own and retain the httpResponseCode state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    int httpResponseCode;
    http_client.begin(apiASRUrl);
    http_client.addHeader("Content-Type", "application/json");

    http_client.setTimeout(5000); // 5s超时时间

/**
 * @brief Execute the http_client.POST operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param _payLoad Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    httpResponseCode = http_client.POST(_payLoad);

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
        String responseErr = doc["err_no"];
        printf("[ASR] Err: %s \n", responseErr);
        if (strcmp(responseErr.c_str(), "3302") == 0 || strcmp(responseErr.c_str(), "3300") == 0)
        {
            gainToken();
            return "<error>";
        }

        // output 输出结果
/**
 * @brief Own and retain the outPutText state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        String outPutText = doc["result"];
        // 去掉首尾的[""]
/**
 * @brief Execute the outPutText.substring operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
        outPutText = outPutText.substring(2);
/**
 * @brief Execute the outPutText.substring operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
        outPutText = outPutText.substring(0, outPutText.length() - 2);

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
void BaiduASR::gainToken(void)
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
    http_client.begin("https://aip.baidubce.com/oauth/2.0/token?grant_type=client_credentials&client_id=souCWerKxgs7khvJE3Bxxxxx&client_secret=92b50AWi00ZEZPyAQTZnMwwEPc4xxxxx");

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
        _LOG("[ASR] Token: %s\n", token.c_str());

        // Storage
        prefs.begin("SaAPI");
        prefs.putString("BaiduVoice", token);
        _LOG("[Storage] BaiduVoiceToken: %s\n", prefs.getString("BaiduVoice").c_str());
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
void BaiduASR::getToken(void)
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
    _token = prefs.getString("BaiduVoice");

    _LOG("[Storage] getBaiduVoiceToken: %s\n", _token.c_str());
    prefs.end();
}
