// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vcontrol_unit.h for the primary calling header

#include "verilated.h"

#include "Vcontrol_unit__Syms.h"
#include "Vcontrol_unit___024root.h"

void Vcontrol_unit___024root___ctor_var_reset(Vcontrol_unit___024root* vlSelf);

Vcontrol_unit___024root::Vcontrol_unit___024root(Vcontrol_unit__Syms* symsp, const char* name)
    : VerilatedModule{name}
    , vlSymsp{symsp}
 {
    // Reset structure values
    Vcontrol_unit___024root___ctor_var_reset(this);
}

void Vcontrol_unit___024root::__Vconfigure(bool first) {
    if (false && first) {}  // Prevent unused
}

Vcontrol_unit___024root::~Vcontrol_unit___024root() {
}
