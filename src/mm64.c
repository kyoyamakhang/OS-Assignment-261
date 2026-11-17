/*
 * Copyright (C) 2026 pdnguyen of HCMC University of Technology VNU-HCM
 */

/* LamiaAtrium release
 * Source Code License Grant: The authors hereby grant to Licensee
 * personal permission to use and modify the Licensed Source Code
 * for the sole purpose of studying while attending the course CO2018.
 */

/*
 * PAGING based Memory Management
 * Memory management unit mm/mm.c
 */

#include "mm64.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <limits.h>

#if defined(MM64)

/*
 * init_pte - Initialize PTE entry
 */
int init_pte(addr_t *pte,
             int pre,    // present
             addr_t fpn,    // FPN
             int drt,    // dirty
             int swp,    // swap
             int swptyp, // swap type
             addr_t swpoff) // swap offset
{
  if (pre != 0) {
    if (swp == 0) { // Non swap ~ page online
      if (fpn == 0)
        return -1;  // Invalid setting

      /* Valid setting with FPN */
      SETBIT(*pte, PAGING_PTE_PRESENT_MASK);
      CLRBIT(*pte, PAGING_PTE_SWAPPED_MASK);
      CLRBIT(*pte, PAGING_PTE_DIRTY_MASK);

      SETVAL(*pte, fpn, PAGING_PTE_FPN_MASK, PAGING_PTE_FPN_LOBIT);
    }
    else
    { // page swapped
      SETBIT(*pte, PAGING_PTE_PRESENT_MASK);
      SETBIT(*pte, PAGING_PTE_SWAPPED_MASK);
      CLRBIT(*pte, PAGING_PTE_DIRTY_MASK);

      SETVAL(*pte, swptyp, PAGING_PTE_SWPTYP_MASK, PAGING_PTE_SWPTYP_LOBIT);
      SETVAL(*pte, swpoff, PAGING_PTE_SWPOFF_MASK, PAGING_PTE_SWPOFF_LOBIT);
    }
  }

  return 0;
}

/*
 helper function: traverse the tables
 */
static addr_t *get_pte_ptr(struct mm_struct *mm, addr_t pgn, int alloc)
{
  addr_t pgd = 0, p4d = 0, pud = 0, pmd = 0, pt = 0;
  addr_t *cur_pgd, *cur_p4d, *cur_pud, *cur_pmd, *cur_pt;

  get_pd_from_pagenum(pgn, &pgd, &p4d, &pud, &pmd, &pt);

  if (mm->pgd == NULL)
  {
    if (!alloc) return NULL;
    mm->pgd = calloc((1 << PAGING64_ADDR_PGD_SZ), sizeof(addr_t));
    if (mm->pgd == NULL) return NULL;
  }
  cur_pgd = mm->pgd;

  if (cur_pgd[pgd] == 0)
  {
    if (!alloc) return NULL;
    cur_pgd[pgd] = (addr_t) calloc((1 << PAGING64_ADDR_P4D_SZ), sizeof(addr_t));
    if (cur_pgd[pgd] == 0) return NULL;
  }
  cur_p4d = (addr_t *) cur_pgd[pgd];

  if (cur_p4d[p4d] == 0)
  {
    if (!alloc) return NULL;
    cur_p4d[p4d] = (addr_t) calloc((1 << PAGING64_ADDR_PUD_SZ), sizeof(addr_t));
    if (cur_p4d[p4d] == 0) return NULL;
  }
  cur_pud = (addr_t *) cur_p4d[p4d];

  if (cur_pud[pud] == 0)
  {
    if (!alloc) return NULL;
    cur_pud[pud] = (addr_t) calloc((1 << PAGING64_ADDR_PMD_SZ), sizeof(addr_t));
    if (cur_pud[pud] == 0) return NULL;
  }
  cur_pmd = (addr_t *) cur_pud[pud];

  if (cur_pmd[pmd] == 0)
  {
    if (!alloc) return NULL;
    cur_pmd[pmd] = (addr_t) calloc((1 << PAGING64_ADDR_PT_SZ), sizeof(addr_t));
    if (cur_pmd[pmd] == 0) return NULL;
  }
  cur_pt = (addr_t *) cur_pmd[pmd];

  return &cur_pt[pt];
}

