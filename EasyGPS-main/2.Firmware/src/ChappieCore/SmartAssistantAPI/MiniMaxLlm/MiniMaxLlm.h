/**
 * @file MiniMaxLlm.h
 * @author kkl
 * @brief
 * @version 0.1
 * @date 2024-05-06
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include <Arduino.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

class MiniMaxLlm
{

public:
/**
 * @brief Construct or destroy the MiniMaxLlm object.
 * @return Operation result or status; inspect it before using dependent state.
 */
    MiniMaxLlm() {}
    ~MiniMaxLlm() {}

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
 * @return Operation result or status; inspect it before using dependent state.
 */
    String getToken(void);

private:
/**
 * @brief Own and retain the apiKey state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    const String apiKey = "xxxxxxxxxxxxxxxxxxxI1NiIsInR5cCI6IkpXVCJ9.eyJHcm91cE5hbWUiOiJDaGVuc2hhbiIsIlVzZXJOYW1lIjoiQ2hlbnNoYW4iLCJBY2NvdW50IjoiIiwiU3ViamVjdElEIjoiMTc4MjU4ODUwOTcwNjUyMjkxMSIsIlBob25lIjoiMTMyNDYxNjYyMTAiLCJHcm91cElEIjoiMTc4MjU4ODUwOTY5ODEzNDMwMyIsIlBhZ2VOYW1lIjoiIiwiTWFpbCI6IiIsIkNyZWF0ZVRpbWUiOiIyMDI0LTA1LTA2IDIyOjM0OjM4IiwiaXNzIjoibWluaW1heCJ9.D_rzFIdaHRBvQ68XCgYKNWs5DkupWPW8RApkDwjWE9A43StEi04Y_UxdFzYABVVce3EJNxL0mSc3nzDN1-0U_QmkJvjGUFioA81tcoGnDn-EWitv7h70xBmQraqc2-zc8rXW8nKYNA5hLMMA5j35whNLqwEBnMgbCrWUNLfmd1TfY80m1uLCErwzlvhh8Hd2EkXLq0SQLWCdbBlHy2Gw9EYle_osy_kvPJhl7mmRmQej1IfQrZUaP5y7bXznGG3gSluT85NOzSCRHOhFSIUQMTUJOInaoFVH37-Tgd2-mkM4MKF9koseg3SmgVxLmTmsZQK4U57BLUeZo1Qbfla3tw";
    const String apiUrl = "https://api.minimax.chat/v1/text/chatcompletion_v2";
};

/**
 * @brief Define the way to format logout
 *
 */
#define _LOG(format, args...) printf(format, ##args)
