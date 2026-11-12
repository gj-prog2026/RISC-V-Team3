// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vinstr_mem.h for the primary calling header

#include "verilated.h"

#include "Vinstr_mem___024root.h"

VL_ATTR_COLD void Vinstr_mem___024root___initial__TOP__0(Vinstr_mem___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vinstr_mem__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vinstr_mem___024root___initial__TOP__0\n"); );
    // Init
    VlWide<7>/*223:0*/ __Vtemp_h7dbfef25__0;
    // Body
    VL_WRITEF("Loading rom.\n");
    __Vtemp_h7dbfef25__0[0U] = 0x2e6d656dU;
    __Vtemp_h7dbfef25__0[1U] = 0x79746573U;
    __Vtemp_h7dbfef25__0[2U] = 0x74725f62U;
    __Vtemp_h7dbfef25__0[3U] = 0x5f696e73U;
    __Vtemp_h7dbfef25__0[4U] = 0x74657374U;
    __Vtemp_h7dbfef25__0[5U] = 0x7374732fU;
    __Vtemp_h7dbfef25__0[6U] = 0x7465U;
    VL_READMEM_N(true, 8, 512, 0, VL_CVT_PACK_STR_NW(7, __Vtemp_h7dbfef25__0)
                 ,  &(vlSelf->instr_mem__DOT__mem_array)
                 , 0, ~0ULL);
}

VL_ATTR_COLD void Vinstr_mem___024root___eval_initial(Vinstr_mem___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vinstr_mem__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vinstr_mem___024root___eval_initial\n"); );
    // Body
    Vinstr_mem___024root___initial__TOP__0(vlSelf);
}

void Vinstr_mem___024root___combo__TOP__0(Vinstr_mem___024root* vlSelf);

VL_ATTR_COLD void Vinstr_mem___024root___eval_settle(Vinstr_mem___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vinstr_mem__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vinstr_mem___024root___eval_settle\n"); );
    // Body
    Vinstr_mem___024root___combo__TOP__0(vlSelf);
}

VL_ATTR_COLD void Vinstr_mem___024root___final(Vinstr_mem___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vinstr_mem__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vinstr_mem___024root___final\n"); );
}

VL_ATTR_COLD void Vinstr_mem___024root___ctor_var_reset(Vinstr_mem___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vinstr_mem__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vinstr_mem___024root___ctor_var_reset\n"); );
    // Body
    vlSelf->addr = VL_RAND_RESET_I(9);
    vlSelf->instr = VL_RAND_RESET_I(32);
    for (int __Vi0=0; __Vi0<512; ++__Vi0) {
        vlSelf->instr_mem__DOT__mem_array[__Vi0] = VL_RAND_RESET_I(8);
    }
}
