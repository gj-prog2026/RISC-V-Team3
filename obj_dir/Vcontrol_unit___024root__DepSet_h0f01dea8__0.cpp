// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vcontrol_unit.h for the primary calling header

#include "verilated.h"

#include "Vcontrol_unit___024root.h"

VL_INLINE_OPT void Vcontrol_unit___024root___combo__TOP__0(Vcontrol_unit___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcontrol_unit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcontrol_unit___024root___combo__TOP__0\n"); );
    // Body
    vlSelf->RegWrite = (0x13U == (IData)(vlSelf->opcode));
    vlSelf->Immsrc = ((0x13U != (IData)(vlSelf->opcode)) 
                      & (0x63U == (IData)(vlSelf->opcode)));
    vlSelf->ALUctrl = ((0x13U != (IData)(vlSelf->opcode)) 
                       & (0x63U == (IData)(vlSelf->opcode)));
    vlSelf->ALUsrc = (0x13U == (IData)(vlSelf->opcode));
    vlSelf->PCsrc = ((0x13U != (IData)(vlSelf->opcode)) 
                     & ((0x63U == (IData)(vlSelf->opcode)) 
                        & (~ (IData)(vlSelf->EQ))));
}

void Vcontrol_unit___024root___eval(Vcontrol_unit___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcontrol_unit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcontrol_unit___024root___eval\n"); );
    // Body
    Vcontrol_unit___024root___combo__TOP__0(vlSelf);
}

#ifdef VL_DEBUG
void Vcontrol_unit___024root___eval_debug_assertions(Vcontrol_unit___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcontrol_unit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcontrol_unit___024root___eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((vlSelf->EQ & 0xfeU))) {
        Verilated::overWidthError("EQ");}
    if (VL_UNLIKELY((vlSelf->opcode & 0x80U))) {
        Verilated::overWidthError("opcode");}
}
#endif  // VL_DEBUG
