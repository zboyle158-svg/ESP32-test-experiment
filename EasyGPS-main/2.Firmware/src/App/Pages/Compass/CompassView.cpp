#include "CompassView.h"
#include <stdarg.h>
#include <stdio.h>

using namespace Page;

/**
 * @brief Create and register the LVGL objects owned by Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param root Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void CompassView::Create(lv_obj_t *root)
{
    // 画布的创建
/**
 * @brief Create and register the LVGL objects owned by MainCont_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param root Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    MainCont_Create(root);
/**
 * @brief Create and register the LVGL objects owned by BtnCont_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param root Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    BtnCont_Create(root);

    // 动画的创建
    ui.anim_timeline = lv_anim_timeline_create();
    ui.anim_timelineClick = lv_anim_timeline_create();

#define ANIM_DEF(start_time, obj, attr, start, end) \
    {start_time, obj, LV_ANIM_EXEC(attr), start, end, 500, lv_anim_path_ease_out, true}

#define ANIM_OPA_DEF(start_time, obj) \
    ANIM_DEF(start_time, obj, opa_scale, LV_OPA_COVER, LV_OPA_TRANSP)
    lv_anim_timeline_wrapper_t wrapper[] =
        {
            // {2000, ui.mainCont.cont, (lv_anim_exec_xcb_t)lv_obj_set_opa_scale, LV_OPA_TRANSP, LV_OPA_COVER, 500, lv_anim_path_ease_out, true},
            {500, ui.mainCont.img, (lv_anim_exec_xcb_t)lv_obj_set_img_opa_scale, LV_OPA_TRANSP, LV_OPA_COVER, 500, lv_anim_path_ease_out, true},
            LV_ANIM_TIMELINE_WRAPPER_END // 这个标志着结构体成员结束，不能省略，在下面函数lv_anim_timeline_add_wrapper的轮询中做判断条件
        };
    lv_anim_timeline_add_wrapper(ui.anim_timeline, wrapper);

    lv_coord_t xOriginal = lv_obj_get_x_aligned(lv_obj_get_child(ui.btnCont.cont, 1));
    lv_coord_t yOriginal = lv_obj_get_y_aligned(lv_obj_get_child(ui.btnCont.cont, 1));

    lv_anim_timeline_wrapper_t wrapperForClick[] =
        {
            ANIM_DEF(0, lv_obj_get_child(ui.btnCont.cont, 1), x, xOriginal, xOriginal - 30),
            ANIM_OPA_DEF(300, lv_obj_get_child(ui.btnCont.cont, 1)),
            {300, lv_obj_get_child(ui.btnCont.cont, 1), (lv_anim_exec_xcb_t)lv_obj_set_shadow_opa_scale, LV_OPA_COVER, LV_OPA_TRANSP, 500, lv_anim_path_ease_out, true},

            ANIM_DEF(0, lv_obj_get_child(ui.btnCont.cont, 2), x, xOriginal, xOriginal - 21),
            ANIM_DEF(0, lv_obj_get_child(ui.btnCont.cont, 2), y, yOriginal, yOriginal - 21),
            ANIM_OPA_DEF(300, lv_obj_get_child(ui.btnCont.cont, 2)),
            {300, lv_obj_get_child(ui.btnCont.cont, 2), (lv_anim_exec_xcb_t)lv_obj_set_shadow_opa_scale, LV_OPA_COVER, LV_OPA_TRANSP, 500, lv_anim_path_ease_out, true},

            ANIM_DEF(0, lv_obj_get_child(ui.btnCont.cont, 3), y, yOriginal, yOriginal - 30),
            ANIM_OPA_DEF(300, lv_obj_get_child(ui.btnCont.cont, 3)),
            {300, lv_obj_get_child(ui.btnCont.cont, 3), (lv_anim_exec_xcb_t)lv_obj_set_shadow_opa_scale, LV_OPA_COVER, LV_OPA_TRANSP, 500, lv_anim_path_ease_out, true},

            ANIM_DEF(0, lv_obj_get_child(ui.btnCont.cont, 4), x, xOriginal, xOriginal + 21),
            ANIM_DEF(0, lv_obj_get_child(ui.btnCont.cont, 4), y, yOriginal, yOriginal - 21),
            ANIM_OPA_DEF(300, lv_obj_get_child(ui.btnCont.cont, 4)),
            {300, lv_obj_get_child(ui.btnCont.cont, 4), (lv_anim_exec_xcb_t)lv_obj_set_shadow_opa_scale, LV_OPA_COVER, LV_OPA_TRANSP, 500, lv_anim_path_ease_out, true},

            ANIM_DEF(0, lv_obj_get_child(ui.btnCont.cont, 5), x, xOriginal, xOriginal + 30),
            ANIM_OPA_DEF(300, lv_obj_get_child(ui.btnCont.cont, 5)),
            {300, lv_obj_get_child(ui.btnCont.cont, 5), (lv_anim_exec_xcb_t)lv_obj_set_shadow_opa_scale, LV_OPA_COVER, LV_OPA_TRANSP, 500, lv_anim_path_ease_out, true},

            ANIM_DEF(0, lv_obj_get_child(ui.btnCont.cont, 6), x, xOriginal, xOriginal + 21),
            ANIM_DEF(0, lv_obj_get_child(ui.btnCont.cont, 6), y, yOriginal, yOriginal + 21),
            ANIM_OPA_DEF(300, lv_obj_get_child(ui.btnCont.cont, 6)),
            {300, lv_obj_get_child(ui.btnCont.cont, 6), (lv_anim_exec_xcb_t)lv_obj_set_shadow_opa_scale, LV_OPA_COVER, LV_OPA_TRANSP, 500, lv_anim_path_ease_out, true},

            ANIM_DEF(0, lv_obj_get_child(ui.btnCont.cont, 7), y, yOriginal, yOriginal + 30),
            ANIM_OPA_DEF(300, lv_obj_get_child(ui.btnCont.cont, 7)),
            {300, lv_obj_get_child(ui.btnCont.cont, 7), (lv_anim_exec_xcb_t)lv_obj_set_shadow_opa_scale, LV_OPA_COVER, LV_OPA_TRANSP, 500, lv_anim_path_ease_out, true},

            ANIM_DEF(0, lv_obj_get_child(ui.btnCont.cont, 8), x, xOriginal, xOriginal - 21),
            ANIM_DEF(0, lv_obj_get_child(ui.btnCont.cont, 8), y, yOriginal, yOriginal + 21),
            ANIM_OPA_DEF(300, lv_obj_get_child(ui.btnCont.cont, 8)),
            {300, lv_obj_get_child(ui.btnCont.cont, 8), (lv_anim_exec_xcb_t)lv_obj_set_shadow_opa_scale, LV_OPA_COVER, LV_OPA_TRANSP, 500, lv_anim_path_ease_out, true},

            LV_ANIM_TIMELINE_WRAPPER_END // 这个标志着结构体成员结束，不能省略，在下面函数lv_anim_timeline_add_wrapper的轮询中做判断条件
        };
    lv_anim_timeline_add_wrapper(ui.anim_timelineClick, wrapperForClick);
}

/**
 * @brief Delete LVGL objects owned by CompassView.
 */
