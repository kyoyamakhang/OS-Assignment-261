# OS Assignment Team Task Split

## Purpose and important note

This plan divides the Operating Systems assignment into six subsystem owners over five weeks. It is based on the assignment brief and the current starter project.

The assignment's page-replacement requirements are lecturer-defined. Confirm the required policy in Week 1 before deciding how much replacement work to implement.

## Team roles and ownership

| Person | Role | Main files | Responsibilities |
|---|---|---|---|
| **1** | Scheduler | `src/queue.c`, `src/sched.c`, relevant queue/scheduler headers | Implement queue operations and MLQ process selection; preserve the specified priority slot behavior; cover concurrent queue access; test process dispatch and time slices; prepare scheduler traces and the Gantt chart. |
| **2** | 64-bit paging | `src/mm64.c`, `include/mm64.h`, relevant definitions in `include/os-mm.h` | Implement multilevel page-table allocation and traversal, address-index extraction, PTE lookup/update, and page mapping/unmapping; test valid and invalid translations; collect translation-access and page-table-storage statistics. |
| **3** | Virtual-memory areas and allocation | `src/mm-vm.c`, user-allocation paths in `src/libmem.c` | Implement VMA lookup and region/free-list handling; connect allocation growth to the memory-map path; support allocation, free, and reuse; test boundaries and allocation sequences; prepare memory-allocation evidence for the report. |
| **4** | Physical memory, swap, and memory synchronization | `src/mm-memphy.c`, `src/mm.c`, frame/swap paths in `src/libmem.c` | Manage physical frames and RAM/swap access; connect frame allocation/release with page mapping; implement the replacement policy required by the lecturer; identify and protect shared memory-management state; test concurrent memory operations. |
| **5** | System calls and user/kernel protection | `src/syscall.c`, `src/sys_mem.c`, `src/syscall.tbl`, syscall and memory-access paths | Verify syscall dispatch and argument handling; enforce PID-based kernel interactions and user/kernel separation; validate addresses and user-copy paths; test successful and rejected operations; answer syscall/protection questionnaire items. |
| **6** | DMA and end-to-end integration | `src/dma_c_testbench.cpp`, `src/dpi_rtl.cpp`, `src/sysbus.c`, DMA integration in `src/os.c` | Integrate and test the real Verilator-backed DMA engine; establish bus-address handling; implement or connect asynchronous completion/error signaling; run end-to-end builds and tests; coordinate demo preparation and final packaging. |

**Which member assigned to which Person (Subjected to change if necessary)**
**Person 1:**       Khoa Phùng
**Person 2:**       Khang
**Person 3:**       Hiệp
**Person 4:**       Nguyên
**Person 5:**       Thông
**Person 6:**       Khoa Phạm
**Integration:**    All members support **Person 6** in integrating

Everyone should review the integrated system, test their own changes, contribute their report section, and be prepared to explain their work in the demonstration. Person 6 coordinates integration and packaging but is not solely responsible for testing other people's subsystems.

## Five-week schedule

### Week 1 — Baseline, requirements, and interfaces

**Person 1 — Scheduler**
- Trace the loader-to-ready-queue-to-CPU flow.
- Write down the expected MLQ selection and time-slice behavior from the brief.
- Identify the scheduling scenarios needed to create a useful Gantt chart.

**Person 2 — 64-bit paging**
- Trace the current 64-bit address and page-table data structures.
- Propose the page-walk, PTE lookup/update, and mapping interfaces.
- Identify which code paths require kernel and process page tables.

**Person 3 — Virtual memory and allocation**
- Trace VMA lookup, heap growth, allocation, free, and region reuse.
- Identify where allocation calls into system calls and page mapping.
- Propose the interface between VMA operations and page mapping.

**Person 4 — Physical memory, swap, and synchronization**
- Trace frame allocation/release and RAM/swap access.
- List shared data structures and operations that may run concurrently.
- Ask the lecturer what page-replacement behavior is required.

**Person 5 — System calls and protection**
- Trace syscall dispatch and existing memory-related syscall operations.
- Identify where PID-based lookup and user/kernel validation must occur.
- Document expected behavior for invalid or privileged memory accesses.

**Person 6 — DMA and integration**
- Build/run the provided DMA testbench and trace the Verilator/DPI/bus path.
- Identify how DMA addresses are expected to refer to simulated memory.
- Record the initialization, completion, and error interfaces that integration needs.

