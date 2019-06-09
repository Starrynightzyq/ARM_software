#include "image.h"
#include "xparameters.h"
#include "xstatus.h"
#include <string.h>
#include "m3_for_arty.h"        // Project specific header
#include "lcd.h"

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

#ifdef XPAR_XPROJECTION_MUL_HLS_0_DEVICE_ID
#include "xdraw_line_hls.h"
#endif

#ifdef XPAR_XRESIZE_HLS_AXIS_0_DEVICE_ID
#include "xresize_hls_axis.h"
#endif

#ifdef XPAR_XCONTRAST_HLS_ROM_0_DEVICE_ID
#include "xcontrast_hls_rom.h"
#endif

#ifdef XPAR_OV_CMOS_IMAGE_PROCESS_AXI_GPIO_0_DEVICE_ID
#include "xgpio.h"
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

#ifdef XPAR_XPROJECTION_MUL_HLS_0_DEVICE_ID
static XDraw_line_hls Draw_Lines;
#endif

#ifdef XPAR_XRESIZE_HLS_AXIS_0_DEVICE_ID
static XResize_hls_axis Resize;
#endif

#ifdef XPAR_XCONTRAST_HLS_ROM_0_DEVICE_ID
static XContrast_hls_rom Contrast;
#endif

#ifdef XPAR_OV_CMOS_IMAGE_PROCESS_AXI_GPIO_0_DEVICE_ID
static XGpio Gpio_Sort;
#endif

volatile u8 Sort_Flag = 0;
volatile u32 char_index = 0;
u32 char_index_t = 0;
volatile u32 char_diff = 0;

u8 char_addr = 0;               // 车牌中字的位置
u32 v_char_index_now[8] = {0}; // 前一组结果
u32 v_char_diff_now[8] = {0};  // 前一组差值
u32 v_char_index_last[8] = {0}; // 前一组结果
u32 v_char_diff_last[8] = {0};  // 前一组差值
u32 v_char_index_show[8] = {0}; // 前一组结果
u32 v_char_diff_show[8] = {0};  // 前一组差值

u8 frame_count = 0;     // 图像帧数计数器

u8 recognize_done = 0;	// 识别完成标记位
u8 show_plate_flag = 0;

int palte_count = 0; // 识别到的车牌数

u8 array_dis[6];      //用来存放8个显示字符的ASCII码

u16 columns = 0; //显示屏上的列数
u16 rows = 0;  //显示屏上的行数

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

	XThreshold2_Set_max_h(&Threshold, 90); // 100
	XThreshold2_Set_min_h(&Threshold, 55);  // 60
	XThreshold2_Set_max_s(&Threshold, 220); // 255
	XThreshold2_Set_min_s(&Threshold, 100);  // 20
	XThreshold2_Set_max_v(&Threshold, 150); // 255
	XThreshold2_Set_min_v(&Threshold, 60); // 150

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
	XProjection1_hls_Set_shrink_x_min(&Projection, 15); //15
	XProjection1_hls_Set_shrink_x_max(&Projection, 5);  // 5
	XProjection1_hls_Set_shrink_y_min(&Projection, 13); // 13
	XProjection1_hls_Set_shrink_y_max(&Projection, 13); // 13

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

	XProjection_mul_hls_InterruptGlobalDisable(&Projection_Mul);
	XProjection_mul_hls_EnableAutoRestart(&Projection_Mul);
	XProjection_mul_hls_Start(&Projection_Mul);
#endif

#ifdef XPAR_XPROJECTION_MUL_HLS_0_DEVICE_ID
	Status = XDraw_line_hls_Initialize(&Draw_Lines, XPAR_XPROJECTION_MUL_HLS_0_DEVICE_ID);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}
	else {
		xil_printf("Initialize the XDraw_line successfully\r\n");
	}

	XDraw_line_hls_Set_rows(&Draw_Lines, IMAGE_ROWS);
	XDraw_line_hls_Set_cols(&Draw_Lines, IMAGE_COLS);
	XDraw_line_hls_InterruptGlobalDisable(&Draw_Lines);
	XDraw_line_hls_EnableAutoRestart(&Draw_Lines);
	XDraw_line_hls_Start(&Draw_Lines);

#endif

#ifdef XPAR_XRESIZE_HLS_AXIS_0_DEVICE_ID
	Status = XResize_hls_axis_Initialize(&Resize, XPAR_XRESIZE_HLS_AXIS_0_DEVICE_ID);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}
	else {
		xil_printf("Initialize the XResize successfully\r\n");
	}

	XResize_hls_axis_Set_src_rows(&Resize, IMAGE_ROWS);
	XResize_hls_axis_Set_src_cols(&Resize, IMAGE_COLS);
	XResize_hls_axis_Set_dst_rows(&Resize, 28);
	XResize_hls_axis_Set_dst_cols(&Resize, 28);
	XResize_hls_axis_InterruptGlobalDisable(&Resize);
	XResize_hls_axis_EnableAutoRestart(&Resize);
	XResize_hls_axis_Start(&Resize);
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

