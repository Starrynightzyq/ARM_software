#include "xstatus.h"
#include <string.h>
#include "m3_for_arty.h"        // Project specific header
#include "lcd.h"
#include "dis_plate.h"

u8 array_dis[6];
u8 ser[4];
u16 columns = 0;
u16 rows = 0;

//?ʾ?????
void show_plate_num(u8 *p, u8 position)
{
	int i;
	for (i = 0; i < 5; i++)
	{
		array_dis[i] = *p + 48;
		p++;
	}
	array_dis[5] = '\0';
	ser[0] = (position + 1) / 10 + 48;
	ser[1] = (position + 1) % 10 + 48;
	ser[2] = ')';
	ser[3] = '\0';

	rows = position % 10;
	columns = position / 10;
	LCD_ShowString(columns * 160 + 15, 48 * rows + 18, ser, RED);
	LCD_ShowString(columns * 160 + 80, 48 * rows + 18, array_dis, BLUE);

	/*
			if(rows==10){
				if(columns==0){
						rows=0; columns=1;
						LCD_ShowString(columns*160+15,48*rows+18,ser,RED);
						LCD_ShowString(columns*160+80,48*rows+18,array_dis, BLUE);
				}
				else if(columns==1){
						columns=0;rows=0;
						LCD_ShowString(columns*160+15,48*rows+18,ser,RED);
						LCD_ShowString(columns*160+80,48*rows+18,array_dis, BLUE);
				}
				rows++;
			}
			else{
				LCD_ShowString(columns*160+15,48*rows+18,ser,RED);
				LCD_ShowString(columns*160+80,48*rows+18,array_dis, BLUE);
				rows++;
			}
	*/
}

//?ʾ????ĸ
void show_plate_english(u8 english_dis)
{

	LCD_ShowChar(columns * 160 + 66, 48 * rows + 18, english_dis, 0, BLUE);
}

/**********************?ʾ??????*************************
??(0) ??1) ??(2) ?(3) ?(4) ?(5) ??6) ?(7)
??8) ??9) ??(10) ??11) ??(12) ³(13) ԥ(15)
?(16) ?(17) ?(18) ?(19) ?(20) ?(21) ?(22) ??23)
?(24) ??25) ??(26) ?(27) ?(28) ??(29) ??30)
***********************************************************/
void show_plate_chinese(u8 chinese_dis)
{
	if (rows == 10) {
		if (columns == 0) {
			rows = 0; columns = 1;
			LCD_ShowChinese32x32(columns * 160 + 48, 48 * rows + 18, chinese_dis, 16, BLUE);
		}
		else {
			columns = 0; rows = 0;
			LCD_ShowChinese32x32(columns * 160 + 48, 48 * rows + 18, chinese_dis, 16, BLUE);
		}
	}
	else {
		LCD_ShowChinese32x32(columns * 160 + 48, 48 * rows + 18, chinese_dis, 16, BLUE);
	}
}

