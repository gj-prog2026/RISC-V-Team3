// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vsign_extend.h"
#include "Vsign_extend__Syms.h"

//============================================================
// Constructors

Vsign_extend::Vsign_extend(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vsign_extend__Syms(contextp(), _vcname__, this)}
    , Immsrc{vlSymsp->TOP.Immsrc}
    , instr{vlSymsp->TOP.instr}
    , immop{vlSymsp->TOP.immop}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vsign_extend::Vsign_extend(const char* _vcname__)
    : Vsign_extend(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vsign_extend::~Vsign_extend() {
    delete vlSymsp;
}

//============================================================
// Evaluation loop

void Vsign_extend___024root___eval_initial(Vsign_extend___024root* vlSelf);
void Vsign_extend___024root___eval_settle(Vsign_extend___024root* vlSelf);
void Vsign_extend___024root___eval(Vsign_extend___024root* vlSelf);
#ifdef VL_DEBUG
void Vsign_extend___024root___eval_debug_assertions(Vsign_extend___024root* vlSelf);
#endif  // VL_DEBUG
void Vsign_extend___024root___final(Vsign_extend___024root* vlSelf);

static void _eval_initial_loop(Vsign_extend__Syms* __restrict vlSymsp) {
    vlSymsp->__Vm_didInit = true;
    Vsign_extend___024root___eval_initial(&(vlSymsp->TOP));
    // Evaluate till stable
    do {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial loop\n"););
        Vsign_extend___024root___eval_settle(&(vlSymsp->TOP));
        Vsign_extend___024root___eval(&(vlSymsp->TOP));
    } while (0);
}

void Vsign_extend::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vsign_extend::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vsign_extend___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    // Initialize
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) _eval_initial_loop(vlSymsp);
    // Evaluate till stable
    do {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Clock loop\n"););
        Vsign_extend___024root___eval(&(vlSymsp->TOP));
    } while (0);
    // Evaluate cleanup
}

//============================================================
// Utilities

const char* Vsign_extend::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

VL_ATTR_COLD void Vsign_extend::final() {
    Vsign_extend___024root___final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vsign_extend::hierName() const { return vlSymsp->name(); }
const char* Vsign_extend::modelName() const { return "Vsign_extend"; }
unsigned Vsign_extend::threads() const { return 1; }
