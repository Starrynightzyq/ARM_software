#include "image.h"
#include "xparameters.h"
#include "xstatus.h"
#include <string.h>
#include "m3_for_arty.h"        // Project specific header
#include "lcd.h"
#include "dis_plate.h"
#include "uart.h"
#include "gpio.h"

#include "gizwits_product.h"
#include "common.h"

#ifdef XPAR_XTHRESHOLD2_0_DEVICE_ID
#include "xthreshold2.h"
#endif

#ifdef XPAR_XPROJECTION1_HLS_0_DEVICE_ID
#include "xprojection1_hls.h"
#endif

#ifdef XPAR_XMASK_0_DEVICE_ID
#include "xmask.h"
#endif

#ifdef XPAR_XPROJECTION_MUL_HLS_0_DEVICE_ID
#include "xprojection_mul_hls.h"
#endif

#ifdef XPAR_XDRAW_LINE_HLS_0_DEVICE_ID
#include "xdraw_line_hls.h"
#endif

#ifdef XPAR_XRESIZE_HLS_AXIS_0_DEVICE_ID
#include "xresize_hls_axis.h"
#endif

#ifdef XPAR_XCONTRAST_HLS_ROM_0_DEVICE_ID
#include "xcontrast_hls_rom.h"
#endif

#ifdef XPAR_OV_CMOS_IMAGE_PROCESS_CONTRAST_JUDGE_1_DEVICE_ID
#include "judge.h"
#endif

#ifdef XPAR_OV_CMOS_IMAGE_PROCESS_CONTRAST_AXI_GPIO_0_DEVICE_ID
#include "xgpio.h"
#endif

#ifdef XPAR_XAXIS2RAM_0_DEVICE_ID
#include "xaxis2ram.h"
#endif

#ifdef XPAR_XREORDER_HLS_0_DEVICE_ID
#include "xreorder_hls.h"
#endif

#ifdef XPAR_XREORDER_RESIZE_0_DEVICE_ID
#include "xreorder_resize.h"
#endif

#ifdef XPAR_XTHRESHOLD2_0_DEVICE_ID
static XThreshold2 Threshold;
#endif

#ifdef XPAR_XPROJECTION1_HLS_0_DEVICE_ID
static XProjection1_hls Projection;
#endif

#ifdef XPAR_XMASK_0_DEVICE_ID
static XMask Mask;
#endif

#ifdef XPAR_XPROJECTION_MUL_HLS_0_DEVICE_ID
static XProjection_mul_hls Projection_Mul;
#endif

#ifdef XPAR_XDRAW_LINE_HLS_0_DEVICE_ID
static XDraw_line_hls Draw_Lines;
#endif

#ifdef XPAR_XRESIZE_HLS_AXIS_0_DEVICE_ID
static XResize_hls_axis Resize;
#endif

#ifdef XPAR_XCONTRAST_HLS_ROM_0_DEVICE_ID
static XContrast_hls_rom Contrast;
#endif

#ifdef XPAR_OV_CMOS_IMAGE_PROCESS_CONTRAST_AXI_GPIO_0_DEVICE_ID
static XGpio Gpio_Sort;
#endif

#ifdef XPAR_XAXIS2RAM_0_DEVICE_ID
static XAxis2ram Axis2ram;
#endif

#ifdef XPAR_XREORDER_RESIZE_0_DEVICE_ID
static XReorder_resize Resize;
#endif

#ifdef XPAR_XREORDER_HLS_0_DEVICE_ID
static XReorder_hls Reorder;
#endif

#define JUDGE_BASEADDR XPAR_OV_CMOS_IMAGE_PROCESS_CONTRAST_JUDGE_1_S_AXI_BASEADDR

volatile u32 char_index = 0;
volatile u32 char_index_first = 0;

u8 v_char_index_now[8] = {0}; // 前一组结果
u8 char_buffer[20][8] = {0}; // 车牌缓冲区
u8 buffer_valid_flag[MAX_PLATE_COUNTER] = {0}; // buffer 中有数据标志

volatile u8 show_plate_flag = 0;

volatile u8 recognize_on = 0;

int plate_counter = 0; // 识别到的车牌数

// #define DEBUG
#define LCD_SHOW

