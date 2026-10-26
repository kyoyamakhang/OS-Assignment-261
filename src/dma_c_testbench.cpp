/*
 * Copyright (C) 2026 pdnguyen of HCMC University of Technology VNU-HCM
 *
 * demacOprx release
 * Source Code License Grant: The authors hereby grant to Licensee
 * personal permission to use and modify the Licensed Source Code
 * for the sole purpose of studying while attending the course CO2018.
 *
 * DMA C Testbench 
 */

/**
 * Build modes:
 *   DMA_MAIN=1 - Build as standalone executable with main()
 *   DMA_MAIN=0 - Build as library module with do_dma()
 */
   
#ifndef DMA_MAIN
#define DMA_MAIN 0
#endif

#include "sysbus.h"
#include "dpi_rtl.h"
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <cstdbool>
#include <thread>
#include <atomic>

// Generated DPI functions from RTL
#include <verilated.h>
#include <verilated_vcd_c.h>
#include "Vdma_top.h"
#include "Vdma_top__Dpi.h"  

#if DMA_MAIN == 1
extern "C" {
#include "common.h"
#include "os-mm.h"
}
#endif

// RTL Direct Test - Drive Verilator RTL directly
extern "C" int dpi_rtl_dma_copy(uint64_t src_offset, uint64_t dst_offset, uint64_t length);
extern "C" int dpi_rtl_dma_is_available(void);

/*
 * dpi_dma_copy - perform DMA copy via DPI
 * src_offset: source memory offset
 * dst_offset: destination memory offset
 * length: number of bytes to copy
 */
int dpi_dma_copy(struct pcb_t *caller, uint64_t src_offset, uint64_t dst_offset, uint64_t length) {
    void *src = NULL;
    void *dst = NULL;
    //struct krnl_t *krnl = caller->krnl;

    if (memory_bank_is_available()) {
        printf("dma_testbench modeo with dpi_dma_copy from memory bank\n");
        src = memory_bank_get_ptr(src_offset);
        dst = memory_bank_get_ptr(dst_offset);
    } else {
        /*
         * TODO: map system OS memory address
         */
        //printf("dma_testbench modeo with OS memory address\n");
        //src =  krnl->...
        //dst =  krnl->...
    }

    printf("dpi_dma_copy: src=%llu, dst=%llu, len=%llu\n", 
		    (unsigned long long) src_offset, 
		    (unsigned long long) dst_offset,
		    (unsigned long long) length);

    uint8_t* psrc = (uint8_t*)src;
    uint64_t pattern_length = (length <= 255) ? length : 255;
    
    for (uint64_t i = 0; i < length; i++) {
        // Pattern cycles through 0x01 to min(length, 255)
        psrc[i] = (uint8_t)((i % pattern_length) + 1);
    }

    printf("Before copy:\n");
    printf("  src[0] = 0x%02x, src[1] = 0x%02x\n"
           "  src[2] = 0x%02x, src[3] = 0x%02x\n"
           "  src[4] = 0x%02x, src[5] = 0x%02x\n"
           "  src[6] = 0x%02x, src[7] = 0x%02x\n",
           ((uint8_t*)src)[0], ((uint8_t*)src)[1],
           ((uint8_t*)src)[2], ((uint8_t*)src)[3],
           ((uint8_t*)src)[4], ((uint8_t*)src)[5],
           ((uint8_t*)src)[6], ((uint8_t*)src)[7]);
    printf("  dst[0] = 0x%02x, dst[1] = 0x%02x\n"
           "  dst[2] = 0x%02x, dst[3] = 0x%02x\n"
           "  dst[4] = 0x%02x, dst[5] = 0x%02x\n"
           "  dst[6] = 0x%02x, dst[7] = 0x%02x\n",
           ((uint8_t*)dst)[0], ((uint8_t*)dst)[1],
           ((uint8_t*)dst)[2], ((uint8_t*)dst)[3],
           ((uint8_t*)dst)[4], ((uint8_t*)dst)[5],
           ((uint8_t*)dst)[6], ((uint8_t*)dst)[7]);

    printf("\nCalling RTL DMA...\n");
    
    // Call the RTL DMA function directly with provided parameters
    int result = dpi_rtl_dma_copy(src_offset, dst_offset, length);
    
    printf("\nAfter copy:\n");
    printf("  src[0] = 0x%02x, src[1] = 0x%02x\n"
           "  src[2] = 0x%02x, src[3] = 0x%02x\n"
           "  src[4] = 0x%02x, src[5] = 0x%02x\n"
           "  src[6] = 0x%02x, src[7] = 0x%02x\n",
           ((uint8_t*)src)[0], ((uint8_t*)src)[1],
           ((uint8_t*)src)[2], ((uint8_t*)src)[3],
           ((uint8_t*)src)[4], ((uint8_t*)src)[5],
           ((uint8_t*)src)[6], ((uint8_t*)src)[7]);
    printf("  dst[0] = 0x%02x, dst[1] = 0x%02x\n"
           "  dst[2] = 0x%02x, dst[3] = 0x%02x\n"
           "  dst[4] = 0x%02x, dst[5] = 0x%02x\n"
           "  dst[6] = 0x%02x, dst[7] = 0x%02x\n",
           ((uint8_t*)dst)[0], ((uint8_t*)dst)[1],
           ((uint8_t*)dst)[2], ((uint8_t*)dst)[3],
           ((uint8_t*)dst)[4], ((uint8_t*)dst)[5],
           ((uint8_t*)dst)[6], ((uint8_t*)dst)[7]);
    
    return result;
}

