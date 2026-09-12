/**
 * @file BaiduTTS.h
 * @author kkl
 * @brief
 * @version 0.1
 * @date 2024-04-07
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include <Arduino.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Preferences.h> // 用于参数数据的

class BaiduTTS
{

public:
/**
 * @brief Construct or destroy the BaiduTTS object.
 * @return Operation result or status; inspect it before using dependent state.
 */
    BaiduTTS() {}
/**
 * @brief Construct or destroy the BaiduTTS object.
 * @param payLoad Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    BaiduTTS(char *payLoad) : _payLoad(payLoad) {}
    ~BaiduTTS() { _payLoad = nullptr; }

/**
 * @brief Initialize BaiduTTS state and hardware or data resources.
 * @param payLoad Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
    void init(char *payLoad)
    {
        // load param 加载变量
        _payLoad = payLoad;
        getToken();
    }

/**
 * @brief Execute the getSynthesis operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param inputText Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param rawData Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param len Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    bool getSynthesis(String inputText, int16_t *rawData, int32_t *len);

/**
 * @brief Execute the getToken operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 */
    void getToken(void);

/**
 * @brief Execute the gainToken operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 */
    void gainToken(void);

private:
    char *_payLoad = nullptr;
/**
 * @brief Own and retain the _token state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    String _token = "";
    String apiTTSUrl = "http://tsn.baidu.com/text2audio";
};

/**
 * @brief Define the way to format logout
 *
 */
#define _LOG(format, args...) printf(format, ##args)
