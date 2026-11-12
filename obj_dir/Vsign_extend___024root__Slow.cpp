// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vsign_extend.h for the primary calling header

#include "verilated.h"

#include "Vsign_extend__Syms.h"
#include "Vsign_extend___024root.h"

void Vsign_extend___024root___ctor_var_reset(Vsign_extend___024root* vlSelf);

Vsign_extend___024root::Vsign_extend___024root(Vsign_extend__Syms* symsp, const char* name)
    : VerilatedModule{name}
    , vlSymsp{symsp}
 {
    // Reset structure values
    Vsign_extend___024root___ctor_var_reset(this);
}

void Vsign_extend___024root::__Vconfigure(bool first) {
    if (false && first) {}  // Prevent unused
}

Vsign_extend___024root::~Vsign_extend___024root() {
}
