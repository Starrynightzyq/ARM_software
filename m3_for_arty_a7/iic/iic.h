#include "xil_types.h"

int InitialiseIIC( void );
int Iic0WriteData(u8 reg, u8 *WriteBuffer, u16 ByteCount);
int Iic0ReadData(u8 reg, u8 *ReadBuffer, u16 ByteCount);

int Iic0WriteData16(u16 reg, u8 *WriteBuffer, u16 ByteCount);
int Iic0ReadData16(u16 reg, u8 *ReadBuffer, u16 ByteCount);

int Iic1WriteData(u8 reg, u8 *WriteBuffer, u16 ByteCount);
int Iic1ReadData(u8 reg, u8 *ReadBuffer, u16 ByteCount);

int Iic1WriteData16(u16 reg, u8 *WriteBuffer, u16 ByteCount);
int Iic1ReadData16(u16 reg, u8 *ReadBuffer, u16 ByteCount);

int Iic0Test(void);
int Iic1Test(void);