int Initialize_image_process(void)
{
	int Status;

#ifdef XPAR_XTHRESHOLD2_0_DEVICE_ID
	Status = XThreshold2_Initialize(&Threshold, XPAR_XTHRESHOLD2_0_DEVICE_ID);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}
	else {
		xil_printf("Initialize the XThreshold2 successfully\r\n");
	}

	XThreshold2_Set_rows(&Threshold, IMAGE_ROWS);  // 480
	XThreshold2_Set_cols(&Threshold, IMAGE_COLS);  // 640

	XThreshold2_Set_max_h(&Threshold, 125); // 100
	XThreshold2_Set_min_h(&Threshold, 105);  // 60
	XThreshold2_Set_max_s(&Threshold, 225); // 255
	XThreshold2_Set_min_s(&Threshold, 120);  // 20
	XThreshold2_Set_max_v(&Threshold, 240); // 255
	XThreshold2_Set_min_v(&Threshold, 20); // 150

	XThreshold2_InterruptGlobalDisable(&Threshold);
	XThreshold2_EnableAutoRestart(&Threshold);
	XThreshold2_Start(&Threshold);
#endif

	/* initialize the projection ip */
#ifdef XPAR_XPROJECTION1_HLS_0_DEVICE_ID
	Status = XProjection1_hls_Initialize(&Projection, XPAR_XPROJECTION1_HLS_0_DEVICE_ID);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}
	else {
		xil_printf("Initialize the XProjection1 successfully\r\n");
	}

	XProjection1_hls_Set_rows(&Projection, IMAGE_ROWS);
	XProjection1_hls_Set_cols(&Projection, IMAGE_COLS);

	XProjection1_hls_Set_threshold_width(&Projection, 20);
	XProjection1_hls_Set_threshold_height(&Projection, 105);
	XProjection1_hls_Set_shrink_x_min(&Projection, 20); //15
	XProjection1_hls_Set_shrink_x_max(&Projection, 5);  // 5
	XProjection1_hls_Set_shrink_y_min(&Projection, 13); // 13
	XProjection1_hls_Set_shrink_y_max(&Projection, 13); // 13
	XProjection1_hls_Set_range_min(&Projection, 10);

	XProjection1_hls_InterruptGlobalDisable(&Projection);
	XProjection1_hls_EnableAutoRestart(&Projection);
	XProjection1_hls_Start(&Projection);
#endif

#ifdef XPAR_XMASK_0_DEVICE_ID
	Status = XMask_Initialize(&Mask, XPAR_XMASK_0_DEVICE_ID);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}
	else {
		xil_printf("Initialize the XMask successfully\r\n");
	}

	XMask_Set_rows(&Mask, IMAGE_ROWS);
	XMask_Set_cols(&Mask, IMAGE_COLS);
	XMask_Set_shrink_x_min(&Mask, 0);
	XMask_Set_shrink_x_max(&Mask, 0);
	XMask_Set_shrink_y_min(&Mask, 0);
	XMask_Set_shrink_y_max(&Mask, 0);

	XMask_InterruptGlobalDisable(&Mask);
	XMask_EnableAutoRestart(&Mask);
	XMask_Start(&Mask);
#endif

#ifdef XPAR_XPROJECTION_MUL_HLS_0_DEVICE_ID
	Status = XProjection_mul_hls_Initialize(&Projection_Mul, XPAR_XPROJECTION_MUL_HLS_0_DEVICE_ID);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}
	else {
		xil_printf("Initialize the XProjection_mul successfully\r\n");
	}

	XProjection_mul_hls_Set_rows(&Projection_Mul, IMAGE_ROWS);
	XProjection_mul_hls_Set_cols(&Projection_Mul, IMAGE_COLS);

	XProjection_mul_hls_Set_threshold_v(&Projection_Mul, 5);

	XProjection_mul_hls_Set_range_min(&Projection_Mul, 10);
	XProjection_mul_hls_Set_range_max(&Projection_Mul, 70);

	XProjection_mul_hls_InterruptGlobalDisable(&Projection_Mul);
	XProjection_mul_hls_EnableAutoRestart(&Projection_Mul);
	XProjection_mul_hls_Start(&Projection_Mul);
#endif

