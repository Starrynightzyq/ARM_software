#include "xil_types.h"

#define USE_HORIZONTAL 0  //设置横屏或者竖屏显示 0或1为竖屏 2或3为横屏

#if USE_HORIZONTAL==0||USE_HORIZONTAL==1
#define LCD_W 320
#define LCD_H 480

#else
#define LCD_W 480
#define LCD_H 320
#endif

//画笔颜色
#define WHITE         	 0xFCFCFC
#define BLACK            0X000000
#define RED           	 0xFC0000
#define GREEN            0x00FC00
#define BLUE             0x0000FC

#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据

void Lcd_Init(void);
void LCD_Clear(u32 Color);
void LCD_ShowNum1(u16 x, u16 y, float num, u8 len, u32 color);
void LCD_ShowString(u16 x, u16 y, const u8 *p, u16 color);
