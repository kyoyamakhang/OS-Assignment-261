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
#include "Vdma_top___024root.h"

VL_ATTR_COLD void Vdma_top___024root___eval_static(Vdma_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vdma_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdma_top___024root___eval_static\n"); );
}

VL_ATTR_COLD void Vdma_top___024root___eval_initial(Vdma_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vdma_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdma_top___024root___eval_initial\n"); );
    // Body
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = vlSelf->clk;
    vlSelf->__Vtrigprevexpr___TOP__rst_n__0 = vlSelf->rst_n;
}

VL_ATTR_COLD void Vdma_top___024root___eval_final(Vdma_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vdma_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdma_top___024root___eval_final\n"); );
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vdma_top___024root___dump_triggers__stl(Vdma_top___024root* vlSelf);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vdma_top___024root___eval_phase__stl(Vdma_top___024root* vlSelf);

VL_ATTR_COLD void Vdma_top___024root___eval_settle(Vdma_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vdma_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdma_top___024root___eval_settle\n"); );
    // Init
    IData/*31:0*/ __VstlIterCount;
    CData/*0:0*/ __VstlContinue;
    // Body
    __VstlIterCount = 0U;
    vlSelf->__VstlFirstIteration = 1U;
    __VstlContinue = 1U;
    while (__VstlContinue) {
        if (VL_UNLIKELY((0x64U < __VstlIterCount))) {
#ifdef VL_DEBUG
            Vdma_top___024root___dump_triggers__stl(vlSelf);
#endif
            VL_FATAL_MT("build/merged_rtl.sv", 252, "", "Settle region did not converge.");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
        __VstlContinue = 0U;
        if (Vdma_top___024root___eval_phase__stl(vlSelf)) {
            __VstlContinue = 1U;
        }
        vlSelf->__VstlFirstIteration = 0U;
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vdma_top___024root___dump_triggers__stl(Vdma_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vdma_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdma_top___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VstlTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelf->__VstlTriggered.word(0U))) {
        VL_DBG_MSGF("         'stl' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vdma_top___024root___stl_sequent__TOP__0(Vdma_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vdma_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdma_top___024root___stl_sequent__TOP__0\n"); );
    // Body
    vlSelf->state = (3U & (IData)(vlSelf->dma_top__DOT__u_dma_rtl__DOT__current_state));
    vlSelf->desc_ready = vlSelf->dma_top__DOT__u_dma_rtl__DOT__desc_ready_reg;
    vlSelf->irq = ((IData)(vlSelf->ch_done) & (IData)(vlSelf->dma_top__DOT__u_dma_rtl__DOT__intr_en));
    vlSelf->dma_top__DOT__u_dma_rtl__DOT__start_cond 
        = ((0U == (IData)(vlSelf->dma_top__DOT__u_dma_rtl__DOT__current_state)) 
           & ((IData)(vlSelf->ch_enable) & ((~ (IData)(vlSelf->ch_pause)) 
                                            & (IData)(vlSelf->desc_valid))));
    vlSelf->dma_top__DOT__u_dma_rtl__DOT__next_state 
        = vlSelf->dma_top__DOT__u_dma_rtl__DOT__current_state;
    if ((4U & (IData)(vlSelf->dma_top__DOT__u_dma_rtl__DOT__current_state))) {
        if ((2U & (IData)(vlSelf->dma_top__DOT__u_dma_rtl__DOT__current_state))) {
            vlSelf->dma_top__DOT__u_dma_rtl__DOT__next_state = 0U;
        } else if ((1U & (IData)(vlSelf->dma_top__DOT__u_dma_rtl__DOT__current_state))) {
            vlSelf->dma_top__DOT__u_dma_rtl__DOT__next_state = 0U;
        } else if ((1U & (~ (IData)(vlSelf->ch_enable)))) {
            vlSelf->dma_top__DOT__u_dma_rtl__DOT__next_state = 0U;
        }
    } else if ((2U & (IData)(vlSelf->dma_top__DOT__u_dma_rtl__DOT__current_state))) {
        if ((1U & (IData)(vlSelf->dma_top__DOT__u_dma_rtl__DOT__current_state))) {
            vlSelf->dma_top__DOT__u_dma_rtl__DOT__next_state = 4U;
        } else if (((IData)(vlSelf->dma_top__DOT__u_dma_rtl__DOT__copy_done_reg) 
                    & (0U == vlSelf->dma_top__DOT__u_dma_rtl__DOT__bytes_remaining))) {
            vlSelf->dma_top__DOT__u_dma_rtl__DOT__next_state = 3U;
        }
    } else if ((1U & (IData)(vlSelf->dma_top__DOT__u_dma_rtl__DOT__current_state))) {
        vlSelf->dma_top__DOT__u_dma_rtl__DOT__next_state = 2U;
    } else if (vlSelf->dma_top__DOT__u_dma_rtl__DOT__start_cond) {
        vlSelf->dma_top__DOT__u_dma_rtl__DOT__next_state = 1U;
    }
}

VL_ATTR_COLD void Vdma_top___024root___eval_stl(Vdma_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vdma_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdma_top___024root___eval_stl\n"); );
    // Body
    if ((1ULL & vlSelf->__VstlTriggered.word(0U))) {
        Vdma_top___024root___stl_sequent__TOP__0(vlSelf);
    }
}

VL_ATTR_COLD void Vdma_top___024root___eval_triggers__stl(Vdma_top___024root* vlSelf);

VL_ATTR_COLD bool Vdma_top___024root___eval_phase__stl(Vdma_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vdma_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdma_top___024root___eval_phase__stl\n"); );
    // Init
    CData/*0:0*/ __VstlExecute;
    // Body
    Vdma_top___024root___eval_triggers__stl(vlSelf);
    __VstlExecute = vlSelf->__VstlTriggered.any();
    if (__VstlExecute) {
        Vdma_top___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vdma_top___024root___dump_triggers__ico(Vdma_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vdma_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdma_top___024root___dump_triggers__ico\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VicoTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelf->__VicoTriggered.word(0U))) {
        VL_DBG_MSGF("         'ico' region trigger index 0 is active: Internal 'ico' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void Vdma_top___024root___dump_triggers__act(Vdma_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vdma_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdma_top___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VactTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelf->__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 0 is active: @(posedge clk or negedge rst_n)\n");
    }
    if ((2ULL & vlSelf->__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 1 is active: @(posedge clk)\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void Vdma_top___024root___dump_triggers__nba(Vdma_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vdma_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdma_top___024root___dump_triggers__nba\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VnbaTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelf->__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 0 is active: @(posedge clk or negedge rst_n)\n");
    }
    if ((2ULL & vlSelf->__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 1 is active: @(posedge clk)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vdma_top___024root___ctor_var_reset(Vdma_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vdma_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdma_top___024root___ctor_var_reset\n"); );
    // Body
    vlSelf->clk = 0;
    vlSelf->rst_n = 0;
    vlSelf->ch_enable = 0;
    vlSelf->ch_pause = 0;
    vlSelf->ch_done = 0;
    vlSelf->ch_error = 0;
    vlSelf->ch_bytes_transferred = 0;
    vlSelf->irq = 0;
    vlSelf->desc_valid = 0;
    vlSelf->desc_data_0 = 0;
    vlSelf->desc_data_1 = 0;
    vlSelf->desc_data_2 = 0;
    vlSelf->desc_data_3 = 0;
    vlSelf->desc_ready = 0;
    vlSelf->state = 0;
    vlSelf->dma_top__DOT__dma_addr = 0;
    vlSelf->dma_top__DOT__dma_wdata = 0;
    vlSelf->dma_top__DOT__dma_write = 0;
    vlSelf->dma_top__DOT__dma_read = 0;
    vlSelf->dma_top__DOT__dma_rdata = 0;
    vlSelf->dma_top__DOT__dma_ready = 0;
    vlSelf->dma_top__DOT__ch_done_d = 0;
    vlSelf->dma_top__DOT__unnamedblk1__DOT__read_value = 0;
    vlSelf->dma_top__DOT__unnamedblk2__DOT__rc = 0;
    vlSelf->dma_top__DOT__unnamedblk2__DOT__readback = 0;
    vlSelf->dma_top__DOT__u_dma_rtl__DOT__current_state = 0;
    vlSelf->dma_top__DOT__u_dma_rtl__DOT__next_state = 0;
    vlSelf->dma_top__DOT__u_dma_rtl__DOT__src_addr = 0;
    vlSelf->dma_top__DOT__u_dma_rtl__DOT__dst_addr = 0;
    vlSelf->dma_top__DOT__u_dma_rtl__DOT__total_bytes = 0;
    vlSelf->dma_top__DOT__u_dma_rtl__DOT__dir_memset = 0;
    vlSelf->dma_top__DOT__u_dma_rtl__DOT__intr_en = 0;
    vlSelf->dma_top__DOT__u_dma_rtl__DOT__last_desc = 0;
    vlSelf->dma_top__DOT__u_dma_rtl__DOT__cross_bank = 0;
    vlSelf->dma_top__DOT__u_dma_rtl__DOT__src_bank = 0;
    vlSelf->dma_top__DOT__u_dma_rtl__DOT__dst_bank = 0;
    vlSelf->dma_top__DOT__u_dma_rtl__DOT__bytes_remaining = 0;
    vlSelf->dma_top__DOT__u_dma_rtl__DOT__read_next = 0;
    vlSelf->dma_top__DOT__u_dma_rtl__DOT__read_data_reg = 0;
    vlSelf->dma_top__DOT__u_dma_rtl__DOT__copy_active = 0;
    vlSelf->dma_top__DOT__u_dma_rtl__DOT__copy_done_reg = 0;
    vlSelf->dma_top__DOT__u_dma_rtl__DOT__error_reg = 0;
    vlSelf->dma_top__DOT__u_dma_rtl__DOT__wait_cnt = 0;
    vlSelf->dma_top__DOT__u_dma_rtl__DOT__start_cond = 0;
    vlSelf->dma_top__DOT__u_dma_rtl__DOT__desc_ready_reg = 0;
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__rst_n__0 = 0;
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->__Vm_traceActivity[__Vi0] = 0;
    }
}
