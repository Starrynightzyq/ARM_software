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
 * File:     uart.c
 * Release Information : Cortex-M3 DesignStart-r0p0-00rel0
 * ----------------------------------------------------------------
 *
 */

/*
 * --------Included Headers--------
 */
/*
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
*/

#include "m3_for_arty.h"        // Project specific header
#include "uart.h"
// #include "gpio.h"

// #include "uart_stdout.h"

// #include "platform.h"
#include "xparameters.h"
#include "xuartlite.h"

// Instance of the UART, local to this module
static XUartLite UART0_instance;
static XUartLite UART_Keyboard;

/*
 * The following counters are used to determine when the entire buffer has
 * been sent and received.
 */
static volatile int TotalReceivedCount;
static volatile int TotalSentCount;

#define UART_BUFFER_SIZE        256

u8 UARTSendBuffer[UART_BUFFER_SIZE];
u8 UARTReceiveBuffer[UART_BUFFER_SIZE];

int InitialiseUART( void )
{
    int Status;

    /*
    * Initialize the UartLite driver so that it's ready to use.
    */
    Status = XUartLite_Initialize(&UART0_instance, XPAR_UARTLITE_0_DEVICE_ID);
    if (Status != XST_SUCCESS) {
        return XST_FAILURE;
    }

    Status = XUartLite_Initialize(&UART_Keyboard, XPAR_UARTLITE_1_DEVICE_ID);
    if (Status != XST_SUCCESS) {
        return XST_FAILURE;
    }

    /*
    * Setup the handlers for the UartLite that will be called from the
    * interrupt context when data has been sent and received, specify a
    * pointer to the UartLite driver instance as the callback reference so
    * that the handlers are able to access the instance data.
    */
    XUartLite_SetSendHandler(&UART0_instance, SendHandler, &UART0_instance);
    XUartLite_SetRecvHandler(&UART0_instance, RecvHandler, &UART0_instance);

    XUartLite_SetSendHandler(&UART_Keyboard, SendHandler_Keyboard, &UART_Keyboard);
    XUartLite_SetRecvHandler(&UART_Keyboard, RecvHandler_Keyboard, &UART_Keyboard);

    /*
    * Start receiving data before sending it since there is a loopback.
    */
    XUartLite_Recv(&UART0_instance, UARTReceiveBuffer, UART_BUFFER_SIZE);

    return XST_SUCCESS;
}

void SendHandler(void *CallBackRef, unsigned int EventData)
{
    TotalSentCount = EventData;
}

void RecvHandler(void *CallBackRef, unsigned int EventData)
{
    TotalReceivedCount = EventData;
}


void SendHandler_Keyboard(void *CallBackRef, unsigned int EventData)
{
}

void RecvHandler_Keyboard(void *CallBackRef, unsigned int EventData)
{
}

int CheckUARTRxBytes( void )
{
    static int  BytesRx;
    int         Diff;
    
    Diff = TotalReceivedCount - BytesRx;
    
    if ( Diff )
        BytesRx = TotalReceivedCount;
    
    return Diff;
}


void EnableUARTInterrupts( void )
{
    XUartLite_EnableInterrupt(&UART0_instance);
    XUartLite_EnableInterrupt(&UART_Keyboard);
}



// Define the UART interrupt handler here
void UART0_Handler ( void )
{
    XUartLite_InterruptHandler(&UART0_instance);
    NVIC_ClearPendingIRQ(UART0_IRQn);

    // Test to indicate when the IRQ is called
    // Used to detect received characters
    // IncLeds();

}

void UART_Keyboard_Handler ( void )
{
    XUartLite_InterruptHandler(&UART_Keyboard);
    NVIC_ClearPendingIRQ(UART_KEY_IRQn);

    // Test to indicate when the IRQ is called
    // Used to detect received characters
    // IncLeds();

}

unsigned int UART_Keyboard_Send(u8 *DataBufferPtr, unsigned int NumBytes)
{
    unsigned int BytesSent;
    BytesSent = XUartLite_Send(&UART_Keyboard, DataBufferPtr, NumBytes);
    return BytesSent;
}

