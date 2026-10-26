/*
 * Copyright (C) 2026 pdnguyen of HCMC University of Technology VNU-HCM
 *
 * demacOprx release
 * Source Code License Grant: The authors hereby grant to Licensee
 * personal permission to use and modify the Licensed Source Code
 * for the sole purpose of studying while attending the course CO2018.
 *
 * Verilated -*- C++ -*-
 * DESCRIPTION: Verilator output: Prototypes for DPI import and export functions.
 *
 * Verilator includes this file in all generated .cpp files that use DPI functions.
 * Manually include this file where DPI .c import functions are declared to ensure
 * the C functions match the expectations of the DPI imports.
 */

#ifndef VERILATED_VDMA_TOP__DPI_H_
#define VERILATED_VDMA_TOP__DPI_H_  // guard

#include "svdpi.h"

#ifdef __cplusplus
extern "C" {
#endif


    // DPI IMPORTS
    // DPI import at build/merged_rtl.sv:276:34
    extern void dma_done_callback();
    // DPI import at build/merged_rtl.sv:274:33
    extern int dpi_bank_read32_legacy(long long offset);
    // DPI import at build/merged_rtl.sv:275:33
    extern int dpi_bank_write32_legacy(long long offset, int value);

#ifdef __cplusplus
}
#endif

#endif  // guard
