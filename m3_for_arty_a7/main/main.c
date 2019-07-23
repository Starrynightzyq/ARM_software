/*
 * Copyright:
 * ----------------------------------------------------------------
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 *   (C) COPYRIGHT 2014, 2016 ARM Limited
 *       ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 * ----------------------------------------------------------------
 * File:     main.c
 * Release Information : Cortex-M3 DesignStart-r0p0-00rel0
 * ----------------------------------------------------------------
 *
 */

/*
 * --------Included Headers--------
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Xilinx specific headers
#include "xparameters.h"
#include "xgpio.h"
#include "sleep.h"

#include "m3_for_arty.h"        // Project specific header
#include "gpio.h"
#include "uart.h"
#include "spi.h"
#include "iic.h"
#include "vdma.h"
#include "cmos.h"
#include "image.h"
#include "timer.h"
#include "spi_my.h"
#include "lcd.h"
#include "switch.h"
#include "uart16550.h"

#include "gizwits_product.h"
#include "common.h"

// extern u8 keyboard_space[12];
// extern u8 keyboard_up[12];
extern u8 Lcd_Clr_Flag;

// #define SIM_BUILD
// #define DEBUG
// #define DDR_TEST
#define GIZ
/*******************************************************************/

int main (void)
{
    // Define local variables
    int     status;
    int     DAPLinkFittedn;
    int     i;
    int     readbackError;
    char    debugStr[256];

    // Illegal location
    volatile u32 emptyLoc;
    volatile u32 QSPIbase;

    // CPU ID register
    volatile u32 *pCPUId = (u32 *)0xE000ED00;
    volatile u32 CPUId;
    int          CPU_part;
    int          CPU_rev;
    int          CPU_var;
    char         CPU_name[20];

    // Enable the following if you wish to test illegal accesses
    // and debug lock-up conditions
    /*
        u32 *pLegalAddr   = (u32 *)0x40120000;
        u32 *pIllegalAddr = (u32 *)0x40200000;
    */

    // Initialise the UART
    InitialiseUART();

    // Iniyialise the UART16550
    UartNs550_Initialize();

    // Initialise the IIC
#ifndef DEBUG
    InitialiseIIC();
#endif

    // Initialize the LCD SPI controler
    Lcd_Spi_Initialize();

    // Clear all interrupts
    NVIC_ClearAllPendingIRQ();

    // Initialise the GPIO
    status = InitialiseGPIO();
    if (status != XST_SUCCESS)  {
        print("Error - Xilinx GPIO failed to initialise\n");
    }

    // Enable GPIO Interrupts
    NVIC_EnableIRQ(GPIO0_IRQn);
    // NVIC_DisableIRQ(GPIO1_IRQn); // GPIO1 连接 CMOS_PWDN CMOS_RST
    EnableGPIOInterrupts();

    // Enable UART Interrupts
    NVIC_EnableIRQ(UART0_IRQn);
    NVIC_EnableIRQ(UART_KEY_IRQn);
    EnableUARTInterrupts();

    // Enable UART16550 Interrupts
    NVIC_EnableIRQ(UartNs0_IRQn);

    // Enable IIC Interrupts
    NVIC_EnableIRQ(IIC0_IRQn);
    // NVIC_DisableIRQ(IIC1_IRQn);

    // Enable SPI Interrupts
    NVIC_EnableIRQ(LCD_SPI_IRQn);

    // Read the DAPLinkFitted input, (assigned to IRQ[31]).
    // Note the IRQ is never enabled, so polling the pending register will indicate the status
    NVIC_DisableIRQ(DAPLinkFittedn_IRQn);
    DAPLinkFittedn = NVIC_GetPendingIRQ( DAPLinkFittedn_IRQn );

    // Set DAPLink QSPI to the normal read-write controller
    // Do NOT do this for code running from the DAPLink QSPI.  This will switch from the XIP QSPI
    // controller to the standard controller, so the processor will not be able to access it's code image
    // This should only be done if the XIP QSPI is used to copy code to internal TCM, then boot-load from that TCM
//    SetDAPLinkQSPIMode( QSPI_QSPIMODE );

    // Read the CPU ID register to auto-detect the CPU and revision
    // Note however that code is compiled for a specific processor, so even though
    // the processor can be auto-detected, if the compiled code has extended commands not
    // supported by the processor, then runtime issues can occur
    CPUId    = *pCPUId;
    CPU_var  = ((CPUId & 0x00F00000) >> 20);
    CPU_part = ((CPUId & 0x0000FFF0) >> 4);
    CPU_rev  = CPUId & (0x0000000F);

    switch (CPU_part)
    {
    case 0xC21 : strcpy(  CPU_name, "Cortex-M1" ); break;
    case 0xC23 : strcpy(  CPU_name, "Cortex-M3" ); break;
    default    : sprintf( CPU_name, "Unknown %x", CPU_part );
    }

    sprintf (debugStr, "Arm %s Revision %i Variant %i\r\n\n", CPU_name, CPU_rev, CPU_var );

#ifndef SIM_BUILD
    // Use Xilinx version print command
    print ("************************************\r\n");
    print ( debugStr );
    print ("Example design for Digilent A7 board\r\n");
    if ( DAPLinkFittedn )
        print ("\nV2C-DAPLink board not detected\r\n");
    else
        print ("\nV2C-DAPLink board detected\r\n");
    print ("Use DIP switches and push buttons to\r\ncontrol LEDS\r\n");
    print (" Version 2.0\r\n");
    print ("************************************\r\n");
#else
    print ( debugStr );
#endif

    // *****************************************************
    // Test the DDRmemory
    // *****************************************************
#ifdef DDR_TEST
    for ( i = 0; i < (sizeof(bram_data) / sizeof(u32)); i++)
        *DDRmemory++ = bram_data[i];
    readbackError = 0;
    // Reset the pointer
    DDRmemory = (u32 *)XPAR_MIG7SERIES_0_BASEADDR;

    // Readback
    for ( i = 0; i < (sizeof(bram_data) / sizeof(u32)); i++)
    {
        if ( *DDRmemory++ != bram_data[i] )
            readbackError++;
    }

    if ( readbackError )
        print( "ERROR - DDR readback corrupted.\r\n" );
    else
        print( "DDR readback correct\r\n" );
#endif

#ifndef DEBUG
    Initialize_image_process();
    Image_Interrupt_setup();
#endif

    // Initialize the AXIS_SWITCH
#ifndef DEBUG
    Switch_Init();
    SetDefaultChannel(0);
#endif

    // Initialize the ov5640 cmos
#ifndef DEBUG
    sensor_init();
#endif

    // Initialize the VDMA
#ifndef DEBUG
    Video_Buffer_Initialize(); // Initialize the video buffer
    VDMA_Config();
#endif

    // timer 0 initialize
    Timer0_Initialise(50000);
    EnableTIMER0Interrupts();
    // DisableTIMER0Interrupts();

    /* Initialize the LCD screen */
#ifndef DEBUG
    Lcd_Init();
    LCD_Clear(WHITE);
#endif

#ifdef GIZ

    userInit();

    gizwitsInit();

#endif

    // Main loop.  Handle LEDs and switches via interrupt
    xil_printf("Initialize all successful, start the main loop\r\n");
    xil_printf("test start\r\n");
    while ( 1 )
    {
        /* Main loop. Wait for interrupts to occur */
        /*
        if ( CheckUARTRxBytes() != 0 )
            print ("x");
        */
        // sleep(10);
        // xil_printf("1s\r\n");

        // test spi send
        // Lcd_Spi_Write_Byte(0x5a);
        // Get_Hsv();
        // plate_fsm();

#ifndef DEBUG
        show_plate();
#endif

        if (Lcd_Clr_Flag)
        {
            LCD_Clear(WHITE);
            Lcd_Clr_Flag = 0;
        }

#ifdef GIZ

        userHandle();

        gizwitsHandle((dataPoint_t *)&currentDataPoint);
#endif

        // UartNs550_0_Send(keyboard_space, 12);
    }
}

/* Interrupt handler for DAPLink Fitted */
// This routine should never be called as the signal is used as IO
// Routine created to prevent exceptions in the case the IRQ is enabled
void DAPLinkFittedn ( void )
{
    // Clear the IRQ and disable any future IRQs
    NVIC_ClearPendingIRQ(DAPLinkFittedn_IRQn);
    NVIC_DisableIRQ(DAPLinkFittedn_IRQn);
}
