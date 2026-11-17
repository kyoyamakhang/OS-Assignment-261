# Memory Layout and Memory Management Documentation

**Project:** Simple Operating System (CO2011/CO2018 assignment source tree)  
**Scope:** Process virtual-memory layout, virtual memory areas (VMA), region allocation, page tables, physical RAM/SWAP frame management, and the interfaces connecting these components.

> **Implementation-status note:** This document describes the code present in the supplied Git ZIP. It distinguishes implemented functions from incomplete/TODO paths. It does not claim that the whole paging pipeline is already working end-to-end.

## 1. Overview

The simulator gives each process its own virtual address space while sharing system-wide physical memory devices. A process uses virtual addresses; the memory-management subsystem translates virtual pages to physical frames in RAM. When a page is not resident in RAM, the design can represent it as swapped and move page contents between RAM and a SWAP device.

The main layers in this repository are:

| Layer | Main files | Responsibility |
|---|---|---|
| Process memory metadata | `include/os-mm.h`, `include/common.h` | Defines `mm_struct`, `vm_area_struct`, `vm_rg_struct`, frame and physical-memory structures; each PCB refers to its own `mm`. |
| Virtual-memory areas and heap growth | `src/mm-vm.c` | Finds VMAs, checks overlap, computes heap growth, and calls the RAM mapping path. |
| User allocation interface | `src/libmem.c` | Implements `ALLOC`/`FREE` region bookkeeping, symbol-table lookup, free-region reuse, and invokes the memory-increment syscall when needed. |
| Page-table and mapping logic | `src/mm64.c` (64-bit build), `src/mm.c` (legacy 32-bit path) | Creates/traverses page-table levels, reads/updates PTEs, allocates/mapping pages, and copies pages between devices. |
| Physical memory and frames | `src/mm-memphy.c` | Owns byte storage, device reads/writes, and free/used physical-frame lists. |
| System initialization | `src/os.c` | Reads RAM/SWAP configuration, initializes physical-memory devices and kernel/process memory-management structures. |
| Memory syscall handlers | `src/sys_mem.c`, `src/syscall.c`, `src/syscall.tbl` | Connects memory-management operations to the kernel syscall interface. |

## 2. Per-process virtual address-space layout

Each process has a `struct pcb_t` in `include/common.h`. Under `MM_PAGING`, the PCB contains a pointer to its own `struct mm_struct *mm`. This is the key isolation boundary: processes have separate memory mappings even though they share the system's RAM and SWAP devices.

The `mm_struct` in `include/os-mm.h` contains:

- `pgd` (and, under `MM64`, the additional `p4d`, `pud`, `pmd`, and `pt` pointers): page-table hierarchy metadata.
- `mmap`: linked list of virtual-memory areas belonging to the process.
- `symrgtbl[PAGING_MAX_SYMTBL_SZ]`: fixed-size symbol/region table. A region ID identifies an allocated memory region used by the simulated program.
- `fifo_pgn`: page-number list used by the page-management/replacement code.
- `kcpooltbl`: kernel-memory cache-pool metadata.

### 2.1 Virtual memory area (`vm_area_struct`)

A VMA describes one continuous interval in a process's virtual address space. Its fields are:

| Field | Meaning |
|---|---|
| `vm_id` | Identifier of the VMA. The current allocation path uses VMA ID `0`. |
| `vm_start` | First virtual address in the VMA. |
| `vm_end` | End boundary of the reserved VMA interval. |
| `sbrk` | Current logical top of usable/allocated heap space. |
| `vm_mm` | Back-pointer to the owning memory-management structure. |
| `vm_freerg_list` | Linked list of free regions available for reuse inside this VMA. |
| `vm_next` | Next VMA in the process's VMA list. |

The interval `[vm_start, vm_end)` describes the VMA's reserved range. The current heap allocation frontier is `sbrk`; it must remain within the VMA boundary. The assignment specification describes the usable portion as the area from `vm_start` up to `sbrk`.

The linked-list design allows a process to have multiple VMAs. In the current implementation, `liballoc()` and `libfree()` call the allocation helpers with `vmaid = 0`, so the main user-allocation path currently operates on VMA 0.

### 2.2 Memory region (`vm_rg_struct`)

A memory region represents a particular allocation or free block within a VMA:

| Field | Meaning |
|---|---|
| `vmaid` | VMA that owns this region. |
| `rg_start` | Starting virtual address of the region. |
| `rg_end` | Ending virtual address of the region. |
| `rg_next` | Link to the next free region when the node is in a free-region list. |

