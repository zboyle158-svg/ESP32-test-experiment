#ifndef LV_ANIM_TIMELINE_WRAPPER_H
#define LV_ANIM_TIMELINE_WRAPPER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

/*Data of anim_timeline*/
typedef struct {
/**
 * @brief Own and retain the start_time state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    uint32_t start_time;
/**
 * @brief Own and retain the obj state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    lv_obj_t* obj;
/**
 * @brief Own and retain the exec_cb state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    lv_anim_exec_xcb_t exec_cb;
/**
 * @brief Own and retain the start state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    int32_t start;
/**
 * @brief Own and retain the end state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    int32_t end;
/**
 * @brief Own and retain the duration state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    uint16_t duration;
/**
 * @brief Own and retain the path_cb state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    lv_anim_path_cb_t path_cb;
/**
 * @brief Own and retain the early_apply state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    bool early_apply;
/**
 * @brief Own and retain the lv_anim_timeline_wrapper_t state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
} lv_anim_timeline_wrapper_t;

/**********************
* GLOBAL PROTOTYPES
**********************/

/**
 * Start animation according to the timeline
 * @param anim_timeline  timeline array address
 * @param playback       whether to play in reverse
 * @return timeline total time spent
 */
void lv_anim_timeline_add_wrapper(lv_anim_timeline_t* at, const lv_anim_timeline_wrapper_t* wrapper);

/**********************
*      MACROS
**********************/

#define LV_ANIM_TIMELINE_WRAPPER_END {0, NULL}

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_ANIM_TIMELINE_wrapper_H*/
