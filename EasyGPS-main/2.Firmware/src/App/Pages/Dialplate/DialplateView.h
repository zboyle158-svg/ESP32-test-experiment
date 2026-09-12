#ifndef __DIALPLATE_VIEW_H
#define __DIALPLATE_VIEW_H

#include "../Page.h"

namespace Page
{

class DialplateView
{

public:
    typedef struct
    {
/**
 * @brief Own and retain the cont state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        lv_obj_t* cont;
/**
 * @brief Own and retain the lableValue state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        lv_obj_t* lableValue;
/**
 * @brief Own and retain the lableUnit state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        lv_obj_t* lableUnit;
/**
 * @brief Own and retain the SubInfo_t state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    } SubInfo_t;

public:
    struct
    {
        struct
        {
/**
 * @brief Own and retain the cont state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
            lv_obj_t* cont;
/**
 * @brief Own and retain the labelSpeed state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
            lv_obj_t* labelSpeed;
/**
 * @brief Own and retain the labelUint state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
            lv_obj_t* labelUint;
/**
 * @brief Own and retain the topInfo state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        } topInfo;

        struct
        {
/**
 * @brief Own and retain the cont state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
            lv_obj_t* cont;
/**
 * @brief Own and retain the labelInfoGrp state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
            SubInfo_t labelInfoGrp[4];
/**
 * @brief Own and retain the bottomInfo state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        } bottomInfo;

        struct
        {
/**
 * @brief Own and retain the cont state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
            lv_obj_t* cont;
/**
 * @brief Own and retain the btnMap state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
            lv_obj_t* btnMap;
/**
 * @brief Own and retain the btnRec state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
            lv_obj_t* btnRec;
/**
 * @brief Own and retain the btnMenu state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
            lv_obj_t* btnMenu;
/**
 * @brief Own and retain the btnCont state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        } btnCont;

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

/**
 * @brief Create and register the LVGL objects owned by Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param root Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
    void Create(lv_obj_t* root);
/**
 * @brief Delete LVGL objects owned by DialplateView.
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
 * @brief Create and register the LVGL objects owned by TopInfo_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param par Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
    void TopInfo_Create(lv_obj_t* par);
/**
 * @brief Create and register the LVGL objects owned by BottomInfo_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param par Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
    void BottomInfo_Create(lv_obj_t* par);
/**
 * @brief Create and register the LVGL objects owned by SubInfoGrp_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param par Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param info Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param unitText Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
    void SubInfoGrp_Create(lv_obj_t* par, SubInfo_t* info, const char* unitText);
/**
 * @brief Create and register the LVGL objects owned by BtnCont_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param par Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
    void BtnCont_Create(lv_obj_t* par);
/**
 * @brief Create and register the LVGL objects owned by Btn_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param par Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param img_src Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param x_ofs Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    lv_obj_t* Btn_Create(lv_obj_t* par, const void* img_src, lv_coord_t x_ofs);
};

}

#endif // !__VIEW_H
