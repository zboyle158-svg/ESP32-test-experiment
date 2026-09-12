#ifndef __LAUNCHOUT_VIEW_H
#define __LAUNCHOUT_VIEW_H

#include "../Page.h"

namespace Page
{

class LaunchOutView
{
public:
/**
 * @brief Create and register the LVGL objects owned by Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param root Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
    void Create(lv_obj_t* root);
/**
 * @brief Delete LVGL objects owned by LaunchOutView.
 */
    void Delete();

public:
    struct
    {
        lv_obj_t *cont;
        lv_obj_t *circleFront;
        lv_obj_t *circleMiddle;
        lv_obj_t *circleBehind;
        lv_obj_t *square;
/**
 * @brief Own and retain the labelLogo state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        lv_obj_t* labelLogo;

/**
 * @brief Own and retain the anim_timeline state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        lv_anim_timeline_t* anim_timeline;
/**
 * @brief Own and retain the ui state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    } ui;

private:
};

}

#endif // !__VIEW_H
