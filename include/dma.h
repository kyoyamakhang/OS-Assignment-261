/*
 * Copyright (C) 2026 pdnguyen of HCMC University of Technology VNU-HCM
 *
 * demacOprx release
 * Source Code License Grant: The authors hereby grant to Licensee
 * personal permission to use and modify the Licensed Source Code
 * for the sole purpose of studying while attending the course CO2018.
 *
 * DMA Interface Header
 */

#ifndef __DMA_H__
#define __DMA_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declaration */
struct pcb_t;

/*
 * do_dma - perform DMA function
 * caller: process control block
 * source: source memory address
 * destination: destination memory address
 * length: number of bytes to copy
 */
int do_dma(struct pcb_t *caller, uint64_t source, uint64_t destination, uint64_t length);

#ifdef __cplusplus
}
#endif

#endif /* __DMA_H__ */