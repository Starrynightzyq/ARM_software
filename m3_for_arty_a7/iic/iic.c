/*
 * --------Included Headers--------
 */

#include "stdlib.h"
#include "m3_for_arty.h"        // Project specific header
#include "iic.h"
#include "xparameters.h"
#include "xiic.h"
#include "xil_io.h"
#include "xil_printf.h"

// Instance of the IIC, local to this module
static XIic IIC0_instance; 	// connect to the temp sensor

#define TEMP_ADDRESS	0x4B	 /* 7 bit number */

volatile typedef struct {
	u8 TransmitComplete;	/* Flag to check completion of Transmission */
	u8 ReceiveComplete;	/* Flag to check completion of Reception */
} HandlerInfo;

HandlerInfo IIC0_HandlerInfo;

static void Iic0SendHandler(XIic *InstancePtr);
static void Iic0ReceiveHandler(XIic *InstancePtr);
static void Iic0StatusHandler(XIic *InstancePtr, int Event);
static int IicWriteData(XIic *InstancePtr, HandlerInfo *IicHandlerInfo, u8 reg, u8 *WriteBuffer, u16 ByteCount);
static int IicReadData(XIic *InstancePtr, HandlerInfo *IicHandlerInfo, u8 reg, u8 *ReadBuffer, u16 ByteCount);

int InitialiseIIC( void )
{
    int Status;

    /*
    * Initialize the UartLite driver so that it's ready to use.
    */
    Status = XIic_Initialize(&IIC0_instance, XPAR_IIC_0_DEVICE_ID);
    if (Status != XST_SUCCESS) {
        return XST_FAILURE;
    }

	/*
	 * Set the Handlers for transmit and reception.
	 */
	XIic_SetSendHandler(&IIC0_instance, &IIC0_instance,
				(XIic_Handler) Iic0SendHandler);
	XIic_SetRecvHandler(&IIC0_instance, &IIC0_instance,
				(XIic_Handler) Iic0ReceiveHandler);
	XIic_SetStatusHandler(&IIC0_instance, &IIC0_instance,
				  (XIic_StatusHandler) Iic0StatusHandler);

	/*
	 * Set the Slave address.
	 */
	Status = XIic_SetAddress(&IIC0_instance, XII_ADDR_TO_SEND_TYPE,
				 TEMP_ADDRESS);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

    return XST_SUCCESS;
}

static void Iic0SendHandler(XIic *InstancePtr)
{
	IIC0_HandlerInfo.TransmitComplete = 0;
}

static void Iic0ReceiveHandler(XIic *InstancePtr)
{
	IIC0_HandlerInfo.ReceiveComplete = 0;
}

static void Iic0StatusHandler(XIic *InstancePtr, int Event)
{

}

// Define the IIC interrupt handler here
void IIC0_Handler ( void )
{
    XIic_InterruptHandler(&IIC0_instance);
    NVIC_ClearPendingIRQ(IIC0_IRQn);
}

/*****************************************************************************/
/**
* This function writes a buffer of data to the IIC serial EEPROM.
*
* @param	ByteCount contains the number of bytes in the buffer to be
*		written.
*
* @param	reg is the iic regeister address, 1 Byte
*
* @return	XST_SUCCESS if successful else XST_FAILURE.
*
* @note		The Byte count should not exceed the page size of the EEPROM as
*		noted by the constant PAGE_SIZE.
*
******************************************************************************/
static int IicWriteData(XIic *InstancePtr, HandlerInfo *IicHandlerInfo, u8 reg, u8 *WriteBuffer, u16 ByteCount)
{
	int Status;
	u16 Index;
	u8 *Buffer_frist_adder;
	u8 *Buffer = (u8 *)malloc(ByteCount+1);

	/*
	 * Set the defaults.
	 */
	IicHandlerInfo->TransmitComplete = 1;
	InstancePtr->Stats.TxErrors = 0;

	/*
	 * Initialize the data to write buffer.
	 */
	Buffer_frist_adder = Buffer;
	*Buffer = reg;
	Buffer++;
	for(Index = 0; Index < ByteCount; Index++) {
		*Buffer = *WriteBuffer;
		Buffer++;
		WriteBuffer++;
	}
	Buffer = Buffer_frist_adder;

	/*
	 * Start the IIC device.
	 */
	Status = XIic_Start(InstancePtr);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Send the Data.
	 */
	Status = XIic_MasterSend(InstancePtr, Buffer, ByteCount+1);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Wait till the transmission is completed.
	 */
	while ((IicHandlerInfo->TransmitComplete) || (XIic_IsIicBusy(InstancePtr) == TRUE)) {
		/*
		 * This condition is required to be checked in the case where we
		 * are writing two consecutive buffers of data to the EEPROM.
		 * The EEPROM takes about 2 milliseconds time to update the data
		 * internally after a STOP has been sent on the bus.
		 * A NACK will be generated in the case of a second write before
		 * the EEPROM updates the data internally resulting in a
		 * Transmission Error.
		 */
		if (InstancePtr->Stats.TxErrors != 0) {


			/*
			 * Enable the IIC device.
			 */
			Status = XIic_Start(InstancePtr);
			if (Status != XST_SUCCESS) {
				return XST_FAILURE;
			}


			if (!XIic_IsIicBusy(InstancePtr)) {
				/*
				 * Send the Data.
				 */
				Status = XIic_MasterSend(InstancePtr,
							 Buffer,
							 ByteCount);
				if (Status == XST_SUCCESS) {
					InstancePtr->Stats.TxErrors = 0;
				}
				else {
				}
			}
		}
	}

	/*
	 * Stop the IIC device.
	 */
	Status = XIic_Stop(InstancePtr);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * free the buffer
	 */
	free(Buffer);

	return XST_SUCCESS;
}

/*****************************************************************************/
/**
* This function reads data from the IIC serial EEPROM into a specified buffer.
*
* @param	BufferPtr contains the address of the data buffer to be filled.
* @param	ByteCount contains the number of bytes in the buffer to be read.
*
* @return	XST_SUCCESS if successful else XST_FAILURE.
*
* @note		None.
*
******************************************************************************/
static int IicReadData(XIic *InstancePtr, HandlerInfo *IicHandlerInfo, u8 reg, u8 *ReadBuffer, u16 ByteCount)
{
	int Status;

	/*
	 * Set the Defaults.
	 */
	IicHandlerInfo->ReceiveComplete = 1;

	/*
	 * Position the Pointer in EEPROM.
	 */
	Status = IicWriteData(InstancePtr, IicHandlerInfo, reg, NULL, 0);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Start the IIC device.
	 */
	Status = XIic_Start(InstancePtr);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Receive the Data.
	 */
	Status = XIic_MasterRecv(InstancePtr, ReadBuffer, ByteCount);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Wait till all the data is received.
	 */
	while ((IicHandlerInfo->ReceiveComplete) || (XIic_IsIicBusy(InstancePtr) == TRUE)) {

	}

	/*
	 * Stop the IIC device.
	 */
	Status = XIic_Stop(InstancePtr);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	return XST_SUCCESS;
}

int Iic0WriteData(u8 reg, u8 *WriteBuffer, u16 ByteCount)
{
	int Status;
	Status = IicWriteData(&IIC0_instance, &IIC0_HandlerInfo, reg, WriteBuffer, ByteCount);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	return XST_SUCCESS;
}

int Iic0ReadData(u8 reg, u8 *ReadBuffer, u16 ByteCount)
{
	int Status;
	Status = IicReadData(&IIC0_instance, &IIC0_HandlerInfo, reg, ReadBuffer, ByteCount);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	return XST_SUCCESS;
}
