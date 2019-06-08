#include "spi_my.h"
#include "xparameters.h"        /* EDK generated parameters */
#include "xspi.h"               /* SPI device driver */
#include "xil_printf.h"
#include "xil_types.h"
#include "m3_for_arty.h"        // Project specific header
#include "stdlib.h"

static XSpi Lcd_Spi;

/*
 * The following variables are shared between non-interrupt processing and
 * interrupt processing such that they must be global.
 */
volatile int TransferInProgress;

/*
 * The following variable tracks any errors that occur during interrupt
 * processing
 */
int Error;

void SpiHandler(void *CallBackRef, u32 StatusEvent, unsigned int ByteCount);

void Lcd_Spi_Transfer(u32 slave, u8 *SendBufPtr,
		  u8 *RecvBufPtr, unsigned int ByteCount);

int Lcd_Spi_Initialize(void)
{
	/*
	 * Initialize the SPI driver so that it is  ready to use.
	 */
	int Status;
	Status = XSpi_Initialize(&Lcd_Spi, XPAR_SPI_0_DEVICE_ID);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}
	else {
		xil_printf("LCD SPI Initialize successfully\r\n");
	}

	/*
	 * Setup the handler for the SPI that will be called from the interrupt
	 * context when an SPI status occurs, specify a pointer to the SPI
	 * driver instance as the callback reference so the handler is able to
	 * access the instance data
	 */
	XSpi_SetStatusHandler(&Lcd_Spi, &Lcd_Spi, (XSpi_StatusHandler)SpiHandler);

	/*
	 * Set the SPI device as a master and in manual slave select mode such
	 * that the slave select signal does not toggle for every byte of a
	 * transfer, this must be done before the slave select is set
	 */
	Status = XSpi_SetOptions(&Lcd_Spi, XSP_MASTER_OPTION |
					XSP_MANUAL_SSELECT_OPTION);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Select the slave on the SPI bus, the EEPROM device so that it can be
	 * read and written using the SPI bus
	 */
	Status = XSpi_SetSlaveSelect(&Lcd_Spi, LCD_SPI_SELECT);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Start the SPI driver so that interrupts and the device are enabled
	 */
	XSpi_Start(&Lcd_Spi);

	return XST_SUCCESS;
}

// int Lcd_Spi_Slave_Select(u32 slave)
// {
	
// 	 * Select the slave on the SPI bus, the EEPROM device so that it can be
// 	 * read and written using the SPI bus
	 
// 	Status = XSpi_SetSlaveSelect(&Spi, slave);
// 	if (Status != XST_SUCCESS) {
// 		return XST_FAILURE;
// 	}
// 	return XST_SUCCESS;
// }

void Lcd_Spi_Transfer(u32 slave, u8 *SendBufPtr,
		  u8 *RecvBufPtr, unsigned int ByteCount)
{
	int Status;
	/*
	 * Wait for the transfer on the SPI bus to be complete before proceeding
	 */
	while (TransferInProgress);

	/*
	 * Select the slave on the SPI bus, the EEPROM device so that it can be
	 * read and written using the SPI bus
	 */
	Status = XSpi_SetSlaveSelect(&Lcd_Spi, slave);
	if (Status != XST_SUCCESS) {
		xil_printf("SPI Transfer Error!\r\n");
		// return XST_FAILURE;
	}

	/*
	 * Send the write command, address, and data to the EEPROM to be
	 * written, no receive buffer is specified since there is nothing to
	 * receive
	 */
	TransferInProgress = TRUE;

	XSpi_Transfer(&Lcd_Spi, SendBufPtr, RecvBufPtr, ByteCount);
}

// LCD控制芯片SPI写函数
void Lcd_Spi_Write(u8 *SendBufPtr, unsigned int ByteCount)
{
	Lcd_Spi_Transfer(LCD_SPI_SELECT, SendBufPtr, NULL, ByteCount);
}

void Lcd_Spi_Write_Byte(u8 SendByte)
{
	Lcd_Spi_Transfer(LCD_SPI_SELECT, &SendByte, NULL, 1);
	// while(TransferInProgress); // 等待发送结束
}

// 字库芯片SPI写函数
void Char_Spi_Write(u8 *SendBufPtr, unsigned int ByteCount)
{
	Lcd_Spi_Transfer(CHAR_SPI_SELECT, SendBufPtr, NULL, ByteCount);
}

void Char_Spi_Write_Byte(u8 SendByte)
{
	Lcd_Spi_Transfer(CHAR_SPI_SELECT, &SendByte, NULL, 1);
	// while(TransferInProgress);
}
/******************************************************************************/
/**
*
* This function is the handler which performs processing for the SPI driver.
* It is called from an interrupt context such that the amount of processing
* performed should be minimized.  It is called when a transfer of SPI data
* completes or an error occurs.
*
* This handler provides an example of how to handle SPI interrupts
* but is application specific.
*
*
* @param 	CallBackRef is a reference passed to the handler.
* @param	StatusEvent is the status of the SPI .
* @param	ByteCount is the number of bytes transferred.
*
* @return	None
*
* @note		None.
*
******************************************************************************/
void SpiHandler(void *CallBackRef, u32 StatusEvent, unsigned int ByteCount)
{
	/*
	 * Indicate the transfer on the SPI bus is no longer in progress
	 * regardless of the status event
	 */
	TransferInProgress = FALSE;

	// xil_printf("spi transfer event\r\n"); // just for test

	/*
	 * If the event was not transfer done, then track it as an error
	 */
	if (StatusEvent != XST_SPI_TRANSFER_DONE) {
		Error++;
		xil_printf("spi transfer error is %d\r\n", Error);
	}
}

void Lcd_Spi_Handler(void)
{
	XSpi_InterruptHandler(&Lcd_Spi);
	NVIC_ClearPendingIRQ(LCD_SPI_IRQn);
}
