/*
 * uart16550.c
 *
 *  Created on: 2019年7月5日
 *      Author: admin
 */


/***************************** Include Files **********************************/
#include "m3_for_arty.h"        // Project specific header
#include "uart16550.h"
#include "xparameters.h"
#include "gizwits_protocol.h"

/************************** Constant Definitions ******************************/

/*
 * The following constants map to the XPAR parameters created in the
 * xparameters.h file. They are defined here such that a user can easily
 * change all the needed parameters in one place.
 */
#define UART0_DEVICE_ID		XPAR_UARTNS550_0_DEVICE_ID

/*
 * The following constant controls the length of the buffers to be sent
 * and received with the UART.
 */
#define TEST_BUFFER_SIZE	1

// #define DEBUG


/************************** Function Prototypes *******************************/

void UartNs550IntrHandler(void *CallBackRef, u32 Event, unsigned int EventData);
int XUartNs550_SetBaudRate(XUartNs550 *InstancePtr, u32 BaudRate);

/************************** Variable Definitions ******************************/

static XUartNs550 UartNs550Instance_0;	/* Instance of the UART Device */

/*
 * The following buffers are used in this example to send and receive data
 * with the UART.
 */
u8 SendBuffer[TEST_BUFFER_SIZE];	/* Buffer for Transmitting Data */
u8 RecvBuffer[TEST_BUFFER_SIZE];	/* Buffer for Receiving Data */

/*
 * The following counters are used to determine when the entire buffer has
 * been sent and received.
 */
static volatile int TotalReceivedCount;
static volatile int TotalSentCount;
static volatile int TotalErrorCount;
volatile u32 LastEventData = 0;

int UartNs550_Initialize(void)
{
	int Status;
	u16 Options;
	XUartNs550Format FormatPtr;

	/*
	 * Initialize the UART driver so that it's ready to use.
	 */
	Status = XUartNs550_Initialize(&UartNs550Instance_0, UART0_DEVICE_ID);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Perform a self-test to ensure that the hardware was built correctly.
	 */
	Status = XUartNs550_SelfTest(&UartNs550Instance_0);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}
	
	FormatPtr.BaudRate = BAUD_RATE;
	FormatPtr.DataBits = XUN_FORMAT_8_BITS;
	FormatPtr.Parity = XUN_FORMAT_NO_PARITY;
	FormatPtr.StopBits = XUN_FORMAT_1_STOP_BIT;

	XUartNs550_SetDataFormat(&UartNs550Instance_0, &FormatPtr);

	/*
	 * Setup the handlers for the UART that will be called from the
	 * interrupt context when data has been sent and received, specify a
	 * pointer to the UART driver instance as the callback reference so
	 * the handlers are able to access the instance data.
	 */
	XUartNs550_SetHandler(&UartNs550Instance_0, UartNs550IntrHandler,
	                      &UartNs550Instance_0);

	/*
	 * Enable the interrupt of the UART so interrupts will occur, setup
	 * a local loopback so data that is sent will be received, and keep the
	 * FIFOs enabled.
	 */
	Options = XUN_OPTION_DATA_INTR |
	          XUN_OPTION_FIFOS_ENABLE;
	XUartNs550_SetOptions(&UartNs550Instance_0, Options);

	// XUartNs550_SetBaudRate(&UartNs550Instance_0, BAUD_RATE);
	XUartNs550_SetFifoThreshold(&UartNs550Instance_0, FIFO_THRESHOLD);

	// xil_printf("FifoThreshold is %02x\r\n", XUartNs550_GetFifoThreshold(&UartNs550Instance_0));

	/*
	 * Start receiving data before sending it since there is a loopback,
	 * ignoring the number of bytes received as the return value since we
	 * know it will be zero and we are using interrupt mode.
	 */
	XUartNs550_Recv(&UartNs550Instance_0, RecvBuffer, TEST_BUFFER_SIZE);

	return XST_SUCCESS;
}

/*****************************************************************************/
/**
*
* This function is the handler which performs processing to handle data events
* from the UartNs550.  It is called from an interrupt context such that the
* amount of processing performed should be minimized.
*
* This handler provides an example of how to handle data for the UART and
* is application specific.
*
* @param	CallBackRef contains a callback reference from the driver,
*		in thiscase it is the instance pointer for the UART driver.
* @param	Event contains the specific kind of event that has occurred.
* @param	EventData contains the number of bytes sent or received for sent
*		and receive events.
*
* @return	None.
*
* @note		None.
*
*******************************************************************************/
void UartNs550IntrHandler(void *CallBackRef, u32 Event, unsigned int EventData)
{
	u8 Errors;
	int i;
	XUartNs550 *UartNs550Ptr = (XUartNs550 *)CallBackRef;

	/*
	 * All of the data has been sent.
	 */
	if (Event == XUN_EVENT_SENT_DATA) {
		// TotalSentCount = EventData;
#ifdef DEBUG
		// xil_printf("Send %02d Bytes\r\n", EventData);
#endif
	}

	/*
	 * All of the data has been received.
	 */
	if (Event == XUN_EVENT_RECV_DATA) {

		gizPutData((uint8_t *)RecvBuffer, 1); /* jizhiyun */

		XUartNs550_Recv(&UartNs550Instance_0, RecvBuffer, TEST_BUFFER_SIZE);
		// TotalReceivedCount = EventData;
#ifdef DEBUG
		// xil_printf("all %d. ", EventData);
		// for (i = 0; i < EventData; i++)
		// {
		// 	xil_printf("%02x ", RecvBuffer[i]);
		// }
		// xil_printf("\r\n", EventData);
		xil_printf("%02x\r\n", RecvBuffer[0]);
#endif
	}

	/*
	 * Data was received, but not the expected number of bytes, a
	 * timeout just indicates the data stopped for 4 character times.
	 */
	if (Event == XUN_EVENT_RECV_TIMEOUT) {
		// gizPutData(RecvBuffer, EventData); /* jizhiyun */

		// XUartNs550_Recv(&UartNs550Instance_0, RecvBuffer, TEST_BUFFER_SIZE);

#ifdef DEBUG
		// xil_printf("\r\n", EventData);
		// for (i = 0; i < EventData; i++)
		// {
		// 	xil_printf("%02x ", RecvBuffer[i]);
		// }
		// xil_printf("\r\n", EventData);
#endif

	}

	/*
	 * Data was received with an error, keep the data but determine
	 * what kind of errors occurred.
	 */
	if (Event == XUN_EVENT_RECV_ERROR) {
		TotalReceivedCount = EventData;
		TotalErrorCount++;
		Errors = XUartNs550_GetLastErrors(UartNs550Ptr);
		xil_printf("Data was received with the %d error\r\n", Errors);
	}
}

u32 UartNs550_0_Receive(u8 *BufferPtr, unsigned int NumBytes)
{
	return XUartNs550_Recv(&UartNs550Instance_0, BufferPtr, NumBytes);
}

u32 UartNs550_0_Send(u8 *BufferPtr, unsigned int NumBytes)
{
	return XUartNs550_Send(&UartNs550Instance_0, BufferPtr, NumBytes);
}

int UartNs550_0_IsSending(void)
{
	return XUartNs550_IsSending(&UartNs550Instance_0);
}

void UartNs0_Handler(void)
{
	XUartNs550_InterruptHandler(&UartNs550Instance_0);
    NVIC_ClearPendingIRQ(UartNs0_IRQn);
}