#ifdef XPAR_XDRAW_LINE_HLS_0_DEVICE_ID
	Status = XDraw_line_hls_Initialize(&Draw_Lines, XPAR_XDRAW_LINE_HLS_0_DEVICE_ID);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}
	else {
		xil_printf("Initialize the XDraw_line successfully\r\n");
	}

	XDraw_line_hls_Set_rows(&Draw_Lines, IMAGE_ROWS);
	XDraw_line_hls_Set_cols(&Draw_Lines, IMAGE_COLS);
	XDraw_line_hls_Set_box_num(&Draw_Lines, 7);

	XDraw_line_hls_InterruptGlobalDisable(&Draw_Lines);
	XDraw_line_hls_EnableAutoRestart(&Draw_Lines);
	XDraw_line_hls_Start(&Draw_Lines);

	xil_printf("Draw_Lines is ready %d\r\n", XDraw_line_hls_IsReady(&Draw_Lines));

#endif

#ifdef XPAR_XRESIZE_HLS_AXIS_0_DEVICE_ID
	Status = XResize_hls_axis_Initialize(&Resize, XPAR_XRESIZE_HLS_AXIS_0_DEVICE_ID);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}
	// else {
	// 	xil_printf("Initialize the XResize successfully\r\n");
	// }
	XResize_hls_axis_Set_src_rows(&Resize, IMAGE_ROWS);
	XResize_hls_axis_Set_src_cols(&Resize, IMAGE_COLS);
	XResize_hls_axis_Set_dst_rows(&Resize, 28);
	XResize_hls_axis_Set_dst_cols(&Resize, 28);
	XResize_hls_axis_InterruptGlobalDisable(&Resize);
	XResize_hls_axis_EnableAutoRestart(&Resize);
	XResize_hls_axis_Start(&Resize);

	xil_printf("Resize is ready %d\r\n", XResize_hls_axis_IsReady(&Resize));

#endif

#ifdef XPAR_XCONTRAST_HLS_ROM_0_DEVICE_ID
	Status = XContrast_hls_rom_Initialize(&Contrast, XPAR_XCONTRAST_HLS_ROM_0_DEVICE_ID);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}
	else {
		xil_printf("Initialize the XContrast successfully\r\n");
	}

	XContrast_hls_rom_EnableAutoRestart(&Contrast);
	XContrast_hls_rom_InterruptGlobalDisable(&Contrast);
	XContrast_hls_rom_Start(&Contrast);
#endif

#ifdef XPAR_OV_CMOS_IMAGE_PROCESS_CONTRAST_JUDGE_1_DEVICE_ID
	JUDGE_mWriteReg(JUDGE_BASEADDR, JUDGE_S_AXI_SLV_REG0_OFFSET, 80); // 最大误差值
	JUDGE_mWriteReg(JUDGE_BASEADDR, JUDGE_S_AXI_SLV_REG1_OFFSET, 2); // 最小连续
	JUDGE_mWriteReg(JUDGE_BASEADDR, JUDGE_S_AXI_SLV_REG2_OFFSET, 3); // 最小计数值
#endif

#ifdef XPAR_XREORDER_RESIZE_0_DEVICE_ID
	Status = XReorder_resize_Initialize(&Resize, XPAR_XREORDER_RESIZE_0_DEVICE_ID);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}
	else {
		xil_printf("Initialize the XResize successfully\r\n");
	}

	XReorder_resize_Set_dst_rows(&Resize, 28);
	XReorder_resize_Set_dst_cols(&Resize, 28);
#endif

#ifdef XPAR_OV_CMOS_IMAGE_PROCESS_CONTRAST_AXI_GPIO_0_DEVICE_ID
	XGpio_Initialize(&Gpio_Sort, XPAR_OV_CMOS_IMAGE_PROCESS_CONTRAST_AXI_GPIO_0_DEVICE_ID);
	XGpio_SetDataDirection(&Gpio_Sort, 1, 0xFFFFFFFF); // all input
	XGpio_SetDataDirection(&Gpio_Sort, 2, 0x00000000); // all output
	XGpio_DiscreteWrite(&Gpio_Sort, 2, 0x0050203); // 0x0050 2 03
	// XGpio_SetDataDirection(&Gpio_Sort, CHAR_DIFF_CHANNEL, 0xFFFFFFFF);
	// XGpio_InterruptGlobalDisable(&Gpio_Sort); // this gpio doesn't have a interrupt controller
#endif

