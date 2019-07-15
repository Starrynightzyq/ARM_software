/*
 * switch.h
 *
 *  Created on: 2019年6月19日
 *      Author: admin
 */

#ifndef SRC_AXIS_SWITCH_SWITCH_H_
#define SRC_AXIS_SWITCH_SWITCH_H_

#include "xil_types.h"

#define MAX_CHANNEL 2

// function to be used outside
void Switch_Init(void);

void SetDefaultChannel(u8 default_ch);
void updateChannel(u32 sw);

#endif /* SRC_AXIS_SWITCH_SWITCH_H_ */
