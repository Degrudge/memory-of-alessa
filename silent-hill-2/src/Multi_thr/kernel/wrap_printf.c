#include "common.h"

#define WRAP_PRINTF_BUF_SIZE 0x10000
#define DB_ALLOCATE 1

#if DB_ALLOCATE == 0
char iprintf_buf[65536];
#endif

void wrap_printf_init(void) {
    #if DB_ALLOCATE == 1
        printf_init(dbAllocatePrintf(WRAP_PRINTF_BUF_SIZE), WRAP_PRINTF_BUF_SIZE, true /* help */);
    #else
        printf_init(iprintf_buf, WRAP_PRINTF_BUF_SIZE, true /* help */);
    #endif
}

#undef DB_ALLOCATE