static int validate_page_range(addr_t addr, int pgnum, addr_t *end)
{
  addr_t address_limit = (addr_t)1 << PAGING64_CPU_BUS_WIDTH;

  if (pgnum <= 0 || (addr & (PAGING64_PAGESZ - 1)) != 0 ||
      addr >= address_limit ||
      (addr_t)pgnum > (UINT64_MAX - addr) / PAGING64_PAGESZ)
    return -1;

  *end = addr + (addr_t)pgnum * PAGING64_PAGESZ;
  return *end <= address_limit ? 0 : -1;
}

static void release_frame_list(struct pcb_t *caller,
                               struct framephy_struct *frames)
{
  struct memphy_struct *mram = NULL;

  if (caller != NULL && caller->krnl != NULL)
    mram = caller->krnl->mram;

  while (frames != NULL)
  {
    struct framephy_struct *next = frames->fp_next;
    if (mram == NULL || MEMPHY_put_freefp(mram, frames->fpn) != 0)
      fprintf(stderr, "Unable to return physical frame %llu to RAM\n",
              (unsigned long long)frames->fpn);
    free(frames);
    frames = next;
  }
}

static void free_page_list(struct pgn_t *pages)
{
  while (pages != NULL)
  {
    struct pgn_t *next = pages->pg_next;
    free(pages);
    pages = next;
  }
}
//----------------------------------------------------------------
//------------<Parse address to 5 page directory level>-----------
//----------------------------------------------------------------
int get_pd_from_address(addr_t addr, addr_t *pgd, addr_t *p4d, addr_t *pud, addr_t *pmd, addr_t *pt) {
  const addr_t mask = 0x1FF; // dùng để lấy 9 bits của mỗi level

  // 64 bits thì sẽ có bit 57-63 là bit sign dựa vào bit 56
  *pgd = (addr >> PAGING64_ADDR_PGD_LOBIT) & mask;
  // lấy 9 bits của bit pgd để trích xuất trang (gồm bit 48-56)

  *p4d = (addr >> PAGING64_ADDR_P4D_LOBIT) & mask;
  // lấy 9 bits của bit p4d để trích xuất trang (gồm bit 39-47)

  *pud = (addr >> PAGING64_ADDR_PUD_LOBIT) & mask;
  // lấy 9 bits của bit pud để trích xuất trang (gồm bit 30-38)

  *pmd = (addr >> PAGING64_ADDR_PMD_LOBIT) & mask;
  // lấy 9 bits của bit pmd để trích xuất trang (gồm bit 21-29)

  *pt = (addr >> PAGING64_ADDR_PT_LOBIT) & mask;     
  // lấy 9 bits của bit pt để trích xuất trang (gồm bit 12-20)

  return 0;
}

int get_pd_from_pagenum (addr_t pgn, addr_t *pgd, addr_t *p4d, addr_t *pud, addr_t *pmd, addr_t *pt) {
  const addr_t page_base = pgn << PAGING64_ADDR_PT_SHIFT;
  // chuyển đổi page number sang địa chỉ vật lý bằng cách dịch trái 12 bit (tương đương nhân với 4096)

  return get_pd_from_address(page_base, pgd, p4d, pud, pmd, pt);
}


/*
 * pte_set_swap - Set PTE entry for swapped page
 * @pte    : target page table entry (PTE)
 * @swptyp : swap type
 * @swpoff : swap offset
 */
