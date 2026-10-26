#ifndef LOADER_H
#define LOADER_H

#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif

struct pcb_t * load(const char * path);

#ifdef __cplusplus
}
#endif

#endif