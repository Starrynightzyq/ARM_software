#include "m3_for_arty.h"        // Project specific header
#include "vdma.h"

#include "xparameters.h"
#include "xil_types.h"
#include "xil_io.h"
#include "xil_cache.h"
#include "xil_printf.h"
#include "xaxivdma_hw.h"
// #include "xaxivdma.h"
// #include "xaxivdma_i.h"

#define DDR_BASEADDR        XPAR_MIG7SERIES_0_BASEADDR
#define DDR_HIGHADDR        XPAR_MIG7SERIES_0_HIGHADDR
#define VDMA_BASEADDR       XPAR_AXIVDMA_0_BASEADDR
#define H_STRIDE            640
#define H_ACTIVE            640
#define V_ACTIVE            480

#define VIDEO_LENGTH  (H_STRIDE*V_ACTIVE)
#define VIDEO_BASEADDR0 DDR_BASEADDR + 0x0000000
#define VIDEO_BASEADDR1 DDR_BASEADDR + 0x1000000
#define VIDEO_BASEADDR2 DDR_BASEADDR + 0x2000000

//函数声明
void Xil_DCacheFlush(void);

// 所有数据格式 为 RGBA，低位的透明度暂不起作用
// extern const unsigned char gImage_beauty[1729536];

void Read_DDR_Config(void)
{
	/*****************从 DDR 读数据设置**********************/
	XAxiVdma_WriteReg(XPAR_AXIVDMA_0_BASEADDR, 0x0, 0x04);                 //reset
	XAxiVdma_WriteReg(XPAR_AXIVDMA_0_BASEADDR, 0x0, 0x08);                 //gen-lock
	XAxiVdma_WriteReg(XPAR_AXIVDMA_0_BASEADDR, 0x5C, VIDEO_BASEADDR0);     // start address
	XAxiVdma_WriteReg(XPAR_AXIVDMA_0_BASEADDR, 0x5C + 4, VIDEO_BASEADDR1); // start address
	XAxiVdma_WriteReg(XPAR_AXIVDMA_0_BASEADDR, 0x5C + 8, VIDEO_BASEADDR2); // start address
	XAxiVdma_WriteReg(XPAR_AXIVDMA_0_BASEADDR, 0x54, 640 * 3);             // h size (640 * 3) bytes
	XAxiVdma_WriteReg(XPAR_AXIVDMA_0_BASEADDR, 0x58, 640 * 3);             // h offset (640 * 3) bytes
	// 第 0 位： 运行 - 启动 VDMA 操作,在运行 VDMA 时，其状态寄存器中的停止位赋值为 0
	// 第 1 位： 循环模式 -通过连续循环帧缓冲
	XAxiVdma_WriteReg(XPAR_AXIVDMA_0_BASEADDR, 0x0, 0x03);
	XAxiVdma_WriteReg(XPAR_AXIVDMA_0_BASEADDR, 0x50, 480);                 // v size (480) bytes

	Xil_DCacheFlush();
}

void Write_DDR_Config(void)
{
	/*********** 写入 DDR 设置*************************/
	XAxiVdma_WriteReg(XPAR_AXIVDMA_0_BASEADDR, 0x30, 0x4); //reset
	XAxiVdma_WriteReg(XPAR_AXIVDMA_0_BASEADDR, 0x30, 0x8); //genlock
	XAxiVdma_WriteReg(XPAR_AXIVDMA_0_BASEADDR, 0xAC, VIDEO_BASEADDR0);
	XAxiVdma_WriteReg(XPAR_AXIVDMA_0_BASEADDR, 0xAC + 4, VIDEO_BASEADDR1);
	XAxiVdma_WriteReg(XPAR_AXIVDMA_0_BASEADDR, 0xAC + 8, VIDEO_BASEADDR2);
	XAxiVdma_WriteReg(XPAR_AXIVDMA_0_BASEADDR, 0xA4, 640 * 3);
	XAxiVdma_WriteReg(XPAR_AXIVDMA_0_BASEADDR, 0xA8, 640 * 3);
	XAxiVdma_WriteReg(XPAR_AXIVDMA_0_BASEADDR, 0x30, 0x03);
	XAxiVdma_WriteReg(XPAR_AXIVDMA_0_BASEADDR, 0xA0, 480);

	Xil_DCacheFlush();
}

void Video_Buffer_Initialize(void)
{
	u32 i;

	for (i = 0; i < VIDEO_LENGTH; i++)
	{
		Xil_Out32(VIDEO_BASEADDR0 + i, 0);
		Xil_Out32(VIDEO_BASEADDR1 + i, 0);
		Xil_Out32(VIDEO_BASEADDR2 + i, 0);
	}
	Xil_DCacheFlush();
}
/*
void show_img(u32 x, u32 y, u32 disp_base_addr, const unsigned char * addr, u32 size_x, u32 size_y)
{
	//计算图片 左上角坐标
	u32 i = 0;
	u32 j = 0;
	u32 r, g, b;
	u32 start_addr = disp_base_addr;
	start_addr = disp_base_addr + 4 * x + y * 4 * H_STRIDE;
	for (j = 0; j < size_y; j++)
	{
		for (i = 0; i < size_x; i++)
		{
			b = *(addr + (i + j * size_x) * 4 + 1);
			g = *(addr + (i + j * size_x) * 4 + 2);
			r = *(addr + (i + j * size_x) * 4 + 3);
			Xil_Out32((start_addr + (i + j * H_STRIDE) * 4), ((r << 16) | (g << 8) | (b << 0) | 0x0));
		}
	}
	Xil_DCacheFlush();
}
*/
void VDMA_Test(void)
{
	u32 x = 0;
	u32 y = 0;
	u32 color_r, color_g, color_b;

	for ( y = 0; y < V_ACTIVE; y++)
	{
		for ( x = 0; x < H_ACTIVE; x++)
		{
			color_r = x % H_ACTIVE;
			color_g = y % V_ACTIVE;
			color_b = (V_ACTIVE - y) % V_ACTIVE;
			Xil_Out32((VIDEO_BASEADDR0 + (x + y * H_STRIDE) * 3),
			          ((color_r << 16) | (color_b << 8) | (color_g << 0) | 0x0));
			Xil_Out32((VIDEO_BASEADDR1 + (x + y * H_STRIDE) * 3),
			          ((color_r << 16) | (color_b << 8) | (color_g << 0) | 0x0));
			Xil_Out32((VIDEO_BASEADDR2 + (x + y * H_STRIDE) * 3),
			          ((color_r << 16) | (color_b << 8) | (color_g << 0) | 0x0));
		}
	}
	Xil_DCacheFlush();
	xil_printf("\r\nVDMA Read Test Done\r\n");
}