int pte_set_swap(struct pcb_t *caller, addr_t pgn, int swptyp, addr_t swpoff)
{
  struct krnl_t *krnl = caller->krnl;

  addr_t *pte = NULL;
	
  // dummy pte alloc to avoid runtime error
  //pte = malloc(sizeof(addr_t));
#ifdef MM64	
  /* Get value from the system */
  /* TODO Perform multi-level page mapping */
  //get_pd_from_pagenum(pgn, &pgd, &p4d, &pud, &pmd, &pt);
  //... krnl->mm->pgd
  //... krnl->mm->pt
  //pte = &krnl->mm->pt;

  pte = get_pte_ptr(krnl->mm, pgn, 1);
  if(pte == NULL) return -1;
#else
  pte = &krnl->mm->pgd[pgn];
#endif
	
  CLRBIT(*pte, PAGING_PTE_PRESENT_MASK);
  SETBIT(*pte, PAGING_PTE_SWAPPED_MASK);

  SETVAL(*pte, swptyp, PAGING_PTE_SWPTYP_MASK, PAGING_PTE_SWPTYP_LOBIT);
  SETVAL(*pte, swpoff, PAGING_PTE_SWPOFF_MASK, PAGING_PTE_SWPOFF_LOBIT);

  return 0;
}

/*
 * pte_set_fpn - Set PTE entry for on-line page
 * @pte   : target page table entry (PTE)
 * @fpn   : frame page number (FPN)
 * @caller: caller
 */
int pte_set_fpn(struct mm_struct *mm, addr_t pgn, addr_t fpn, struct pcb_t *caller)
{
  struct krnl_t *krnl = caller->krnl;

  addr_t* pte = NULL;
	
  // dummy pte alloc to avoid runtime error
  //pte = malloc(sizeof(addr_t));
#ifdef MM64	
  /* Get value from the system */
  /* TODO Perform multi-level page mapping */
  //get_pd_from_pagenum(pgn, &pgd, &p4d, &pud, &pmd, &pt);
  //... krnl->mm->pgd
  //... krnl->mm->pt
  //pte = &krnl->mm->pt;
  pte = get_pte_ptr(mm, pgn, 1);
  if(pte == NULL) return -1;
#else
  pte = &krnl->mm->pgd[pgn];
#endif

  SETBIT(*pte, PAGING_PTE_PRESENT_MASK);
  CLRBIT(*pte, PAGING_PTE_SWAPPED_MASK);

  SETVAL(*pte, fpn, PAGING_PTE_FPN_MASK, PAGING_PTE_FPN_LOBIT);

  return 0;
}


/* Get PTE page table entry
 * @caller : caller
 * @pgn    : page number
 * @caller: caller
 * @ret    : page table entry
 **/
addr_t pte_get_entry(struct mm_struct *mm, addr_t pgn, struct pcb_t *caller)
{
  struct krnl_t *krnl = caller->krnl;
	
  addr_t* pte = NULL;

  // dummy pte alloc to avoid runtime error
  //pte = malloc(sizeof(addr_t));
#ifdef MM64	
  /* Get value from the system */
  /* TODO Perform multi-level page mapping */
  //get_pd_from_pagenum(pgn, &pgd, &p4d, &pud, &pmd, &pt);
  //... krnl->mm->pgd
  //... krnl->mm->pt
  //pte = &krnl->mm->pt;
  pte = get_pte_ptr(mm, pgn, 0);
  if(pte == NULL) return 0;
#else	
  pte = &krnl->mm->pgd[pgn];
#endif

  //return (addr_t) &pte;
  return *pte;
}

/* Set PTE page table entry
 * @caller : caller
 * @pgn    : page number
 * @ret    : page table entry
 **/
int pte_set_entry(struct mm_struct *mm, addr_t pgn, uint64_t pte_val, struct pcb_t *caller)
{
  struct krnl_t *krnl = caller->krnl;
  addr_t *pte = NULL;
	
  // dummy pte alloc to avoid runtime error
  //pte = malloc(sizeof(addr_t));
#ifdef MM64	
  /* Get value from the system */
  /* TODO Perform multi-level page mapping */
  //get_pd_from_pagenum(pgn, &pgd, &p4d, &pud, &pmd, &pt);
  //... krnl->mm->pgd
  //... krnl->mm->pt
  //pte = &krnl->mm->pt;
  pte = get_pte_ptr(mm, pgn, 1);
  if(pte == NULL) return -1;

  *pte = pte_val;
#else	
  pte = pte_val;
#endif

	return 0;
}

