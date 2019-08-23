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
 * File:     gpio.c
 * Release Information : Cortex-M3 DesignStart-r0p0-00rel0
 * ----------------------------------------------------------------
 *
 */

/*
 * --------Included Headers--------
 */

#include "gpio.h"
#include "xparameters.h"        // Project memory and device map
#include "xgpio.h"              // Xilinx GPIO routines
#include "peripherallink.h"     // IRQ definitions
#include "switch.h"
#include "gizwits_product.h"
#include "lcd.h"
#include "delay.h"
#include "image.h"

/************************** Variable Definitions **************************/
/*
 * The following are declared static to this module so they are zeroed and so they are
 * easily accessible from a debugger
 *
 * Also they are initialised in main, but accessed by the IRQ routines
 */

extern int plate_counter; // 识别到的车牌数, 定义在 image.c
extern u8 recognize_on;
extern u8 read_pointer;

static XGpio Gpio_Led_DIPSw;   /* The driver instance for GPIO Device 0 */
static XGpio Gpio_Cmos_Ctrl;   /* The driver instance for GPIO Device 1 */
static XGpio Gpio_DAPLink;     /* The driver instance for the DAPLink GPIO */
static XGpio Gpio_Lcd;         /* The driver instance for the lcd gpio, [2:0] = {BLK,RES,DC} */
static XGpio Gpio_ApCtrl;

/*****************************************************************************/

volatile u8 Lcd_Clr_Flag = 0;

// Initialise the GPIO and zero the outputs
int InitialiseGPIO( void )
{
    // Define local variables
    int status;

    /*
     * Initialize the GPIO driver so that it's ready to use,
     * specify the device ID that is generated in xparameters.h
    */
    status = XGpio_Initialize(&Gpio_Led_DIPSw, XPAR_AXI_GPIO_0_DEVICE_ID);
    if (status != XST_SUCCESS)  {
        return XST_FAILURE;
    }

    status = XGpio_Initialize(&Gpio_Cmos_Ctrl, XPAR_OV_CMOS_CMOS2AXIS_AXI_GPIO_1_DEVICE_ID);
    if (status != XST_SUCCESS)  {
        return XST_FAILURE;
    }

    status = XGpio_Initialize(&Gpio_Lcd, XPAR_LCD_AXI_GPIO_1_DEVICE_ID);
    if (status != XST_SUCCESS)  {
        return XST_FAILURE;
    }

    status = XGpio_Initialize(&Gpio_ApCtrl, XPAR_OV_CMOS_IMAGE_PROCESS_GPIO_AP_CTRL_DEVICE_ID);
    if (status != XST_SUCCESS)  {
        return XST_FAILURE;
    }

    // GPIO0
    // Port0 drives led_4bits.  Set bottom 4 UART ports to be outputs.
    XGpio_SetDataDirection(&Gpio_Led_DIPSw, ARTY_A7_LED_CHANNEL, 0xFFFFFFF0);
//    ARTY_A7_GPIO0->TRI0 = 0xfffffff0;

    // Port 1 inputs the dip switches. Set to be inputs
    XGpio_SetDataDirection(&Gpio_Led_DIPSw, ARTY_A7_DIP_CHANNEL, 0xFFFFFFFF);
//    ARTY_A7_GPIO0->TRI1 = 0xffffffff;

    // GPIO1
    // Port 0 drives cmos_pwdn.  all output.
    XGpio_SetDataDirection(&Gpio_Cmos_Ctrl, CMOS_PWDN_CHANNEL, 0x00000000);
    // Port 1 drives cmos_rst.  all output.
    XGpio_SetDataDirection(&Gpio_Cmos_Ctrl, CMOS_RST_CHANNEL, 0x00000000);

    // DAPLink GPIO
    // Single channel, all output.
    XGpio_SetDataDirection(&Gpio_Lcd, 1, 0x00000000);

    // Ap Ctrl Gpio
    XGpio_SetDataDirection(&Gpio_ApCtrl, 1, 0x00000000);

    // Default value of cmos_pwdn and cmos_rst
    XGpio_DiscreteWrite(&Gpio_Cmos_Ctrl, CMOS_PWDN_CHANNEL, 0x1); // pwdn works high
    delay_ms(10);
    XGpio_DiscreteWrite(&Gpio_Cmos_Ctrl, CMOS_PWDN_CHANNEL, 0x0); // pwdn works high
    delay_ms(10);
    XGpio_DiscreteWrite(&Gpio_Cmos_Ctrl, CMOS_RST_CHANNEL, 0x0);  // rst works low
    delay_ms(10);
    XGpio_DiscreteWrite(&Gpio_Cmos_Ctrl, CMOS_RST_CHANNEL, 0x1);  // rst works low
//    ARTY_A7_GPIO1->DATA0 = 0x0;

    // Write 0xA to LEDs
    XGpio_DiscreteWrite(&Gpio_Led_DIPSw, ARTY_A7_LED_CHANNEL, 0x0);
//    ARTY_A7_GPIO0->DATA0 = 0x0;

//
    XGpio_DiscreteWrite(&Gpio_Lcd, 1, 0x00000000);

    return XST_SUCCESS;

}

