// ==============================================================
// File generated by Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC
// Version: 2018.2
// Copyright (C) 1986-2018 Xilinx, Inc. All Rights Reserved.
// 
// ==============================================================

/***************************** Include Files *********************************/
#include "xresize_hls_axis.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XResize_hls_axis_CfgInitialize(XResize_hls_axis *InstancePtr, XResize_hls_axis_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Axilites_BaseAddress = ConfigPtr->Axilites_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XResize_hls_axis_Start(XResize_hls_axis *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XResize_hls_axis_ReadReg(InstancePtr->Axilites_BaseAddress, XRESIZE_HLS_AXIS_AXILITES_ADDR_AP_CTRL) & 0x80;
    XResize_hls_axis_WriteReg(InstancePtr->Axilites_BaseAddress, XRESIZE_HLS_AXIS_AXILITES_ADDR_AP_CTRL, Data | 0x01);
}

u32 XResize_hls_axis_IsDone(XResize_hls_axis *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XResize_hls_axis_ReadReg(InstancePtr->Axilites_BaseAddress, XRESIZE_HLS_AXIS_AXILITES_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XResize_hls_axis_IsIdle(XResize_hls_axis *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XResize_hls_axis_ReadReg(InstancePtr->Axilites_BaseAddress, XRESIZE_HLS_AXIS_AXILITES_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XResize_hls_axis_IsReady(XResize_hls_axis *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XResize_hls_axis_ReadReg(InstancePtr->Axilites_BaseAddress, XRESIZE_HLS_AXIS_AXILITES_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XResize_hls_axis_EnableAutoRestart(XResize_hls_axis *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XResize_hls_axis_WriteReg(InstancePtr->Axilites_BaseAddress, XRESIZE_HLS_AXIS_AXILITES_ADDR_AP_CTRL, 0x80);
}

void XResize_hls_axis_DisableAutoRestart(XResize_hls_axis *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XResize_hls_axis_WriteReg(InstancePtr->Axilites_BaseAddress, XRESIZE_HLS_AXIS_AXILITES_ADDR_AP_CTRL, 0);
}

void XResize_hls_axis_Set_src_rows(XResize_hls_axis *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XResize_hls_axis_WriteReg(InstancePtr->Axilites_BaseAddress, XRESIZE_HLS_AXIS_AXILITES_ADDR_SRC_ROWS_DATA, Data);
}

u32 XResize_hls_axis_Get_src_rows(XResize_hls_axis *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XResize_hls_axis_ReadReg(InstancePtr->Axilites_BaseAddress, XRESIZE_HLS_AXIS_AXILITES_ADDR_SRC_ROWS_DATA);
    return Data;
}

void XResize_hls_axis_Set_src_cols(XResize_hls_axis *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XResize_hls_axis_WriteReg(InstancePtr->Axilites_BaseAddress, XRESIZE_HLS_AXIS_AXILITES_ADDR_SRC_COLS_DATA, Data);
}

u32 XResize_hls_axis_Get_src_cols(XResize_hls_axis *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XResize_hls_axis_ReadReg(InstancePtr->Axilites_BaseAddress, XRESIZE_HLS_AXIS_AXILITES_ADDR_SRC_COLS_DATA);
    return Data;
}

void XResize_hls_axis_Set_dst_rows(XResize_hls_axis *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XResize_hls_axis_WriteReg(InstancePtr->Axilites_BaseAddress, XRESIZE_HLS_AXIS_AXILITES_ADDR_DST_ROWS_DATA, Data);
}

u32 XResize_hls_axis_Get_dst_rows(XResize_hls_axis *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XResize_hls_axis_ReadReg(InstancePtr->Axilites_BaseAddress, XRESIZE_HLS_AXIS_AXILITES_ADDR_DST_ROWS_DATA);
    return Data;
}

void XResize_hls_axis_Set_dst_cols(XResize_hls_axis *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XResize_hls_axis_WriteReg(InstancePtr->Axilites_BaseAddress, XRESIZE_HLS_AXIS_AXILITES_ADDR_DST_COLS_DATA, Data);
}

u32 XResize_hls_axis_Get_dst_cols(XResize_hls_axis *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XResize_hls_axis_ReadReg(InstancePtr->Axilites_BaseAddress, XRESIZE_HLS_AXIS_AXILITES_ADDR_DST_COLS_DATA);
    return Data;
}

void XResize_hls_axis_InterruptGlobalEnable(XResize_hls_axis *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XResize_hls_axis_WriteReg(InstancePtr->Axilites_BaseAddress, XRESIZE_HLS_AXIS_AXILITES_ADDR_GIE, 1);
}

void XResize_hls_axis_InterruptGlobalDisable(XResize_hls_axis *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XResize_hls_axis_WriteReg(InstancePtr->Axilites_BaseAddress, XRESIZE_HLS_AXIS_AXILITES_ADDR_GIE, 0);
}

void XResize_hls_axis_InterruptEnable(XResize_hls_axis *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XResize_hls_axis_ReadReg(InstancePtr->Axilites_BaseAddress, XRESIZE_HLS_AXIS_AXILITES_ADDR_IER);
    XResize_hls_axis_WriteReg(InstancePtr->Axilites_BaseAddress, XRESIZE_HLS_AXIS_AXILITES_ADDR_IER, Register | Mask);
}

void XResize_hls_axis_InterruptDisable(XResize_hls_axis *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XResize_hls_axis_ReadReg(InstancePtr->Axilites_BaseAddress, XRESIZE_HLS_AXIS_AXILITES_ADDR_IER);
    XResize_hls_axis_WriteReg(InstancePtr->Axilites_BaseAddress, XRESIZE_HLS_AXIS_AXILITES_ADDR_IER, Register & (~Mask));
}

void XResize_hls_axis_InterruptClear(XResize_hls_axis *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XResize_hls_axis_WriteReg(InstancePtr->Axilites_BaseAddress, XRESIZE_HLS_AXIS_AXILITES_ADDR_ISR, Mask);
}

u32 XResize_hls_axis_InterruptGetEnabled(XResize_hls_axis *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XResize_hls_axis_ReadReg(InstancePtr->Axilites_BaseAddress, XRESIZE_HLS_AXIS_AXILITES_ADDR_IER);
}

u32 XResize_hls_axis_InterruptGetStatus(XResize_hls_axis *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XResize_hls_axis_ReadReg(InstancePtr->Axilites_BaseAddress, XRESIZE_HLS_AXIS_AXILITES_ADDR_ISR);
}