/*
 * vmap_pgd_memset - map a range of page at aligned address
 */
int vmap_pgd_memset(struct pcb_t *caller,           // process call
                    addr_t addr,                       // start address which is aligned to pagesz
                    int pgnum)                      // num of mapping page
{
  //int pgit = 0;
  //uint64_t pattern = 0xdeadbeef;

  /* TODO memset the page table with given pattern
   */
  const uint32_t pattern = 0xdeadbeef;
  addr_t end;
  addr_t ram_frames;
  addr_t encodable_frames =
      (PAGING_PTE_FPN_MASK >> PAGING_PTE_FPN_LOBIT) + 1;
  int page;

  if (caller == NULL || caller->krnl == NULL || caller->mm == NULL ||
      caller->krnl->mram == NULL || caller->krnl->mram->storage == NULL ||
      caller->krnl->mram->maxsz <= 0 ||
      validate_page_range(addr, pgnum, &end) != 0)
    return -1;

  ram_frames = (addr_t)caller->krnl->mram->maxsz / PAGING64_PAGESZ;
  if (ram_frames > encodable_frames)
    ram_frames = encodable_frames;
  for (page = 0; page < pgnum; page++)
  {
    addr_t pgn = (addr >> PAGING64_ADDR_PT_SHIFT) + (addr_t)page;
    addr_t pte = pte_get_entry(caller->mm, pgn, caller);
    addr_t fpn;

    if (!PAGING_PAGE_PRESENT(pte) || (pte & PAGING_PTE_SWAPPED_MASK))
      return -1;

    fpn = PAGING_FPN(pte);
    if (fpn >= ram_frames)
      return -1;
  }

  for (page = 0; page < pgnum; page++)
  {
    addr_t pgn = (addr >> PAGING64_ADDR_PT_SHIFT) + (addr_t)page;
    addr_t fpn = PAGING_FPN(pte_get_entry(caller->mm, pgn, caller));
    addr_t byte;

    for (byte = 0; byte < PAGING64_PAGESZ; byte++)
    {
      BYTE value = (BYTE)((pattern >> ((byte & 3) * 8)) & 0xff);
      addr_t physical_addr = fpn * PAGING64_PAGESZ + byte;
      if (MEMPHY_write(caller->krnl->mram, physical_addr, value) != 0)
        return -1;
    }
  }

  return 0;
}

/*
 * vmap_page_range - map a range of page at aligned address
 */
addr_t vmap_page_range(struct pcb_t *caller,           // process call
                    addr_t addr,                       // start address which is aligned to pagesz // start
                    int pgnum,                      // num of mapping page
                    struct framephy_struct *frames, // list of the mapped frames
                    struct vm_rg_struct *ret_rg)    // return mapped region, the real mapped fp
{                                                   // no guarantee all given pages are mapped
//struct framephy_struct *fpit;
//int pgit = 0;
//addr_t pgn;

  /* TODO: update the rg_end and rg_start of ret_rg 
  //ret_rg->rg_end =  ....
  //ret_rg->rg_start = ...
  //ret_rg->vmaid = ...
  */

  /* TODO map range of frame to address space
   *      [addr to addr + pgnum*PAGING_PAGESZ
   *      in page table caller->krnl->mm->pgd,
   *                    caller->krnl->mm->pud...
   *                    ...
   */

  /* Tracking for later page replacement activities (if needed)
   * Enqueue new usage page */
  //enlist_pgn_node(&caller->krnl->mm->fifo_pgn, pgn64 + pgit);

  struct framephy_struct *frame = frames;
  struct pgn_t *new_pages = NULL;
  struct pgn_t *new_pages_tail = NULL;
  addr_t end;
  addr_t first_pgn;
  addr_t ram_frames;
  addr_t encodable_frames = (PAGING_PTE_FPN_MASK >> PAGING_PTE_FPN_LOBIT) + 1;
  int page;

