/**
 * @file BaiduErnieBot.h
 * @author kkl
 * @brief
 * @version 0.1
 * @date 2024-04-06
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include <Arduino.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Preferences.h> // 用于参数数据的

class BaiduErnieBot
{

public:
/**
 * @brief Construct or destroy the BaiduErnieBot object.
 * @return Operation result or status; inspect it before using dependent state.
 */
    BaiduErnieBot() {}
    ~BaiduErnieBot() {}

/**
 * @brief Initialize BaiduErnieBot state and hardware or data resources.
 */
    void init(void)
    {
        // load param 加载变量
        getToken();
    }
    
/**
 * @brief Execute the getResponse operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param inputText Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    String getResponse(String inputText);

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
    // String _token = "24.a5491e2c24a7530134953afb40aa0a23.2592000.1718098342.282335-57964024";
/**
 * @brief Own and retain the _token state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    String _token = "";
    String apiErnieBotUrl = "https://aip.baidubce.com/rpc/2.0/ai_custom/v1/wenxinworkshop/chat/completions?access_token=";
    // https://aip.baidubce.com/rpc/2.0/ai_custom/v1/wenxinworkshop/chat/completions // ERNIE-3.5-8K
    // https://aip.baidubce.com/rpc/2.0/ai_custom/v1/wenxinworkshop/chat/completions_pro // ERNIE-4.0-8K
};

/**
 * @brief Define the way to format logout
 *
 */
#define _LOG(format, args...) printf(format, ##args)
