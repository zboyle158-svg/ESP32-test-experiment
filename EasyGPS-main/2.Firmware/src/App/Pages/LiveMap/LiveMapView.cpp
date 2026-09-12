#include "LiveMapView.h"
#include "App/Config/Config.h"
#include <stdarg.h>
#include <stdio.h>

using namespace Page;

#if CONFIG_MAP_IMG_PNG_ENABLE
#include "Utils/lv_img_png/lv_img_png.h"
#  define TILE_IMG_CREATE  lv_img_png_create
#  define TILE_IMG_SET_SRC lv_img_png_set_src
#else
#  define TILE_IMG_CREATE  lv_img_create
#  define TILE_IMG_SET_SRC lv_img_set_src
#endif

/**
 * @brief Create and register the LVGL objects owned by Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param root Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param tileNum Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void LiveMapView::Create(lv_obj_t* root, uint32_t tileNum)
{
    lv_obj_set_style_bg_color(root, lv_color_white(), 0);

    lv_obj_t* label = lv_label_create(root);
    lv_obj_center(label);
    lv_obj_set_style_text_font(label, ResourcePool::GetFont("bahnschrift_17"), 0);
    lv_label_set_text(label, "LOADING...");
    ui.labelInfo = label;

/**
 * @brief Create and register the LVGL objects owned by Style_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Style_Create();
/**
 * @brief Create and register the LVGL objects owned by Map_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param root Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param tileNum Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Map_Create(root, tileNum);
/**
 * @brief Create and register the LVGL objects owned by ZoomCtrl_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param root Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    ZoomCtrl_Create(root);
/**
 * @brief Create and register the LVGL objects owned by SportInfo_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param root Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    SportInfo_Create(root);
}

/**
 * @brief Delete LVGL objects owned by LiveMapView.
 */
void LiveMapView::Delete()
{
    if (ui.track.lineTrack)
    {
        delete ui.track.lineTrack;
        ui.track.lineTrack = nullptr;
    }

    if (ui.map.imgTiles)
    {
        lv_mem_free(ui.map.imgTiles);
        ui.map.imgTiles = nullptr;
    }

    lv_style_reset(&ui.styleCont);
    lv_style_reset(&ui.styleLabel);
    lv_style_reset(&ui.styleLine);
}

/**
 * @brief Create and register the LVGL objects owned by Style_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 */
void LiveMapView::Style_Create()
{
    lv_style_init(&ui.styleCont);
    lv_style_set_bg_color(&ui.styleCont, lv_color_black());
    lv_style_set_bg_opa(&ui.styleCont, LV_OPA_60);
    lv_style_set_radius(&ui.styleCont, 6);
    lv_style_set_shadow_width(&ui.styleCont, 10);
    lv_style_set_shadow_color(&ui.styleCont, lv_color_black());

    lv_style_init(&ui.styleLabel);
    lv_style_set_text_font(&ui.styleLabel, ResourcePool::GetFont("bahnschrift_17"));
    lv_style_set_text_color(&ui.styleLabel, lv_color_white());

    lv_style_init(&ui.styleLine);
    lv_style_set_line_color(&ui.styleLine, lv_color_hex(0xff931e));
    lv_style_set_line_width(&ui.styleLine, 5);
    lv_style_set_line_opa(&ui.styleLine, LV_OPA_COVER);
    lv_style_set_line_rounded(&ui.styleLine, true);
}

