#include "xil_types.h"

int InitialiseIIC( void );
int Iic0WriteData(u8 reg, u8 *WriteBuffer, u16 ByteCount);
int Iic0ReadData(u8 reg, u8 *ReadBuffer, u16 ByteCount);
