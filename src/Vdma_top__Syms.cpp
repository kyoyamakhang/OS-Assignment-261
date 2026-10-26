/*
 * Copyright (C) 2026 pdnguyen of HCMC University of Technology VNU-HCM
 *
 * demacOprx release
 * Source Code License Grant: The authors hereby grant to Licensee
 * personal permission to use and modify the Licensed Source Code
 * for the sole purpose of studying while attending the course CO2018.
 *
 * Verilated -*- C++ -*-
 * DESCRIPTION: Verilator output: Symbol table implementation internals
 */

#include "Vdma_top__pch.h"
#include "Vdma_top.h"
#include "Vdma_top___024root.h"

// FUNCTIONS
Vdma_top__Syms::~Vdma_top__Syms()
{
}

Vdma_top__Syms::Vdma_top__Syms(VerilatedContext* contextp, const char* namep, Vdma_top* modelp)
    : VerilatedSyms{contextp}
    // Setup internal state of the Syms class
    , __Vm_modelp{modelp}
    // Setup module instances
    , TOP{this, namep}
{
    // Configure time unit / time precision
    _vm_contextp__->timeunit(-9);
    _vm_contextp__->timeprecision(-12);
    // Setup each module's pointers to their submodules
    // Setup each module's pointer back to symbol table (for public functions)
    TOP.__Vconfigure(true);
    // Setup export functions
    for (int __Vfinal = 0; __Vfinal < 2; ++__Vfinal) {
    }
}
