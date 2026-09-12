#ifndef __DATA_PROC_H
#define __DATA_PROC_H

#include "App/Utils/DataCenter/DataCenter.h"
#include "App/Common/HAL/HAL_Def.h"
#include "DataProc_Def.h"

#define DATA_PROC_INIT_DEF(name)   void _DP_##name##_Init(Account* account)
#define DATA_PROC_INIT_STRUCT(sct) memset(&sct, 0, sizeof(sct))

/**
 * @brief Create and initialise all DataCenter accounts listed in DP_LIST.inc.
 *
 * @details Each account is a named publish/subscribe channel.  HAL producers
 * publish snapshots to an account; pages and other processors pull or listen
 * to that account without coupling to a concrete hardware driver.
 */
/**
 * @brief Initialize DataProc state and hardware or data resources.
 */
void DataProc_Init();

/** @brief Data acquisition, transformation and inter-page communication API. */
namespace DataProc
{

/** @brief Return the process-wide message and data cache centre. */
DataCenter* Center();
/**
 * @brief Read Tick from the current object state.
 * @return Operation result or status; inspect it before using dependent state.
 */
uint32_t    GetTick();
/**
 * @brief Read TickElaps from the current object state.
 * @param prevTick Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
uint32_t    GetTickElaps(uint32_t prevTick);
/**
 * @brief Execute the MakeTimeString operation and update the owning module state.
 * @details This interface is the module boundary: callers provide the documented inputs, while the implementation performs the hardware, model, or view operation without transferring ownership of caller-managed objects.
 * @param ms Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param buf Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @param len Input/output argument for this operation; the caller retains ownership unless the function contract states otherwise.
 * @return Operation result or status; inspect it before using dependent state.
 */
const char* MakeTimeString(uint64_t ms, char* buf, uint16_t len);

}

#endif