  if (caller == NULL || caller->krnl == NULL || caller->mm == NULL ||
      caller->krnl->mram == NULL || frames == NULL || ret_rg == NULL ||
      caller->krnl->mram->maxsz <= 0 ||
      validate_page_range(addr, pgnum, &end) != 0)
  {
    release_frame_list(caller, frames);
    return -1;
  }

  first_pgn = addr >> PAGING64_ADDR_PT_SHIFT;
  ram_frames = (addr_t)caller->krnl->mram->maxsz / PAGING64_PAGESZ;
  if (ram_frames > encodable_frames)
    ram_frames = encodable_frames;

  for (page = 0; page < pgnum; page++)
  {
    addr_t *pte;
    struct pgn_t *page_node;

    if (frame == NULL || frame->fpn >= ram_frames)
      goto fail;

    pte = get_pte_ptr(caller->mm, first_pgn + (addr_t)page, 0);
    if (pte != NULL && *pte != 0)
      goto fail;

    page_node = malloc(sizeof(struct pgn_t));
    if (page_node == NULL)
      goto fail;
    page_node->pgn = first_pgn + (addr_t)page;
    page_node->pg_next = new_pages;
    new_pages = page_node;
    if (new_pages_tail == NULL)
      new_pages_tail = page_node;

    frame = frame->fp_next;
  }

  if (frame != NULL)
    goto fail;

  frame = frames;
  for (page = 0; page < pgnum; page++)
  {
    if (pte_set_fpn(caller->mm, first_pgn + (addr_t)page,
                    frame->fpn, caller) != 0)
      goto rollback;
    frame = frame->fp_next;
  }

  new_pages_tail->pg_next = caller->mm->fifo_pgn;
  caller->mm->fifo_pgn = new_pages;

  ret_rg->vmaid = 0;
  ret_rg->rg_start = addr;
  ret_rg->rg_end = end;
  ret_rg->rg_next = NULL;

  while (frames != NULL)
  {
    struct framephy_struct *next = frames->fp_next;
    free(frames);
    frames = next;
  }
  return 0;

rollback:
  while (page > 0)
  {
    addr_t *pte = get_pte_ptr(caller->mm, first_pgn + (addr_t)--page, 0);
    if (pte != NULL)
      *pte = 0;
  }
fail:
  free_page_list(new_pages);
  release_frame_list(caller, frames);
  return -1;
}

/*
 * alloc_pages_range - allocate req_pgnum of frame in ram
 * @caller    : caller
 * @req_pgnum : request page num
 * @frm_lst   : frame list
 */

addr_t alloc_pages_range(struct pcb_t *caller, int req_pgnum, struct framephy_struct **frm_lst)
{
  //addr_t fpn;
  //int pgit;
  //struct framephy_struct *newfp_str = NULL;
  //struct framephy_struct **cur = frm_lst;

  /* TODO: allocate the page 
  //caller-> ...
  //frm_lst-> ...
  */

  struct memphy_struct *mram;
  struct framephy_struct *head = NULL;
  struct framephy_struct *tail = NULL;
  addr_t max_frames;
  addr_t encodable_frames = (PAGING_PTE_FPN_MASK >> PAGING_PTE_FPN_LOBIT) + 1;
  int page;

  if (frm_lst == NULL)
    return -1;
  *frm_lst = NULL;

  if (caller == NULL || caller->krnl == NULL ||
      (mram = caller->krnl->mram) == NULL ||
      mram->storage == NULL || req_pgnum <= 0 || mram->maxsz <= 0)
    return -1;

  max_frames = (addr_t) mram->maxsz / PAGING64_PAGESZ;
  if (max_frames > encodable_frames)
    max_frames = encodable_frames;
  if ((addr_t) req_pgnum > max_frames)
    return -3000; // not enough free frame

  for (page = 0; page < req_pgnum; page++)
  {
    // TODO: allocate the page
    struct framephy_struct *new_frame = malloc(sizeof(struct framephy_struct));
    addr_t fpn;

    if (new_frame == NULL)
      goto allocation_error;

    if (MEMPHY_get_freefp(mram, &fpn) == 0)
    {
      if (fpn >= max_frames)
      {
        free(new_frame);
        if (MEMPHY_put_freefp(mram, fpn) != 0)
          fprintf(stderr, "Unable to return invalid physical frame %llu to RAM\n",
                  (unsigned long long)fpn);
        goto allocation_error;
      }

      new_frame->fpn = fpn;
      new_frame->owner = caller->mm;
      new_frame->fp_next = NULL;
      if (tail == NULL)
        head = new_frame;
      else
        tail->fp_next = new_frame;
      tail = new_frame;
    }
    else
    { // TODO: ERROR CODE of obtaining somes but not enough frames
      free(new_frame);
      goto out_of_memory;
    }
  }

  *frm_lst = head;
  return 0;

  /* End TODO */

out_of_memory:
  release_frame_list(caller, head);
  return -3000;

allocation_error:
  release_frame_list(caller, head);
  return -1;
}