void CompassView::Delete()
{
    if (ui.anim_timeline)
    {
        lv_anim_timeline_del(ui.anim_timeline);
        ui.anim_timeline = nullptr;
    }
    if (ui.anim_timelineClick)
    {
        lv_anim_timeline_del(ui.anim_timelineClick);
        ui.anim_timelineClick = nullptr;
    }
}

/**
 * @brief Execute the AppearAnimStart operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param reverse Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void CompassView::AppearAnimStart(bool reverse) // 开始开场动画
{
    lv_anim_timeline_set_reverse(ui.anim_timeline, reverse);
    lv_anim_timeline_start(ui.anim_timeline);
}

/**
 * @brief Execute the AppearAnimClick operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param reverse Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void CompassView::AppearAnimClick(bool reverse) // 按钮动画
{
    lv_anim_timeline_set_reverse(ui.anim_timelineClick, reverse);
    lv_anim_timeline_start(ui.anim_timelineClick);
}

/**
 * @brief Create and register the LVGL objects owned by MainCont_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param par Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void CompassView::MainCont_Create(lv_obj_t *par)
{
    lv_obj_t *cont = lv_obj_create(par);
    lv_obj_remove_style_all(cont);
    lv_obj_set_size(cont, LV_HOR_RES, LV_VER_RES);
    lv_obj_clear_flag(cont, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(cont, lv_color_hex(0x000000), 0);
    lv_obj_set_style_bg_opa(cont, LV_OPA_COVER, 0);
    lv_obj_center(cont);
    ui.mainCont.cont = cont;

    lv_obj_t *img = lv_img_create(cont);
    lv_obj_set_size(img, 240, 240);
    lv_img_set_src(img, ResourcePool::GetImage("compass_bg"));
    lv_obj_align(img, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_img_opa(img, LV_OPA_COVER, 0);
    ui.mainCont.img = img;

    lv_obj_t *label = lv_label_create(cont);
    lv_obj_set_style_text_font(label, ResourcePool::GetFont("compass_24"), 0);
    lv_obj_set_style_text_color(label, lv_color_hex(0xA0A6A5), 0);
    lv_obj_center(label);
    lv_label_set_text(label, "北0°");
    ui.mainCont.label[label_angle] = label;
}

/**
 * @brief Create and register the LVGL objects owned by CalibrationCont_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param par Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void CompassView::CalibrationCont_Create(lv_obj_t *par)
{
    lv_obj_t *cont = lv_obj_create(par);
    lv_obj_remove_style_all(cont);
    lv_obj_set_size(cont, LV_HOR_RES, LV_VER_RES);

    lv_obj_set_style_bg_img_src(cont, ResourcePool::GetImage("compass_bg"), 0); // lv_obj_set_style_bg_img_src用于设置对象的背景图像源。通过这个函数可以为指定的对象设置背景图像，可以是内存中的图片数据，也可以是文件路径

    lv_obj_set_style_bg_opa(cont, LV_OPA_COVER, 0);
    lv_obj_set_style_bg_color(cont, lv_color_hex(0x000000), 0);
    lv_obj_align(cont, LV_ALIGN_CENTER, 0, 0);

    ui.calibrationCont.cont = cont;

    // lv_obj_t *label = lv_label_create(cont);
    // lv_label_set_text(label, "CLICK IT!");

    // lv_obj_set_style_text_font(label, &lv_font_montserrat_32, 0);
    // lv_obj_set_style_text_color(label, lv_color_hex(0x236952), 0);

    // lv_obj_align(label, LV_ALIGN_CENTER, 0, -30);

    // ui.labelCont.label = label;
}

/**
 * @brief Create and register the LVGL objects owned by BtnCont_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param par Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void CompassView::BtnCont_Create(lv_obj_t *par) // 按钮容器画布的创建
{
    lv_obj_t *cont = lv_obj_create(par);
    lv_obj_remove_style_all(cont);
    lv_obj_set_size(cont, lv_pct(70), lv_pct(70));

    lv_obj_set_style_bg_opa(cont, LV_OPA_COVER, 0);
    lv_obj_set_style_bg_color(cont, lv_color_hex(0x6a8d6d), 0);
    lv_obj_align(cont, LV_ALIGN_CENTER, 0, 0);

    lv_obj_set_style_radius(cont, 16, LV_PART_MAIN);

    lv_obj_set_style_shadow_width(cont, 10, 0);
    lv_obj_set_style_shadow_ofs_x(cont, 5, 0);
    lv_obj_set_style_shadow_ofs_y(cont, 5, 0);
    lv_obj_set_style_shadow_color(cont, lv_color_hex(0x5d8c3d), 0);
    lv_obj_set_style_shadow_spread(cont, 0, 0);
    lv_obj_set_style_shadow_opa(cont, LV_OPA_COVER, 0);

    ui.btnCont.cont = cont;

/**
 * @brief Create and register the LVGL objects owned by Btn_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param cont Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    ui.btnCont.btn = Btn_Create(cont, ResourcePool::GetImage("start"), 30);

    /* Render octagon explode */
