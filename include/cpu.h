#ifndef CPU_H
#define CPU_H

#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Execute an instruction of a process. Return 0
 * if the instruction is executed successfully.
 * Otherwise, return 1. */
int run(struct pcb_t * proc);

#ifdef __cplusplus
}
#endif

#endif