A region is valid when `rg_start < rg_end`. The symbol table stores active region descriptors by region ID. When a region is freed, its descriptor is copied into a node in the VMA's free-region list, and the symbol-table slot is cleared.

## 3. Virtual allocation and release flow

The user-level memory library in `src/libmem.c` provides the allocation/free interface used by simulated process instructions.

### 3.1 `ALLOC`

The current `liballoc()` path is:

1. Check that the requested region/register index is within `PAGING_MAX_SYMTBL_SZ`.
2. Call `__alloc(proc, 0, rgid, size, &alloc_addr)` for VMA 0.
3. `__alloc()` validates the process, its `mm`, output pointer, and requested size.
4. It locks `mmvm_lock` while updating shared allocation metadata.
5. It obtains the region slot through `get_symrg_byid()` and locates the VMA through `get_vma_by_num()`.
6. It rejects a region slot that is already occupied.
7. It asks `get_free_vmrg_area()` for a suitable free block.
8. If no free block is available, it invokes syscall number `17` with `SYSMEM_INC_OP`, passing the VMA ID and requested size. On success, it records a new region beginning at the previous `sbrk`.
9. It stores the resulting region in the symbol table and returns its start address.

The assignment's intended design is to reuse released regions before growing the heap. When the heap must grow, the VMA limit is extended and newly required virtual pages are mapped to physical frames.

### 3.2 `FREE`

The current `libfree()` path is:

1. Validate the region ID.
2. Call `__free(proc, 0, rgid)`.
3. `__free()` validates the process memory structure, active region, VMA ID, and region bounds.
4. It allocates a free-list node and copies the region descriptor into it.
5. `enlist_vm_freerg_list()` inserts the node into the owning VMA's free-region list.
6. The symbol-table entry is reset to an empty region.

This design makes the virtual address range reusable by a later allocation. It does not, by itself, prove that the corresponding physical frames are immediately reclaimed; physical-page release is a separate page/frame-management responsibility.

## 4. VMA lookup and heap expansion

The VMA helper functions are in `src/mm-vm.c`.

### 4.1 `get_vma_by_num(mm, vmaid)`

Traverses `mm->mmap` and returns the VMA whose `vm_id` matches the requested ID. It returns `NULL` for a null memory structure, invalid negative ID, or missing VMA.

### 4.2 `get_vm_area_node_at_brk(caller, vmaid, alignedsz)`

Finds the requested VMA and creates a region descriptor beginning at the current `sbrk`. It checks for a zero size and address overflow before computing the end address.

### 4.3 `validate_overlap_vm_area(caller, vmaid, start, end)`

Rejects invalid ranges and checks the proposed interval against the other VMAs in the process. The overlap condition is:

`new_start < existing_end && existing_start < new_end`

The current VMA is skipped during this check.

### 4.4 `inc_vma_limit(caller, vmaid, inc_sz)`

This function grows the heap frontier:

1. Validate the process, requested increment, VMA, and current `sbrk`.
2. Compute `new_sbrk = old_sbrk + inc_sz`, checking overflow.
3. If the new frontier remains within the current `vm_end`, update `sbrk` only.
4. Otherwise, round the required end upward to a page-size boundary.
5. Calculate how many additional pages are required.
6. Reject overlap with another VMA.
7. Call `vm_map_ram()` to obtain physical frames and create the page mappings.
8. If mapping succeeds, update `vm_end` and `sbrk`.

The code uses `PAGING64_PAGESZ` for page alignment in this function.

## 5. Page-table layout and address translation

The 64-bit implementation is in `src/mm64.c`. The assignment specification describes a five-level page-table scheme. A virtual address is divided into indexes for:

1. Page Global Directory (PGD)
2. Page Level 4 Directory (P4D)
3. Page Upper Directory (PUD)
4. Page Middle Directory (PMD)
5. Page Table (PT)
6. Page offset

The page offset selects a byte inside the page. The five indexes select the page-table entry that stores the page's mapping state and physical frame number.

The helper `get_pte_ptr()` walks the hierarchy. If its `alloc` argument is true, missing lower-level tables are created with zero-initialized allocation; otherwise, a missing level causes lookup to return `NULL`. `pte_get_entry()` reads an entry, while `pte_set_entry()` and `pte_set_fpn()` update entries.

The PTE encodes whether a page is present or swapped, its frame number or swap metadata, and status bits such as dirty. The assignment specification's PTE description identifies the present and swapped flags, frame number, swap type/offset, and dirty bit.

**Important distinction:** the assignment document explains the target architecture, but the repository's current implementation must be checked function by function. In particular, `init_mm()` in the supplied `src/mm64.c` allocates the top-level PGD but leaves several VMA initialization/linking statements as TODO/commented code. The code shown in the ZIP therefore does not yet establish a fully initialized per-process VMA list simply by calling `init_mm()`.

