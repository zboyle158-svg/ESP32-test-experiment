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
void DataProc_Init();

/** @brief Data acquisition, transformation and inter-page communication API. */
namespace DataProc
{

/** @brief Return the process-wide message and data cache centre. */
DataCenter* Center();
uint32_t    GetTick();
uint32_t    GetTickElaps(uint32_t prevTick);
const char* MakeTimeString(uint64_t ms, char* buf, uint16_t len);

}

#endif
