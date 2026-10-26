/*
 * Copyright (C) 2026 pdnguyen of HCMC University of Technology VNU-HCM
 *
 * demacOprx release
 * Source Code License Grant: The authors hereby grant to Licensee
 * personal permission to use and modify the Licensed Source Code
 * for the sole purpose of studying while attending the course CO2018.
 *
 * Verilated -*- C++ -*-
 * DESCRIPTION: Verilator output: Precompiled header
 *
 * Internal details; most user sources do not need this header,
 * unless using verilator public meta comments.
 * Suggest use Vdma_top.h instead.
 */
 
#ifndef VERILATED_VDMA_TOP__PCH_H_
#define VERILATED_VDMA_TOP__PCH_H_  // guard

// GCC and Clang only will precompile headers (PCH) for the first header.
// So, make sure this is the one and only PCH.
// If multiple module's includes are needed, use individual includes.
#ifdef VL_PCH_INCLUDED
# error "Including multiple precompiled header files"
#endif
#define VL_PCH_INCLUDED


#include "verilated.h"
#include "verilated_dpi.h"

#include "Vdma_top__Syms.h"
#include "Vdma_top.h"

#endif  // guard
