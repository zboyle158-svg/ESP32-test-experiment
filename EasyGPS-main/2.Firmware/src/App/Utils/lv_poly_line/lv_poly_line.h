#ifndef LV_POLY_LINE_H
#define LV_POLY_LINE_H

#include "lvgl.h"
#include <vector>

class lv_poly_line
{
public:
    lv_poly_line(lv_obj_t* par);
    ~lv_poly_line();

/**
 * @brief Execute the set_style operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param style Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
    void set_style(lv_style_t* style)
    {
        styleLine = style;
    }

/**
 * @brief Execute the start operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 */
    void start();
/**
 * @brief Execute the append operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param point Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
    void append(const lv_point_t* point);
/**
 * @brief Execute the append operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param x Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param y Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
    void append(lv_coord_t x, lv_coord_t y)
    {
/**
 * @brief Own and retain the point state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        lv_point_t point = { x, y };
        append(&point);
    }
/**
 * @brief Execute the append_to_end operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param point Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
    void append_to_end(const lv_point_t* point);
/**
 * @brief Execute the append_to_end operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param x Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param y Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
    void append_to_end(lv_coord_t x, lv_coord_t y)
    {
/**
 * @brief Own and retain the point state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        lv_point_t point = { x, y };
        append_to_end(&point);
    }
/**
 * @brief Release or reset resources managed by lv_poly_line.
 */
    void stop();
/**
 * @brief Execute the reset operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 */
    void reset();
/**
 * @brief Execute the get_end_point operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param point Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    bool get_end_point(lv_point_t* point);

private:
    typedef struct
    {
/**
 * @brief Own and retain the line state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        lv_obj_t* line;
/**
 * @brief Own and retain the points state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        std::vector<lv_point_t> points;
/**
 * @brief Own and retain the single_line_t state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    } single_line_t;

private:
/**
 * @brief Execute the add_line operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 */
    void add_line();
/**
 * @brief Execute the refresh_line operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 */
    void refresh_line();
/**
 * @brief Execute the get_end_line operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    single_line_t* get_end_line();
/**
 * @brief Execute the get_points operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param single_line Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    const lv_point_t* get_points(single_line_t* single_line);

private:
/**
 * @brief Own and retain the poly_line state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    std::vector<single_line_t> poly_line;
/**
 * @brief Own and retain the current_index state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    uint32_t current_index;
/**
 * @brief Own and retain the styleLine state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    lv_style_t* styleLine;
/**
 * @brief Own and retain the parent state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    lv_obj_t* parent;
};

#endif // !LV_POLY_LINE_H
