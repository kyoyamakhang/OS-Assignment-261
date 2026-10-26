# Copyright (C) 2026 pdnguyen of HCMC University of Technology VNU-HCM
#
# demacOprx release
# Source Code License Grant: The authors hereby grant to Licensee
# personal permission to use and modify the Licensed Source Code
# for the sole purpose of studying while attending the course CO2018.
#
# Verilated -*- Makefile -*-
# DESCRIPTION: Verilator output: Makefile for building Verilated archive or executable
#
# Execute this makefile from the object directory:
#    make -f Vdma_top.mk
default: Vdma_top

### Constants...
# Path to Verilator kit (from $VERILATOR_ROOT)
ifeq ($(shell uname -s),Darwin)
    ifeq ($(shell uname -m),arm64)
        ifneq ($(wildcard /usr/local/share/verilator/include/verilated.h),)
            VERILATOR_ROOT := /usr/local/share/verilator
        else
            VERILATOR_ROOT := /opt/homebrew/share/verilator
        endif
    else
        VERILATOR_ROOT ?= /usr/local/share/verilator
    endif
    VM_USER_LDLIBS += 
else
    VERILATOR_ROOT := /usr/share/verilator
    LDLIBS += -lpthread
endif

export VERILATOR_ROOT
LDLIBS += -lpthread

# SystemC include directory with systemc.h (from $SYSTEMC_INCLUDE)
SYSTEMC_INCLUDE ?=
# SystemC library directory with libsystemc.a (from $SYSTEMC_LIBDIR)
SYSTEMC_LIBDIR ?=

LDLIBS += -lpthread

### Switches...
# C++ code coverage  0/1 (from --prof-c)
VM_PROFC = 0
# SystemC output mode?  0/1 (from --sc)
VM_SC = 0
# Legacy or SystemC output mode?  0/1 (from --sc)
VM_SP_OR_SC = $(VM_SC)
# Deprecated
VM_PCLI = 1
DVM_VPI = 0
VM_TRACE_SAIF = 0
# Deprecated: SystemC architecture to find link library path (from $SYSTEMC_ARCH)
VM_SC_TARGET_ARCH = linux

### Vars...
# Design prefix (from --prefix)
VM_PREFIX = Vdma_top
# Module prefix (from --prefix)
VM_MODPREFIX = Vdma_top
# User CFLAGS (from -CFLAGS on Verilator command line)
VM_USER_CFLAGS = \
	-std=c++14 -O2 -DDEBUG_ENABLED=1 -I./ \

# User LDLIBS (from -LDFLAGS on Verilator command line)
VM_USER_LDLIBS = \

# User .cpp files (from .cpp's on Verilator command line)
VM_USER_CLASSES = \
	dpi_rtl \
	sysbus \
	dma_c_testbench \

# User .cpp directories (from .cpp's on Verilator command line)
VM_USER_DIR = \
	. \


### Default rules...
# Include list of all generated classes
include Vdma_top_classes.mk
# Include global rules
include $(VERILATOR_ROOT)/include/verilated.mk

### Executable rules... (from --exe)
VPATH += $(VM_USER_DIR)

%.o: %.cpp
	$(OBJCACHE) $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(OPT_FAST) -c -o $@ $<

%.o: %.c
	$(OBJCACHE) $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(OPT_FAST) -c -o $@ $<

clean:
	rm -f *.o *.a *.d *.vcd
	rm Vdma_top

### Link rules... (from --exe)
Vdma_top: $(VK_USER_OBJS) $(VK_GLOBAL_OBJS) $(VM_PREFIX)__ALL.a $(VM_HIER_LIBS)
	$(LINK) $(LDFLAGS) $^ $(LOADLIBES) $(LDLIBS) $(LIBS) $(SC_LIBS) -o $@


# Verilated -*- Makefile -*-
