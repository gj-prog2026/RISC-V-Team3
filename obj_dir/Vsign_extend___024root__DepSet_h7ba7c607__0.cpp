// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vsign_extend.h for the primary calling header

#include "verilated.h"

#include "Vsign_extend___024root.h"

VL_INLINE_OPT void Vsign_extend___024root___combo__TOP__0(Vsign_extend___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsign_extend__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsign_extend___024root___combo__TOP__0\n"); );
    // Body
    vlSelf->immop = ((IData)(vlSelf->Immsrc) ? (((- (IData)(
                                                            (vlSelf->instr 
                                                             >> 0x1fU))) 
                                                 << 0xdU) 
                                                | ((0x1000U 
                                                    & (vlSelf->instr 
                                                       >> 0x13U)) 
                                                   | ((0x800U 
                                                       & (vlSelf->instr 
                                                          << 4U)) 
                                                      | ((0x7e0U 
                                                          & (vlSelf->instr 
                                                             >> 0x14U)) 
                                                         | (0x1eU 
                                                            & (vlSelf->instr 
                                                               >> 7U))))))
                      : (((- (IData)((vlSelf->instr 
                                      >> 0x1fU))) << 0xcU) 
                         | (vlSelf->instr >> 0x14U)));
}

void Vsign_extend___024root___eval(Vsign_extend___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsign_extend__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsign_extend___024root___eval\n"); );
    // Body
    Vsign_extend___024root___combo__TOP__0(vlSelf);
}

#ifdef VL_DEBUG
void Vsign_extend___024root___eval_debug_assertions(Vsign_extend___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsign_extend__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsign_extend___024root___eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((vlSelf->Immsrc & 0xfeU))) {
        Verilated::overWidthError("Immsrc");}
}
#endif  // VL_DEBUG
