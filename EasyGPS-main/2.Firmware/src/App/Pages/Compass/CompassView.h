#ifndef __COMPASS_VIEW_H
#define __COMPASS_VIEW_H

#include "../Page.h"

namespace Page
{
    static const char *rotation_ch[] = {
        "西南%d°",
        "西%d°",
        "西北%d°",
        "北%d°",
        "东北%d°",
        "东%d°",
        "东南%d°",
        "南%d°"};

    enum
    {
        label_start_calibration,
        label_x_min,
        label_y_min,
        label_z_min,
        label_x_max,
        label_y_max,
        label_z_max,
        label_tip,
        label_angle,
        label_cnt
    };

    class CompassView
    {
    public:

    public:
        struct
        {
            struct
            {
                lv_obj_t *cont;
                lv_obj_t *img;
                lv_obj_t *label[label_cnt];

/**
 * @brief Own and retain the mainCont state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
            } mainCont;

            struct 
            {
                lv_obj_t *cont;
/**
 * @brief Own and retain the calibrationCont state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
            } calibrationCont;
            
            struct
            {
                lv_obj_t *cont;
                lv_obj_t *label;
                lv_obj_t *btn; 
/**
 * @brief Own and retain the btnCont state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
            } btnCont;

            lv_anim_timeline_t *anim_timeline;
            lv_anim_timeline_t *anim_timelineClick;
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
 * @brief Delete LVGL objects owned by CompassView.
 */
        void Delete();
/**
 * @brief Execute the AppearAnimStart operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param reverse Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
        void AppearAnimStart(bool reverse = false);
/**
 * @brief Execute the AppearAnimClick operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param reverse Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
        void AppearAnimClick(bool reverse = false);

    private:
/**
 * @brief Create and register the LVGL objects owned by MainCont_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param par Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
        void MainCont_Create(lv_obj_t *par);
/**
 * @brief Create and register the LVGL objects owned by CalibrationCont_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param par Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
        void CalibrationCont_Create(lv_obj_t *par);
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
 * @param img_src Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param y_ofs Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
        lv_obj_t *Btn_Create(lv_obj_t *par, const void *img_src, lv_coord_t y_ofs);
/**
 * @brief Create and register the LVGL objects owned by RoundRect_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param par Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param x_ofs Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param y_ofs Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
        lv_obj_t *RoundRect_Create(lv_obj_t *par, lv_coord_t x_ofs, lv_coord_t y_ofs);
    };

}

#endif // !__VIEW_H
