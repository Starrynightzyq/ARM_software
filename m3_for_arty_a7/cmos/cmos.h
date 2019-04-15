#ifndef __CMOS_H__
#define __CMOS_H__

#include "xil_types.h"

#define SEQUENCE_END	     0xFFFF

struct reginfo
{
    u16 reg;
    u8 val;
};

int sensor_init(void);

#endif