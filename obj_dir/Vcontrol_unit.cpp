// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vcontrol_unit.h"
#include "Vcontrol_unit__Syms.h"

//============================================================
// Constructors

Vcontrol_unit::Vcontrol_unit(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vcontrol_unit__Syms(contextp(), _vcname__, this)}
    , EQ{vlSymsp->TOP.EQ}
    , opcode{vlSymsp->TOP.opcode}
    , RegWrite{vlSymsp->TOP.RegWrite}
    , ALUctrl{vlSymsp->TOP.ALUctrl}
    , ALUsrc{vlSymsp->TOP.ALUsrc}
    , Immsrc{vlSymsp->TOP.Immsrc}
    , PCsrc{vlSymsp->TOP.PCsrc}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vcontrol_unit::Vcontrol_unit(const char* _vcname__)
    : Vcontrol_unit(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vcontrol_unit::~Vcontrol_unit() {
    delete vlSymsp;
}

//============================================================
// Evaluation loop

void Vcontrol_unit___024root___eval_initial(Vcontrol_unit___024root* vlSelf);
void Vcontrol_unit___024root___eval_settle(Vcontrol_unit___024root* vlSelf);
void Vcontrol_unit___024root___eval(Vcontrol_unit___024root* vlSelf);
#ifdef VL_DEBUG
void Vcontrol_unit___024root___eval_debug_assertions(Vcontrol_unit___024root* vlSelf);
#endif  // VL_DEBUG
void Vcontrol_unit___024root___final(Vcontrol_unit___024root* vlSelf);

static void _eval_initial_loop(Vcontrol_unit__Syms* __restrict vlSymsp) {
    vlSymsp->__Vm_didInit = true;
    Vcontrol_unit___024root___eval_initial(&(vlSymsp->TOP));
    // Evaluate till stable
    do {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial loop\n"););
        Vcontrol_unit___024root___eval_settle(&(vlSymsp->TOP));
        Vcontrol_unit___024root___eval(&(vlSymsp->TOP));
    } while (0);
}

void Vcontrol_unit::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vcontrol_unit::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vcontrol_unit___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    // Initialize
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) _eval_initial_loop(vlSymsp);
    // Evaluate till stable
    do {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Clock loop\n"););
        Vcontrol_unit___024root___eval(&(vlSymsp->TOP));
    } while (0);
    // Evaluate cleanup
}

//============================================================
// Utilities

const char* Vcontrol_unit::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

VL_ATTR_COLD void Vcontrol_unit::final() {
    Vcontrol_unit___024root___final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vcontrol_unit::hierName() const { return vlSymsp->name(); }
const char* Vcontrol_unit::modelName() const { return "Vcontrol_unit"; }
unsigned Vcontrol_unit::threads() const { return 1; }
