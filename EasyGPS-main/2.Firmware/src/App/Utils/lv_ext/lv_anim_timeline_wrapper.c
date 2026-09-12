#include "lv_anim_timeline_wrapper.h"

void lv_anim_timeline_add_wrapper(lv_anim_timeline_t* at, const lv_anim_timeline_wrapper_t* wrapper)
{
    for(uint32_t i = 0; wrapper[i].obj != NULL; i++)
    {
/**
 * @brief Own and retain the atw state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        const lv_anim_timeline_wrapper_t* atw = &wrapper[i];

/**
 * @brief Own and retain the a state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        lv_anim_t a;
        lv_anim_init(&a);
        lv_anim_set_var(&a, atw->obj);
        lv_anim_set_values(&a, atw->start, atw->end);
        lv_anim_set_exec_cb(&a, atw->exec_cb);
        lv_anim_set_time(&a, atw->duration);
        lv_anim_set_path_cb(&a, atw->path_cb);
        lv_anim_set_early_apply(&a, atw->early_apply);

        lv_anim_timeline_add(at, atw->start_time, &a);
    }
}
