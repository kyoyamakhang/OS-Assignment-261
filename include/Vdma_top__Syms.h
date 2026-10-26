/*
 * Copyright (C) 2026 pdnguyen of HCMC University of Technology VNU-HCM
 *
 * demacOprx release
 * Source Code License Grant: The authors hereby grant to Licensee
 * personal permission to use and modify the Licensed Source Code
 * for the sole purpose of studying while attending the course CO2018.
 *
 * Verilated -*- C++ -*-
 * DESCRIPTION: Verilator output: Symbol table internal header
 * Internal details; most calling programs do not need this header,
 * unless using verilator public meta comments.
 */

#ifndef VERILATED_VDMA_TOP__SYMS_H_
#define VERILATED_VDMA_TOP__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vdma_top.h"

// INCLUDE MODULE CLASSES
#include "Vdma_top___024root.h"

// DPI TYPES for DPI Export callbacks (Internal use)

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES)Vdma_top__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vdma_top* const __Vm_modelp;
    bool __Vm_activity = false;  ///< Used by trace routines to determine change occurred
    uint32_t __Vm_baseCode = 0;  ///< Used by trace routines when tracing multiple models
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vdma_top___024root             TOP;

    // CONSTRUCTORS
    Vdma_top__Syms(VerilatedContext* contextp, const char* namep, Vdma_top* modelp);
    ~Vdma_top__Syms();

    // METHODS
    const char* name() { return TOP.name(); }
};

#endif  // guard
