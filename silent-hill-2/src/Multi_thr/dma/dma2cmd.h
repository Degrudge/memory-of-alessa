#ifndef DMA2CMD_H
#define DMA2CMD_H

#include "sce/sif.h"
#include "Multi_thr/dma/dma2serv.h"

void d2cSubCmdUpdataLastRegistCid(signed int cid /* r16 */);

int d2cSubSubCmdCheckFlushCache(void);

void d2cSubCmdFlushCache(void);

int d2cInit(void);

int d2cCmdSend(void* tag /* r16 */);

#endif // DMA2CMD_H
