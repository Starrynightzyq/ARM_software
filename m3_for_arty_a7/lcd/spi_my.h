
#include "xil_types.h"
/*
 * The following constant defines the slave select signal that is used to
 * to select the EEPROM device on the SPI bus, this signal is typically
 * connected to the chip select of the device
 */
#define LCD_SPI_SELECT 0x01
#define CHAR_SPI_SELECT 0x02

// 初始化 LCD SPI 控制器
int Lcd_Spi_Initialize(void);

// LCD 控制芯片 SPI 写函数
void Lcd_Spi_Write(u8 *SendBufPtr, unsigned int ByteCount);

void Lcd_Spi_Write_Byte(u8 SendByte);

// 字库芯片 SPI 写函数
void Char_Spi_Write(u8 *SendBufPtr, unsigned int ByteCount);

void Char_Spi_Write_Byte(u8 SendByte);