/**
 * @brief Create and register the LVGL objects owned by RoundRect_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param cont Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    lv_obj_t *roundRect_1 = RoundRect_Create(cont, 0, 30);
/**
 * @brief Create and register the LVGL objects owned by RoundRect_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param cont Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    lv_obj_t *roundRect_2 = RoundRect_Create(cont, 0, 30);
/**
 * @brief Create and register the LVGL objects owned by RoundRect_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param cont Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    lv_obj_t *roundRect_3 = RoundRect_Create(cont, 0, 30);
/**
 * @brief Create and register the LVGL objects owned by RoundRect_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param cont Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    lv_obj_t *roundRect_4 = RoundRect_Create(cont, 0, 30);
/**
 * @brief Create and register the LVGL objects owned by RoundRect_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param cont Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    lv_obj_t *roundRect_5 = RoundRect_Create(cont, 0, 30);
/**
 * @brief Create and register the LVGL objects owned by RoundRect_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param cont Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    lv_obj_t *roundRect_6 = RoundRect_Create(cont, 0, 30);
/**
 * @brief Create and register the LVGL objects owned by RoundRect_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param cont Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    lv_obj_t *roundRect_7 = RoundRect_Create(cont, 0, 30);
/**
 * @brief Create and register the LVGL objects owned by RoundRect_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param cont Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    lv_obj_t *roundRect_8 = RoundRect_Create(cont, 0, 30);

    lv_obj_t *label = lv_label_create(cont);
    lv_obj_set_style_text_font(label, ResourcePool::GetFont("compass_24"), 0);
    lv_obj_set_style_text_color(label, lv_color_hex(0x236952), 0);
    lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 30);
    lv_label_set_text(label, "软件角校准");

    ui.btnCont.label = label;
}

/**
 * @brief Create and register the LVGL objects owned by Btn_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param par Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param img_src Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param y_ofs Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
lv_obj_t *CompassView::Btn_Create(lv_obj_t *par, const void *img_src, lv_coord_t y_ofs)
{
    lv_obj_t *obj = lv_obj_create(par);
    lv_obj_remove_style_all(obj);
    lv_obj_set_size(obj, 105, 31);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_align(obj, LV_ALIGN_CENTER, 0, y_ofs);
    lv_obj_set_style_bg_img_src(obj, img_src, 0);

    lv_obj_set_style_bg_opa(obj, LV_OPA_COVER, 0);
    lv_obj_set_style_width(obj, 65, LV_STATE_PRESSED); // 设置button按下时的长宽
    lv_obj_set_style_height(obj, 25, LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0x356b8c), 0);                // 设置按钮默认的颜色
    lv_obj_set_style_bg_color(obj, lv_color_hex(0x242947), LV_STATE_PRESSED); // 设置按钮在被按下时的颜色
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xf2daaa), LV_STATE_FOCUSED); // 设置按钮在被聚焦时的颜色
    lv_obj_set_style_radius(obj, 9, 0);                                       // 按钮画圆角

/**
 * @brief Own and retain the tran state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    static lv_style_transition_dsc_t tran;
/**
 * @brief Own and retain the prop state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    static const lv_style_prop_t prop[] = {LV_STYLE_WIDTH, LV_STYLE_HEIGHT, LV_STYLE_PROP_INV};
    lv_style_transition_dsc_init(
        &tran,
        prop,
        lv_anim_path_ease_out,
        150,
        0,
        nullptr);
    lv_obj_set_style_transition(obj, &tran, LV_STATE_PRESSED);
    lv_obj_set_style_transition(obj, &tran, LV_STATE_FOCUSED);

    lv_obj_update_layout(obj);

/**
 * @brief Own and retain the obj state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    return obj;
}

/**
 * @brief Create and register the LVGL objects owned by RoundRect_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param par Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param x_ofs Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param y_ofs Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
lv_obj_t *CompassView::RoundRect_Create(lv_obj_t *par, lv_coord_t x_ofs, lv_coord_t y_ofs)
{
    /* Render octagon explode */
    lv_obj_t *roundRect = lv_obj_create(par);
    lv_obj_remove_style_all(roundRect);
    lv_obj_set_size(roundRect, 10, 10);
    lv_obj_set_style_radius(roundRect, 2, 0);

    lv_obj_set_style_shadow_width(roundRect, 10, 0);
    lv_obj_set_style_shadow_ofs_x(roundRect, 1, 0);
    lv_obj_set_style_shadow_ofs_y(roundRect, 1, 0);
    lv_obj_set_style_shadow_color(roundRect, lv_color_hex(0x5d8c3d), 0);
    lv_obj_set_style_shadow_spread(roundRect, 1, 0);
    lv_obj_set_style_shadow_opa(roundRect, LV_OPA_TRANSP, 0);

    lv_obj_set_style_bg_color(roundRect, lv_color_hex(0x88d35e), 0);
    lv_obj_set_style_bg_opa(roundRect, LV_OPA_TRANSP, 0);
    lv_obj_align(roundRect, LV_ALIGN_CENTER, x_ofs, y_ofs);

/**
 * @brief Own and retain the roundRect state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    return roundRect;
}