#ifdef XPAR_OV_CMOS_IMAGE_PROCESS_AXI_GPIO_0_DEVICE_ID
	XGpio_Initialize(&Gpio_Sort, XPAR_OV_CMOS_IMAGE_PROCESS_AXI_GPIO_0_DEVICE_ID);
	XGpio_SetDataDirection(&Gpio_Sort, CHAR_INDEX_CHANNEL, 0xFFFFFFFF);
	// XGpio_SetDataDirection(&Gpio_Sort, CHAR_DIFF_CHANNEL, 0xFFFFFFFF);
	// XGpio_InterruptGlobalDisable(&Gpio_Sort); // this gpio doesn't have a interrupt controller
#endif

	return 0;
}

/* Interrupt Handler */
void XResize_InterruptHandler(void)
{
#ifdef XPAR_XRESIZE_HLS_AXIS_0_DEVICE_ID
	XResize_hls_axis_InterruptClear(&Resize, 1);
//	XResize_hls_Start(&Resize);
//	xil_printf("test\r\n");
#endif
}

void XContrast_InterruptHandler(void)
{
#ifdef XPAR_XCONTRAST_HLS_ROM_0_DEVICE_ID
	XContrast_hls_rom_InterruptClear(&Contrast, 1);
//	XResize_hls_Start(&Resize);
//	xil_printf("test\r\n");
#endif
}

void XSort_InterruptHandler(void)
{
#ifndef DEBUG
	Sort_Flag = 1;
	char_index = XGpio_DiscreteRead(&Gpio_Sort, CHAR_INDEX_CHANNEL);
	// char_diff = XGpio_DiscreteRead(&Gpio_Sort, CHAR_DIFF_CHANNEL);
	xil_printf("char is %d\r\n", char_index);
//	XContrast_hls_rom_InterruptClear(&Contrast, 1);
//	XResize_hls_Start(&Resize);
//	xil_printf("test\r\n");
#endif
}

void XPlate_InterruptHandler(void)
{
	show_plate_flag = 1;
	char_index = XGpio_DiscreteRead(&Gpio_Sort, CHAR_INDEX_CHANNEL);
	xil_printf("char is %d\r\n", char_index);
}

int Image_Interrupt_setup(void)
{
	int Status;
#ifndef DEBUG
	// XScuGic_Connect(IntcInstancePtr, XPAR_FABRIC_RESIZE_HLS_AXIS_0_VEC_ID,
	// 		   (Xil_ExceptionHandler)XResize_InterruptHandler,
	// 		   &Resize);
	// XScuGic_Connect(IntcInstancePtr, XPAR_FABRIC_CONTRAST_HLS_ROM_0_VEC_ID,
	// 		   (Xil_ExceptionHandler)XContrast_InterruptHandler,
	// 		   &Contrast);
	// XScuGic_Connect(IntcInstancePtr, XPAR_FABRIC_SORT_0_INTERRUPT_INTR,
	// 		   (Xil_ExceptionHandler)XSort_InterruptHandler,
	// 		   NULL);

	// XScuGic_SetPriorityTriggerType(IntcInstancePtr, XPAR_FABRIC_SORT_0_INTERRUPT_INTR, 0x00, 0x03); // 0x03 边沿触发

	// XScuGic_Enable(IntcInstancePtr, XPAR_FABRIC_RESIZE_HLS_AXIS_0_VEC_ID);
	// XScuGic_Enable(IntcInstancePtr, XPAR_FABRIC_CONTRAST_HLS_ROM_0_VEC_ID);
	// XScuGic_Enable(IntcInstancePtr, XPAR_FABRIC_SORT_0_INTERRUPT_INTR);

	NVIC_DisableIRQ(HLS_RESIZE_IRQn);
	NVIC_DisableIRQ(HLS_SORT_IRQn);
	NVIC_DisableIRQ(HLS_CONTRAST_IRQn);

	NVIC_EnableIRQ(Plate_IRQn);

	XResize_hls_axis_InterruptGlobalDisable(&Resize);
	// XResize_hls_axis_InterruptDisable(&Resize, 1);

	XContrast_hls_rom_InterruptGlobalDisable(&Contrast);
	// XContrast_hls_rom_InterruptEnable(&Contrast, 1);
#endif
	return XST_SUCCESS;

}