**Whole team**
- Build and run the starter scenarios; record baseline behavior and failures.
- Confirm the six-person group size and page-replacement policy with the lecturer.
- Agree on function signatures, ownership boundaries, test cases, and integration rules.
- Agree how changes will be shared and how to avoid conflicting edits to common files.

**Friday checkpoint:** baseline results recorded; unresolved requirements listed; interface decisions documented; each owner has a prioritized implementation and test list.

### Week 2 — Independent foundations

**Person 1**
- Implement queue enqueue/dequeue and any required queue removal behavior.
- Implement the basic MLQ priority selection/slot state.
- Protect scheduler queue operations consistently.
- Add focused tests or repeatable scenarios for empty, single-process, and multi-process queues.

**Person 2**
- Implement 64-bit address-index extraction and page-table hierarchy creation/traversal.
- Implement basic page-table entry lookup and update.
- Add tests for valid, absent, and boundary address translations.

**Person 3**
- Implement VMA lookup and free-region list operations.
- Support allocation from an existing free region and validate requested region IDs/sizes.
- Add tests for free-region selection, exhaustion, and invalid requests.

**Person 4**
- Implement physical-frame list allocation and release.
- Verify basic RAM/frame access and device bounds.
- Identify the exact synchronization protection needed for the frame/device structures.

**Person 5**
- Verify syscall table entries, dispatch, and build wiring for the existing memory operations.
- Define and test the expected PID-based syscall interaction.
- Write a checklist for user/kernel access validation and copy operations.

**Person 6**
- Verify that the actual Verilator RTL can initialize and run in the supported testbench.
- Test DMA source/destination/length handling and identify invalid-parameter cases.
- Document how the DMA path should access the same simulated memory used by the OS.

**Friday checkpoint:** each owner has an independently testable foundation or a specific blocker. The team has agreed interfaces for page mapping, frame allocation, syscall memory operations, and DMA bus addresses.

### Week 3 — Connect subsystems

**Person 1**
- Test MLQ behavior across priorities, time slices, multiple processes, and CPUs.
- Fix process ordering, queue state, and synchronization issues found in those tests.

**Person 2**
- Connect virtual-page mapping and unmapping to the multilevel page tables.
- Verify page-table behavior for user and kernel address ranges.
- Provide the mapping interface to Persons 3 and 4.

**Person 3**
- Connect allocation growth to the memory-map syscall and page mapping.
- Connect free operations to free-region tracking and later reuse.
- Test allocation/free sequences, heap growth, and invalid region operations.

**Person 4**
- Connect frame allocation/release to page mapping and memory reads/writes.
- Implement the required swap behavior and the lecturer-specified replacement policy.
- Add locks around shared frame, swap, and memory-device operations where needed.

**Person 5**
- Implement/test syscall argument validation and PID-based process lookup.
- Verify that user processes cannot directly access kernel memory.
- Test user-to-kernel and kernel-to-user data-copy paths, including invalid addresses.

**Person 6**
- Connect DMA start/control to the OS path without making DMA a synchronous CPU copy.
- Establish the exact bus-address contract with Persons 2 and 4.
- Expose and test a completion/error outcome for DMA operations.

**Joint work (Persons 2, 3, 4, and 5)**
- Walk through one full allocation-to-access path: allocation, page mapping, frame use, syscall boundary, and memory access.
- Confirm each module handles errors consistently and does not bypass another module's ownership.

**Joint work (Persons 2, 4, and 6)**
- Verify how the DMA engine's bus address reaches simulated physical memory.
- Confirm that a process virtual address is not accidentally treated as a physical/bus address.

**Friday checkpoint:** basic integrated allocation/read/write/free works for agreed scenarios; prohibited accesses are rejected; a DMA transfer can be started and its completion or error can be observed.

### Week 4 — Full-system tests and report evidence

**Person 1**
- Run scheduling test scenarios with multiple priorities and CPUs.
- Save reproducible traces and draw the report's CPU Gantt chart.
- Explain how the observed scheduling corresponds to the MLQ policy.

**Person 2**
- Test multilevel translation over representative address ranges.
- Calculate and record page-table storage and translation-access statistics.
- Prepare the report's address-translation diagram and design explanation.

**Person 3**
- Test allocation, free, free-region reuse, heap growth, and boundary conditions.
- Capture memory allocation state/output for the report.
- Document how allocation and mapping interact.

