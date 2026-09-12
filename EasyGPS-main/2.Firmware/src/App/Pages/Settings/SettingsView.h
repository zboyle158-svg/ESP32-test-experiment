#ifndef __SETTINGS_VIEW_H
#define __SETTINGS_VIEW_H

#include "../Page.h"

namespace Page
{

    class SettingsView
    {

    public:
        typedef struct
        {
            lv_obj_t *cont;
            lv_obj_t *lableValue;
            lv_obj_t *lableUnit;
/**
 * @brief Own and retain the SubInfo_t state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        } SubInfo_t;

        typedef uint8_t lv_menu_builder_variant_t;

        enum
        {
            LV_MENU_ITEM_BUILDER_VARIANT_1,
            LV_MENU_ITEM_BUILDER_VARIANT_2
        };

    public:
        struct
        {
            struct
            {
                lv_obj_t *cont;
                lv_obj_t *page;
                lv_obj_t *section;
/**
 * @brief Own and retain the menuCont state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
            } menuCont;

            struct
            {
                lv_obj_t *cont;
                lv_obj_t *AXPTemp;
                lv_obj_t *BatVolt;
                lv_obj_t *BatCurr;
                lv_obj_t *BatPower;
                lv_obj_t *swAutoPowOff;
                lv_obj_t *USBCharing;
/**
 * @brief Own and retain the powInfo state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
            } powInfo;

            struct
            {
                lv_obj_t *cont;
                lv_obj_t *labelConnect;
                lv_obj_t *labelName;
                lv_obj_t *labelIP;
                lv_obj_t *swAP;
                lv_obj_t *swSTA;
/**
 * @brief Own and retain the wifiInfo state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
            } wifiInfo;

            struct
            {
                lv_obj_t *cont;
                lv_obj_t *labelConnect;
                lv_obj_t *labelName;
                lv_obj_t *sw;
/**
 * @brief Own and retain the bleInfo state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
            } bleInfo;

            struct
            {
                lv_obj_t *cont;
                lv_obj_t *brig;
/**
 * @brief Own and retain the displayInfo state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
            } displayInfo;

            struct
            {
                lv_obj_t *cont;
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
                lv_obj_t *cont;
                lv_obj_t *btnMap;
                lv_obj_t *btnRec;
                lv_obj_t *btnMenu;
/**
 * @brief Own and retain the btnCont state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
            } btnCont;

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
 * @brief Delete LVGL objects owned by SettingsView.
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
 * @brief Create and register the LVGL objects owned by SwitchBox_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param par Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param title Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
        lv_obj_t *SwitchBox_Create(lv_obj_t *par, const char *title);
/**
 * @brief Create and register the LVGL objects owned by SliderBox_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param par Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param title Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param min Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param max Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param val Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
        lv_obj_t *SliderBox_Create(lv_obj_t *par, const char *title, int32_t min = 0, int32_t max = 255, int32_t val = 128);
/**
 * @brief Create and register the LVGL objects owned by ContentBox_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param par Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param title Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param content Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
        lv_obj_t *ContentBox_Create(lv_obj_t *par, const char *title, const char *content = nullptr);
/**
 * @brief Create and register the LVGL objects owned by Switch_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param par Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param state Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param x_ofs Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param y_ofs Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
        lv_obj_t *Switch_Create(lv_obj_t *par, bool state = false, lv_coord_t x_ofs = 0, lv_coord_t y_ofs = 0);
/**
 * @brief Create and register the LVGL objects owned by Slider_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param par Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param img_src Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param x_ofs Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param y_ofs Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param min Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param max Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param val Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
        lv_obj_t *Slider_Create(lv_obj_t *par, const void *img_src, lv_coord_t x_ofs = 0, lv_coord_t y_ofs = 0, int32_t min = 0, int32_t max = 255, int32_t val = 127);
/**
 * @brief Create and register the LVGL objects owned by Btn_Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param par Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param img_src Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param x_ofs Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
        lv_obj_t *Btn_Create(lv_obj_t *par, const void *img_src = nullptr, lv_coord_t x_ofs = 0);
    };

}

#endif // !__VIEW_H
