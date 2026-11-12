// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vinstr_mem.h for the primary calling header

#include "verilated.h"

#include "Vinstr_mem__Syms.h"
#include "Vinstr_mem___024root.h"

void Vinstr_mem___024root___ctor_var_reset(Vinstr_mem___024root* vlSelf);

Vinstr_mem___024root::Vinstr_mem___024root(Vinstr_mem__Syms* symsp, const char* name)
    : VerilatedModule{name}
    , vlSymsp{symsp}
 {
    // Reset structure values
    Vinstr_mem___024root___ctor_var_reset(this);
}

void Vinstr_mem___024root::__Vconfigure(bool first) {
    if (false && first) {}  // Prevent unused
}

Vinstr_mem___024root::~Vinstr_mem___024root() {
}
