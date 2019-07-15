#ifndef IMAGE_H
#define IMAGE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "xparameters.h"
#include "xil_types.h"

#define CHAR_INDEX_CHANNEL 1
#define CHAR_DIFF_CHANNEL 2

#define IMAGE_ROWS 480
#define IMAGE_COLS 640

#define FRAME_NUM 5    // 帧数最大值
#define CHAR_NUM 8      // 车牌中字的个数
#define POINT_MAX_DIFF 70 // 车牌中点的最大差值

int Initialize_image_process(void);

int Image_Interrupt_setup(void);

void show_plate(void);

void Get_Hsv(void);

#ifdef __cplusplus
}
#endif

#endif