**Person 4**
- Stress frame allocation, RAM/swap operations, and concurrent memory operations.
- Verify the required replacement behavior and synchronization.
- Record relevant memory test outputs and known limitations.

**Person 5**
- Test syscall success, malformed arguments, invalid PID, and prohibited user/kernel access.
- Complete the report section on system calls, protection, and PID-based communication.
- Ensure all questionnaire items assigned to the team have an owner and draft answer.

**Person 6**
- Test DMA using the real Verilator-backed engine through the OS-integrated path.
- Verify copied data and the completion/error behavior.
- Prepare a concise demonstration procedure and integration notes.

**Whole team**
- Run the full-system scenarios and save input files, commands, and outputs needed to reproduce report claims.
- Draft each report section and review that the results match the implementation.
- Identify remaining bugs and assign an owner and deadline for each.

**Friday checkpoint:** reproducible full-system runs; report evidence captured; each report section drafted; demo scenario identified; remaining issues prioritized.

### Week 5 — Stabilize, rehearse, and submit

**Person 1**
- Fix scheduler regressions and rerun multi-priority/multi-CPU tests.
- Finalize the Gantt chart and scheduling explanation.

**Person 2**
- Fix translation regressions and rerun paging tests.
- Finalize the address diagram, access statistics, and storage calculations.

**Person 3**
- Fix allocation/free and region-reuse regressions.
- Finalize memory allocation evidence and explanation.

**Person 4**
- Recheck frame/swap correctness, replacement-policy requirements, and locking.
- Run concurrency-focused regression scenarios and document any limitations.

**Person 5**
- Review syscall routing, PID passing, validation, and user/kernel access restrictions.
- Verify every questionnaire question has an answer and the report follows the brief.

**Person 6**
- Run the final integrated build and DMA demo with the real RTL engine.
- Confirm the documented run instructions work from a clean project state.
- Assemble the full source directory and report into the required archive.

**Whole team**
- Review the report for consistent terminology, correct outputs, and complete attribution of contributions.
- Rehearse the demonstration so each member can explain their subsystem and its tests.
- Keep the final tested source and output together; do not include unexplained build artifacts.

**Friday checkpoint:** clean final build; final regression results; complete report and questionnaire answers; demo rehearsed; submission archive named `assignment_STUDENTID.zip`.

## Interfaces and integration rules

Agree on these in Week 1 and revisit them before integration:

1. **Page mapping:** Person 2 owns page-table lookup/update and mapping interfaces. Person 3 requests virtual mappings; Person 4 provides/releases physical frames.
2. **Memory access:** define the path from virtual address validation through translation, page presence/swap handling, and physical access.
3. **User/kernel boundary:** Person 5 owns syscall validation and PID-based lookup. User-facing code must not bypass the syscall boundary or directly access kernel memory.
4. **DMA addresses:** Person 6, with Persons 2 and 4, documents whether the DMA receives a physical address, a memory-bank offset, or another bus address. Do not assume a process virtual address is directly valid for DMA.
5. **Synchronization:** each owner lists mutable shared state and its protecting lock. Coordinate before changing lock ownership or adding a second lock around the same state.
6. **Shared files:** agree before changing common headers, configuration definitions, or central initialization paths, especially `include/os-mm.h`, `include/os-cfg.h`, and `src/os.c`.
7. **Failure behavior:** agree how errors are returned or reported for invalid addresses, allocation failure, missing mappings, swap failure, and DMA failure.

## Definition of done for each task

A task is complete when its owner can provide:

- A reproducible test case for expected behavior.
- A boundary or failure case where applicable.
- The command/input and observed result.
- A brief explanation suitable for the report and demonstration.
- Confirmation that the integrated build still works after the change.

## Report and submission checklist

- [ ] Answer every question in the assignment brief.
- [ ] Include a scheduling Gantt chart and interpretation of the run.
- [ ] Show memory allocation status and explain the user/kernel syscall boundary, including PID passing.
- [ ] Show the multilevel paging address-translation scheme.
- [ ] Report memory-access and page-table-storage statistics and explain the design.
- [ ] Explain and demonstrate the required asynchronous co-processor/DMA behavior and bus addressing.
- [ ] Include reproducible test results from each major subsystem.
- [ ] Move the report into the source-code directory.
- [ ] Compress the entire source-code directory into `assignment_STUDENTID.zip`.
- [ ] Confirm the page-replacement requirements with the lecturer.
