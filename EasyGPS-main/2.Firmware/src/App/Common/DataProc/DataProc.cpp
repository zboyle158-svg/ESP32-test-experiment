#include "DataProc.h"
#include "../HAL/HAL.h"

/** @brief Global account registry used by all data producers and consumers. */
static DataCenter center("CENTER");

/**
 * @brief Return the singleton DataCenter instance.
 * @return Pointer with firmware-lifetime ownership; callers must not delete it.
 */
DataCenter* DataProc::Center()
{
    return &center;
}

/**
 * @brief Instantiate every account and invoke every node initialiser.
 *
 * @details DP_LIST.inc is included twice intentionally: the first pass creates
 * named Account objects, and the second pass binds each account to its
 * corresponding `_DP_<name>_Init()` implementation. Add a node to the list
 * only after its implementation and data definition exist.
 */
void DataProc_Init()
{
#define DP_DEF(NODE_NAME, BUFFER_SIZE)\
    Account* act##NODE_NAME = new Account(#NODE_NAME, &center, BUFFER_SIZE);
#  include "DP_LIST.inc"
#undef DP_DEF

#define DP_DEF(NODE_NAME, BUFFER_SIZE)\
do{\
    DATA_PROC_INIT_DEF(NODE_NAME);\
    _DP_##NODE_NAME##_Init(act##NODE_NAME);\
}while(0)
#  include "DP_LIST.inc"
#undef DP_DEF

}
