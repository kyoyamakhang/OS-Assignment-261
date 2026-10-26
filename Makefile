# Copyright (C) 2026 pdnguyen of HCMC University of Technology VNU-HCM
#
# demacOprx release
# Source Code License Grant: The authors hereby grant to Licensee
# personal permission to use and modify the Licensed Source Code
# for the sole purpose of studying while attending the course CO2018.
#
INC = -Iinclude
LIB = -lpthread

SRC = src
OBJ = obj
INCLUDE = include

CC = gcc
CXX = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

vpath %.c $(SRC)
vpath %.cpp $(SRC)
vpath %.h $(INCLUDE)

CFLAGS =   -std=gnu11 -c $(DEBUG)
CXXFLAGS = -std=gnu++14 -c $(DEBUG)

# Verilator configuration
VERILATOR_ROOT ?= /usr/share/verilator
ifeq ($(shell uname -s),Darwin)
    ifeq ($(shell uname -m),arm64)
        CFLAGS = -Wall -c $(DEBUG)
        CXXFLAGS = -Wall -std=c++14 -c $(DEBUG)
	ifneq ($(wildcard /usr/local/share/verilator/include/verilated.h),)
            VERILATOR_ROOT := /usr/local/share/verilator
	else
            VERILATOR_ROOT := /opt/homebrew/share/verilator
        endif
    else
        VERILATOR_ROOT ?= /usr/local/share/verilator
    endif
endif
export VERILATOR_ROOT

MAKE = $(CC) $(INC)
CXX_MAKE = $(CXX) -iquote include -I$(VERILATOR_ROOT)/include -I$(VERILATOR_ROOT)/include/vltstd

# Object files needed by modules
MEM_OBJ = $(addprefix $(OBJ)/, paging.o mem.o cpu.o loader.o)
SYSCALL_OBJ = $(addprefix $(OBJ)/, syscall.o  sys_mem.o sys_listsyscall.o)
OS_OBJ = $(addprefix $(OBJ)/, cpu.o mem.o loader.o queue.o os.o sched.o timer.o mm-vm.o mm64.o mm.o mm-memphy.o libstd.o libmem.o)
OS_OBJ += $(SYSCALL_OBJ)

# VDMA objects (from Verilator)
VDMA_CLASSES_FAST = Vdma_top Vdma_top___024root__DepSet_had36784a__0 Vdma_top___024root__DepSet_hbdce0907__0
VDMA_CLASSES_SLOW = Vdma_top___024root__Slow Vdma_top___024root__DepSet_had36784a__0__Slow Vdma_top___024root__DepSet_hbdce0907__0__Slow Vdma_top___024unit__Slow Vdma_top___024unit__DepSet_hf68f5ab9__0__Slow
VDMA_SUPPORT_FAST = Vdma_top__Dpi Vdma_top__Trace__0
VDMA_SUPPORT_SLOW = Vdma_top__Syms Vdma_top__Trace__0__Slow Vdma_top__TraceDecls__0__Slow
VDMA_GLOBAL_FAST = verilated verilated_dpi verilated_vcd_c verilated_threads

VDMA_OBJ_FAST = $(addprefix $(OBJ)/, $(addsuffix .o, $(VDMA_CLASSES_FAST) $(VDMA_SUPPORT_FAST) $(VDMA_GLOBAL_FAST)))
VDMA_OBJ_SLOW = $(addprefix $(OBJ)/, $(addsuffix .o, $(VDMA_CLASSES_SLOW) $(VDMA_SUPPORT_SLOW)))

# User C++ classes
VDMA_USER_CLASSES = dpi_rtl sysbus dma_c_testbench
VDMA_USER_OBJ = $(addprefix $(OBJ)/, $(addsuffix .o, $(VDMA_USER_CLASSES)))

# For OS target: dma_c_testbench compiled with DMA_MAIN=0 (default)
VDMA_USER_OBJ_OS = $(OBJ)/dpi_rtl.o $(OBJ)/sysbus.o $(OBJ)/dma_c_testbench.o
# For DMA target: dma_c_testbench compiled with DMA_MAIN=1
VDMA_USER_OBJ_DMA = $(OBJ)/dpi_rtl.o $(OBJ)/sysbus.o $(OBJ)/dma_c_testbench_dma.o