/**
 * @brief Create and register the LVGL objects owned by Map_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param par Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param tileNum Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void LiveMapView::Map_Create(lv_obj_t* par, uint32_t tileNum)
{
    lv_obj_t* cont = lv_obj_create(par);
    lv_obj_remove_style_all(cont);
#if CONFIG_LIVE_MAP_DEBUG_ENABLE
    lv_obj_set_style_outline_color(cont, lv_palette_main(LV_PALETTE_BLUE), 0);
    lv_obj_set_style_outline_width(cont, 2, 0);
#endif
    ui.map.cont = cont;

    ui.map.imgTiles = (lv_obj_t**)lv_mem_alloc(tileNum * sizeof(lv_obj_t*));
    ui.map.tileNum = tileNum;

    for (uint32_t i = 0; i < tileNum; i++)
    {
/**
 * @brief Execute the TILE_IMG_CREATE operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param cont Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
        lv_obj_t* img = TILE_IMG_CREATE(cont);
        lv_obj_remove_style_all(img);
        ui.map.imgTiles[i] = img;
    }

/**
 * @brief Create and register the LVGL objects owned by Track_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param cont Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    Track_Create(cont);

    lv_obj_t* img = lv_img_create(cont);
    lv_img_set_src(img, ResourcePool::GetImage("gps_arrow_dark"));

    lv_img_t* imgOri = (lv_img_t*)img;
    lv_obj_set_pos(img, -imgOri->w, -imgOri->h);
    ui.map.imgArrow = img;
}

/**
 * @brief Change the MapTile configuration of the object.
 * @param tileSize Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param widthCnt Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void LiveMapView::SetMapTile(uint32_t tileSize, uint32_t widthCnt)
{
/**
 * @brief Own and retain the tileNum state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    uint32_t tileNum = ui.map.tileNum;

    lv_coord_t width = (lv_coord_t)(tileSize * widthCnt);
    lv_coord_t height = (lv_coord_t)(tileSize * (ui.map.tileNum / widthCnt));

    lv_obj_set_size(ui.map.cont, width, height);

    for (uint32_t i = 0; i < tileNum; i++)
    {
/**
 * @brief Own and retain the img state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        lv_obj_t* img = ui.map.imgTiles[i];

        lv_obj_set_size(img, tileSize, tileSize);

        lv_coord_t x = (i % widthCnt) * tileSize;
        lv_coord_t y = (i / widthCnt) * tileSize;
        lv_obj_set_pos(img, x, y);
    }
}

/**
 * @brief Change the MapTileSrc configuration of the object.
 * @param index Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param src Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void LiveMapView::SetMapTileSrc(uint32_t index, const char* src)
{
    if (index >= ui.map.tileNum)
    {
        return;
    }

/**
 * @brief Execute the TILE_IMG_SET_SRC operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param imgTiles Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param src Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    TILE_IMG_SET_SRC(ui.map.imgTiles[index], src);
}

/**
 * @brief Change the ArrowTheme configuration of the object.
 * @param theme Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void LiveMapView::SetArrowTheme(const char* theme)
{
/**
 * @brief Own and retain the buf state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    char buf[32];
    snprintf(buf, sizeof(buf), "gps_arrow_%s", theme);

/**
 * @brief Read Image from the current object state.
 * @param buf Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    const void* src = ResourcePool::GetImage(buf);

    if (src == nullptr)
    {
/**
 * @brief Read Image from the current object state.
 * @return Operation result or status; inspect it before using dependent state.
 */
        ResourcePool::GetImage("gps_arrow_default");
    }

    lv_img_set_src(ui.map.imgArrow, src);
}