## 6. System physical memory: RAM and SWAP

The assignment models physical memory as one RAM device and up to four SWAP devices. `src/os.c` reads the memory sizes from the configuration when custom memory sizing is enabled, then initializes the devices using `init_memphy()`.

The `struct memphy_struct` in `include/os-mm.h` stores:

- `storage`: byte array representing the device's contents.
- `maxsz`: device capacity in bytes.
- `rdmflg`: selects random-access or sequential-access behavior.
- `cursor`: cursor used by sequential access.
- `free_fp_list`: list of unused physical frames.
- `used_fp_list`: list of allocated physical frames.

The RAM device is the primary memory accessed by the simulated CPU. SWAP is secondary storage; page contents must be copied between SWAP and RAM before a swapped-out page can be accessed as a resident RAM page.

### 6.1 Physical frame descriptor

Each `framephy_struct` stores:

- `fpn`: physical frame number.
- `fp_next`: next frame descriptor in a free/used list.
- `owner`: reserved tracking pointer for the owning memory-management instance.

A physical address is derived from a frame number and an offset within the frame:

`physical_address = frame_number * page_size + page_offset`

### 6.2 Device initialization and frame-list operations

In `src/mm-memphy.c`:

- `init_memphy()` initializes the device fields, allocates and zeroes the byte storage, and calls `MEMPHY_format()` to create the frame list. A zero-sized device is treated as disabled.
- `MEMPHY_format()` calculates the number of frames from device size and page size, then creates the free-frame list.
- `MEMPHY_get_freefp()` removes the first descriptor from `free_fp_list`, adds it to `used_fp_list`, and returns its frame number.
- `MEMPHY_put_freefp()` searches the used list for a frame number, removes that descriptor, and returns it to the free list.
- `MEMPHY_read()` and `MEMPHY_write()` access a byte in the device, checking pointers and address bounds. They support random access and route sequential access through the cursor helpers.

The current `MEMPHY_get_freefp()` and `MEMPHY_put_freefp()` implementations manipulate linked lists directly. The inspected functions do not take an internal mutex, so callers must ensure that concurrent access is protected at an appropriate higher layer.

## 7. How the components connect

The intended allocation-to-access path is:

```text
Simulated process
      |
      v
PCB (struct pcb_t)
      |
      +----> process-owned mm_struct
                  |
                  +----> mmap: linked list of vm_area_struct
                  |              |
                  |              +----> vm_freerg_list
                  |
                  +----> symrgtbl[region_id]
                  |
                  +----> multi-level page tables (MM64)
                                  |
                                  v
                         Page Table Entry (PTE)
                                  |
                         virtual page -> frame
                                  |
                  +---------------+----------------+
                  |                                |
                  v                                v
             MEMRAM device                    MEMSWP device(s)
             storage + frames                 storage + frames
```

For a memory access, the logical sequence is:

1. Identify the process and its region/virtual address.
2. Validate the region and calculate the virtual address.
3. Split the virtual address into page number and page offset.
4. Look up the page-table entry.
5. If the page is resident, obtain its frame number.
6. If the page is swapped or absent, the page-in/replacement path must obtain a RAM frame and copy page contents as required.
7. Calculate the physical byte address from frame number and offset.
8. Read or write the byte in the RAM device.

The assignment's memory-system overview separates these responsibilities across `LIBMEM`, `MM-VM`, `MM`, and `MEMPHY`. The user library manages allocation regions; the VM module manages virtual areas; the MM layer manages mappings and page operations; and MEMPHY provides physical storage and frame lists.

## 8. Implementation status found in the supplied ZIP

The following status is based on source inspection and Git history in the archive, not on a successful full-system test run.

