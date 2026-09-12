#include "MiniMaxLlm.h"

/* 百度文心一言 */
/**
 * @brief Execute the getResponse operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param inputText Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
String MiniMaxLlm::getResponse(String inputText)
{
/**
 * @brief Own and retain the http_client state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    HTTPClient http_client;

    http_client.begin(apiUrl);
    http_client.addHeader("Content-Type", "application/json");
/**
 * @brief Execute the String operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    String tokenKey = String("Bearer ") + apiKey;
    http_client.addHeader("Authorization", tokenKey);

    http_client.setTimeout(20000); // 20s的超时时间

    // String payload = "{\"messages\":[{\"role\":\"user\",\"content\":\"请用一句话回答我，严格规定在二十个字以内。\"},{\"role\":\"assistant\",\"content\":\"好的。\"},{\"role\":\"user\",\"content\":\"" + inputText + "\"}]}";
/**
 * @brief Own and retain the payload state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    String payload = "{\"model\":\"abab5.5s-chat\",\"messages\":[{\"role\": \"system\",\"content\": \"你是生活助手机器人贾维斯，要求下面的回答严格控制在64字符以内。\"},{\"role\":\"user\",\"content\":\"" + inputText + "\"}]}";

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

        // String outPutText = doc["result"];
/**
 * @brief Own and retain the outPutText state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        String outPutText = doc["choices"][0]["message"]["content"];

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
