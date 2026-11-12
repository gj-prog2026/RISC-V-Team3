// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vinstr_mem__Syms.h"


VL_ATTR_COLD void Vinstr_mem___024root__trace_init_sub__TOP__0(Vinstr_mem___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vinstr_mem__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vinstr_mem___024root__trace_init_sub__TOP__0\n"); );
    // Init
    const int c = vlSymsp->__Vm_baseCode;
    // Body
    tracep->declBus(c+1,"addr", false,-1, 8,0);
    tracep->declBus(c+2,"instr", false,-1, 31,0);
    tracep->pushNamePrefix("instr_mem ");
    tracep->declBus(c+3,"BYTE_WIDTH", false,-1, 31,0);
    tracep->declBus(c+4,"ADDRESS_WIDTH", false,-1, 31,0);
    tracep->declBus(c+5,"INSTR_WIDTH", false,-1, 31,0);
    tracep->declBus(c+1,"addr", false,-1, 8,0);
    tracep->declBus(c+2,"instr", false,-1, 31,0);
    tracep->popNamePrefix(1);
}

VL_ATTR_COLD void Vinstr_mem___024root__trace_init_top(Vinstr_mem___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vinstr_mem__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vinstr_mem___024root__trace_init_top\n"); );
    // Body
    Vinstr_mem___024root__trace_init_sub__TOP__0(vlSelf, tracep);
}

VL_ATTR_COLD void Vinstr_mem___024root__trace_full_top_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void Vinstr_mem___024root__trace_chg_top_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void Vinstr_mem___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/);

VL_ATTR_COLD void Vinstr_mem___024root__trace_register(Vinstr_mem___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vinstr_mem__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vinstr_mem___024root__trace_register\n"); );
    // Body
    tracep->addFullCb(&Vinstr_mem___024root__trace_full_top_0, vlSelf);
    tracep->addChgCb(&Vinstr_mem___024root__trace_chg_top_0, vlSelf);
    tracep->addCleanupCb(&Vinstr_mem___024root__trace_cleanup, vlSelf);
}

VL_ATTR_COLD void Vinstr_mem___024root__trace_full_sub_0(Vinstr_mem___024root* vlSelf, VerilatedVcd::Buffer* bufp);

VL_ATTR_COLD void Vinstr_mem___024root__trace_full_top_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vinstr_mem___024root__trace_full_top_0\n"); );
    // Init
    Vinstr_mem___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vinstr_mem___024root*>(voidSelf);
    Vinstr_mem__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    Vinstr_mem___024root__trace_full_sub_0((&vlSymsp->TOP), bufp);
}

VL_ATTR_COLD void Vinstr_mem___024root__trace_full_sub_0(Vinstr_mem___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    if (false && vlSelf) {}  // Prevent unused
    Vinstr_mem__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vinstr_mem___024root__trace_full_sub_0\n"); );
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode);
    // Body
    bufp->fullSData(oldp+1,(vlSelf->addr),9);
    bufp->fullIData(oldp+2,(vlSelf->instr),32);
    bufp->fullIData(oldp+3,(8U),32);
    bufp->fullIData(oldp+4,(9U),32);
    bufp->fullIData(oldp+5,(0x20U),32);
}
