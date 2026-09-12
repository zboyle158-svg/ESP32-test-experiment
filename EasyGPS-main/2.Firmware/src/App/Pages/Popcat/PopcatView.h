#ifndef __POPCAT_VIEW_H
#define __POPCAT_VIEW_H

#include "../Page.h"

namespace Page
{

    class PopcatView
    {
    public:
    public:
        struct
        {

            struct
            {
                lv_obj_t *cont;
                lv_obj_t *imgPopCat;
/**
 * @brief Own and retain the popcatInfo state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
            } popcatInfo;

            lv_anim_timeline_t *anim_timeline;

/**
 * @brief Own and retain the ui state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        } ui;

/**
 * @brief Create and register the LVGL objects owned by Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param root Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
        void Create(lv_obj_t *root);
/**
 * @brief Delete LVGL objects owned by PopcatView.
 */
        void Delete();
/**
 * @brief Execute the AppearAnimStart operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param reverse Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
        void AppearAnimStart(bool reverse = false);

    private:
    };

}

#endif // !__VIEW_H
