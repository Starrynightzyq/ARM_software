#ifndef IMAGE_H
#define IMAGE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "xparameters.h"
#include "xil_types.h"

#if defined(XPAR_AXIS_SWITCH_0_DEVICE_ID) || defined(XPAR_AXIS_SWITCH_1_DEVICE_ID)
#include "xaxis_switch.h"
#endif

int Initialize_image_process(void);

#if defined(XPAR_AXIS_SWITCH_0_DEVICE_ID) || defined(XPAR_AXIS_SWITCH_1_DEVICE_ID)
int AxisSwitch_Choose(XAxis_Switch *XAxis_Switch, u8 MiIndex, u8 SiIndex);
#endif

#ifdef __cplusplus
}
#endif

#endif