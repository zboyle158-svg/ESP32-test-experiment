#include "lv_poly_line.h"

/**
 * @brief Construct or destroy the lv_poly_line object.
 * @param par Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
lv_poly_line::lv_poly_line(lv_obj_t* par)
/**
 * @brief Execute the current_index operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    : current_index(0)
/**
 * @brief Execute the styleLine operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param nullptr Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    , styleLine(nullptr)
/**
 * @brief Execute the parent operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param par Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    , parent(par)
{
}

/**
 * @brief Release resources owned by the lv_poly_line object.
 * @return Operation result or status; inspect it before using dependent state.
 */
lv_poly_line::~lv_poly_line()
{
    for (auto iter : poly_line)
    {
        if (iter.line)
        {
            lv_obj_del(iter.line);
        }

        decltype(iter.points) vec;
        iter.points.swap(vec);
    }
}

/**
 * @brief Execute the add_line operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 */
void lv_poly_line::add_line()
{
    lv_obj_t* line = lv_line_create(parent);
    lv_obj_remove_style_all(line);

    if (styleLine != nullptr)
    {
        lv_obj_add_style(line, styleLine, 0);
    }

/**
 * @brief Own and retain the single_line state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    single_line_t single_line;
    single_line.line = line;
    poly_line.push_back(single_line);

/**
 * @brief Execute the LV_LOG_INFO operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param p Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param line Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param parent Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    LV_LOG_INFO("line: %p, parent: %p", line, parent);
}

/**
 * @brief Execute the refresh_line operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 */
void lv_poly_line::refresh_line()
{
/**
 * @brief Execute the poly_line.size operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    size_t size = poly_line.size();

    for (size_t i = 0; i < size; i++)
    {
/**
 * @brief Own and retain the single_line state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        single_line_t* single_line = &poly_line[i];
/**
 * @brief Execute the get_points operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param single_line Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
        const lv_point_t* points = get_points(single_line);
        lv_line_set_points(single_line->line, points, (uint16_t)single_line->points.size());
    }
}

/**
 * @brief Execute the start operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 */
void lv_poly_line::start()
{
    if (current_index >= poly_line.size())
    {
/**
 * @brief Execute the LV_LOG_INFO operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param current_index Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
        LV_LOG_INFO("current_index[%d] >= poly_line.size()[%d]", current_index, poly_line.size());
        add_line();
        refresh_line();
    }

/**
 * @brief Execute the LV_LOG_INFO operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param current_index Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    LV_LOG_INFO("show poly_line[%d]", current_index);

/**
 * @brief Own and retain the single_line state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    single_line_t* single_line = &poly_line[current_index];

    lv_obj_clear_flag(single_line->line, LV_OBJ_FLAG_HIDDEN);
    lv_line_set_points(single_line->line, nullptr, 0);
}

/**
 * @brief Execute the append operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param point Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void lv_poly_line::append(const lv_point_t* point)
{
    if (poly_line.size() == 0)
    {
/**
 * @brief Execute the LV_LOG_WARN operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
        LV_LOG_WARN("poly_line.size() = 0");
        return;
    }

/**
 * @brief Execute the LV_LOG_INFO operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param d Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param current_index Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param x Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param y Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    LV_LOG_INFO("poly_line[%d]: (%d, %d)", current_index, point->x, point->y);
    poly_line[current_index].points.push_back(*point);
}

/**
 * @brief Execute the append_to_end operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param point Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 */
void lv_poly_line::append_to_end(const lv_point_t* point)
{
/**
 * @brief Execute the get_end_line operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    single_line_t* single_line = get_end_line();
    if (single_line == nullptr)
    {
/**
 * @brief Execute the LV_LOG_ERROR operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
        LV_LOG_ERROR("failed");
        return;
    }

    single_line->points.push_back(*point);

/**
 * @brief Execute the LV_LOG_INFO operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param d Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param size Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param x Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param y Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    LV_LOG_INFO("end_line: (%d, %d), size = %d", point->x, point->y, single_line->points.size());

/**
 * @brief Execute the get_points operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param single_line Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    const lv_point_t* points = get_points(single_line);
    lv_line_set_points(single_line->line, points, (uint16_t)single_line->points.size());
}

/**
 * @brief Release or reset resources managed by lv_poly_line.
 */
void lv_poly_line::stop()
{
    if (poly_line.size() == 0)
    {
/**
 * @brief Execute the LV_LOG_ERROR operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
        LV_LOG_ERROR("poly_line.size() = 0");
        return;
    }

/**
 * @brief Own and retain the single_line state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    single_line_t* single_line = &poly_line[current_index];
/**
 * @brief Execute the get_points operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param single_line Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    const lv_point_t* points = get_points(single_line);
    lv_line_set_points(single_line->line, points, (uint16_t)single_line->points.size());

/**
 * @brief Execute the LV_LOG_INFO operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param size Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param current_index Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    LV_LOG_INFO("poly_line[%d] size = %d", current_index, single_line->points.size());
    current_index++;
}

/**
 * @brief Execute the reset operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 */
void lv_poly_line::reset()
{
    current_index = 0;
/**
 * @brief Execute the poly_line.size operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    size_t size = poly_line.size();
/**
 * @brief Execute the LV_LOG_INFO operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param size Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
    LV_LOG_INFO("poly_line.size() = %d", size);
/**
 * @brief Execute the LV_LOG_INFO operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    LV_LOG_INFO("reset current_index");

    for (size_t i = 0; i < size; i++)
    {
/**
 * @brief Own and retain the single_line state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        single_line_t* single_line = &poly_line[i];
        lv_line_set_points(single_line->line, nullptr, 0);
        single_line->points.clear();
        lv_obj_add_flag(single_line->line, LV_OBJ_FLAG_HIDDEN);
    }
}

/**
 * @brief Execute the get_end_line operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
lv_poly_line::single_line_t* lv_poly_line::get_end_line()
{
/**
 * @brief Execute the poly_line.size operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    size_t size = poly_line.size();
    if (size == 0)
    {
/**
 * @brief Execute the LV_LOG_ERROR operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
        LV_LOG_ERROR("NOT found");
/**
 * @brief Own and retain the nullptr state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        return nullptr;
    }
    else
    {
/**
 * @brief Execute the LV_LOG_INFO operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param index Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
        LV_LOG_INFO("end_line index = %d", current_index - 1);
    }

    return &poly_line[current_index - 1];
}

/**
 * @brief Execute the get_points operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param single_line Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
const lv_point_t* lv_poly_line::get_points(single_line_t* single_line)
{
/**
 * @brief Own and retain the points state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    const lv_point_t* points =  nullptr;

    if (single_line->points.size())
    {
        points = &single_line->points[0];
    }
    else
    {
/**
 * @brief Execute the LV_LOG_WARN operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
        LV_LOG_WARN("NOT found");
    }

/**
 * @brief Own and retain the points state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    return points;
}

/**
 * @brief Execute the get_end_point operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param point Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
bool lv_poly_line::get_end_point(lv_point_t* point)
{
/**
 * @brief Execute the get_end_line operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
    single_line_t* single_line = get_end_line();
    if (single_line == nullptr)
    {
/**
 * @brief Execute the LV_LOG_ERROR operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
        LV_LOG_ERROR("end line NOT found");
/**
 * @brief Own and retain the false state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        return false;
    }

    if (single_line->points.size() == 0)
    {
/**
 * @brief Execute the LV_LOG_ERROR operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @return Operation result or status; inspect it before using dependent state.
 */
        LV_LOG_ERROR("single_line->points is EMPTY");
/**
 * @brief Own and retain the false state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
        return false;
    }

    *point = single_line->points.back();
/**
 * @brief Own and retain the true state required by this module.
 * @details The value remains valid for the lifetime of its enclosing object or task.  Access is limited to the module unless the declaration explicitly documents a public interface.
 */
    return true;
}