VDMA_OBJ_OS = $(VDMA_OBJ_FAST) $(VDMA_OBJ_SLOW) $(VDMA_USER_OBJ_OS)
VDMA_OBJ_DMA = $(VDMA_OBJ_FAST) $(VDMA_OBJ_SLOW) $(VDMA_USER_OBJ_DMA)

OS_OBJ += $(VDMA_OBJ_OS)

SCHED_OBJ = $(addprefix $(OBJ)/, cpu.o loader.o)
HEADER = $(wildcard $(INCLUDE)/*.h)
  
all: os
#mem sched os

# Just compile memory management modules
mem: $(MEM_OBJ)
	$(MAKE) $(LFLAGS) $(MEM_OBJ) -o mem $(LIB)

# Just compile scheduler
sched: $(SCHED_OBJ)
	$(MAKE) $(LFLAGS) $(MEM_OBJ) -o sched $(LIB)

# Compile DMA testbench with C 
# define DMA_MAIN=1 in src/dma_c_testbench.cpp to enable main()
dma: $(OBJ) $(VDMA_OBJ_FAST) $(VDMA_OBJ_SLOW) $(OBJ)/dpi_rtl.o $(OBJ)/sysbus.o $(OBJ)/dma_c_testbench_dma.o
	$(CXX) $(LFLAGS) $(VDMA_OBJ_FAST) $(VDMA_OBJ_SLOW) $(OBJ)/dpi_rtl.o $(OBJ)/sysbus.o $(OBJ)/dma_c_testbench_dma.o -o dma_testbench $(LIB)

# Compile dma_c_testbench with DMA_MAIN=1 for standalone testbench
$(OBJ)/dma_c_testbench_dma.o: src/dma_c_testbench.cpp ${HEADER} $(OBJ)
	$(CXX_MAKE) $(CXXFLAGS) -DDEBUG_ENABLED=1 -DDMA_MAIN=1 $< -o $@

# Compile syscall
syscalltbl.lst: $(SRC)/syscall.tbl
	@echo $(OS_OBJ)
	chmod +x $(SRC)/syscalltbl.sh
	$(SRC)/syscalltbl.sh $< $(SRC)/$@
#	mv $(OBJ)/syscalltbl.lst $(INCLUDE)/

# Compile the whole OS simulation
os: $(OBJ) syscalltbl.lst $(OS_OBJ)
	$(CXX) $(LFLAGS) $(OS_OBJ) -o os $(LIB) -lpthread

$(OBJ)/%.o: %.c ${HEADER} $(OBJ)
	$(MAKE) $(CFLAGS) $< -o $@

$(OBJ)/%.o: %.cpp ${HEADER} $(OBJ)
	$(CXX_MAKE) $(CXXFLAGS) -DDEBUG_ENABLED=1 $< -o $@

# Compile dma_c_testbench for OS target with DMA_MAIN=0 (library mode)
$(OBJ)/dma_c_testbench.o: src/dma_c_testbench.cpp ${HEADER} $(OBJ)
	$(CXX_MAKE) $(CXXFLAGS) -DDEBUG_ENABLED=1 -DDMA_MAIN=0 $< -o $@

# Verilated
$(OBJ)/verilated.o: $(VERILATOR_ROOT)/include/verilated.cpp
	$(CXX_MAKE) $(CXXFLAGS) -DDEBUG_ENABLED=1 -I$(VERILATOR_ROOT)/include $< -o $@

# Verilated global objects (from verilated.mk)
$(OBJ)/verilated_%.o: $(VERILATOR_ROOT)/include/verilated_%.cpp
	$(CXX_MAKE) $(CXXFLAGS) -DDEBUG_ENABLED=1 -I$(VERILATOR_ROOT)/include $< -o $@

# Prepare objectives container
$(OBJ):
	mkdir -p $(OBJ)

clean:
	rm -f $(SRC)/*.lst
	rm -f $(OBJ)/*.o os sched mem pdg dma_testbench *.vcd
	rm -rf $(OBJ)