/*
 * vm_map_ram - do the mapping all vm are to ram storage device
 * @caller    : caller
 * @astart    : vm area start
 * @aend      : vm area end
 * @mapstart  : start mapping point
 * @incpgnum  : number of mapped page
 * @ret_rg    : returned region
 */
addr_t vm_map_ram(struct pcb_t *caller, addr_t astart, addr_t aend, addr_t mapstart, int incpgnum, struct vm_rg_struct *ret_rg)
{
  struct framephy_struct *frm_lst = NULL;
  addr_t ret_alloc = 0;

  /*@bksysnet: author provides a feasible solution of getting frames
   *FATAL logic in here, wrong behaviour if we have not enough page
   *i.e. we request 1000 frames meanwhile our RAM has size of 3 frames
   *Don't try to perform that case in this simple work, it will result
   *in endless procedure of swap-off to get frame and we have not provide
   *duplicate control mechanism, keep it simple
   */
  ret_alloc = alloc_pages_range(caller, incpgnum, &frm_lst);

  if (ret_alloc != 0 && ret_alloc != (addr_t)-3000)
    return -1;

  /* Out of memory */
  if (ret_alloc == (addr_t)-3000)
  {
    return -1;
  }

  /* it leaves the case of memory is enough but half in ram, half in swap
   * do the swaping all to swapper to get the all in ram */
  if (vmap_page_range(caller, mapstart, incpgnum, frm_lst, ret_rg) != 0)
    return -1;

  return 0;
}

/* Swap copy content page from source frame to destination frame
 * @mpsrc  : source memphy
 * @srcfpn : source physical page number (FPN)
 * @mpdst  : destination memphy
 * @dstfpn : destination physical page number (FPN)
 **/