void plate_fsm(void)
{
// 	int i = 0;

// 	if (Sort_Flag)
// 	{
// 		if (char_index == 10 && char_diff <= POINT_MAX_DIFF) // 如果当前的字符是点
// 		{
// 			char_addr = 0;
// 			v_char_index_now[char_addr] = char_index;
// 			v_char_diff_now[char_addr] = char_diff;
// 		}
// 		else
// 		{
// 			v_char_index_last[char_addr] = v_char_index_now[char_addr]; // 保存上次结果
// //			v_char_diff_last[char_addr] = v_char_diff_now[char_addr];

// 			char_addr = (char_addr < (CHAR_NUM - 1)) ? char_addr + 1 : char_addr;

// 			v_char_index_now[char_addr] = char_index;                   // 保存当前结果
// 			v_char_diff_now[char_addr] = char_diff;

// 			if (((char_addr >= 0) && (char_addr <= 6)) && (v_char_index_last[char_addr] != v_char_index_now[char_addr]))
// 			{
// 				frame_count = 0;
// 			}

// 			if (char_addr == CHAR_NUM - 1)
// 			{
// 				if (frame_count < FRAME_NUM)
// 				{
// 					frame_count++;
// 					recognize_done = 0;
// 				}
// 				else if (frame_count == FRAME_NUM)
// 				{
// 					frame_count++;
// 					recognize_done = 1;
// 					show_plate_flag = 1; // 通知显示函数
// 				}
// 				else
// 				{
// 					recognize_done = 1;
// 				}
// 			}

// //			xil_printf("frame_count = %d\r\n", frame_count);

// #ifdef DEBUG
// 			if ((char_addr == (CHAR_NUM - 1)))
// 			{
// 				xil_printf("plate %2d:\r\n", palte_count++);
// 				for (i = 0; i < 8; i++)
// 				{
// 					xil_printf("%4d ", v_char_index_now[i]);
// 				}
// 				xil_printf("\r\n different is:\r\n");
// 				for (i = 0; i < 8; i++)
// 				{
// 					xil_printf("%4d ", v_char_diff_now[i]);
// 				}
// 				xil_printf("\r\n \r\n");
// 			}
// #endif
// 		}
// 		Sort_Flag = 0;
// 	}
}

void show_plate(void)
{
	int i = 0;
	volatile u8 isdiff = 0;
	u32 char_index_tt = 0;

	if ((char_index_t & 0xfffff000) != (char_index & 0xfffff000))
	{
		isdiff = 1;
		char_index_t = char_index;
		char_index_tt = char_index_t;
		for (i = 0; i < 8; i++)
		{
			v_char_index_now[i] = char_index_tt & 0x000F;
			char_index_tt = char_index_tt >> 4;
		}
	}
	else
	{
		isdiff = 0;
	}

#ifdef LCD_SHOW
	if ((show_plate_flag == 1)&&(isdiff == 1))               //if识别到新的车牌号
	{
		for (i = 0; i < 5; i++)			         //把数组或字母转化为ASCII存放到array_dis中
		{
			array_dis[i] = v_char_index_now[i + 3] + 48;
		}
		array_dis[5] = '\0';
		if (rows == 10) {													 //将20个数分成10行2列显示，第一列满 到第二列，第二列满 清屏从头开始
			if (columns == 0) {
				rows = 0; columns++;
				LCD_ShowString(columns * 160 + 50, 48 * rows + 18, array_dis, BLUE);
			}
			else {
				LCD_Clear(WHITE);
				columns = 0; rows = 0;
				LCD_ShowString(columns * 160 + 50, 48 * rows + 18, array_dis, BLUE);
			}
		}
		else {
			LCD_ShowString(columns * 160 + 50, 48 * rows + 18, array_dis, BLUE);
			rows++;
		}

		/* print to console */
		xil_printf("plate %2d:\r\n", palte_count++);
		for (i = 0; i < 8; i++)
		{
			xil_printf("%4d ", v_char_index_now[i]);
		}
		// xil_printf("\r\n different is:\r\n");
		// for (i = 0; i < 8; i++)
		// {
		// 	xil_printf("%4d ", v_char_diff_now[i]);
		// }
		xil_printf("\r\n \r\n");

		show_plate_flag = 0;
	}
#else
	if ((show_plate_flag == 1)&&(isdiff == 1))
	{

		/* print to console */
		xil_printf("plate %2d:\r\n", palte_count++);
		for (i = 0; i < 8; i++)
		{
			xil_printf("%4d ", v_char_index_now[i]);
		}
		// xil_printf("\r\n different is:\r\n");
		// for (i = 0; i < 8; i++)
		// {
		// 	xil_printf("%4d ", v_char_diff_now[i]);
		// }
		xil_printf("\r\n \r\n");

		isdiff = 0;
		show_plate_flag = 0;
	}
#endif
}


/* Interrupt Handler */
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
