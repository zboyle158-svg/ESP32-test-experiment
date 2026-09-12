#include "HAL.h"
#include "lvgl.h"

#include "ChappieCore/ChappieCore.h"

/**
 * @brief Own and retain the Chappie state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
extern ChappieCore Chappie;

/**
 * @brief  背光亮度渐变，受lv_anim控制
 * @param  obj:无用
 * @param  brightness:亮度值
 * @retval None
 */
/**
 * @brief Execute the Backlight_AnimCallback operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param obj Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param brightness Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
static void Backlight_AnimCallback(void *obj, int32_t brightness)
{
/**
 * @brief Execute the Backlight_SetValue operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param brightness Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    HAL::Backlight_SetValue(brightness);
}

/**
 * @brief  背光初始化
 * @param  无
 * @retval 无
 */
/**
 * @brief Execute the Backlight_Init operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 */
void HAL::Backlight_Init()
{

}

/**
 * @brief  背光设置，渐变效果
 * @param  target:目标亮度(0~1000 -> 0~100%)
 * @retval 无
 */
/**
 * @brief Execute the Backlight_SetGradual operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param target Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param time Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void HAL::Backlight_SetGradual(uint16_t target, uint16_t time)
{
/**
 * @brief Own and retain the a state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)Backlight_AnimCallback);
    lv_anim_set_values(&a, Backlight_GetValue(), target);
    lv_anim_set_time(&a, time);
    lv_anim_set_path_cb(&a, lv_anim_path_ease_out);

    lv_anim_start(&a);
}

/**
 * @brief  获取背光亮度
 * @param  无
 * @retval 当前亮度(0~1000 -> 0~100%)
 */
/**
 * @brief Execute the Backlight_GetValue operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
uint16_t HAL::Backlight_GetValue(void)
{
    return Chappie.Lcd.getBrightness();
}

/**
 * @brief  设置背光亮度
 * @param  val: 亮度(0~1000 -> 0~100%)
 * @retval 无
 */
/**
 * @brief Execute the Backlight_SetValue operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param val Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void HAL::Backlight_SetValue(int16_t val)
{
    val = constrain(val, 0, 255);
    
/**
 * @brief Execute the Chappie.Lcd.setBrightness operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param val Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Chappie.Lcd.setBrightness((uint8_t)val);
}

/**
 * @brief  背光强制点亮
 * @param  en: 背光使能
 * @retval 无
 */
/**
 * @brief Execute the Backlight_ForceLit operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param en Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void HAL::Backlight_ForceLit(bool en)
{
/**
 * @brief Execute the Chappie.Lcd.light operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Chappie.Lcd.light();
}
