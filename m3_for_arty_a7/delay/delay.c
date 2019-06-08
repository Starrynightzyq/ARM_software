#include "delay.h"

void delay_ms(u32 time)
{
	u32 i, j = 0;
	for (i = 0; i < time; i++)
	{
		for (j = 0; j < 12270; j++);
	}
}