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

VL_INLINE_OPT void Vdma_top___024root___ico_sequent__TOP__0(Vdma_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vdma_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdma_top___024root___ico_sequent__TOP__0\n"); );
    // Body
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

void Vdma_top___024root___eval_ico(Vdma_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vdma_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdma_top___024root___eval_ico\n"); );
    // Body
    if ((1ULL & vlSelf->__VicoTriggered.word(0U))) {
        Vdma_top___024root___ico_sequent__TOP__0(vlSelf);
    }
}

void Vdma_top___024root___eval_triggers__ico(Vdma_top___024root* vlSelf);

bool Vdma_top___024root___eval_phase__ico(Vdma_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vdma_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdma_top___024root___eval_phase__ico\n"); );
    // Init
    CData/*0:0*/ __VicoExecute;
    // Body
    Vdma_top___024root___eval_triggers__ico(vlSelf);
    __VicoExecute = vlSelf->__VicoTriggered.any();
    if (__VicoExecute) {
        Vdma_top___024root___eval_ico(vlSelf);
    }
    return (__VicoExecute);
}

void Vdma_top___024root___eval_act(Vdma_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vdma_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdma_top___024root___eval_act\n"); );
}

void Vdma_top___024root____Vdpiimwrap_dma_top__DOT__dpi_bank_read32_legacy_TOP(QData/*63:0*/ offset, IData/*31:0*/ &dpi_bank_read32_legacy__Vfuncrtn);
void Vdma_top___024root____Vdpiimwrap_dma_top__DOT__dpi_bank_write32_legacy_TOP(QData/*63:0*/ offset, IData/*31:0*/ value, IData/*31:0*/ &dpi_bank_write32_legacy__Vfuncrtn);

VL_INLINE_OPT void Vdma_top___024root___nba_sequent__TOP__0(Vdma_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vdma_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdma_top___024root___nba_sequent__TOP__0\n"); );
    // Init
    IData/*31:0*/ __Vfunc_dma_top__DOT__dpi_bank_read32_legacy__1__Vfuncout;
    __Vfunc_dma_top__DOT__dpi_bank_read32_legacy__1__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_dma_top__DOT__dpi_bank_write32_legacy__2__Vfuncout;
    __Vfunc_dma_top__DOT__dpi_bank_write32_legacy__2__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_dma_top__DOT__dpi_bank_read32_legacy__3__Vfuncout;
    __Vfunc_dma_top__DOT__dpi_bank_read32_legacy__3__Vfuncout = 0;
    CData/*0:0*/ __Vdly__dma_top__DOT__dma_ready;
    __Vdly__dma_top__DOT__dma_ready = 0;
    IData/*31:0*/ __Vdly__dma_top__DOT__dma_rdata;
    __Vdly__dma_top__DOT__dma_rdata = 0;
    CData/*0:0*/ __Vdly__dma_top__DOT__u_dma_rtl__DOT__copy_active;
    __Vdly__dma_top__DOT__u_dma_rtl__DOT__copy_active = 0;
    CData/*3:0*/ __Vdly__dma_top__DOT__u_dma_rtl__DOT__wait_cnt;
    __Vdly__dma_top__DOT__u_dma_rtl__DOT__wait_cnt = 0;
    IData/*31:0*/ __Vdly__dma_top__DOT__u_dma_rtl__DOT__read_data_reg;
    __Vdly__dma_top__DOT__u_dma_rtl__DOT__read_data_reg = 0;
    CData/*0:0*/ __Vdly__dma_top__DOT__u_dma_rtl__DOT__read_next;
    __Vdly__dma_top__DOT__u_dma_rtl__DOT__read_next = 0;
    QData/*63:0*/ __Vdly__dma_top__DOT__u_dma_rtl__DOT__src_addr;
    __Vdly__dma_top__DOT__u_dma_rtl__DOT__src_addr = 0;
    QData/*63:0*/ __Vdly__dma_top__DOT__u_dma_rtl__DOT__dst_addr;
    __Vdly__dma_top__DOT__u_dma_rtl__DOT__dst_addr = 0;
    IData/*31:0*/ __Vdly__ch_bytes_transferred;
    __Vdly__ch_bytes_transferred = 0;
    IData/*31:0*/ __Vdly__dma_top__DOT__u_dma_rtl__DOT__bytes_remaining;
    __Vdly__dma_top__DOT__u_dma_rtl__DOT__bytes_remaining = 0;
    // Body
    __Vdly__ch_bytes_transferred = vlSelf->ch_bytes_transferred;
    __Vdly__dma_top__DOT__u_dma_rtl__DOT__dst_addr 
        = vlSelf->dma_top__DOT__u_dma_rtl__DOT__dst_addr;
    __Vdly__dma_top__DOT__u_dma_rtl__DOT__src_addr 
        = vlSelf->dma_top__DOT__u_dma_rtl__DOT__src_addr;
    __Vdly__dma_top__DOT__u_dma_rtl__DOT__read_next 
        = vlSelf->dma_top__DOT__u_dma_rtl__DOT__read_next;
    __Vdly__dma_top__DOT__u_dma_rtl__DOT__read_data_reg 
        = vlSelf->dma_top__DOT__u_dma_rtl__DOT__read_data_reg;
    __Vdly__dma_top__DOT__u_dma_rtl__DOT__wait_cnt 
        = vlSelf->dma_top__DOT__u_dma_rtl__DOT__wait_cnt;
    __Vdly__dma_top__DOT__u_dma_rtl__DOT__copy_active 
        = vlSelf->dma_top__DOT__u_dma_rtl__DOT__copy_active;
    __Vdly__dma_top__DOT__u_dma_rtl__DOT__bytes_remaining 
        = vlSelf->dma_top__DOT__u_dma_rtl__DOT__bytes_remaining;
    __Vdly__dma_top__DOT__dma_rdata = vlSelf->dma_top__DOT__dma_rdata;
    __Vdly__dma_top__DOT__dma_ready = vlSelf->dma_top__DOT__dma_ready;
    if (vlSelf->rst_n) {
        __Vdly__dma_top__DOT__dma_ready = ((IData)(vlSelf->dma_top__DOT__dma_read) 
                                           | (IData)(vlSelf->dma_top__DOT__dma_write));
        if (vlSelf->dma_top__DOT__dma_read) {
            Vdma_top___024root____Vdpiimwrap_dma_top__DOT__dpi_bank_read32_legacy_TOP(vlSelf->dma_top__DOT__dma_addr, __Vfunc_dma_top__DOT__dpi_bank_read32_legacy__1__Vfuncout);
            __Vdly__dma_top__DOT__dma_rdata = __Vfunc_dma_top__DOT__dpi_bank_read32_legacy__1__Vfuncout;
        }
        if (vlSelf->dma_top__DOT__dma_write) {
            Vdma_top___024root____Vdpiimwrap_dma_top__DOT__dpi_bank_write32_legacy_TOP(vlSelf->dma_top__DOT__dma_addr, vlSelf->dma_top__DOT__dma_wdata, __Vfunc_dma_top__DOT__dpi_bank_write32_legacy__2__Vfuncout);
            vlSelf->dma_top__DOT__unnamedblk2__DOT__rc 
                = __Vfunc_dma_top__DOT__dpi_bank_write32_legacy__2__Vfuncout;
            Vdma_top___024root____Vdpiimwrap_dma_top__DOT__dpi_bank_read32_legacy_TOP(vlSelf->dma_top__DOT__dma_addr, __Vfunc_dma_top__DOT__dpi_bank_read32_legacy__3__Vfuncout);
            vlSelf->dma_top__DOT__unnamedblk2__DOT__readback 
                = __Vfunc_dma_top__DOT__dpi_bank_read32_legacy__3__Vfuncout;
        }
    } else {
        __Vdly__dma_top__DOT__dma_ready = 0U;
        __Vdly__dma_top__DOT__dma_rdata = 0U;
    }
    if (vlSelf->rst_n) {
        if ((4U & (IData)(vlSelf->dma_top__DOT__u_dma_rtl__DOT__current_state))) {
            if ((1U & (~ ((IData)(vlSelf->dma_top__DOT__u_dma_rtl__DOT__current_state) 
                          >> 1U)))) {
                if ((1U & (~ (IData)(vlSelf->dma_top__DOT__u_dma_rtl__DOT__current_state)))) {
                    vlSelf->ch_error = vlSelf->dma_top__DOT__u_dma_rtl__DOT__error_reg;
                }
            }
        } else if ((1U & (~ ((IData)(vlSelf->dma_top__DOT__u_dma_rtl__DOT__current_state) 
                             >> 1U)))) {
            if ((1U & (~ (IData)(vlSelf->dma_top__DOT__u_dma_rtl__DOT__current_state)))) {
                if (vlSelf->dma_top__DOT__u_dma_rtl__DOT__start_cond) {
                    vlSelf->ch_error = 0U;
                }
            }
        }
        if ((1U & (~ ((IData)(vlSelf->dma_top__DOT__u_dma_rtl__DOT__current_state) 
                      >> 2U)))) {
            if ((1U & (~ ((IData)(vlSelf->dma_top__DOT__u_dma_rtl__DOT__current_state) 
                          >> 1U)))) {
                if ((1U & (~ (IData)(vlSelf->dma_top__DOT__u_dma_rtl__DOT__current_state)))) {
                    if (vlSelf->dma_top__DOT__u_dma_rtl__DOT__start_cond) {
                        vlSelf->dma_top__DOT__u_dma_rtl__DOT__dst_bank = 0U;
                        vlSelf->dma_top__DOT__u_dma_rtl__DOT__src_bank = 0U;
                        vlSelf->dma_top__DOT__u_dma_rtl__DOT__cross_bank = 0U;
                        vlSelf->dma_top__DOT__u_dma_rtl__DOT__last_desc = 1U;
                        vlSelf->dma_top__DOT__u_dma_rtl__DOT__dir_memset = 0U;
                        vlSelf->dma_top__DOT__u_dma_rtl__DOT__total_bytes 
                            = (IData)(vlSelf->desc_data_2);
                        vlSelf->dma_top__DOT__u_dma_rtl__DOT__intr_en = 0U;
                        vlSelf->dma_top__DOT__u_dma_rtl__DOT__error_reg = 0U;
                    }
                }
            }
        }
        if ((4U & (IData)(vlSelf->dma_top__DOT__u_dma_rtl__DOT__current_state))) {
            if ((2U & (IData)(vlSelf->dma_top__DOT__u_dma_rtl__DOT__current_state))) {
                __Vdly__dma_top__DOT__u_dma_rtl__DOT__copy_active = 0U;
            } else if ((1U & (IData)(vlSelf->dma_top__DOT__u_dma_rtl__DOT__current_state))) {
                __Vdly__dma_top__DOT__u_dma_rtl__DOT__copy_active = 0U;
            }
        } else if ((2U & (IData)(vlSelf->dma_top__DOT__u_dma_rtl__DOT__current_state))) {
            if ((1U & (IData)(vlSelf->dma_top__DOT__u_dma_rtl__DOT__current_state))) {
                __Vdly__dma_top__DOT__u_dma_rtl__DOT__copy_active = 0U;
                vlSelf->dma_top__DOT__u_dma_rtl__DOT__copy_done_reg = 0U;
            } else if ((1U & (~ (IData)(vlSelf->ch_pause)))) {
                if ((0U == vlSelf->dma_top__DOT__u_dma_rtl__DOT__bytes_remaining)) {
                    __Vdly__dma_top__DOT__u_dma_rtl__DOT__copy_active = 0U;
                    vlSelf->dma_top__DOT__u_dma_rtl__DOT__copy_done_reg = 1U;
                    vlSelf->dma_top__DOT__dma_read = 0U;
                    vlSelf->dma_top__DOT__dma_write = 0U;
                    __Vdly__dma_top__DOT__u_dma_rtl__DOT__wait_cnt = 0U;
                } else if (vlSelf->dma_top__DOT__u_dma_rtl__DOT__copy_active) {
                    if (vlSelf->dma_top__DOT__dma_ready) {
                        if ((1U > (IData)(vlSelf->dma_top__DOT__u_dma_rtl__DOT__wait_cnt))) {
                            __Vdly__dma_top__DOT__u_dma_rtl__DOT__wait_cnt 
                                = (0xfU & ((IData)(1U) 
                                           + (IData)(vlSelf->dma_top__DOT__u_dma_rtl__DOT__wait_cnt)));
                        } else {
                            __Vdly__dma_top__DOT__u_dma_rtl__DOT__copy_active = 0U;
                            vlSelf->dma_top__DOT__dma_read = 0U;
                            vlSelf->dma_top__DOT__dma_write = 0U;
                            __Vdly__dma_top__DOT__u_dma_rtl__DOT__wait_cnt = 0U;
                            if (vlSelf->dma_top__DOT__u_dma_rtl__DOT__read_next) {
                                __Vdly__dma_top__DOT__u_dma_rtl__DOT__read_data_reg 
                                    = vlSelf->dma_top__DOT__dma_rdata;
                                __Vdly__dma_top__DOT__u_dma_rtl__DOT__read_next = 0U;
                            } else {
                                __Vdly__dma_top__DOT__u_dma_rtl__DOT__src_addr 
                                    = (4ULL + vlSelf->dma_top__DOT__u_dma_rtl__DOT__src_addr);
                                __Vdly__dma_top__DOT__u_dma_rtl__DOT__dst_addr 
                                    = (4ULL + vlSelf->dma_top__DOT__u_dma_rtl__DOT__dst_addr);
                                if ((4U >= vlSelf->dma_top__DOT__u_dma_rtl__DOT__bytes_remaining)) {
                                    __Vdly__ch_bytes_transferred 
                                        = (vlSelf->ch_bytes_transferred 
                                           + vlSelf->dma_top__DOT__u_dma_rtl__DOT__bytes_remaining);
                                    __Vdly__dma_top__DOT__u_dma_rtl__DOT__bytes_remaining = 0U;
                                } else {
                                    __Vdly__dma_top__DOT__u_dma_rtl__DOT__bytes_remaining 
                                        = (vlSelf->dma_top__DOT__u_dma_rtl__DOT__bytes_remaining 
                                           - (IData)(4U));
                                    __Vdly__ch_bytes_transferred 
                                        = ((IData)(4U) 
                                           + vlSelf->ch_bytes_transferred);
                                }
                                __Vdly__dma_top__DOT__u_dma_rtl__DOT__read_next = 1U;
                            }
                        }
                    }
                } else {
                    __Vdly__dma_top__DOT__u_dma_rtl__DOT__copy_active = 1U;
                    __Vdly__dma_top__DOT__u_dma_rtl__DOT__wait_cnt = 0U;
                    if (vlSelf->dma_top__DOT__u_dma_rtl__DOT__read_next) {
                        vlSelf->dma_top__DOT__dma_addr 
                            = vlSelf->dma_top__DOT__u_dma_rtl__DOT__src_addr;
                        vlSelf->dma_top__DOT__dma_read = 1U;
                        vlSelf->dma_top__DOT__dma_write = 0U;
                    } else {
                        vlSelf->dma_top__DOT__dma_addr 
                            = vlSelf->dma_top__DOT__u_dma_rtl__DOT__dst_addr;
                        vlSelf->dma_top__DOT__dma_wdata 
                            = vlSelf->dma_top__DOT__u_dma_rtl__DOT__read_data_reg;
                        vlSelf->dma_top__DOT__dma_write = 1U;
                        vlSelf->dma_top__DOT__dma_read = 0U;
                    }
                }
            }
        } else if ((1U & (~ (IData)(vlSelf->dma_top__DOT__u_dma_rtl__DOT__current_state)))) {
            if (vlSelf->dma_top__DOT__u_dma_rtl__DOT__start_cond) {
                __Vdly__dma_top__DOT__u_dma_rtl__DOT__src_addr 
                    = vlSelf->desc_data_0;
                __Vdly__dma_top__DOT__u_dma_rtl__DOT__dst_addr 
                    = vlSelf->desc_data_1;
                __Vdly__dma_top__DOT__u_dma_rtl__DOT__bytes_remaining 
                    = (IData)(vlSelf->desc_data_2);
                __Vdly__dma_top__DOT__u_dma_rtl__DOT__read_next = 1U;
                __Vdly__ch_bytes_transferred = 0U;
                __Vdly__dma_top__DOT__u_dma_rtl__DOT__read_data_reg = 0U;
                __Vdly__dma_top__DOT__u_dma_rtl__DOT__copy_active = 0U;
                vlSelf->dma_top__DOT__u_dma_rtl__DOT__copy_done_reg = 0U;
                __Vdly__dma_top__DOT__u_dma_rtl__DOT__wait_cnt = 0U;
            }
        }
        vlSelf->dma_top__DOT__u_dma_rtl__DOT__desc_ready_reg 
            = vlSelf->dma_top__DOT__u_dma_rtl__DOT__start_cond;
    } else {
        vlSelf->dma_top__DOT__u_dma_rtl__DOT__dst_bank = 0U;
        vlSelf->dma_top__DOT__u_dma_rtl__DOT__src_bank = 0U;
        vlSelf->dma_top__DOT__u_dma_rtl__DOT__cross_bank = 0U;
        vlSelf->dma_top__DOT__u_dma_rtl__DOT__last_desc = 0U;
        vlSelf->dma_top__DOT__u_dma_rtl__DOT__dir_memset = 0U;
        vlSelf->dma_top__DOT__u_dma_rtl__DOT__total_bytes = 0U;
        vlSelf->dma_top__DOT__u_dma_rtl__DOT__intr_en = 0U;
        vlSelf->ch_error = 0U;
        __Vdly__dma_top__DOT__u_dma_rtl__DOT__src_addr = 0ULL;
        __Vdly__dma_top__DOT__u_dma_rtl__DOT__dst_addr = 0ULL;
        __Vdly__dma_top__DOT__u_dma_rtl__DOT__bytes_remaining = 0U;
        __Vdly__dma_top__DOT__u_dma_rtl__DOT__read_next = 0U;
        __Vdly__ch_bytes_transferred = 0U;
        __Vdly__dma_top__DOT__u_dma_rtl__DOT__read_data_reg = 0U;
        __Vdly__dma_top__DOT__u_dma_rtl__DOT__copy_active = 0U;
        vlSelf->dma_top__DOT__u_dma_rtl__DOT__copy_done_reg = 0U;
        __Vdly__dma_top__DOT__u_dma_rtl__DOT__wait_cnt = 0U;
        vlSelf->dma_top__DOT__dma_addr = 0ULL;
        vlSelf->dma_top__DOT__dma_wdata = 0U;
        vlSelf->dma_top__DOT__dma_read = 0U;
        vlSelf->dma_top__DOT__dma_write = 0U;
        vlSelf->dma_top__DOT__u_dma_rtl__DOT__error_reg = 0U;
        vlSelf->dma_top__DOT__u_dma_rtl__DOT__desc_ready_reg = 0U;
    }
    vlSelf->desc_ready = vlSelf->dma_top__DOT__u_dma_rtl__DOT__desc_ready_reg;
    vlSelf->dma_top__DOT__dma_ready = __Vdly__dma_top__DOT__dma_ready;
    vlSelf->dma_top__DOT__dma_rdata = __Vdly__dma_top__DOT__dma_rdata;
    vlSelf->dma_top__DOT__u_dma_rtl__DOT__copy_active 
        = __Vdly__dma_top__DOT__u_dma_rtl__DOT__copy_active;
    vlSelf->dma_top__DOT__u_dma_rtl__DOT__wait_cnt 
        = __Vdly__dma_top__DOT__u_dma_rtl__DOT__wait_cnt;
    vlSelf->dma_top__DOT__u_dma_rtl__DOT__read_data_reg 
        = __Vdly__dma_top__DOT__u_dma_rtl__DOT__read_data_reg;
    vlSelf->dma_top__DOT__u_dma_rtl__DOT__read_next 
        = __Vdly__dma_top__DOT__u_dma_rtl__DOT__read_next;
    vlSelf->dma_top__DOT__u_dma_rtl__DOT__src_addr 
        = __Vdly__dma_top__DOT__u_dma_rtl__DOT__src_addr;
    vlSelf->dma_top__DOT__u_dma_rtl__DOT__dst_addr 
        = __Vdly__dma_top__DOT__u_dma_rtl__DOT__dst_addr;
    vlSelf->ch_bytes_transferred = __Vdly__ch_bytes_transferred;
    vlSelf->dma_top__DOT__u_dma_rtl__DOT__bytes_remaining 
        = __Vdly__dma_top__DOT__u_dma_rtl__DOT__bytes_remaining;
}

void Vdma_top___024root____Vdpiimwrap_dma_top__DOT__dma_done_callback_TOP();

VL_INLINE_OPT void Vdma_top___024root___nba_sequent__TOP__1(Vdma_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vdma_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdma_top___024root___nba_sequent__TOP__1\n"); );
    // Body
    if (((~ (IData)(vlSelf->dma_top__DOT__ch_done_d)) 
         & (IData)(vlSelf->ch_done))) {
        Vdma_top___024root____Vdpiimwrap_dma_top__DOT__dma_done_callback_TOP();
    }
}

VL_INLINE_OPT void Vdma_top___024root___nba_sequent__TOP__2(Vdma_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vdma_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdma_top___024root___nba_sequent__TOP__2\n"); );
    // Body
    if (vlSelf->rst_n) {
        vlSelf->dma_top__DOT__ch_done_d = vlSelf->ch_done;
        if ((4U & (IData)(vlSelf->dma_top__DOT__u_dma_rtl__DOT__current_state))) {
            if ((1U & (~ ((IData)(vlSelf->dma_top__DOT__u_dma_rtl__DOT__current_state) 
                          >> 1U)))) {
                if ((1U & (~ (IData)(vlSelf->dma_top__DOT__u_dma_rtl__DOT__current_state)))) {
                    vlSelf->ch_done = 1U;
                }
            }
        } else if ((1U & (~ ((IData)(vlSelf->dma_top__DOT__u_dma_rtl__DOT__current_state) 
                             >> 1U)))) {
            if ((1U & (~ (IData)(vlSelf->dma_top__DOT__u_dma_rtl__DOT__current_state)))) {
                vlSelf->ch_done = 0U;
            }
        }
        if ((1U & (~ (IData)(vlSelf->ch_pause)))) {
            vlSelf->dma_top__DOT__u_dma_rtl__DOT__current_state 
                = vlSelf->dma_top__DOT__u_dma_rtl__DOT__next_state;
        }
    } else {
        vlSelf->dma_top__DOT__ch_done_d = 0U;
        vlSelf->ch_done = 0U;
        vlSelf->dma_top__DOT__u_dma_rtl__DOT__current_state = 0U;
    }
    vlSelf->irq = ((IData)(vlSelf->ch_done) & (IData)(vlSelf->dma_top__DOT__u_dma_rtl__DOT__intr_en));
    vlSelf->state = (3U & (IData)(vlSelf->dma_top__DOT__u_dma_rtl__DOT__current_state));
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

void Vdma_top___024root___eval_nba(Vdma_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vdma_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdma_top___024root___eval_nba\n"); );
    // Body
    if ((1ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vdma_top___024root___nba_sequent__TOP__0(vlSelf);
        vlSelf->__Vm_traceActivity[1U] = 1U;
    }
    if ((2ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vdma_top___024root___nba_sequent__TOP__1(vlSelf);
    }
    if ((1ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vdma_top___024root___nba_sequent__TOP__2(vlSelf);
    }
}

void Vdma_top___024root___eval_triggers__act(Vdma_top___024root* vlSelf);

bool Vdma_top___024root___eval_phase__act(Vdma_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vdma_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdma_top___024root___eval_phase__act\n"); );
    // Init
    VlTriggerVec<2> __VpreTriggered;
    CData/*0:0*/ __VactExecute;
    // Body
    Vdma_top___024root___eval_triggers__act(vlSelf);
    __VactExecute = vlSelf->__VactTriggered.any();
    if (__VactExecute) {
        __VpreTriggered.andNot(vlSelf->__VactTriggered, vlSelf->__VnbaTriggered);
        vlSelf->__VnbaTriggered.thisOr(vlSelf->__VactTriggered);
        Vdma_top___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

bool Vdma_top___024root___eval_phase__nba(Vdma_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vdma_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdma_top___024root___eval_phase__nba\n"); );
    // Init
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = vlSelf->__VnbaTriggered.any();
    if (__VnbaExecute) {
        Vdma_top___024root___eval_nba(vlSelf);
        vlSelf->__VnbaTriggered.clear();
    }
    return (__VnbaExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vdma_top___024root___dump_triggers__ico(Vdma_top___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vdma_top___024root___dump_triggers__nba(Vdma_top___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vdma_top___024root___dump_triggers__act(Vdma_top___024root* vlSelf);
#endif  // VL_DEBUG

void Vdma_top___024root___eval(Vdma_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vdma_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdma_top___024root___eval\n"); );
    // Init
    IData/*31:0*/ __VicoIterCount;
    CData/*0:0*/ __VicoContinue;
    IData/*31:0*/ __VnbaIterCount;
    CData/*0:0*/ __VnbaContinue;
    // Body
    __VicoIterCount = 0U;
    vlSelf->__VicoFirstIteration = 1U;
    __VicoContinue = 1U;
    while (__VicoContinue) {
        if (VL_UNLIKELY((0x64U < __VicoIterCount))) {
#ifdef VL_DEBUG
            Vdma_top___024root___dump_triggers__ico(vlSelf);
#endif
            VL_FATAL_MT("build/merged_rtl.sv", 252, "", "Input combinational region did not converge.");
        }
        __VicoIterCount = ((IData)(1U) + __VicoIterCount);
        __VicoContinue = 0U;
        if (Vdma_top___024root___eval_phase__ico(vlSelf)) {
            __VicoContinue = 1U;
        }
        vlSelf->__VicoFirstIteration = 0U;
    }
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        if (VL_UNLIKELY((0x64U < __VnbaIterCount))) {
#ifdef VL_DEBUG
            Vdma_top___024root___dump_triggers__nba(vlSelf);
#endif
            VL_FATAL_MT("build/merged_rtl.sv", 252, "", "NBA region did not converge.");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        __VnbaContinue = 0U;
        vlSelf->__VactIterCount = 0U;
        vlSelf->__VactContinue = 1U;
        while (vlSelf->__VactContinue) {
            if (VL_UNLIKELY((0x64U < vlSelf->__VactIterCount))) {
#ifdef VL_DEBUG
                Vdma_top___024root___dump_triggers__act(vlSelf);
#endif
                VL_FATAL_MT("build/merged_rtl.sv", 252, "", "Active region did not converge.");
            }
            vlSelf->__VactIterCount = ((IData)(1U) 
                                       + vlSelf->__VactIterCount);
            vlSelf->__VactContinue = 0U;
            if (Vdma_top___024root___eval_phase__act(vlSelf)) {
                vlSelf->__VactContinue = 1U;
            }
        }
        if (Vdma_top___024root___eval_phase__nba(vlSelf)) {
            __VnbaContinue = 1U;
        }
    }
}

#ifdef VL_DEBUG
void Vdma_top___024root___eval_debug_assertions(Vdma_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vdma_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdma_top___024root___eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((vlSelf->clk & 0xfeU))) {
        Verilated::overWidthError("clk");}
    if (VL_UNLIKELY((vlSelf->rst_n & 0xfeU))) {
        Verilated::overWidthError("rst_n");}
    if (VL_UNLIKELY((vlSelf->ch_enable & 0xfeU))) {
        Verilated::overWidthError("ch_enable");}
    if (VL_UNLIKELY((vlSelf->ch_pause & 0xfeU))) {
        Verilated::overWidthError("ch_pause");}
    if (VL_UNLIKELY((vlSelf->desc_valid & 0xfeU))) {
        Verilated::overWidthError("desc_valid");}
}
#endif  // VL_DEBUG
