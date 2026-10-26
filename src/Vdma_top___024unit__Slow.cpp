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

#include "Vdma_top__pch.h"
#include "Vdma_top__Syms.h"
#include "Vdma_top___024unit.h"

void Vdma_top___024unit___ctor_var_reset(Vdma_top___024unit* vlSelf);

Vdma_top___024unit::Vdma_top___024unit(Vdma_top__Syms* symsp, const char* v__name)
    : VerilatedModule{v__name}
    , vlSymsp{symsp}
 {
    // Reset structure values
    Vdma_top___024unit___ctor_var_reset(this);
}

void Vdma_top___024unit::__Vconfigure(bool first) {
    if (false && first) {}  // Prevent unused
}

Vdma_top___024unit::~Vdma_top___024unit() {
}
