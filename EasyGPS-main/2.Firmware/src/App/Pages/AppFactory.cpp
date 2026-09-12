/*
 * MIT License
 * Copyright (c) 2021 _VIFEXTech
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include "AppFactory.h"
#include "_Template/Template.h"
#include "Dialplate/Dialplate.h"
#include "SystemInfos/SystemInfos.h"
#include "StartUp/StartUp.h"
#include "Popcat/Popcat.h"
#include "LaunchOut/LaunchOut.h"
#include "WaveTable/WaveTable.h"
#include "Settings/Settings.h"
#include "SmartAssistant/SmartAssistant.h"
#include "Compass/Compass.h"
#include "LiveMap/LiveMap.h"
#include "BLEKeyboard/BLEKeyboard.h"

#define APP_CLASS_MATCH(className)         \
    do                                     \
    {                                      \
        if (strcmp(name, #className) == 0) \
        {                                  \
            return new Page::className;    \
        }                                  \
    } while (0)

/**
 * @brief Construct a concrete page based on its registered class name.
 * @param name Class name supplied by PageManager.
 * @return Heap-allocated page when matched; otherwise nullptr.
 *
 * @note A new page requires both an `APP_CLASS_MATCH` line here and an
 * `Install()` call in App_Init(). Missing either half causes navigation failure.
 */
/**
 * @brief Execute the CreatePage operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param name Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
PageBase *AppFactory::CreatePage(const char *name)
{
/**
 * @brief Execute the APP_CLASS_MATCH operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param Template Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    APP_CLASS_MATCH(Template);
/**
 * @brief Execute the APP_CLASS_MATCH operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param Dialplate Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    APP_CLASS_MATCH(Dialplate);
/**
 * @brief Execute the APP_CLASS_MATCH operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param SystemInfos Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    APP_CLASS_MATCH(SystemInfos);
    // APP_CLASS_MATCH(Startup);
/**
 * @brief Execute the APP_CLASS_MATCH operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param Popcat Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    APP_CLASS_MATCH(Popcat);
/**
 * @brief Execute the APP_CLASS_MATCH operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param LaunchOut Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    APP_CLASS_MATCH(LaunchOut);
/**
 * @brief Execute the APP_CLASS_MATCH operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param WaveTable Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    APP_CLASS_MATCH(WaveTable);
/**
 * @brief Execute the APP_CLASS_MATCH operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param Settings Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    APP_CLASS_MATCH(Settings);
/**
 * @brief Execute the APP_CLASS_MATCH operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param SmartAssistant Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    APP_CLASS_MATCH(SmartAssistant);
/**
 * @brief Execute the APP_CLASS_MATCH operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param Compass Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    APP_CLASS_MATCH(Compass);
/**
 * @brief Execute the APP_CLASS_MATCH operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param LiveMap Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    APP_CLASS_MATCH(LiveMap);
/**
 * @brief Execute the APP_CLASS_MATCH operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param BLEKeyboard Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    APP_CLASS_MATCH(BLEKeyboard);

/**
 * @brief Own and retain the nullptr state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    return nullptr;
}
