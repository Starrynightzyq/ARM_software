/*
 * uart16550.h
 *
 *  Created on: 2019年7月5日
 *      Author: admin
 */

#ifndef SRC_UART16550_UART16550_H_
#define SRC_UART16550_UART16550_H_

#include "xuartns550.h"

#define BAUD_RATE 9600
#define FIFO_THRESHOLD XUN_FIFO_TRIGGER_14

/**************************** Type Definitions ********************************/

/************************** Function Prototypes *******************************/

int UartNs550_Initialize(void);

u32 UartNs550_0_Receive(u8 *BufferPtr, unsigned int NumBytes);

u32 UartNs550_0_Send(u8 *BufferPtr, unsigned int NumBytes);

int UartNs550_0_IsSending(void);

#endif /* SRC_UART16550_UART16550_H_ */
