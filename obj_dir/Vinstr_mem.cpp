// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vinstr_mem.h"
#include "Vinstr_mem__Syms.h"
#include "verilated_vcd_c.h"

//============================================================
// Constructors

Vinstr_mem::Vinstr_mem(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vinstr_mem__Syms(contextp(), _vcname__, this)}
    , addr{vlSymsp->TOP.addr}
    , instr{vlSymsp->TOP.instr}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vinstr_mem::Vinstr_mem(const char* _vcname__)
    : Vinstr_mem(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vinstr_mem::~Vinstr_mem() {
    delete vlSymsp;
}

//============================================================
// Evaluation loop

void Vinstr_mem___024root___eval_initial(Vinstr_mem___024root* vlSelf);
void Vinstr_mem___024root___eval_settle(Vinstr_mem___024root* vlSelf);
void Vinstr_mem___024root___eval(Vinstr_mem___024root* vlSelf);
#ifdef VL_DEBUG
void Vinstr_mem___024root___eval_debug_assertions(Vinstr_mem___024root* vlSelf);
#endif  // VL_DEBUG
void Vinstr_mem___024root___final(Vinstr_mem___024root* vlSelf);

static void _eval_initial_loop(Vinstr_mem__Syms* __restrict vlSymsp) {
    vlSymsp->__Vm_didInit = true;
    Vinstr_mem___024root___eval_initial(&(vlSymsp->TOP));
    // Evaluate till stable
    vlSymsp->__Vm_activity = true;
    do {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial loop\n"););
        Vinstr_mem___024root___eval_settle(&(vlSymsp->TOP));
        Vinstr_mem___024root___eval(&(vlSymsp->TOP));
    } while (0);
}

void Vinstr_mem::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vinstr_mem::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vinstr_mem___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    // Initialize
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) _eval_initial_loop(vlSymsp);
    // Evaluate till stable
    vlSymsp->__Vm_activity = true;
    do {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Clock loop\n"););
        Vinstr_mem___024root___eval(&(vlSymsp->TOP));
    } while (0);
    // Evaluate cleanup
}

//============================================================
// Utilities

const char* Vinstr_mem::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

VL_ATTR_COLD void Vinstr_mem::final() {
    Vinstr_mem___024root___final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vinstr_mem::hierName() const { return vlSymsp->name(); }
const char* Vinstr_mem::modelName() const { return "Vinstr_mem"; }
unsigned Vinstr_mem::threads() const { return 1; }
std::unique_ptr<VerilatedTraceConfig> Vinstr_mem::traceConfig() const {
    return std::unique_ptr<VerilatedTraceConfig>{new VerilatedTraceConfig{false, false, false}};
};

//============================================================
// Trace configuration

void Vinstr_mem___024root__trace_init_top(Vinstr_mem___024root* vlSelf, VerilatedVcd* tracep);

VL_ATTR_COLD static void trace_init(void* voidSelf, VerilatedVcd* tracep, uint32_t code) {
    // Callback from tracep->open()
    Vinstr_mem___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vinstr_mem___024root*>(voidSelf);
    Vinstr_mem__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (!vlSymsp->_vm_contextp__->calcUnusedSigs()) {
        VL_FATAL_MT(__FILE__, __LINE__, __FILE__,
            "Turning on wave traces requires Verilated::traceEverOn(true) call before time 0.");
    }
    vlSymsp->__Vm_baseCode = code;
    tracep->scopeEscape(' ');
    tracep->pushNamePrefix(std::string{vlSymsp->name()} + ' ');
    Vinstr_mem___024root__trace_init_top(vlSelf, tracep);
    tracep->popNamePrefix();
    tracep->scopeEscape('.');
}

VL_ATTR_COLD void Vinstr_mem___024root__trace_register(Vinstr_mem___024root* vlSelf, VerilatedVcd* tracep);

VL_ATTR_COLD void Vinstr_mem::trace(VerilatedVcdC* tfp, int levels, int options) {
    if (false && levels && options) {}  // Prevent unused
    tfp->spTrace()->addModel(this);
    tfp->spTrace()->addInitCb(&trace_init, &(vlSymsp->TOP));
    Vinstr_mem___024root__trace_register(&(vlSymsp->TOP), tfp->spTrace());
}