/*
 * do_dma - perform DMA function
 * source: source memory
 * destination: destination memory
 * length: number of bytes to copy
 */
extern "C" int do_dma(struct pcb_t *caller,uint64_t source, uint64_t destination, uint64_t length) {
    
    int test_errors = 0;

    /* Perform DMA copy using DPI with provided caller and parameters */
    test_errors += dpi_dma_copy(caller, source, destination, length);

    /*
     * TODO: This asynchronous implementation of DMA
     *        DMA completion callback is not yet implemented in this testbench
     */
    // Install callback handler
    //dma_done_callback();  // Call the callback to signal DMA completion

    return test_errors;
}

#if DMA_MAIN == 1
/* main function for independent standalone dma_testbench build
 * [Usage]: ./dma_testbench [source_offset] [destination_offset] [length]
 * source: source memory offset
 * destination: destination memory offset
 * length: number of bytes to copy
 */
int main(int argc, char** argv) {
    // Default test parameters
    uint64_t source = 0x1000;
    uint64_t destination = 0x2000;
    uint64_t length = 512;

    /*
     *  Only accept command line arguments if provided
     *  [Usage]: ./dma_testbench [source_offset] [destination_offset] [length]
     */
    if (argc >= 4) {
        source = strtoull(argv[1], NULL, 0);
        destination = strtoull(argv[2], NULL, 0);
        length = strtoull(argv[3], NULL, 0);
    }
    
    printf("Running dma_testbench source=0x%llx, destination=0x%llx, length=%llu\n",
           (unsigned long long)source, (unsigned long long)destination, (unsigned long long)length);

    /*
     * Initialize the system memory bank
     * This is necessary to independent standalone dma_testbench build .
     */
    memory_bank_init(1024 * 1024);

    /* Initialize the internal Verilator RTL simulation
     * This is necessary to ensure that the RTL simulation is ready for DPI calls.
     */
    if (rtl_dma_init_simulation() != 0) {
        printf("Cannot initialize RTL simulation\n");
        return 1;
    }

    /*
    * Create process control block for the caller
    * Properly initialize all required fields
    */
    struct pcb_t *caller = (struct pcb_t *)calloc(1, sizeof(struct pcb_t));
    caller->krnl = (struct krnl_t *)calloc(1, sizeof(struct krnl_t));
    caller->krnl->mm = (struct mm_struct *)calloc(1, sizeof(struct mm_struct));
    caller->krnl->mram = (struct memphy_struct *)calloc(1, sizeof(struct memphy_struct));
    caller->krnl->active_mswp = (struct memphy_struct *)calloc(1, sizeof(struct memphy_struct));
    caller->mm = caller->krnl->mm;
    caller->pid = 0;  // Set a default PID

    int result = do_dma(caller, source, destination, length);

    // Cleanup
    free(caller->krnl->active_mswp);
    free(caller->krnl->mram);
    free(caller->krnl->mm);
    free(caller->krnl);
    free(caller);

    return result;
}
#endif