#ifdef XPAR_XAXIS2RAM_0_DEVICE_ID
	XAxis2ram_Initialize(&Axis2ram, XPAR_XAXIS2RAM_0_DEVICE_ID);
	XAxis2ram_InterruptGlobalDisable(&Axis2ram);
	XAxis2ram_EnableAutoRestart(&Axis2ram);
	XAxis2ram_Start(&Axis2ram);
#endif

#ifdef XPAR_XREORDER_HLS_0_DEVICE_ID
	XReorder_hls_Initialize(&Reorder, XPAR_XREORDER_HLS_0_DEVICE_ID);
	XReorder_hls_InterruptGlobalDisable(&Reorder);
	XReorder_hls_EnableAutoRestart(&Reorder);
	XReorder_hls_Start(&Reorder);
#endif

	Ap_Start();

	return 0;
}

/* Interrupt Handler */
void XPlate_InterruptHandler(void)
{
	show_plate_flag = 1;

	if (recognize_on)
	{	
		if (plate_counter < (MAX_PLATE_COUNTER - 1))
		{
			Keyboard_Space();
		}
	}

	// char_index = XGpio_DiscreteRead(&Gpio_Sort, CHAR_INDEX_CHANNEL);
	char_index = JUDGE_mReadReg(JUDGE_BASEADDR, JUDGE_S_AXI_SLV_REG3_OFFSET);
	xil_printf("plate is %07x\r\n", char_index);
}

int Image_Interrupt_setup(void)
{

	NVIC_EnableIRQ(Plate_IRQn);

	return XST_SUCCESS;

}


void show_plate(void)
{
	int i = 0;
	u32 char_index_t = 0;

	if (recognize_on)
	{		
		
		if (plate_counter == 0)
		{
			Keyboard_Space();
		}
		
		if (show_plate_flag == 1)           //if识别到新的车牌号
		{
			char_index_t = char_index >> 8; // 不显示前两位
			for (i = 0; i < 5; i++)
			{
				v_char_index_now[i] = char_index_t & 0x000F;
				char_index_t = char_index_t >> 4;
				if (v_char_index_now[i] == 0xA)
				{
					goto end;
				}
			}
			xil_printf("plate num is %2d\r\n", plate_counter);

	#ifdef LCD_SHOW
			show_plate_num(v_char_index_now, plate_counter);

			// 写入缓冲队列
			memcpy((uint8_t *)&(char_buffer[plate_counter][0]), (uint8_t *)(v_char_index_now), sizeof(v_char_index_now)); // 将识别的车牌复制到缓存中
			buffer_valid_flag[plate_counter] = 1; // 将有效位置1

	#endif
			if (plate_counter >= (MAX_PLATE_COUNTER - 1))
			{
	//			plate_counter = 0;
				Gpio_Image_Set();
			}
			else
			{
				plate_counter++;
			}

	end:	show_plate_flag = 0;
		}
	}

}


/* Interrupt Handler */
/*
void XResize_Handler(void)
{
	XResize_InterruptHandler();
	NVIC_ClearPendingIRQ(HLS_RESIZE_IRQn);
}

void XSort_Handler(void)
{
	XSort_InterruptHandler();
	NVIC_ClearPendingIRQ(HLS_SORT_IRQn);
}

void XContrast_Handler(void)
{
	XContrast_InterruptHandler();
	NVIC_ClearPendingIRQ(HLS_CONTRAST_IRQn);
}
*/
void XPlate_Handler(void)
{
	XPlate_InterruptHandler();
	NVIC_ClearPendingIRQ(Plate_IRQn);
}

/* 获取中心点的hsv值 */
void Get_Hsv(void)
{
	u32 h, s, v;
	while (!XThreshold2_Get_h_vld(&Threshold));
	h = XThreshold2_Get_h(&Threshold);
	s = XThreshold2_Get_s(&Threshold);
	v = XThreshold2_Get_v(&Threshold);
	xil_printf("\r\nh %d, s %d, v %d\r\n", h, s, v);
}

void Clear_Buffer_Valid_Flag(void)
{
	// int i = 0;
	// for (int i = 0; i < MAX_PLATE_COUNTER; i++)
	// {
	// 	buffer_valid_flag[i] = 0;
	// }

	memset((uint8_t*)&buffer_valid_flag, 0, sizeof(buffer_valid_flag));
}