// Set GPIO interrupts
void EnableGPIOInterrupts( void )
{
    // Push buttons and DIP switches are on Channel 2
    // XGpio_InterruptEnable(&Gpio_Cmos_Ctrl, XGPIO_IR_CH2_MASK);
    XGpio_InterruptEnable(&Gpio_Led_DIPSw, XGPIO_IR_CH2_MASK);

    // Having enabled the M1 to handle the interrupts, now enable the GPIO to send the interrupts
    // XGpio_InterruptGlobalEnable(&Gpio_Cmos_Ctrl);
    XGpio_InterruptGlobalEnable(&Gpio_Led_DIPSw);
}


// Define the GPIO interrupt handlers
void GPIO0_Handler ( void )
{
    volatile uint32_t gpio_dip_switches;

    Gpio_Image_Clr();

    // Read dip switches, change LEDs to match
    gpio_dip_switches = XGpio_DiscreteRead(&Gpio_Led_DIPSw, ARTY_A7_DIP_CHANNEL);   // Capture DIP status
    XGpio_DiscreteWrite(&Gpio_Led_DIPSw, ARTY_A7_LED_CHANNEL, gpio_dip_switches);   // Set LEDs

    // clear the plate_counter
    if (!((gpio_dip_switches >> 1) & 0x01))
    {
        plate_counter = 0;
        // read_pointer = 0;
        // Clear_Buffer_Valid_Flag();
    }
    // set the AXIS_SWITCH
    updateChannel((gpio_dip_switches >> 2) & 0x01); // the second sw control the channel  ((gpio_dip_switches >> 1) & 0x03)

    recognize_on = ((gpio_dip_switches >> 1) & 0x01);

    // clear lcd
    if ((gpio_dip_switches >> 3) & 0x01)
    {
        plate_counter = 0;
        read_pointer = 0;
        Lcd_Clr_Flag = 1;
    }

    // GIZ
    // switch((gpio_dip_switches) & 0x07) {
    //     case 0x01: gizwitsSetMode(WIFI_RESET_MODE); xil_printf("WIFI_RESET_MODE\r\n"); break;
    //     case 0x02: gizwitsSetMode(WIFI_SOFTAP_MODE); xil_printf("WIFI_SOFTAP_MODE\r\n"); break;
    //     case 0x04: gizwitsSetMode(WIFI_AIRLINK_MODE); xil_printf("WIFI_AIRLINK_MODE\r\n"); break;
    //     default: break;
    // }
    if (gpio_dip_switches & 0x01)
    {
        gizwitsSetMode(WIFI_SOFTAP_MODE); xil_printf("WIFI_SOFTAP_MODE\r\n");
    }

    // Clear interrupt from GPIO
    XGpio_InterruptClear(&Gpio_Led_DIPSw, XGPIO_IR_MASK);
    // Clear interrupt in NVIC
    NVIC_ClearPendingIRQ(GPIO0_IRQn);
}

