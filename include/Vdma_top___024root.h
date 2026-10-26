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

#ifndef VERILATED_VDMA_TOP___024ROOT_H_
#define VERILATED_VDMA_TOP___024ROOT_H_  // guard

#include "verilated.h"


class Vdma_top__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vdma_top___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(clk,0,0);
    VL_IN8(rst_n,0,0);
    VL_IN8(ch_enable,0,0);
    VL_IN8(ch_pause,0,0);
    VL_OUT8(ch_done,0,0);
    VL_OUT8(ch_error,0,0);
    VL_OUT8(irq,0,0);
    VL_IN8(desc_valid,0,0);
    VL_OUT8(desc_ready,0,0);
    VL_OUT8(state,1,0);
    CData/*0:0*/ dma_top__DOT__dma_write;
    CData/*0:0*/ dma_top__DOT__dma_read;
    CData/*0:0*/ dma_top__DOT__dma_ready;
    CData/*0:0*/ dma_top__DOT__ch_done_d;
    CData/*2:0*/ dma_top__DOT__u_dma_rtl__DOT__current_state;
    CData/*2:0*/ dma_top__DOT__u_dma_rtl__DOT__next_state;
    CData/*0:0*/ dma_top__DOT__u_dma_rtl__DOT__dir_memset;
    CData/*0:0*/ dma_top__DOT__u_dma_rtl__DOT__intr_en;
    CData/*0:0*/ dma_top__DOT__u_dma_rtl__DOT__last_desc;
    CData/*0:0*/ dma_top__DOT__u_dma_rtl__DOT__cross_bank;
    CData/*7:0*/ dma_top__DOT__u_dma_rtl__DOT__src_bank;
    CData/*7:0*/ dma_top__DOT__u_dma_rtl__DOT__dst_bank;
    CData/*0:0*/ dma_top__DOT__u_dma_rtl__DOT__read_next;
    CData/*0:0*/ dma_top__DOT__u_dma_rtl__DOT__copy_active;
    CData/*0:0*/ dma_top__DOT__u_dma_rtl__DOT__copy_done_reg;
    CData/*0:0*/ dma_top__DOT__u_dma_rtl__DOT__error_reg;
    CData/*3:0*/ dma_top__DOT__u_dma_rtl__DOT__wait_cnt;
    CData/*0:0*/ dma_top__DOT__u_dma_rtl__DOT__start_cond;
    CData/*0:0*/ dma_top__DOT__u_dma_rtl__DOT__desc_ready_reg;
    CData/*0:0*/ __VstlFirstIteration;
    CData/*0:0*/ __VicoFirstIteration;
    CData/*0:0*/ __Vtrigprevexpr___TOP__clk__0;
    CData/*0:0*/ __Vtrigprevexpr___TOP__rst_n__0;
    CData/*0:0*/ __VactContinue;
    VL_OUT(ch_bytes_transferred,31,0);
    IData/*31:0*/ dma_top__DOT__dma_wdata;
    IData/*31:0*/ dma_top__DOT__dma_rdata;
    IData/*31:0*/ dma_top__DOT__unnamedblk1__DOT__read_value;
    IData/*31:0*/ dma_top__DOT__unnamedblk2__DOT__rc;
    IData/*31:0*/ dma_top__DOT__unnamedblk2__DOT__readback;
    IData/*31:0*/ dma_top__DOT__u_dma_rtl__DOT__total_bytes;
    IData/*31:0*/ dma_top__DOT__u_dma_rtl__DOT__bytes_remaining;
    IData/*31:0*/ dma_top__DOT__u_dma_rtl__DOT__read_data_reg;
    IData/*31:0*/ __VactIterCount;
    VL_IN64(desc_data_0,63,0);
    VL_IN64(desc_data_1,63,0);
    VL_IN64(desc_data_2,63,0);
    VL_IN64(desc_data_3,63,0);
    QData/*63:0*/ dma_top__DOT__dma_addr;
    QData/*63:0*/ dma_top__DOT__u_dma_rtl__DOT__src_addr;
    QData/*63:0*/ dma_top__DOT__u_dma_rtl__DOT__dst_addr;
    VlUnpacked<CData/*0:0*/, 2> __Vm_traceActivity;
    VlTriggerVec<1> __VstlTriggered;
    VlTriggerVec<1> __VicoTriggered;
    VlTriggerVec<2> __VactTriggered;
    VlTriggerVec<2> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vdma_top__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vdma_top___024root(Vdma_top__Syms* symsp, const char* v__name);
    ~Vdma_top___024root();
    VL_UNCOPYABLE(Vdma_top___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
