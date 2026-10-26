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
#include "Vdma_top___024root.h"

#ifdef VL_DEBUG
VL_ATTR_COLD void Vdma_top___024root___dump_triggers__stl(Vdma_top___024root* vlSelf);
#endif  // VL_DEBUG

VL_ATTR_COLD void Vdma_top___024root___eval_triggers__stl(Vdma_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vdma_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdma_top___024root___eval_triggers__stl\n"); );
    // Body
    vlSelf->__VstlTriggered.set(0U, (IData)(vlSelf->__VstlFirstIteration));
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vdma_top___024root___dump_triggers__stl(vlSelf);
    }
#endif
}
