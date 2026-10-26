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

extern "C" int dpi_bank_read32_legacy(long long offset);

VL_INLINE_OPT void Vdma_top___024root____Vdpiimwrap_dma_top__DOT__dpi_bank_read32_legacy_TOP(QData/*63:0*/ offset, IData/*31:0*/ &dpi_bank_read32_legacy__Vfuncrtn) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdma_top___024root____Vdpiimwrap_dma_top__DOT__dpi_bank_read32_legacy_TOP\n"); );
    // Body
    long long offset__Vcvt;
    for (size_t offset__Vidx = 0; offset__Vidx < 1; ++offset__Vidx) offset__Vcvt = offset;
    int dpi_bank_read32_legacy__Vfuncrtn__Vcvt;
    dpi_bank_read32_legacy__Vfuncrtn__Vcvt = dpi_bank_read32_legacy(offset__Vcvt);
    dpi_bank_read32_legacy__Vfuncrtn = dpi_bank_read32_legacy__Vfuncrtn__Vcvt;
}

extern "C" int dpi_bank_write32_legacy(long long offset, int value);

VL_INLINE_OPT void Vdma_top___024root____Vdpiimwrap_dma_top__DOT__dpi_bank_write32_legacy_TOP(QData/*63:0*/ offset, IData/*31:0*/ value, IData/*31:0*/ &dpi_bank_write32_legacy__Vfuncrtn) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdma_top___024root____Vdpiimwrap_dma_top__DOT__dpi_bank_write32_legacy_TOP\n"); );
    // Body
    long long offset__Vcvt;
    for (size_t offset__Vidx = 0; offset__Vidx < 1; ++offset__Vidx) offset__Vcvt = offset;
    int value__Vcvt;
    for (size_t value__Vidx = 0; value__Vidx < 1; ++value__Vidx) value__Vcvt = value;
    int dpi_bank_write32_legacy__Vfuncrtn__Vcvt;
    dpi_bank_write32_legacy__Vfuncrtn__Vcvt = dpi_bank_write32_legacy(offset__Vcvt, value__Vcvt);
    dpi_bank_write32_legacy__Vfuncrtn = dpi_bank_write32_legacy__Vfuncrtn__Vcvt;
}

extern "C" void dma_done_callback();

VL_INLINE_OPT void Vdma_top___024root____Vdpiimwrap_dma_top__DOT__dma_done_callback_TOP() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdma_top___024root____Vdpiimwrap_dma_top__DOT__dma_done_callback_TOP\n"); );
    // Body
    dma_done_callback();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vdma_top___024root___dump_triggers__ico(Vdma_top___024root* vlSelf);
#endif  // VL_DEBUG

void Vdma_top___024root___eval_triggers__ico(Vdma_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vdma_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdma_top___024root___eval_triggers__ico\n"); );
    // Body
    vlSelf->__VicoTriggered.set(0U, (IData)(vlSelf->__VicoFirstIteration));
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vdma_top___024root___dump_triggers__ico(vlSelf);
    }
#endif
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vdma_top___024root___dump_triggers__act(Vdma_top___024root* vlSelf);
#endif  // VL_DEBUG

void Vdma_top___024root___eval_triggers__act(Vdma_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vdma_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdma_top___024root___eval_triggers__act\n"); );
    // Body
    vlSelf->__VactTriggered.set(0U, (((IData)(vlSelf->clk) 
                                      & (~ (IData)(vlSelf->__Vtrigprevexpr___TOP__clk__0))) 
                                     | ((~ (IData)(vlSelf->rst_n)) 
                                        & (IData)(vlSelf->__Vtrigprevexpr___TOP__rst_n__0))));
    vlSelf->__VactTriggered.set(1U, ((IData)(vlSelf->clk) 
                                     & (~ (IData)(vlSelf->__Vtrigprevexpr___TOP__clk__0))));
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = vlSelf->clk;
    vlSelf->__Vtrigprevexpr___TOP__rst_n__0 = vlSelf->rst_n;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vdma_top___024root___dump_triggers__act(vlSelf);
    }
#endif
}
