#ifndef TH_PAD_H
#define TH_PAD_H

#include "common.h"
#include "debug.h"
#include "shPad/lib_sh_pad.h"

int ThreadPadStart(void* stack /* r20 */, int stackSize /* r19 */, int prio /* r18 */, int option /* r17 */, int wait_sid /* r2 */);

#endif // TH_PAD_H