int __swap_cp_page(struct memphy_struct *mpsrc, addr_t srcfpn,
                   struct memphy_struct *mpdst, addr_t dstfpn)
{
  int cellidx;
  addr_t addrsrc, addrdst;
#ifdef MM64
  for (cellidx = 0; cellidx < PAGING64_PAGESZ; cellidx++)
  {
    addrsrc = srcfpn * PAGING64_PAGESZ + cellidx;
    addrdst = dstfpn * PAGING64_PAGESZ + cellidx;
#else
  for (cellidx = 0; cellidx < PAGING64_PAGESZ; cellidx++)
  {
    addrsrc = srcfpn * PAGING64_PAGESZ + cellidx;
    addrdst = dstfpn * PAGING64_PAGESZ + cellidx;
#endif

    BYTE data;
    MEMPHY_read(mpsrc, addrsrc, &data);
    MEMPHY_write(mpdst, addrdst, data);
  }

  return 0;
}

/*
 *Initialize a empty Memory Management instance
 * @mm:     self mm
 * @caller: mm owner
 */
int init_mm(struct mm_struct *mm, struct pcb_t *caller)
{
  struct vm_area_struct *vma0 = malloc(sizeof(struct vm_area_struct));

  /* TODO init page table directory */
   mm->pgd = calloc((1 << PAGING64_ADDR_PGD_SZ), sizeof(addr_t));
   mm->p4d = NULL;
   mm->pud = NULL;
   mm->pmd = NULL;
   mm->pt = NULL;
   /* lazy table creation, only creates table if it is accessed at least once,
    otherwise emtpy */
  if(mm->pgd == NULL)
  {
    return -1; /* malloc failed, return error code */
  }
  


  /* By default the owner comes with at least one vma */
  vma0->vm_id = 0;
  vma0->vm_start = 0;
  vma0->vm_end = vma0->vm_start;
  vma0->sbrk = vma0->vm_start;
  struct vm_rg_struct *first_rg = init_vm_rg(vma0->vm_start, vma0->vm_end);
  enlist_vm_rg_node(&vma0->vm_freerg_list, first_rg);

  /* TODO update VMA0 next */
  // vma0->next = ...

  /* Point vma owner backward */
  //vma0->vm_mm = mm; 

  /* TODO: update mmap */
  //mm->mmap = ...
  //mm->symrgtbl = ...
  //mm->kcpooltbl

  return 0;
}

//----------------------------------------------------------------
//--------------------<Initialize a VM region>-------------------
//----------------------------------------------------------------
struct vm_rg_struct *init_vm_rg(addr_t rg_start, addr_t rg_end) {
    struct vm_rg_struct *rgnode = malloc(sizeof *rgnode);
    if (rgnode == NULL) return NULL;

    rgnode->vmaid = 0;
    rgnode->rg_start = rg_start;
    rgnode->rg_end = rg_end;
    rgnode->rg_next = NULL;

