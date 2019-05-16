#ifndef __VDMA_H__
#define __VDMA_H__

#include "xil_types.h"

void Read_DDR_Config(void);
void Write_DDR_Config(void);
void Video_Buffer_Initialize(void);

int VDMA_Config(void);

// void show_img(u32 x, u32 y, u32 disp_base_addr, const unsigned char * addr, u32 size_x, u32 size_y);
void VDMA_Test(void);
void VDMA_Read_Config(u32 AXIVDMA_BASEADDR, u32 VIDEO_BASEADDR);
void VDMA_Write_Config(u32 AXIVDMA_BASEADDR, u32 VIDEO_BASEADDR);


#endif
