// ==============================================================
// File generated by Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC
// Version: 2018.2
// Copyright (C) 1986-2018 Xilinx, Inc. All Rights Reserved.
// 
// ==============================================================

// CONTROL_BUS
// 0x00 : reserved
// 0x04 : reserved
// 0x08 : reserved
// 0x0c : reserved
// 0x10 : reserved
// 0x14 : Data signal of rows
//        bit 31~0 - rows[31:0] (Read/Write)
// 0x18 : reserved
// 0x1c : Data signal of cols
//        bit 31~0 - cols[31:0] (Read/Write)
// 0x20 : reserved
// 0x24 : Data signal of max_h
//        bit 31~0 - max_h[31:0] (Read/Write)
// 0x28 : reserved
// 0x2c : Data signal of min_h
//        bit 31~0 - min_h[31:0] (Read/Write)
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define XTHRESHOLD2_CONTROL_BUS_ADDR_ROWS_DATA  0x14
#define XTHRESHOLD2_CONTROL_BUS_BITS_ROWS_DATA  32
#define XTHRESHOLD2_CONTROL_BUS_ADDR_COLS_DATA  0x1c
#define XTHRESHOLD2_CONTROL_BUS_BITS_COLS_DATA  32
#define XTHRESHOLD2_CONTROL_BUS_ADDR_MAX_H_DATA 0x24
#define XTHRESHOLD2_CONTROL_BUS_BITS_MAX_H_DATA 32
#define XTHRESHOLD2_CONTROL_BUS_ADDR_MIN_H_DATA 0x2c
#define XTHRESHOLD2_CONTROL_BUS_BITS_MIN_H_DATA 32

