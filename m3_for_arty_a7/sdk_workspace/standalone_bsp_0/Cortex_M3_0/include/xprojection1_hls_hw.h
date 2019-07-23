// ==============================================================
// File generated by Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC
// Version: 2018.2
// Copyright (C) 1986-2018 Xilinx, Inc. All Rights Reserved.
// 
// ==============================================================

// AXILiteS
// 0x00 : Control signals
//        bit 0  - ap_start (Read/Write/COH)
//        bit 1  - ap_done (Read/COR)
//        bit 2  - ap_idle (Read)
//        bit 3  - ap_ready (Read)
//        bit 7  - auto_restart (Read/Write)
//        others - reserved
// 0x04 : Global Interrupt Enable Register
//        bit 0  - Global Interrupt Enable (Read/Write)
//        others - reserved
// 0x08 : IP Interrupt Enable Register (Read/Write)
//        bit 0  - Channel 0 (ap_done)
//        bit 1  - Channel 1 (ap_ready)
//        others - reserved
// 0x0c : IP Interrupt Status Register (Read/TOW)
//        bit 0  - Channel 0 (ap_done)
//        bit 1  - Channel 1 (ap_ready)
//        others - reserved
// 0x10 : Data signal of rows
//        bit 31~0 - rows[31:0] (Read/Write)
// 0x14 : reserved
// 0x18 : Data signal of cols
//        bit 31~0 - cols[31:0] (Read/Write)
// 0x1c : reserved
// 0x20 : Data signal of threshold_width
//        bit 31~0 - threshold_width[31:0] (Read/Write)
// 0x24 : reserved
// 0x28 : Data signal of threshold_height
//        bit 31~0 - threshold_height[31:0] (Read/Write)
// 0x2c : reserved
// 0x30 : Data signal of shrink_x_min
//        bit 7~0 - shrink_x_min[7:0] (Read/Write)
//        others  - reserved
// 0x34 : reserved
// 0x38 : Data signal of shrink_x_max
//        bit 7~0 - shrink_x_max[7:0] (Read/Write)
//        others  - reserved
// 0x3c : reserved
// 0x40 : Data signal of shrink_y_min
//        bit 7~0 - shrink_y_min[7:0] (Read/Write)
//        others  - reserved
// 0x44 : reserved
// 0x48 : Data signal of shrink_y_max
//        bit 7~0 - shrink_y_max[7:0] (Read/Write)
//        others  - reserved
// 0x4c : reserved
// 0x50 : Data signal of range_min
//        bit 15~0 - range_min[15:0] (Read/Write)
//        others   - reserved
// 0x54 : reserved
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define XPROJECTION1_HLS_AXILITES_ADDR_AP_CTRL               0x00
#define XPROJECTION1_HLS_AXILITES_ADDR_GIE                   0x04
#define XPROJECTION1_HLS_AXILITES_ADDR_IER                   0x08
#define XPROJECTION1_HLS_AXILITES_ADDR_ISR                   0x0c
#define XPROJECTION1_HLS_AXILITES_ADDR_ROWS_DATA             0x10
#define XPROJECTION1_HLS_AXILITES_BITS_ROWS_DATA             32
#define XPROJECTION1_HLS_AXILITES_ADDR_COLS_DATA             0x18
#define XPROJECTION1_HLS_AXILITES_BITS_COLS_DATA             32
#define XPROJECTION1_HLS_AXILITES_ADDR_THRESHOLD_WIDTH_DATA  0x20
#define XPROJECTION1_HLS_AXILITES_BITS_THRESHOLD_WIDTH_DATA  32
#define XPROJECTION1_HLS_AXILITES_ADDR_THRESHOLD_HEIGHT_DATA 0x28
#define XPROJECTION1_HLS_AXILITES_BITS_THRESHOLD_HEIGHT_DATA 32
#define XPROJECTION1_HLS_AXILITES_ADDR_SHRINK_X_MIN_DATA     0x30
#define XPROJECTION1_HLS_AXILITES_BITS_SHRINK_X_MIN_DATA     8
#define XPROJECTION1_HLS_AXILITES_ADDR_SHRINK_X_MAX_DATA     0x38
#define XPROJECTION1_HLS_AXILITES_BITS_SHRINK_X_MAX_DATA     8
#define XPROJECTION1_HLS_AXILITES_ADDR_SHRINK_Y_MIN_DATA     0x40
#define XPROJECTION1_HLS_AXILITES_BITS_SHRINK_Y_MIN_DATA     8
#define XPROJECTION1_HLS_AXILITES_ADDR_SHRINK_Y_MAX_DATA     0x48
#define XPROJECTION1_HLS_AXILITES_BITS_SHRINK_Y_MAX_DATA     8
#define XPROJECTION1_HLS_AXILITES_ADDR_RANGE_MIN_DATA        0x50
#define XPROJECTION1_HLS_AXILITES_BITS_RANGE_MIN_DATA        16

