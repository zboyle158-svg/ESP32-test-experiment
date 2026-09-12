#ifndef __LIVEMAP_VIEW_H
#define __LIVEMAP_VIEW_H

#include "../Page.h"
#include <vector>
#include "App/Utils/lv_poly_line/lv_poly_line.h"

namespace Page
{

class LiveMapView
{
public:
    struct
    {
/**
 * @brief Own and retain the labelInfo state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        lv_obj_t* labelInfo;

/**
 * @brief Own and retain the styleCont state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        lv_style_t styleCont;
/**
 * @brief Own and retain the styleLabel state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        lv_style_t styleLabel;
/**
 * @brief Own and retain the styleLine state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        lv_style_t styleLine;

        struct
        {
/**
 * @brief Own and retain the cont state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
            lv_obj_t* cont;
/**
 * @brief Own and retain the imgArrow state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
            lv_obj_t* imgArrow;
/**
 * @brief Own and retain the imgTiles state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
            lv_obj_t** imgTiles;
/**
 * @brief Own and retain the tileNum state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
            uint32_t tileNum;            
/**
 * @brief Own and retain the map state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        } map;

        struct
        {
/**
 * @brief Own and retain the cont state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
            lv_obj_t* cont;
/**
 * @brief Own and retain the lineTrack state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
            lv_poly_line* lineTrack;
/**
 * @brief Own and retain the lineActive state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
            lv_obj_t* lineActive;
/**
 * @brief Own and retain the pointActive state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
            lv_point_t pointActive[2];
/**
 * @brief Own and retain the track state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        } track;

        struct
        {
/**
 * @brief Own and retain the cont state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
            lv_obj_t* cont;
/**
 * @brief Own and retain the labelInfo state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
            lv_obj_t* labelInfo;
/**
 * @brief Own and retain the slider state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
            lv_obj_t* slider;
/**
 * @brief Own and retain the zoom state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        } zoom;

        struct
        {
/**
 * @brief Own and retain the cont state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
            lv_obj_t* cont;
/**
 * @brief Own and retain the move state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        } move;

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
 * @brief Own and retain the labelTrip state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
            lv_obj_t* labelTrip;
/**
 * @brief Own and retain the labelTime state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
            lv_obj_t* labelTime;
/**
 * @brief Own and retain the sportInfo state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        } sportInfo;
/**
 * @brief Own and retain the ui state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    } ui;

/**
 * @brief Create and register the LVGL objects owned by Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param root Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param tileNum Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
    void Create(lv_obj_t* root, uint32_t tileNum);
/**
 * @brief Delete LVGL objects owned by LiveMapView.
 */
    void Delete();
/**
 * @brief Change the ImgArrowStatus configuration of the object.
 * @param x Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param y Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param angle Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
    void SetImgArrowStatus(lv_coord_t x, lv_coord_t y, float angle)
    {
/**
 * @brief Own and retain the img state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        lv_obj_t* img = ui.map.imgArrow;
        lv_obj_set_pos(img, x, y);
        lv_img_set_angle(img, int16_t(angle * 10));
    }
/**
 * @brief Change the MapTile configuration of the object.
 * @param tileSize Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param widthCnt Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
    void SetMapTile(uint32_t tileSize, uint32_t widthCnt);
/**
 * @brief Change the MapTileSrc configuration of the object.
 * @param index Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param src Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
    void SetMapTileSrc(uint32_t index, const char* src);
/**
 * @brief Change the ArrowTheme configuration of the object.
 * @param theme Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
    void SetArrowTheme(const char* theme);
/**
 * @brief Change the LineActivePoint configuration of the object.
 * @param x Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param y Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
    void SetLineActivePoint(lv_coord_t x, lv_coord_t y);

private:
/**
 * @brief Create and register the LVGL objects owned by Style_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 */
    void Style_Create();
/**
 * @brief Create and register the LVGL objects owned by Map_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param par Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param tileNum Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
    void Map_Create(lv_obj_t* par, uint32_t tileNum);
/**
 * @brief Create and register the LVGL objects owned by ZoomCtrl_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param par Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
    void ZoomCtrl_Create(lv_obj_t* par);
/**
 * @brief Create and register the LVGL objects owned by SportInfo_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param par Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
    void SportInfo_Create(lv_obj_t* par);
/**
 * @brief Create and register the LVGL objects owned by ImgLabel_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param par Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param img_src Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param x_ofs Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param y_ofs Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    lv_obj_t* ImgLabel_Create(lv_obj_t* par, const void* img_src, lv_coord_t x_ofs, lv_coord_t y_ofs);
/**
 * @brief Create and register the LVGL objects owned by Track_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param par Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
    void Track_Create(lv_obj_t* par);
};

}

#endif // !__VIEW_H
