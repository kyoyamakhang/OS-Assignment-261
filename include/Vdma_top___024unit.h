/*
 * Copyright (C) 2026 pdnguyen of HCMC University of Technology VNU-HCM
 *
 * demacOprx release
 * Source Code License Grant: The authors hereby grant to Licensee
 * personal permission to use and modify the Licensed Source Code
 * for the sole purpose of studying while attending the course CO2018.
 *
 * Vdma_top.h Design implementation internals
 * Verilated -*- C++ -*-
 * DESCRIPTION: Verilator output: Design implementation internals
 * See Vdma_top.h for the primary calling header
 */

#ifndef VERILATED_VDMA_TOP___024UNIT_H_
#define VERILATED_VDMA_TOP___024UNIT_H_  // guard

#include "verilated.h"


class Vdma_top__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vdma_top___024unit final : public VerilatedModule {
  public:

    // INTERNAL VARIABLES
    Vdma_top__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vdma_top___024unit(Vdma_top__Syms* symsp, const char* v__name);
    ~Vdma_top___024unit();
    VL_UNCOPYABLE(Vdma_top___024unit);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
