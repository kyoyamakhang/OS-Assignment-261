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
#include "dma.h"
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <cstdbool>
#include <pthread.h>

// Generated DPI functions from RTL
#include <verilated.h>
#include <verilated_vcd_c.h>
#include "Vdma_top.h"
#include "Vdma_top__Dpi.h"  

extern "C" {
#include "common.h"
#include "os-mm.h"
#include "mm.h"
#ifdef MM64
#include "mm64.h"
#endif
}

// RTL Direct Test - Drive Verilator RTL directly
extern "C" int dpi_rtl_dma_copy(uint64_t src_offset, uint64_t dst_offset, uint64_t length);
extern "C" int dpi_rtl_dma_is_available(void);

// Asynchronous DMA request queue for non-blocking CPU offload
#define DMA_QUEUE_MAX 32

struct dma_req_t {
    struct pcb_t *caller;
    uint64_t source;
    uint64_t destination;
    uint64_t length;
};

static pthread_mutex_t dma_lock = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t dma_req_cond = PTHREAD_COND_INITIALIZER;
static pthread_cond_t dma_done_cond = PTHREAD_COND_INITIALIZER;

static struct dma_req_t g_dma_queue[DMA_QUEUE_MAX];
static int g_dma_head = 0;
static int g_dma_tail = 0;
static int g_dma_count = 0;
static int g_dma_worker_active = 0;
static int g_dma_worker_stop = 0;

/*
 * translate_vaddr_to_paddr - Translate process virtual address to physical RAM bus offset
 */
static int translate_vaddr_to_paddr(struct pcb_t *caller, uint64_t vaddr, uint64_t *paddr) {
    if (paddr == NULL) {
        return -1;
    }

#if DMA_MAIN == 0
    if (caller != NULL) {
#ifdef MM64
        uint64_t page_sz = PAGING64_PAGESZ;
#else
        uint64_t page_sz = PAGING_PAGESZ;
#endif
        addr_t pgn = (addr_t)(vaddr / page_sz);
        uint64_t page_off = vaddr % page_sz;
        addr_t pte = 0;

        /* Look up PTE in process user page table first, then kernel page table */
        if (caller->mm != NULL && caller->mm->pgd != NULL) {
            pte = pte_get_entry(caller->mm, pgn, caller);
        }
        if (pte == 0 && caller->krnl != NULL &&
            caller->krnl->mm != NULL && caller->krnl->mm->pgd != NULL) {
            pte = pte_get_entry(caller->krnl->mm, pgn, caller);
        }

        if (pte != 0) {
            if (!PAGING_PAGE_PRESENT(pte) || (pte & PAGING_PTE_SWAPPED_MASK)) {
                return -1;
            }
            addr_t fpn = PAGING_FPN(pte);
            *paddr = (uint64_t)fpn * page_sz + page_off;
            return 0;
        }

        /* Reject unmapped virtual address when process VMA is active */
        if ((caller->mm != NULL && caller->mm->mmap != NULL && caller->mm->mmap->sbrk > 0) ||
            (caller->krnl != NULL && caller->krnl->mm != NULL &&
             caller->krnl->mm->mmap != NULL && caller->krnl->mm->mmap->sbrk > 0)) {
            return -1;
        }
    }
#else
    (void)caller;
#endif

    *paddr = vaddr;
    return 0;
}

/*
 * dpi_dma_copy - perform DMA copy via DPI
 * src_offset: source memory address/offset
 * dst_offset: destination memory address/offset
 * length: number of bytes to copy
 */
