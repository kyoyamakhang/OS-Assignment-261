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
 * DESCRIPTION: Verilator output: Implementation of DPI export functions.
 *
 * Verilator compiles this file in when DPI functions are used.
 * If you have multiple Verilated designs with the same DPI exported
 * function names, you will get multiple definition link errors from here.
 * This is an unfortunate result of the DPI specification.
 * To solve this, either
 *    1. Call Vdma_top::{export_function} instead,
 *       and do not even bother to compile this file
 * or 2. Compile all __Dpi.cpp files in the same compiler run,
 *       and #ifdefs already inserted here will sort everything out.
 */

#include "Vdma_top__Dpi.h"
#include "Vdma_top.h"

