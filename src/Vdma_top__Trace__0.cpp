/*
 * Copyright (C) 2026 pdnguyen of HCMC University of Technology VNU-HCM
 *
 * demacOprx release
 * Source Code License Grant: The authors hereby grant to Licensee
 * personal permission to use and modify the Licensed Source Code
 * for the sole purpose of studying while attending the course CO2018.
 *
 * Verilated -*- C++ -*-
 * DESCRIPTION: Verilator output: Tracing implementation internals
 */
#include "verilated_vcd_c.h"
#include "Vdma_top__Syms.h"


void Vdma_top___024root__trace_chg_0_sub_0(Vdma_top___024root* vlSelf, VerilatedVcd::Buffer* bufp);

void Vdma_top___024root__trace_chg_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdma_top___024root__trace_chg_0\n"); );
    // Init
    Vdma_top___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vdma_top___024root*>(voidSelf);
    Vdma_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    // Body
    Vdma_top___024root__trace_chg_0_sub_0((&vlSymsp->TOP), bufp);
}

void Vdma_top___024root__trace_chg_0_sub_0(Vdma_top___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    if (false && vlSelf) {}  // Prevent unused
    Vdma_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdma_top___024root__trace_chg_0_sub_0\n"); );
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode + 1);
    // Body
    if (VL_UNLIKELY(vlSelf->__Vm_traceActivity[1U])) {
        bufp->chgQData(oldp+0,(vlSelf->dma_top__DOT__dma_addr),64);
        bufp->chgIData(oldp+2,(vlSelf->dma_top__DOT__dma_wdata),32);
        bufp->chgBit(oldp+3,(vlSelf->dma_top__DOT__dma_write));
        bufp->chgBit(oldp+4,(vlSelf->dma_top__DOT__dma_read));
        bufp->chgIData(oldp+5,(vlSelf->dma_top__DOT__dma_rdata),32);
        bufp->chgBit(oldp+6,(vlSelf->dma_top__DOT__dma_ready));
        bufp->chgQData(oldp+7,(vlSelf->dma_top__DOT__u_dma_rtl__DOT__src_addr),64);
        bufp->chgQData(oldp+9,(vlSelf->dma_top__DOT__u_dma_rtl__DOT__dst_addr),64);
        bufp->chgIData(oldp+11,(vlSelf->dma_top__DOT__u_dma_rtl__DOT__total_bytes),32);
        bufp->chgBit(oldp+12,(vlSelf->dma_top__DOT__u_dma_rtl__DOT__dir_memset));
        bufp->chgBit(oldp+13,(vlSelf->dma_top__DOT__u_dma_rtl__DOT__intr_en));
        bufp->chgBit(oldp+14,(vlSelf->dma_top__DOT__u_dma_rtl__DOT__last_desc));
        bufp->chgBit(oldp+15,(vlSelf->dma_top__DOT__u_dma_rtl__DOT__cross_bank));
        bufp->chgCData(oldp+16,(vlSelf->dma_top__DOT__u_dma_rtl__DOT__src_bank),8);
        bufp->chgCData(oldp+17,(vlSelf->dma_top__DOT__u_dma_rtl__DOT__dst_bank),8);
        bufp->chgIData(oldp+18,(vlSelf->dma_top__DOT__u_dma_rtl__DOT__bytes_remaining),32);
        bufp->chgBit(oldp+19,(vlSelf->dma_top__DOT__u_dma_rtl__DOT__read_next));
        bufp->chgIData(oldp+20,(vlSelf->dma_top__DOT__u_dma_rtl__DOT__read_data_reg),32);
        bufp->chgBit(oldp+21,(vlSelf->dma_top__DOT__u_dma_rtl__DOT__copy_active));
        bufp->chgBit(oldp+22,(vlSelf->dma_top__DOT__u_dma_rtl__DOT__copy_done_reg));
        bufp->chgBit(oldp+23,(vlSelf->dma_top__DOT__u_dma_rtl__DOT__error_reg));
        bufp->chgCData(oldp+24,(vlSelf->dma_top__DOT__u_dma_rtl__DOT__wait_cnt),4);
        bufp->chgBit(oldp+25,(vlSelf->dma_top__DOT__u_dma_rtl__DOT__desc_ready_reg));
        bufp->chgIData(oldp+26,(vlSelf->dma_top__DOT__unnamedblk2__DOT__rc),32);
        bufp->chgIData(oldp+27,(vlSelf->dma_top__DOT__unnamedblk2__DOT__readback),32);
    }
    bufp->chgBit(oldp+28,(vlSelf->clk));
    bufp->chgBit(oldp+29,(vlSelf->rst_n));
    bufp->chgBit(oldp+30,(vlSelf->ch_enable));
    bufp->chgBit(oldp+31,(vlSelf->ch_pause));
    bufp->chgBit(oldp+32,(vlSelf->ch_done));
    bufp->chgBit(oldp+33,(vlSelf->ch_error));
    bufp->chgIData(oldp+34,(vlSelf->ch_bytes_transferred),32);
    bufp->chgBit(oldp+35,(vlSelf->irq));
    bufp->chgBit(oldp+36,(vlSelf->desc_valid));
    bufp->chgQData(oldp+37,(vlSelf->desc_data_0),64);
    bufp->chgQData(oldp+39,(vlSelf->desc_data_1),64);
    bufp->chgQData(oldp+41,(vlSelf->desc_data_2),64);
    bufp->chgQData(oldp+43,(vlSelf->desc_data_3),64);
    bufp->chgBit(oldp+45,(vlSelf->desc_ready));
    bufp->chgCData(oldp+46,(vlSelf->state),2);
    bufp->chgBit(oldp+47,(vlSelf->dma_top__DOT__ch_done_d));
    bufp->chgBit(oldp+48,(((~ (IData)(vlSelf->dma_top__DOT__ch_done_d)) 
                           & (IData)(vlSelf->ch_done))));
    bufp->chgCData(oldp+49,(vlSelf->dma_top__DOT__u_dma_rtl__DOT__current_state),3);
    bufp->chgCData(oldp+50,(vlSelf->dma_top__DOT__u_dma_rtl__DOT__next_state),3);
    bufp->chgBit(oldp+51,(vlSelf->dma_top__DOT__u_dma_rtl__DOT__start_cond));
}

void Vdma_top___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdma_top___024root__trace_cleanup\n"); );
    // Init
    Vdma_top___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vdma_top___024root*>(voidSelf);
    Vdma_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    vlSymsp->__Vm_activity = false;
    vlSymsp->TOP.__Vm_traceActivity[0U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[1U] = 0U;
}
