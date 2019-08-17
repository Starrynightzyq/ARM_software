#include "timer.h"
#include "xparameters.h"
#include "xtmrctr.h"
#include "m3_for_arty.h"        // Project specific header
#include "xil_printf.h"

/*
 * The following constant determines which timer counter of the device that is
 * used for this example, there are currently 2 timer counters in a device
 * and this example uses the first one, 0, the timer numbers are 0 based
 */
#define TIMER_CNTR_0	 0

// #define DEBUG

static u32 read_buffer_time_counter = 0;
u8 read_flag = 0;

static XTmrCtr Timer0_Inst;   /* The instance of the Timer Counter */

static void Timer0CounterHandler(void *CallBackRef, u8 TmrCtrNumber);

void gizTimerMs(void);

/*
 * 初始化定时器0
 * 向下计数（从 ResetValue 数到 0）
 * 自动重载
 * 中断模式
 */
int Timer0_Initialise(u32 ResetValue)
{
	int Status;

	/*
	 * Initialize the timer counter so that it's ready to use,
	 * specify the device ID that is generated in xparameters.h
	 */
	Status = XTmrCtr_Initialize(&Timer0_Inst, XPAR_TMRCTR_0_DEVICE_ID);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Perform a self-test to ensure that the hardware was built
	 * correctly, use the 1st timer in the device (0)
	 */
	Status = XTmrCtr_SelfTest(&Timer0_Inst, TIMER_CNTR_0);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Setup the handler for the timer counter that will be called from the
	 * interrupt context when the timer expires, specify a pointer to the
	 * timer counter driver instance as the callback reference so the handler
	 * is able to access the instance data
	 */
	XTmrCtr_SetHandler(&Timer0_Inst, Timer0CounterHandler,
					   &Timer0_Inst);

	/*
	 * Enable the interrupt of the timer counter so interrupts will occur
	 * and use auto reload mode such that the timer counter will reload
	 * itself automatically and continue repeatedly, without this option
	 * it would expire once only
	 */
	XTmrCtr_SetOptions(&Timer0_Inst, TIMER_CNTR_0,
				XTC_INT_MODE_OPTION | XTC_AUTO_RELOAD_OPTION | XTC_DOWN_COUNT_OPTION);

	/*
	 * Set a reset value for the timer counter such that it will expire
	 * eariler than letting it roll over from 0, the reset value is loaded
	 * into the timer counter when it is started
	 */
	XTmrCtr_SetResetValue(&Timer0_Inst, TIMER_CNTR_0, ResetValue);

	/*
	 * Start the timer counter such that it's incrementing by default,
	 * then wait for it to timeout a number of times
	 */
	XTmrCtr_Start(&Timer0_Inst, TIMER_CNTR_0);

	xil_printf("timer 0 initializes done\r\n");

	return XST_SUCCESS;
}

/*
 * 开定时器0中断
 */
void EnableTIMER0Interrupts(void)
{
	NVIC_EnableIRQ(TIMER0_IRQn);
}

/*
 * 关定时器0中断
 */
void DisableTIMER0Interrupts(void)
{
	NVIC_DisableIRQ(TIMER0_IRQn);
}

/*****************************************************************************/
/**
* This function is the handler which performs processing for the timer counter.
* It is called from an interrupt context such that the amount of processing
* performed should be minimized.  It is called when the timer counter expires
* if interrupts are enabled.
*
* This handler provides an example of how to handle timer counter interrupts
* but is application specific.
*
* @param	CallBackRef is a pointer to the callback function
* @param	TmrCtrNumber is the number of the timer to which this
*		handler is associated with.
*
* @return	None.
*
* @note		None.
*
******************************************************************************/
void Timer0CounterHandler(void *CallBackRef, u8 TmrCtrNumber)
{
	// XTmrCtr *InstancePtr = (XTmrCtr *)CallBackRef;
	gizTimerMs();

	read_buffer_time_counter++;
	if (read_buffer_time_counter == 500) // 500 ms计时
	{
		read_buffer_time_counter = 0;
		read_flag = 1;
	}
	
#ifdef DEBUG
	xil_printf("tim0 intr\r\n");
#endif
}

/*
 * 对 timer 驱动里的 handler 的封装
 * 不要修改此函数
 * 需要修改中断函数请修改 void Timer0CounterHandler(void *CallBackRef, u8 TmrCtrNumber)
 */
void Timer0_Handler ( void )
{
	XTmrCtr_InterruptHandler(&Timer0_Inst);
	NVIC_ClearPendingIRQ(TIMER0_IRQn);
}