void GPIO1_Handler ( void )
{
    /*
        int mask, led_val, incr;
        volatile uint32_t gpio_push_buttons;
        volatile uint32_t gpio_leds_rgb;

        // For LEDs, cycle around colour each time respective push button is pressed
        // Only change if a pushbutton is pressed.
        // This prevents a double change as the button is released.
        if( XGpio_DiscreteRead(&Gpio_Cmos_Ctrl, CMOS_RST_CHANNEL) != 0 )
        {
            // LEDs are on a 3 spacing.  So multiply button press by 2^3 to increment the correct LED
            gpio_push_buttons = XGpio_DiscreteRead(&Gpio_Cmos_Ctrl, CMOS_RST_CHANNEL);
            gpio_leds_rgb     = XGpio_DiscreteRead(&Gpio_Cmos_Ctrl, CMOS_PWDN_CHANNEL);
            if ( gpio_push_buttons & 0x1 ) {
                    mask = 0x7;
                    incr = 0x1;
            } else if ( gpio_push_buttons & 0x2 ) {
                    mask = (0x7 << 3);
                    incr = (0x1 << 3);
            } else if ( gpio_push_buttons & 0x4 ) {
                    mask = (0x7 << 6);
                    incr = (0x1 << 6);
            } else if ( gpio_push_buttons & 0x8 ) {
                    mask = (0x7 << 9);
                    incr = (0x1 << 9);
            }

            led_val = gpio_leds_rgb & mask;
            led_val = (led_val+incr) & mask;
            gpio_leds_rgb = (gpio_leds_rgb & ~mask) | led_val;

            XGpio_DiscreteWrite(&Gpio_Cmos_Ctrl, CMOS_PWDN_CHANNEL, gpio_leds_rgb);
        }

        // Clear interrupt from GPIO
        XGpio_InterruptClear(&Gpio_Cmos_Ctrl, XGPIO_IR_MASK);
        // Clear interrupt in NVIC
        NVIC_ClearPendingIRQ(GPIO1_IRQn);
    */
}

/* Note : No interrupt handler for DAPLink GPIO, it does not have the IRQ line connected
          No requirement as it is only a toggle between QSPI XIP and QSPI normal controllers
          Instead, standard routine provided
*/

void SetDAPLinkQSPIMode( u32 mode )
{
    // Set the qspi_sel line
    // XGpio_DiscreteWrite(&Gpio_DAPLink, ARTY_A7_DAPLINK_GPIO_CHANNEL, mode);

}

void IncLeds( void )
{
    // Routine to allow other blocks to indicate activity
    volatile uint32_t gpio_dip_switches;

    // Read dip switches, change LEDs to match
    gpio_dip_switches = XGpio_DiscreteRead(&Gpio_Led_DIPSw, ARTY_A7_DIP_CHANNEL);   // Capture DIP status
    XGpio_DiscreteWrite(&Gpio_Led_DIPSw, ARTY_A7_LED_CHANNEL, (gpio_dip_switches + 1)); // Set LEDs

}

void Gpio_Lcd_ResetBits(u8 pin)
{
    volatile u32 gpio_lcd_data;
    u32 mask;

    /*
     * 设一个操作数x有s位则循环左移n位的操作为：
     * (x << n) | (x >> (s - n));
     * 同理右移n位位:
     * (x >> n) | (x << (s - n));
     */
    mask = (0xFFFFFFFE << pin) | (0xFFFFFFFE >> (32 - pin));

    gpio_lcd_data = XGpio_DiscreteRead(&Gpio_Lcd, 1);

    XGpio_DiscreteWrite(&Gpio_Lcd, 1, (mask & gpio_lcd_data));//(mask & gpio_lcd_data)
}

void Gpio_Lcd_SetBits(u8 pin)
{
    volatile u32 gpio_lcd_data;
    u32 mask;

    /*
     * 设一个操作数x有s位则循环左移n位的操作为：
     * (x << n) | (x >> (s - n));
     * 同理右移n位位:
     * (x >> n) | (x << (s - n));
     */
    mask = (0x00000001 << pin) | (0x00000001 >> (32 - pin));

    gpio_lcd_data = XGpio_DiscreteRead(&Gpio_Lcd, 1);

    XGpio_DiscreteWrite(&Gpio_Lcd, 1, (mask | gpio_lcd_data));//(mask | gpio_lcd_data)
}

void Gpio_Image_Set(void)
{
    XGpio_DiscreteWrite(&Gpio_Led_DIPSw, ARTY_A7_LED_CHANNEL, 0xffff);   // Set LEDs
}

void Gpio_Image_Clr(void)
{
    XGpio_DiscreteWrite(&Gpio_Led_DIPSw, ARTY_A7_LED_CHANNEL, 0x0000);   // Set LEDs
}

void Ap_Start(void)
{
    u32 temp;
    XGpio_DiscreteWrite(&Gpio_ApCtrl, 1, 1);
}

