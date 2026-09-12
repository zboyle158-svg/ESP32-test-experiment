#ifndef __RESOURCE_POOL
#define __RESOURCE_POOL

#include "lvgl.h"

namespace ResourcePool
{

/**
 * @brief Initialize ResourcePool state and hardware or data resources.
 */
void Init();
/**
 * @brief Read Font from the current object state.
 * @param name Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
lv_font_t* GetFont(const char* name);
/**
 * @brief Read Image from the current object state.
 * @param name Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
const void* GetImage(const char* name);

}

#endif