/**
 * @brief Change the LineActivePoint configuration of the object.
 * @param x Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param y Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void LiveMapView::SetLineActivePoint(lv_coord_t x, lv_coord_t y)
{
/**
 * @brief Own and retain the end_point state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    lv_point_t end_point;
    if (!ui.track.lineTrack->get_end_point(&end_point))
    {
        return;
    }

    ui.track.pointActive[0] = end_point;
    ui.track.pointActive[1].x = x;
    ui.track.pointActive[1].y = y;
    lv_line_set_points(ui.track.lineActive, ui.track.pointActive, 2);
}

/**
 * @brief Create and register the LVGL objects owned by ZoomCtrl_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param par Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void LiveMapView::ZoomCtrl_Create(lv_obj_t* par)
{
    lv_obj_t* cont = lv_obj_create(par);
    lv_obj_remove_style_all(cont);
    lv_obj_add_style(cont, &ui.styleCont, 0);
    lv_obj_set_style_opa(cont, LV_OPA_COVER, 0);
    lv_obj_set_size(cont, 50, 30);
    lv_obj_set_pos(cont, lv_obj_get_style_width(par, 0) - lv_obj_get_style_width(cont, 0) + 5, 40);
    ui.zoom.cont = cont;

    static const lv_style_prop_t prop[] =
    {
        LV_STYLE_X,
        LV_STYLE_OPA,
        LV_STYLE_PROP_INV
    };
/**
 * @brief Own and retain the tran state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    static lv_style_transition_dsc_t tran;
    lv_style_transition_dsc_init(&tran, prop, lv_anim_path_ease_out, 200, 0, nullptr);
    lv_obj_set_style_x(cont, lv_obj_get_style_width(par, 0), LV_STATE_USER_1);
    lv_obj_set_style_opa(cont, LV_OPA_TRANSP, LV_STATE_USER_1);
    lv_obj_set_style_transition(cont, &tran, LV_STATE_USER_1);
    lv_obj_set_style_transition(cont, &tran, LV_STATE_DEFAULT);
    lv_obj_add_state(cont, LV_STATE_USER_1);

    lv_obj_t* label = lv_label_create(cont);
    lv_obj_add_style(label, &ui.styleLabel, 0);
    lv_obj_align(label, LV_ALIGN_CENTER, -2, 0);
    lv_label_set_text(label, "--");
    ui.zoom.labelInfo = label;

    lv_obj_t* slider = lv_slider_create(cont);
    lv_obj_remove_style_all(slider);
    // lv_obj_set_style_opa(slider, LV_OPA_COVER, 0); // #new
    lv_slider_set_value(slider, 15, LV_ANIM_OFF);
    ui.zoom.slider = slider;
}

/**
 * @brief Create and register the LVGL objects owned by SportInfo_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param par Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void LiveMapView::SportInfo_Create(lv_obj_t* par)
{
    /* cont */
    lv_obj_t* obj = lv_obj_create(par);
    lv_obj_remove_style_all(obj);
    lv_obj_add_style(obj, &ui.styleCont, 0);
    lv_obj_set_size(obj, 159, 66);
    lv_obj_align(obj, LV_ALIGN_BOTTOM_LEFT, -10, 10);
    lv_obj_set_style_radius(obj, 10, 0);
    ui.sportInfo.cont = obj;

    /* speed */
    lv_obj_t* label = lv_label_create(obj);
    lv_label_set_text(label, "00");
    lv_obj_set_style_text_font(label, ResourcePool::GetFont("bahnschrift_32"), 0);
    lv_obj_set_style_text_color(label, lv_color_white(), 0);
    lv_obj_align(label, LV_ALIGN_LEFT_MID, 20, -10);
    ui.sportInfo.labelSpeed = label;

    label = lv_label_create(obj);
    lv_label_set_text(label, "km/h");
    lv_obj_set_style_text_font(label, ResourcePool::GetFont("bahnschrift_13"), 0);
    lv_obj_set_style_text_color(label, lv_color_white(), 0);
    lv_obj_align_to(label, ui.sportInfo.labelSpeed, LV_ALIGN_OUT_BOTTOM_MID, 0, 3);

/**
 * @brief Create and register the LVGL objects owned by ImgLabel_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param obj Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    ui.sportInfo.labelTrip = ImgLabel_Create(obj, ResourcePool::GetImage("trip"), 5, 10);
/**
 * @brief Create and register the LVGL objects owned by ImgLabel_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param obj Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    ui.sportInfo.labelTime = ImgLabel_Create(obj, ResourcePool::GetImage("alarm"), 5, 30);
}

/**
 * @brief Create and register the LVGL objects owned by ImgLabel_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param par Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param img_src Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param x_ofs Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param y_ofs Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
lv_obj_t* LiveMapView::ImgLabel_Create(lv_obj_t* par, const void* img_src, lv_coord_t x_ofs, lv_coord_t y_ofs)
{
    lv_obj_t* img = lv_img_create(par);
    lv_img_set_src(img, img_src);

    lv_obj_align(img, LV_ALIGN_TOP_MID, 0, y_ofs);

    lv_obj_t* label = lv_label_create(par);
    lv_label_set_text(label, "--");
    lv_obj_add_style(label, &ui.styleLabel, 0);
    lv_obj_align_to(label, img, LV_ALIGN_OUT_RIGHT_MID, x_ofs, 0);
/**
 * @brief Own and retain the label state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    return label;
}

/**
 * @brief Create and register the LVGL objects owned by Track_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param par Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void LiveMapView::Track_Create(lv_obj_t* par)
{
    lv_obj_t* cont = lv_obj_create(par);
    lv_obj_remove_style_all(cont);
    lv_obj_set_size(cont, LV_PCT(100), LV_PCT(100));
    ui.track.cont = cont;

    ui.track.lineTrack = new lv_poly_line(cont);

    ui.track.lineTrack->set_style(&ui.styleLine);

    lv_obj_t* line = lv_line_create(cont);
    lv_obj_remove_style_all(line);
    lv_obj_add_style(line, &ui.styleLine, 0);
#if CONFIG_LIVE_MAP_DEBUG_ENABLE
    lv_obj_set_style_line_color(line, lv_palette_main(LV_PALETTE_BLUE), 0);
#endif
    ui.track.lineActive = line;
}
