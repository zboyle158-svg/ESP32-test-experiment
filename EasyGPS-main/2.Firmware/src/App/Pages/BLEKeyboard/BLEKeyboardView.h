#ifndef __BLEKEYBOARD_VIEW_H
#define __BLEKEYBOARD_VIEW_H

#include "../Page.h"

namespace Page
{

    class BLEKeyboardView
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

            struct
            {
                lv_obj_t *cont;

/**
 * @brief Own and retain the btnNextTrack state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
                btnCont btnNextTrack;
/**
 * @brief Own and retain the btnPrevTrack state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
                btnCont btnPrevTrack;
/**
 * @brief Own and retain the btnPause state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
                btnCont btnPause;
/**
 * @brief Own and retain the btnMute state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
                btnCont btnMute;
/**
 * @brief Own and retain the btnVolumeUp state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
                btnCont btnVolumeUp;
/**
 * @brief Own and retain the btnVolumeDown state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
                btnCont btnVolumeDown;

/**
 * @brief Own and retain the musicCtrlCont state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
            } musicCtrlCont;

            struct
            {
                lv_obj_t *cont;

/**
 * @brief Own and retain the btnDirUp state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
                btnCont btnDirUp;
/**
 * @brief Own and retain the btnDirDown state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
                btnCont btnDirDown;
/**
 * @brief Own and retain the btnPaste state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
                btnCont btnPaste;
/**
 * @brief Own and retain the btnCopy state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
                btnCont btnCopy;
/**
 * @brief Own and retain the btnCut state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
                btnCont btnCut;
/**
 * @brief Own and retain the btnWithdraw state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
                btnCont btnWithdraw;

/**
 * @brief Own and retain the directionCtrlCont state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
            } directionCtrlCont;

            struct
            {
                lv_obj_t *cont;
                lv_obj_t *btnMouse;

/**
 * @brief Own and retain the mouseMoveCtrlCont state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
            } mouseMoveCtrlCont;

            struct
            {
                lv_obj_t *cont;

/**
 * @brief Own and retain the btnLeft state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
                btnCont btnLeft;
/**
 * @brief Own and retain the btnRight state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
                btnCont btnRight;
/**
 * @brief Own and retain the btnBack state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
                btnCont btnBack;
/**
 * @brief Own and retain the btnForward state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
                btnCont btnForward;
/**
 * @brief Own and retain the btnPageUp state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
                btnCont btnPageUp;
/**
 * @brief Own and retain the btnPageDown state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
                btnCont btnPageDown;

/**
 * @brief Own and retain the mouseClickCtrlCont state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
            } mouseClickCtrlCont;

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
 * @brief Delete LVGL objects owned by BLEKeyboardView.
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
 * @param c Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
        lv_obj_t *BtnCont_Create(lv_obj_t *par, uint32_t c = 0xffffff);
/**
 * @brief Create and register the LVGL objects owned by BtnKeyboard_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param par Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param cont Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param name Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param img_src Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
        void BtnKeyboard_Create(lv_obj_t *par, btnCont *cont, const char *name, const void *img_src);
/**
 * @brief Create and register the LVGL objects owned by MouseCircle_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param par Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
        lv_obj_t *MouseCircle_Create(lv_obj_t *par);
    };

}

#endif // !__VIEW_H
