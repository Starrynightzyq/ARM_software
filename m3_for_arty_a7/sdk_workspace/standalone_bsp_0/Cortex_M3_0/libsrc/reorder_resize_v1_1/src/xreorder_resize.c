// ==============================================================
// File generated by Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC
// Version: 2018.2
// Copyright (C) 1986-2018 Xilinx, Inc. All Rights Reserved.
// 
// ==============================================================

/***************************** Include Files *********************************/
#include "xreorder_resize.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XReorder_resize_CfgInitialize(XReorder_resize *InstancePtr, XReorder_resize_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Axilites_BaseAddress = ConfigPtr->Axilites_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XReorder_resize_Set_dst_rows(XReorder_resize *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XReorder_resize_WriteReg(InstancePtr->Axilites_BaseAddress, XREORDER_RESIZE_AXILITES_ADDR_DST_ROWS_DATA, Data);
}

u32 XReorder_resize_Get_dst_rows(XReorder_resize *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XReorder_resize_ReadReg(InstancePtr->Axilites_BaseAddress, XREORDER_RESIZE_AXILITES_ADDR_DST_ROWS_DATA);
    return Data;
}

void XReorder_resize_Set_dst_cols(XReorder_resize *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XReorder_resize_WriteReg(InstancePtr->Axilites_BaseAddress, XREORDER_RESIZE_AXILITES_ADDR_DST_COLS_DATA, Data);
}

u32 XReorder_resize_Get_dst_cols(XReorder_resize *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XReorder_resize_ReadReg(InstancePtr->Axilites_BaseAddress, XREORDER_RESIZE_AXILITES_ADDR_DST_COLS_DATA);
    return Data;
}