| Area | Evidence in repository | Assessment |
|---|---|---|
| VMA lookup and heap-growth helpers | `src/mm-vm.c`: `get_vma_by_num`, `get_vm_area_node_at_brk`, `validate_overlap_vm_area`, `inc_vma_limit` | Functions are present. Their integration depends on valid VMA initialization and successful mapping. |
| User region allocation/free | `src/libmem.c`: `__alloc`, `__free`, `liballoc`, `libfree` | Region bookkeeping and free-list insertion are present; the path invokes syscall 17 when the free list cannot satisfy an allocation. |
| Physical frame list | `src/mm-memphy.c`: `MEMPHY_format`, `MEMPHY_get_freefp`, `MEMPHY_put_freefp` | Free/used frame-list management is implemented in the inspected source. |
| Physical byte storage | `src/mm-memphy.c`: `init_memphy`, `MEMPHY_read`, `MEMPHY_write` | Device storage and byte access functions are present. |
| 64-bit page-table hierarchy | `src/mm64.c`: `get_pte_ptr`, PTE helpers | Hierarchical traversal and lazy lower-level table creation are present in the source. |
| VMA initialization | `src/mm64.c`: `init_mm` | Incomplete in the supplied source: VMA setup is allocated but list/back-pointer initialization is left commented/TODO. |
| Page-in/page-out and replacement | `src/libmem.c`: `pg_getpage`, `pg_getval`, `pg_setval` | Important operations still contain TODO/commented sections for frame acquisition, page copying, PTE updates, and physical read/write. Do not describe swapping/replacement as complete. |
| End-to-end memory path | Across `libmem`, `mm-vm`, `mm64`, `mm-memphy`, syscall code | Not proven complete by source inspection alone. It needs integrated tests. |

### 8.1 Git history relevant to the memory work

The archive contains these relevant commits/branches:

- `900910f` — “Implement VMA lookup and heap growth”
- `1052ca5` — “Update virtual memory allocation”
- `36ba12a` — “paging draft 1”
- `b087796` — “week 2: implement physical-frame list allocation and release”
- `c70d93d` — “implemented additional functions (vma)”
- `d209196` — merge commit for the paging work on `master`

The task split file assigns VMA/allocation work to Person 3 and physical memory, swap, and memory synchronization to Person 4. It assigns 64-bit paging/page-table work to Person 2. The memory-layout documentation should therefore describe the interfaces across these owners rather than claim that one person implemented the entire memory subsystem.

## 9. Remaining work and verification checklist

Before calling the memory layout and memory-management subsystem complete, the team should verify:

- [ ] `init_mm()` correctly initializes the page-table root, VMA 0, `mmap`, VMA back-pointer, free-region list, symbol table, and any required cache-pool metadata.
- [ ] Each process receives a distinct and valid `mm_struct`; kernel memory structures are initialized consistently.
- [ ] `get_free_vmrg_area()` actually reuses a suitable free region and handles splitting or retaining the remainder correctly.
- [ ] `inc_vma_limit()` maps only valid page-aligned ranges and handles partial allocation failure without leaving inconsistent metadata or leaked frames.
- [ ] `vm_map_ram()` and the page-table mapping functions agree on page numbers, frame numbers, page size, and ownership.
- [ ] `pg_getpage()` correctly handles resident, absent, and swapped pages.
- [ ] Swap-in/swap-out copies a full page, updates PTE state, and releases/retains the correct frame descriptors.
- [ ] `pg_getval()` and `pg_setval()` calculate the physical byte address and propagate `MEMPHY_read()`/`MEMPHY_write()` failures.
- [ ] `FREE` makes the virtual region reusable and the team explicitly defines when physical frames are reclaimed.
- [ ] Shared free/used frame lists and memory-device storage are protected against concurrent access by multiple simulated CPUs.
- [ ] User-mode reads/writes cannot access kernel-space addresses; cross-boundary copies go through the required kernel validation path.
- [ ] Tests cover allocation, free, reuse, heap growth, out-of-memory, invalid region IDs, page boundaries, RAM/SWAP transitions, and concurrent requests.

## 10. Build and test evidence to collect

The assignment asks the team to build the simulator and compare behavior with the supplied sample outputs. For the memory report section, save:

1. The exact configuration file used (for example, one of the `input/os_*_paging` scenarios).
2. The build command and whether it completed successfully.
3. The run command and complete output.
4. A trace showing an allocation, memory access, free, and reuse.
5. A page-table dump or equivalent evidence showing virtual-page-to-frame mapping.
6. A frame-list or memory-device trace showing frame allocation/release.
7. A RAM/SWAP test showing page contents are preserved across a swap transition, once that path is implemented.
8. Negative tests for invalid addresses, missing mappings, and exhausted memory.

Do not state that a test passed in the report until the command has actually been run and its output has been checked.

## References

- Assignment specification, Section 2.2.1, “The process memory layout” (pp. 13–14).
- Assignment specification, Section 2.2.2, “The virtual memory mapping in each process” (p. 15).
- Assignment specification, Section 2.2.3, “The system’s physical memory” (pp. 17–18).
- Assignment specification, Sections 2.2.4–2.2.5, paging, allocation/free/read/write, and memory-system integration (pp. 18–20).
- Repository source: `include/os-mm.h`, `include/common.h`, `src/mm-vm.c`, `src/libmem.c`, `src/mm64.c`, `src/mm-memphy.c`, `src/os.c`.
