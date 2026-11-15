/*
 * Copyright (C) 2026 pdnguyen of HCMC University of Technology VNU-HCM
 */

/* Caitoa release
 * Source Code License Grant: The authors hereby grant to Licensee
 * personal permission to use and modify the Licensed Source Code
 * for the sole purpose of studying while attending the course CO2018.
 */

//#ifdef MM_PAGING
/*
 * PAGING based Memory Management
 * Virtual memory module mm/mm-vm.c
 */

#include "string.h"
#include "mm64.h"
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <limits.h>

//----------------------------------------------------------------
//-----------------------<Get VM area by ID>----------------------
//----------------------------------------------------------------
struct vm_area_struct *get_vma_by_num (struct mm_struct *mm, int vmaid_target) {
    if (!mm || vmaid_target < 0) return NULL; 
    // kiểm tra rỗng hoặc target khoong hơp lệ (âm)
    struct vm_area_struct *p = mm->mmap;

    while (p) {
        if (p->vm_id == (unsigned long)vmaid_target) return p;
        p = p->vm_next;
    }

    return NULL;
}

//----------------------------------------------------------------
//-----------<Get VM area for a number of pages>------------------
//----------------------------------------------------------------
struct vm_rg_struct *get_vm_area_node_at_brk(struct pcb_t *caller, int vmaid, addr_t alignedsz)
{
    if (!caller || alignedsz == 0) return NULL;

    struct vm_area_struct *cur_vma = get_vma_by_num(caller->mm, vmaid); 
    // lấy virtual mem area với vmaid target đã cho
    if (!cur_vma) return NULL;

    const addr_t rg_start = cur_vma->sbrk;
    if (alignedsz > UINT64_MAX - rg_start) return NULL; 
    // cấp phát sẽ có nguy cơ bị tràn nên phải kiểm tra trước khi cộng

    struct vm_rg_struct *new_register = malloc(sizeof *new_register); 
    // cấp phát vùng nhớ cho node mới
    if (!new_register) return NULL;

    new_register->vmaid = vmaid;
    new_register->rg_start = rg_start;
    new_register->rg_end = rg_start + alignedsz;
    new_register->rg_next = NULL;

    return new_register;
}

//----------------------------------------------------------------
//---------------------<Check for VMA overlap>--------------------
//----------------------------------------------------------------
int validate_overlap_vm_area(struct pcb_t *caller, int vmaid,
                             addr_t vmastart, addr_t vmaend)
{
    if (!caller || vmastart >= vmaend) return -1;

    struct vm_area_struct *cur_area = get_vma_by_num(caller->mm, vmaid);
    if (!cur_area) return -1;

    struct vm_area_struct *vma = caller->mm->mmap;
    while (vma) {
        if (vma == cur_area || vma->vm_start >= vma->vm_end) { vma = vma->vm_next; continue;}
        // bỏ qua vma hiện tại nếu nó là cur_area hoặc nếu start > hoặc = end thì bỏ vì không hợp lệ

        if (vmastart < vma->vm_end && vma->vm_start < vmaend) return -1;
        // vma1 bắt đầu từ a -> b, vma2 bắt đầu từ c -> d
        // nếu a < d và c < b thì có overlap
        vma = vma->vm_next;
    }

    return 0;
}

//----------------------------------------------------------------
//---------------------<Extend a virtual memory area>-------------
//----------------------------------------------------------------
int inc_vma_limit(struct pcb_t *caller, int vmaid, addr_t inc_sz)
{
    if (!caller || inc_sz == 0) return -1;

    struct vm_area_struct *cur_vma = get_vma_by_num(caller->mm, vmaid);
    if (!cur_vma) return -1;

    const addr_t old_sbrk = cur_vma->sbrk;
    const addr_t old_end = cur_vma->vm_end;

    if (old_sbrk < cur_vma->vm_start || old_sbrk > old_end || inc_sz > UINT64_MAX - old_sbrk) return -1; 
    // kiểm tra 3 trường hợp : rỗng hoặc sbrk không hợp lệ hoặc inc_sz quá lớn gây tràn

    const addr_t new_sbrk = old_sbrk + inc_sz;
    if (new_sbrk <= old_end) {
        cur_vma->sbrk = new_sbrk;
        return 0;
    } // nếu new_sbrk < hoặc = old_end thì cần cập nhật sbrk

    const addr_t page_size = PAGING64_PAGESZ;
    if (old_end % page_size != 0) return -1; 
    // nếu old_end không chia hết cho page_size thì không hợp lệ

    const addr_t remainder = new_sbrk % page_size;
    const addr_t padding = (remainder == 0) ? 0 : page_size - remainder; 
    // cộng padding để làm tròn new_sbrk lên bội số của page_size để đảm bảo mở rộng vùng nhớ theo page_size
    if (padding > UINT64_MAX - new_sbrk) return -1; 
    // cộng padding có thể gây tràn nên ta cần kiểm tra trước

    const addr_t new_end = new_sbrk + padding;
    const addr_t page_count = (new_end - old_end) / page_size; 
    // để tính số lượng page cần cấp phát
    if (page_count > INT_MAX) return -1; // nếu một số lượng page vượt quá giới hạn của int thì không hợp lệ

    if (validate_overlap_vm_area(caller, vmaid, old_end, new_end) != 0) return -1; 
    // để kiểm tra xem thử có gặp overlap so với các vùng nhớ khác không

    struct vm_rg_struct mapped_region = {0};
    if (vm_map_ram(caller, cur_vma->vm_start, new_end, old_end, (int)page_count, &mapped_region) != 0) return -1;

    cur_vma->vm_end = new_end;
    cur_vma->sbrk = new_sbrk;

    return 0;
}

//----------------------------------------------------------------
//---------------------<Copy a RAM page to swap>------------------
//----------------------------------------------------------------
int __mm_swap_page(struct pcb_t *caller, addr_t victim_fpn, addr_t swap_fpn)
{
    if (!caller) return -1; // kiểm tra caller rỗng
    if (!caller->krnl) return -1; // sau đó kiểm tra caller->krnl rỗng

    struct krnl_t *krnl = caller->krnl;
    if (!krnl->mram || !krnl->active_mswp) return -1;

    return __swap_cp_page (krnl->mram, victim_fpn, krnl->active_mswp, swap_fpn);
}
