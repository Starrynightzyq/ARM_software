#include "image.h"
#include "xparameters.h"
#include "xstatus.h"

#ifdef XPAR_XTHRESHOLD2_0_DEVICE_ID
#include "xthreshold2.h"
#endif

#ifdef XPAR_XHLS_SATURATION_ENHANCE_0_DEVICE_ID
#include "xhls_saturation_enhance.h"
#endif

#ifdef XPAR_OV_CMOS_IMAGE_PROCESS_PROJECTION_0_DEVICE_ID
#include "Projection.h"
#endif

#if defined(XPAR_AXIS_SWITCH_0_DEVICE_ID) || defined(XPAR_AXIS_SWITCH_1_DEVICE_ID)
#include "xaxis_switch.h"
#endif

#ifdef XPAR_XTHRESHOLD2_0_DEVICE_ID
static XThreshold2 Threshold;
#endif

#ifdef XPAR_XHLS_SATURATION_ENHANCE_0_DEVICE_ID
static XHls_saturation_enhance Saturation_Enhance;
#endif

#ifdef XPAR_AXIS_SWITCH_0_DEVICE_ID
	XAxis_Switch Switch_0;
#endif

#ifdef XPAR_AXIS_SWITCH_1_DEVICE_ID
	XAxis_Switch Switch_1;
#endif

int Initialize_image_process(void) 
{
	int Status;

#if defined(XPAR_AXIS_SWITCH_0_DEVICE_ID) || defined(XPAR_AXIS_SWITCH_1_DEVICE_ID)
	XAxis_Switch_Config *Config;
#endif

#ifdef XPAR_AXIS_SWITCH_0_DEVICE_ID
	Config = XAxisScr_LookupConfig(XPAR_AXIS_SWITCH_0_DEVICE_ID);
	if (NULL == Config) {
		return XST_FAILURE;
	}

	Status = XAxisScr_CfgInitialize(&Switch_0, Config,
						Config->BaseAddress);
	if (Status != XST_SUCCESS) {
		xil_printf("AXI4-Stream-0 initialization failed.\r\n");
		return XST_FAILURE;
	}

	AxisSwitch_Choose(&Switch_0, 0, 0);
#endif

#ifdef XPAR_AXIS_SWITCH_1_DEVICE_ID
	Config = XAxisScr_LookupConfig(XPAR_AXIS_SWITCH_1_DEVICE_ID);
	if (NULL == Config) {
		return XST_FAILURE;
	}

	Status = XAxisScr_CfgInitialize(&Switch_1, Config,
						Config->BaseAddress);
	if (Status != XST_SUCCESS) {
		xil_printf("AXI4-Stream-1 initialization failed.\r\n");
		return XST_FAILURE;
	}

	AxisSwitch_Choose(&Switch_0, 0, 0);
#endif

#ifdef XPAR_XTHRESHOLD2_0_DEVICE_ID
	Status = XThreshold2_Initialize(&Threshold, XPAR_XTHRESHOLD2_0_DEVICE_ID);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}
	else {
		xil_printf("Initialize the XThreshold2 successfully\r\n");
	}

	XThreshold2_SetRows(&Threshold, 480);  // 480
	XThreshold2_SetCols(&Threshold, 640);  // 640
	
	XThreshold2_SetMax_h(&Threshold, 100); // 100
	XThreshold2_SetMin_h(&Threshold, 60);  // 60
	
	XThreshold2_SetMax_s(&Threshold, 255); // 255
	XThreshold2_SetMin_s(&Threshold, 20);  // 20
	
	XThreshold2_SetMax_v(&Threshold, 255); // 255
	XThreshold2_SetMin_v(&Threshold, 100); // 150
#endif

#ifdef XPAR_XHLS_SATURATION_ENHANCE_0_DEVICE_ID
	Status = XHls_saturation_enhance_Initialize(&Saturation_Enhance, XPAR_XHLS_SATURATION_ENHANCE_0_DEVICE_ID);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	XHls_saturation_enhance_Set_height(&Saturation_Enhance, 480);
	XHls_saturation_enhance_Set_width(&Saturation_Enhance, 640);
	XHls_saturation_enhance_Set_sat(&Saturation_Enhance, 0);
#endif

#ifdef XPAR_OV_CMOS_IMAGE_PROCESS_PROJECTION_0_DEVICE_ID
	PROJECTION_mWriteReg(XPAR_OV_CMOS_IMAGE_PROCESS_PROJECTION_0_DEVICE_ID, 
		PROJECTION_Ctrl_AXI_SLV_REG0_OFFSET, 100); // thresh_width_h
	PROJECTION_mWriteReg(XPAR_OV_CMOS_IMAGE_PROCESS_PROJECTION_0_DEVICE_ID, 
		PROJECTION_Ctrl_AXI_SLV_REG1_OFFSET, 100); // thresh_width_v
#endif

	return 0;
}

#if defined(XPAR_AXIS_SWITCH_0_DEVICE_ID) || defined(XPAR_AXIS_SWITCH_1_DEVICE_ID)
int AxisSwitch_Choose(XAxis_Switch *AxisSwitch, u8 MiIndex, u8 SiIndex)
{
	int Status;
	
	/* Disable register update */
	XAxisScr_RegUpdateDisable(AxisSwitch);

	/* Disable all MI ports */
	XAxisScr_MiPortDisableAll(AxisSwitch);

	/* Source SI[1] to MI[0] */
	// MiIndex = 0;
	// SiIndex = 1;
	XAxisScr_MiPortEnable(AxisSwitch, MiIndex, SiIndex);

	/* Enable register update */
	XAxisScr_RegUpdateEnable(AxisSwitch);

	/* Check for MI port enable */
	Status = XAxisScr_IsMiPortEnabled(AxisSwitch, MiIndex, SiIndex);
	if (Status) {
		xil_printf("MI[%d] is sourced from SI[%d].\r\n", MiIndex,
				SiIndex);
	}

	// /* Disable MI[MiIndex] */
	// XAxisScr_MiPortDisable(AxisSwitch, MiIndex);

	// /* Check for MI port enable */
	// Status = XAxisScr_IsMiPortEnabled(AxisSwitch, MiIndex, SiIndex);
	// if (!Status) {
	// 	xil_printf("MI[%d] is not sourced from SI[%d].\r\n", MiIndex,
	// 			SiIndex);
	// }

	return XST_SUCCESS;
}
#endif