int dpi_dma_copy(struct pcb_t *caller, uint64_t src_offset, uint64_t dst_offset, uint64_t length) {
    void *src = NULL;
    void *dst = NULL;
    struct krnl_t *krnl = (caller != NULL) ? caller->krnl : NULL;
    uint64_t first_src_paddr = src_offset;
    uint64_t first_dst_paddr = dst_offset;

    if (length == 0) {
        printf("dpi_dma_copy: invalid length 0\n");
        return -1;
    }

    if (memory_bank_is_available()) {
        printf("dma_testbench modeo with dpi_dma_copy from memory bank\n");
        size_t bank_sz = memory_bank_get_size();
        if (src_offset >= bank_sz || dst_offset >= bank_sz ||
            length > bank_sz - src_offset || length > bank_sz - dst_offset) {
            printf("dpi_dma_copy: address out of memory bank range\n");
            return -1;
        }
        src = memory_bank_get_ptr(src_offset);
        dst = memory_bank_get_ptr(dst_offset);
    } else {
        /*
         * Map system OS physical memory address (krnl->mram) via page tables
         */
        if (krnl == NULL || krnl->mram == NULL ||
            krnl->mram->storage == NULL || krnl->mram->maxsz <= 0) {
            printf("dpi_dma_copy: OS physical memory (mram) is not initialized\n");
            return -1;
        }

        size_t mram_sz = (size_t)krnl->mram->maxsz;
        if (translate_vaddr_to_paddr(caller, src_offset, &first_src_paddr) != 0 ||
            translate_vaddr_to_paddr(caller, dst_offset, &first_dst_paddr) != 0) {
            printf("dpi_dma_copy: failed to translate virtual address to physical bus address\n");
            return -1;
        }

        if (first_src_paddr >= mram_sz || first_dst_paddr >= mram_sz) {
            printf("dpi_dma_copy: physical address out of OS mram range\n");
            return -1;
        }

        printf("dma_testbench modeo with OS memory address\n");
        memory_bank_set_os_mem(krnl->mram->storage, mram_sz);
        src = krnl->mram->storage + first_src_paddr;
        dst = krnl->mram->storage + first_dst_paddr;
    }

    if (src == NULL || dst == NULL) {
        return -1;
    }

    printf("dpi_dma_copy: src=%llu, dst=%llu, len=%llu\n", 
		    (unsigned long long) src_offset, 
		    (unsigned long long) dst_offset,
		    (unsigned long long) length);

    /* Only initialize synthetic test pattern in standalone testbench mode */
    if (memory_bank_is_available()) {
        uint8_t* psrc = (uint8_t*)src;
        uint64_t pattern_length = (length <= 255) ? length : 255;
        
        for (uint64_t i = 0; i < length; i++) {
            // Pattern cycles through 0x01 to min(length, 255)
            psrc[i] = (uint8_t)((i % pattern_length) + 1);
        }
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
    
    int result = 0;
    if (memory_bank_is_available()) {
        // Standalone mode: contiguous offset in memory bank
        result = dpi_rtl_dma_copy(src_offset, dst_offset, length);
    } else {
        // OS mode: split transfer across page boundaries so each chunk is physically contiguous
#ifdef MM64
        uint64_t page_sz = PAGING64_PAGESZ;
#else
        uint64_t page_sz = PAGING_PAGESZ;
#endif
        size_t mram_sz = (size_t)krnl->mram->maxsz;
        uint64_t cur_src_vaddr = src_offset;
        uint64_t cur_dst_vaddr = dst_offset;
        uint64_t remaining = length;

        while (remaining > 0) {
            uint64_t src_page_rem = page_sz - (cur_src_vaddr % page_sz);
            uint64_t dst_page_rem = page_sz - (cur_dst_vaddr % page_sz);
            uint64_t chunk_len = remaining;
            if (chunk_len > src_page_rem) chunk_len = src_page_rem;
            if (chunk_len > dst_page_rem) chunk_len = dst_page_rem;

            uint64_t chunk_src_paddr = 0;
            uint64_t chunk_dst_paddr = 0;
            if (translate_vaddr_to_paddr(caller, cur_src_vaddr, &chunk_src_paddr) != 0 ||
                translate_vaddr_to_paddr(caller, cur_dst_vaddr, &chunk_dst_paddr) != 0) {
                result = -1;
                break;
            }

            if (chunk_src_paddr >= mram_sz || chunk_dst_paddr >= mram_sz ||
                chunk_len > mram_sz - chunk_src_paddr || chunk_len > mram_sz - chunk_dst_paddr) {
                result = -1;
                break;
            }

            if (dpi_rtl_dma_copy(chunk_src_paddr, chunk_dst_paddr, chunk_len) != 0) {
                result = -1;
                break;
            }

            cur_src_vaddr += chunk_len;
            cur_dst_vaddr += chunk_len;
            remaining -= chunk_len;
        }
    }
    
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
 * dma_worker_loop - Asynchronous co-processor worker loop
 */
extern "C" void dma_worker_loop(void) {
    pthread_mutex_lock(&dma_lock);
    g_dma_worker_active = 1;
    g_dma_worker_stop = 0;

    while (1) {
        while (g_dma_count == 0 && !g_dma_worker_stop) {
            pthread_cond_wait(&dma_req_cond, &dma_lock);
        }

        if (g_dma_count == 0 && g_dma_worker_stop) {
            break;
        }

        /* Dequeue next DMA request */
        struct dma_req_t req = g_dma_queue[g_dma_head];
        g_dma_head = (g_dma_head + 1) % DMA_QUEUE_MAX;
        g_dma_count--;
        pthread_cond_signal(&dma_done_cond);
        pthread_mutex_unlock(&dma_lock);

        /* Execute DMA transfer asynchronously on the co_processor thread */
        int err = dpi_dma_copy(req.caller, req.source, req.destination, req.length);
        if (err == 0 && !dma_is_done()) {
            dma_done_callback();
        }

        pthread_mutex_lock(&dma_lock);
    }

    g_dma_worker_active = 0;
    pthread_mutex_unlock(&dma_lock);
}

/*
 * dma_stop_worker - Stop asynchronous co-processor worker loop
 */
extern "C" void dma_stop_worker(void) {
    pthread_mutex_lock(&dma_lock);
    g_dma_worker_stop = 1;
    pthread_cond_signal(&dma_req_cond);
    pthread_mutex_unlock(&dma_lock);
}

/*
 * do_dma - perform DMA function
 * source: source memory
 * destination: destination memory
 * length: number of bytes to copy
 */
extern "C" int do_dma(struct pcb_t *caller,uint64_t source, uint64_t destination, uint64_t length) {
    
    int test_errors = 0;

    if (length == 0) {
        return -1;
    }

    pthread_mutex_lock(&dma_lock);
    if (g_dma_worker_active) {
        /* Wait only if the hardware request queue is completely full */
        while (g_dma_count >= DMA_QUEUE_MAX && !g_dma_worker_stop) {
            pthread_cond_wait(&dma_done_cond, &dma_lock);
        }

        /* Enqueue DMA descriptor and return immediately (Asynchronous non-blocking) */
        g_dma_queue[g_dma_tail].caller = caller;
        g_dma_queue[g_dma_tail].source = source;
        g_dma_queue[g_dma_tail].destination = destination;
        g_dma_queue[g_dma_tail].length = length;
        g_dma_tail = (g_dma_tail + 1) % DMA_QUEUE_MAX;
        g_dma_count++;

        pthread_cond_signal(&dma_req_cond);
        pthread_mutex_unlock(&dma_lock);
        return 0;
    }
    pthread_mutex_unlock(&dma_lock);

    /* Standalone testbench mode: perform DMA copy directly */
    test_errors += dpi_dma_copy(caller, source, destination, length);
    if (test_errors == 0 && !dma_is_done()) {
        dma_done_callback();
    }

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
