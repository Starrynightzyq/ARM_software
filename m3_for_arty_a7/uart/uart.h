/*
 * Copyright:
 * ----------------------------------------------------------------
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 *   (C) COPYRIGHT 2014, 2018 ARM Limited
 *       ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 * ----------------------------------------------------------------
 * File:     uart.h
 * Release Information : Cortex-M3 DesignStart-r0p0-00rel0
 * ----------------------------------------------------------------
 *
 */

#include "xil_types.h"

// Define the UART interrupt handler here
// Already defined in startup_CMSDK_CM1.s
// void UART0_Handler ( void );
int InitialiseUART( void );
void EnableUARTInterrupts( void );
int CheckUARTRxBytes( void );
void SendHandler(void *CallBackRef, unsigned int EventData);
void RecvHandler(void *CallBackRef, unsigned int EventData);
void SendHandler_Keyboard(void *CallBackRef, unsigned int EventData);
void RecvHandler_Keyboard(void *CallBackRef, unsigned int EventData);


unsigned int UART_Keyboard_Send(u8 *DataBufferPtr, unsigned int NumBytes);
void Keyboard_Space(void);

