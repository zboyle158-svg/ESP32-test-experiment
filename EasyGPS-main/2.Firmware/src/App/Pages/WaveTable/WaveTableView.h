#ifndef __WAVETABLE_VIEW_H
#define __WAVETABLE_VIEW_H

#include "../Page.h"

namespace Page
{
    class WaveTableView
    {
    public:
        struct btnCont
        {
            lv_obj_t *btn;
            lv_obj_t *img;
            lv_obj_t *label;
        };

    public:
        struct
        {
            lv_obj_t *cont;

/**
 * @brief Own and retain the btnA state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
            btnCont btnA;
/**
 * @brief Own and retain the btnB state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
            btnCont btnB;
/**
 * @brief Own and retain the btnC state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
            btnCont btnC;
/**
 * @brief Own and retain the btnD state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
            btnCont btnD;
/**
 * @brief Own and retain the btnE state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
            btnCont btnE;
/**
 * @brief Own and retain the btnF state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
            btnCont btnF;
/**
 * @brief Own and retain the btnG state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
            btnCont btnG;

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
 * @brief Delete LVGL objects owned by WaveTableView.
 */
        void Delete();
/**
 * @brief Execute the AppearAnimStart operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param reverse Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
        void AppearAnimStart(bool reverse = false);

    private:
/**
 * @brief Create and register the LVGL objects owned by BtnCont_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param par Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
        void BtnCont_Create(lv_obj_t *par);
/**
 * @brief Create and register the LVGL objects owned by Btn_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param par Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param cont Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param name Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param img_src Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
        void Btn_Create(lv_obj_t *par, btnCont *cont, const char *name, const void *img_src);
    };

}

#endif // !__VIEW_H
