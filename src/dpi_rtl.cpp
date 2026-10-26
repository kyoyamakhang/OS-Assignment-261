/*
 * Copyright (C) 2026 pdnguyen of HCMC University of Technology VNU-HCM
 *
 * demacOprx release
 * Source Code License Grant: The authors hereby grant to Licensee
 * personal permission to use and modify the Licensed Source Code
 * for the sole purpose of studying while attending the course CO2018.
 *
 * DPI RTL C++ interface to  DMA RTL
 */

#include <verilated.h>
#include <verilated_vcd_c.h>
#include "Vdma_top.h"
#include "sysbus.h"
#include "dpi_rtl.h"
#include <cstdio>
#include <cstdint>
#include <cstring>

// DMA RTL simulation structures
static Vdma_top* top = nullptr;
static VerilatedContext* context = nullptr;
static VerilatedVcdC* tracer = nullptr;

static bool is_tracing = false;
static uint64_t sim_time = 0;

/**
 * rtl_dma_init_simulation - Initialize the RTL simulation for DMA
 */
extern "C" int rtl_dma_init_simulation(void) {
    if (top) return 0;
    if (context) return 0;
    
    context = new VerilatedContext;
    const char* args[] = {};
    context->commandArgs(0, args);
    top = new Vdma_top(context, "dma_top");
    
    tracer = new VerilatedVcdC;
    context->traceEverOn(true);
    top->trace(tracer, 99);
    tracer->open("rtl_trace.vcd");
    is_tracing = true;
    sim_time = 0;
    
    printf("Initialized dma_rtl simulation\n");
    return 0;
}

/**
 * rtl_dma_cleanup_simulation - Cleanup the RTL simulation for DMA
 */
extern "C" void rtl_dma_cleanup_simulation(void) {
    if (tracer) {
        tracer->close();
        delete tracer;
        tracer = nullptr;
    }
    if (top) {
        delete top;
        top = nullptr;
    }
    if (context) {
        delete context;
        context = nullptr;
    }
    is_tracing = false;
    sim_time = 0;
    printf("Clean up dma_rtl simulation\n");
}

/**
 * rtl_dma_copy - Execute DMA copy using Verilator RTL
 * source: source memory offset
 * destination: destination memory offset
 * length: number of bytes to copy
 */
extern "C" int dpi_rtl_dma_copy(uint64_t source, uint64_t destination, uint64_t length) {
    if (!top) {
        printf("Cannot perform DMA copy: RTL simulation not initialized\n");
        return -1;
    }
    
    //printf("RTL DMA Copy: src=%llu, dst=%llu, len=%llu\n",
    //       (unsigned long long) source,
    //       (unsigned long long) destination,
    //       (unsigned long long) length);
    
    // Reset
    top->clk = 0;
    top->rst_n = 0;
    top->eval();
    top->clk ^= 1;
    top->eval();
    
    top->rst_n = 1;
    top->clk ^= 1;
    top->eval();
    top->clk ^= 1;
    top->eval();
    
    // Set descriptor
    top->desc_valid = 1;
    top->desc_data_0 = source;
    top->desc_data_1 = destination;
    top->desc_data_2 = length;
    top->desc_data_3 = 0;
    
    top->ch_enable = 1;
    top->ch_pause = 0;
    
    // Run simulation
    int cycle = 0;
    int max_cycles = 100000;
    
    while (cycle < max_cycles && !top->ch_done) {
        top->clk ^= 1;
        top->eval();
        
    //    if (cycle % 10 == 0) {
    //        printf("  Cycle %d: clk=%d, state=%d, ch_done=%d\n",
    //               cycle, (int)top->clk, (int)top->state, (int)top->ch_done);
    //    }
        
        if (is_tracing) {
            tracer->dump(sim_time);
            sim_time += 10;
        }
        
        cycle++;
    }

    // ch_done is high now. Keep clocking (2 full cycles) with ch_enable still asserted
    // dma_done_callback() on the next rising edge.
    top->clk ^= 1;
    top->eval();
    top->clk ^= 1;
    top->eval();
   
    top->desc_valid = 0;
    top->ch_enable = 0;
    top->ch_pause = 0;
    
    //printf("RTL DMA Copy: Completed in %d cycles, ch_done=%d\n", cycle, (int)top->ch_done);

    return top->ch_done ? 0 : -1;
}


/**
 * dpi_rtl_dma_is_available - Check if RTL DMA is available
 */
extern "C" int dpi_rtl_dma_is_available(void) {
    return top != nullptr;
}



