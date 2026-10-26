// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vdma_top__pch.h"
#include "verilated_vcd_c.h"

//============================================================
// Constructors

Vdma_top::Vdma_top(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vdma_top__Syms(contextp(), _vcname__, this)}
    , clk{vlSymsp->TOP.clk}
    , rst_n{vlSymsp->TOP.rst_n}
    , ch_enable{vlSymsp->TOP.ch_enable}
    , ch_pause{vlSymsp->TOP.ch_pause}
    , ch_done{vlSymsp->TOP.ch_done}
    , ch_error{vlSymsp->TOP.ch_error}
    , irq{vlSymsp->TOP.irq}
    , desc_valid{vlSymsp->TOP.desc_valid}
    , desc_ready{vlSymsp->TOP.desc_ready}
    , state{vlSymsp->TOP.state}
    , ch_bytes_transferred{vlSymsp->TOP.ch_bytes_transferred}
    , desc_data_0{vlSymsp->TOP.desc_data_0}
    , desc_data_1{vlSymsp->TOP.desc_data_1}
    , desc_data_2{vlSymsp->TOP.desc_data_2}
    , desc_data_3{vlSymsp->TOP.desc_data_3}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vdma_top::Vdma_top(const char* _vcname__)
    : Vdma_top(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vdma_top::~Vdma_top() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vdma_top___024root___eval_debug_assertions(Vdma_top___024root* vlSelf);
#endif  // VL_DEBUG
void Vdma_top___024root___eval_static(Vdma_top___024root* vlSelf);
void Vdma_top___024root___eval_initial(Vdma_top___024root* vlSelf);
void Vdma_top___024root___eval_settle(Vdma_top___024root* vlSelf);
void Vdma_top___024root___eval(Vdma_top___024root* vlSelf);

void Vdma_top::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vdma_top::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vdma_top___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_activity = true;
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        vlSymsp->__Vm_didInit = true;
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vdma_top___024root___eval_static(&(vlSymsp->TOP));
        Vdma_top___024root___eval_initial(&(vlSymsp->TOP));
        Vdma_top___024root___eval_settle(&(vlSymsp->TOP));
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vdma_top___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vdma_top::eventsPending() { return false; }

uint64_t Vdma_top::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "%Error: No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* Vdma_top::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vdma_top___024root___eval_final(Vdma_top___024root* vlSelf);

VL_ATTR_COLD void Vdma_top::final() {
    Vdma_top___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vdma_top::hierName() const { return vlSymsp->name(); }
const char* Vdma_top::modelName() const { return "Vdma_top"; }
unsigned Vdma_top::threads() const { return 1; }
void Vdma_top::prepareClone() const { contextp()->prepareClone(); }
void Vdma_top::atClone() const {
    contextp()->threadPoolpOnClone();
}
std::unique_ptr<VerilatedTraceConfig> Vdma_top::traceConfig() const {
    return std::unique_ptr<VerilatedTraceConfig>{new VerilatedTraceConfig{false, false, false}};
};

//============================================================
// Trace configuration

void Vdma_top___024root__trace_decl_types(VerilatedVcd* tracep);

void Vdma_top___024root__trace_init_top(Vdma_top___024root* vlSelf, VerilatedVcd* tracep);

VL_ATTR_COLD static void trace_init(void* voidSelf, VerilatedVcd* tracep, uint32_t code) {
    // Callback from tracep->open()
    Vdma_top___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vdma_top___024root*>(voidSelf);
    Vdma_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (!vlSymsp->_vm_contextp__->calcUnusedSigs()) {
        VL_FATAL_MT(__FILE__, __LINE__, __FILE__,
            "Turning on wave traces requires Verilated::traceEverOn(true) call before time 0.");
    }
    vlSymsp->__Vm_baseCode = code;
    tracep->pushPrefix(std::string{vlSymsp->name()}, VerilatedTracePrefixType::SCOPE_MODULE);
    Vdma_top___024root__trace_decl_types(tracep);
    Vdma_top___024root__trace_init_top(vlSelf, tracep);
    tracep->popPrefix();
}

VL_ATTR_COLD void Vdma_top___024root__trace_register(Vdma_top___024root* vlSelf, VerilatedVcd* tracep);

VL_ATTR_COLD void Vdma_top::trace(VerilatedVcdC* tfp, int levels, int options) {
    if (tfp->isOpen()) {
        vl_fatal(__FILE__, __LINE__, __FILE__,"'Vdma_top::trace()' shall not be called after 'VerilatedVcdC::open()'.");
    }
    if (false && levels && options) {}  // Prevent unused
    tfp->spTrace()->addModel(this);
    tfp->spTrace()->addInitCb(&trace_init, &(vlSymsp->TOP));
    Vdma_top___024root__trace_register(&(vlSymsp->TOP), tfp->spTrace());
}
