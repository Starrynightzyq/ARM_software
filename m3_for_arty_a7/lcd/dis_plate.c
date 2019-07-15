#include "xstatus.h"
#include <string.h>
#include "m3_for_arty.h"        // Project specific header
#include "lcd.h" 
#include "dis_plate.h"

u8 array_dis[6]; 
u8 ser[4];
u16 columns=0;
u16 rows=0; 

//ÏÔÊ¾³µÅÆÊý×Ö
void show_plate_num(u32 *p)
{
		int i;
		p+=2;
		for(i=0;i<5;i++)			              
		{
			p++;	
			array_dis[i] = *p + 48;
		}
		array_dis[5]='\0';
		ser[0]=(columns*10+rows+1)/10+48;
		ser[1]=(columns*10+rows+1)%10+48;
		ser[2]=')';
		ser[3]='\0';
		
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
}

//ÏÔÊ¾³µÅÆ×ÖÄ¸
void show_plate_english(u8 english_dis)
{
		
		LCD_ShowChar(columns*160+66,48*rows+18,english_dis,0,BLUE);
}

/**********************ÏÔÊ¾³µÅÆºº×Ö*************************
¾©(0) ½ò(1) »¦(2) Óå(3) ÃÉ(4) ÐÂ(5) ²Ø(6) Äþ(7)
¹ð(8) ºÚ(9) ¼ª(10) ÁÉ(11) ½ú(12) Â³(13) Ô¥(15)
ËÕ(16) Õã(17) Íî(18) Ãö(19) ÔÁ(20) Çí(21) Çà(22) ¸Ê(23)
ÔÆ(24) ¹ó(25) ´¨(26) ÉÂ(27) Ïæ(28) ¶õ(29) ¸Ó(30)
***********************************************************/
void show_plate_chinese(u8 chinese_dis)
{
			if(rows==10){													  
				if(columns==0){
						rows=0; columns=1;
						LCD_ShowChinese32x32(columns*160+48,48*rows+18,chinese_dis, 16,BLUE);
				}
				else{
						columns=0;rows=0;
						LCD_ShowChinese32x32(columns*160+48,48*rows+18,chinese_dis, 16,BLUE);
				}
			} 
			else{
					LCD_ShowChinese32x32(columns*160+48,48*rows+18,chinese_dis, 16,BLUE);
			}	
}

