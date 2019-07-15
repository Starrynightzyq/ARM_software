/*
 * switch.c
 *
 *  Created on: 2019年6月19日
 *      Author: admin
 */
#include "switch.h"
#include "xil_printf.h"
#include "xaxis_switch.h"

static XAxis_Switch axis_sw_src;
static XAxis_Switch axis_sw_dst;

volatile u32 current_sw;	// 当前 sw_gpio 的值

void Switch_Init_l(XAxis_Switch *InstancePtr, u16 dev_id)
{
	XAxis_Switch_Config *Config;
	XStatus Status;

	Config = XAxisScr_LookupConfig(dev_id);
	if (NULL == Config) {
		xil_printf("Find axis switch %d failed!\r\n", dev_id);
	}

	Status = XAxisScr_CfgInitialize(InstancePtr, Config,
	                                Config->BaseAddress);
	if (Status != XST_SUCCESS) {
		xil_printf("Initialize axis switch %d failed!\r\n", dev_id);
	}
	else {
		xil_printf("Initialize axis switch %d successfully!\r\n", dev_id);
	}
}

void changeSlaveChannel_l(XAxis_Switch *InstancePtr, u8 slave_ch)
{
	XAxisScr_RegUpdateDisable(InstancePtr);
	XAxisScr_MiPortDisableAll(InstancePtr);
	XAxisScr_MiPortEnable(InstancePtr, 0, slave_ch);
	XAxisScr_RegUpdateEnable(InstancePtr);
}

void changeMasterChannel_l(XAxis_Switch *InstancePtr, u8 master_ch)
{
	XAxisScr_RegUpdateDisable(InstancePtr);
	XAxisScr_MiPortDisableAll(InstancePtr);
	XAxisScr_MiPortEnable(InstancePtr, master_ch, 0);
	XAxisScr_RegUpdateEnable(InstancePtr);
}

void Switch_Init(void)
{
	Switch_Init_l(&axis_sw_src, XPAR_AXIS_SWITCH_0_DEVICE_ID);
	Switch_Init_l(&axis_sw_dst, XPAR_AXIS_SWITCH_1_DEVICE_ID);
}

void SetDefaultChannel(u8 default_ch)
{
	changeMasterChannel_l(&axis_sw_src, default_ch);
	changeSlaveChannel_l(&axis_sw_dst, default_ch);
}

void updateChannel(u32 sw)
{
	// u32 sw;
	// sw = Switch_Gpio_Read();
	if (sw > (MAX_CHANNEL - 1))
	{
		sw = 0;
	}

	if (sw != current_sw)
	{
		xil_printf("sw gpio is %x\r\n", sw);
		current_sw = sw;
		changeMasterChannel_l(&axis_sw_src, sw);
		changeSlaveChannel_l(&axis_sw_dst, sw);
	}
}
