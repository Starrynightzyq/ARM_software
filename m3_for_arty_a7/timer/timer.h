#include "xil_types.h"

/*
 * 初始化定时器0
 * 向下计数（从 ResetValue 数到 0）
 * 自动重载
 * 中断模式
 */
int Timer0_Initialise(u32 ResetValue);

/*
 * 开定时器0中断
 */
void EnableTIMER0Interrupts(void);

/*
 * 关定时器0中断
 */
void DisableTIMER0Interrupts(void);
