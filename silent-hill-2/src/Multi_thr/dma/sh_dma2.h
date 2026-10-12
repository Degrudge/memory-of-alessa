#ifndef SH_DMA2_H
#define SH_DMA2_H

#include "sce/eeregs.h"
#include "sce/eekernel.h"

int shDmaGifInit(void);

int shDmaGifSend(void* packet /* r16 */);

#endif // SH_DMA2_H
