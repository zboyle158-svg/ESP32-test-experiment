#ifndef __SYSTEM_INFOS_VIEW_H
#define __SYSTEM_INFOS_VIEW_H

#include "../Page.h"

namespace Page
{

class SystemInfosView
{
public:
/**
 * @brief Create and register the LVGL objects owned by Create.
 * @details Allocated widgets are children of the supplied parent and are released by the page's Delete/unload lifecycle.  The caller retains ownership of the parent object.
 * @param root Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
    void Create(lv_obj_t* root);
/**
 * @brief Delete LVGL objects owned by SystemInfosView.
 */
    void Delete();

public:
    typedef struct
    {
/**
 * @brief Own and retain the cont state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        lv_obj_t* cont;
/**
 * @brief Own and retain the icon state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        lv_obj_t* icon;
/**
 * @brief Own and retain the labelInfo state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        lv_obj_t* labelInfo;
/**
 * @brief Own and retain the labelData state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        lv_obj_t* labelData;
/**
 * @brief Own and retain the item_t state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    } item_t;

    struct
    {
/**
 * @brief Own and retain the sport state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        item_t sport;
/**
 * @brief Own and retain the gps state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        item_t gps;
/**
 * @brief Own and retain the mag state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        item_t mag;
/**
 * @brief Own and retain the imu state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        item_t imu;
/**
 * @brief Own and retain the rtc state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        item_t rtc;
/**
 * @brief Own and retain the battery state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        item_t battery;
/**
 * @brief Own and retain the storage state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        item_t storage;
/**
 * @brief Own and retain the system state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        item_t system;
/**
 * @brief Own and retain the ui state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    } ui;

public:
    void SetSport(
        float trip,
        const char* time,
        float maxSpd
    );
    void SetGPS(
        float lat,
        float lng,
        float alt,
        const char* utc,
        float course,
        float speed
    );
    void SetMAG(
        float dir,
        int x,
        int y,
        int z
    );
    void SetIMU(
        int step,
        const char* info
    );
    void SetRTC(
        const char* dateTime
    );
    void SetBattery(
        int usage,
        float voltage,
        const char* state
    );
    void SetStorage(
        const char* detect,
        const char* size,
        const char* type,
        const char* version
    );
    void SetSystem(
        const char* firmVer,
        const char* authorName,
        const char* lvglVer,
        const char* bootTime,
        const char* compilerName,
        const char* bulidTime
    );

/**
 * @brief Change the ScrollToY configuration of the object.
 * @param obj Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param y Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param en Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
    void SetScrollToY(lv_obj_t* obj, lv_coord_t y, lv_anim_enable_t en);
/**
 * @brief Execute the onFocus operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param e Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
    static void onFocus(lv_group_t* e);

private:
    struct
    {
/**
 * @brief Own and retain the icon state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        lv_style_t icon;
/**
 * @brief Own and retain the focus state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        lv_style_t focus;
/**
 * @brief Own and retain the info state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        lv_style_t info;
/**
 * @brief Own and retain the data state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        lv_style_t data;
/**
 * @brief Own and retain the style state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    } style;

private:
/**
 * @brief Execute the Group_Init operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 */
    void Group_Init();
/**
 * @brief Execute the Style_Init operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 */
    void Style_Init();
/**
 * @brief Execute the Style_Reset operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 */
    void Style_Reset();
    void Item_Create(
        item_t* item,
        lv_obj_t* par,
        const char* name,
        const char* img_src,
        const char* infos
    );
};

}

#endif // !__VIEW_H