    return rgnode;
}

int enlist_vm_rg_node(struct vm_rg_struct **rglist, struct vm_rg_struct *rgnode)
{
  rgnode->rg_next = *rglist;
  *rglist = rgnode;

  return 0;
}

int enlist_pgn_node(struct pgn_t **plist, addr_t pgn)
{
  struct pgn_t *pnode = malloc(sizeof(struct pgn_t));

  pnode->pgn = pgn;
  pnode->pg_next = *plist;
  *plist = pnode;

  return 0;
}

int print_list_fp(struct framephy_struct *ifp)
{
  struct framephy_struct *fp = ifp;

  printf("print_list_fp: ");
  if (fp == NULL) { printf("NULL list\n"); return -1;}
  printf("\n");
  while (fp != NULL)
  {
    printf("fp[" FORMAT_ADDR "]\n", fp->fpn);
    fp = fp->fp_next;
  }
  printf("\n");
  return 0;
}

int print_list_rg(struct vm_rg_struct *irg)
{
  struct vm_rg_struct *rg = irg;

  printf("print_list_rg: ");
  if (rg == NULL) { printf("NULL list\n"); return -1; }
  printf("\n");
  while (rg != NULL)
  {
    printf("rg[" FORMAT_ADDR "->"  FORMAT_ADDR "]\n", rg->rg_start, rg->rg_end);
    rg = rg->rg_next;
  }
  printf("\n");
  return 0;
}

int print_list_vma(struct vm_area_struct *ivma)
{
  struct vm_area_struct *vma = ivma;

  printf("print_list_vma: ");
  if (vma == NULL) { printf("NULL list\n"); return -1; }
  printf("\n");
  while (vma != NULL)
  {
    printf("va[" FORMAT_ADDR "->" FORMAT_ADDR "]\n", vma->vm_start, vma->vm_end);
    vma = vma->vm_next;
  }
  printf("\n");
  return 0;
}

int print_list_pgn(struct pgn_t *ip)
{
  printf("print_list_pgn: ");
  if (ip == NULL) { printf("NULL list\n"); return -1; }
  printf("\n");
  while (ip != NULL)
  {
    printf("va[" FORMAT_ADDR "]-\n", ip->pgn);
    ip = ip->pg_next;
  }
  printf("\n");
  return 0;
}

int print_pgtbl(struct pcb_t *caller, addr_t start, addr_t end)
{
//addr_t pgn = ...
//addr_t pgit = ...
//struct mm_struct *mm = ...
  addr_t pgd=0;
  addr_t p4d=0;
  addr_t pud=0;
  addr_t pmd=0;
  addr_t pt=0;

  get_pd_from_address(start, &pgd, &p4d, &pud, &pmd, &pt);

  /* TODO traverse the page map and dump the page directory entries */
  addr_t address_limit = (addr_t)1 << PAGING64_CPU_BUS_WIDTH;
  addr_t first_pgn;
  addr_t last_pgn;
  int pgd_index;

  if (caller == NULL || caller->mm == NULL)
    return -1;
  if (caller->mm->pgd == NULL)
  {
    printf("Page table is empty\n");
    return 0;
  }
  if (start >= address_limit)
    return -1;
  if (end == (addr_t)-1)
    end = address_limit - 1;
  else if (end >= address_limit)
    return -1;
  if (end < start)
    return -1;

  first_pgn = start >> PAGING64_ADDR_PT_SHIFT;
  last_pgn = end >> PAGING64_ADDR_PT_SHIFT;

  for (pgd_index = 0; pgd_index < (1 << PAGING64_ADDR_PGD_SZ); pgd_index++)
  {
    addr_t *p4d_table = (addr_t *)(uintptr_t)caller->mm->pgd[pgd_index];
    int p4d_index;

    if (p4d_table == NULL)
      continue;
    for (p4d_index = 0; p4d_index < (1 << PAGING64_ADDR_P4D_SZ); p4d_index++)
    {
      addr_t *pud_table = (addr_t *)(uintptr_t)p4d_table[p4d_index];
      int pud_index;

      if (pud_table == NULL)
        continue;
      for (pud_index = 0; pud_index < (1 << PAGING64_ADDR_PUD_SZ); pud_index++)
      {
        addr_t *pmd_table = (addr_t *)(uintptr_t)pud_table[pud_index];
        int pmd_index;

        if (pmd_table == NULL)
          continue;
        for (pmd_index = 0; pmd_index < (1 << PAGING64_ADDR_PMD_SZ); pmd_index++)
        {
          addr_t *pt_table = (addr_t *)(uintptr_t)pmd_table[pmd_index];
          int pt_index;

          if (pt_table == NULL)
            continue;
          for (pt_index = 0; pt_index < (1 << PAGING64_ADDR_PT_SZ); pt_index++)
          {
            addr_t pgn = (addr_t)pgd_index;
            addr_t pte = pt_table[pt_index];

            pgn = (pgn << PAGING64_ADDR_P4D_SZ) | (addr_t)p4d_index;
            pgn = (pgn << PAGING64_ADDR_PUD_SZ) | (addr_t)pud_index;
            pgn = (pgn << PAGING64_ADDR_PMD_SZ) | (addr_t)pmd_index;
            pgn = (pgn << PAGING64_ADDR_PT_SZ) | (addr_t)pt_index;
            if (pte == 0 || pgn < first_pgn || pgn > last_pgn)
              continue;

            printf("VA=0x%016llx PGN=0x%llx PTE=0x%016llx ",
                   (unsigned long long)(pgn << PAGING64_ADDR_PT_SHIFT),
                   (unsigned long long)pgn,
                   (unsigned long long)pte);
            if (PAGING_PAGE_PRESENT(pte) &&
                !(pte & PAGING_PTE_SWAPPED_MASK))
              printf("RAM FPN=%llu\n",
                     (unsigned long long)PAGING_FPN(pte));
            else if (pte & PAGING_PTE_SWAPPED_MASK)
              printf("SWAP type=%llu offset=%llu\n",
                     (unsigned long long)PAGING_PTE_SWPTYP(pte),
                     (unsigned long long)PAGING_PTE_SWP(pte));
            else
              printf("not present\n");
          }
        }
      }
    }
  }

  return 0;
}

#endif  //def MM64
