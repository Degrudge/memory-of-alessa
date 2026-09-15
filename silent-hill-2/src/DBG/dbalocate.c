#include "DBG/dbalocate.h"

void* dbAllocatePrintf(int require_size) {

    
    ASSERT_ON_LINE(require_size<=UPPER_SIZE_PRINTF, 28);    
    return (void* )0x2000000;



}
