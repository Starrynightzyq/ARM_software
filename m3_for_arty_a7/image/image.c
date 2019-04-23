#include "image.h"
#include "xparameters.h"

static XThreshold2 Threshold;

int Initialize_image_process(void) 
{
	int Status;

	Status = XThreshold2_Initialize(&Threshold, XPAR_XTHRESHOLD2_0_DEVICE_ID);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	XThreshold2_SetRows(&Threshold, 480);
	XThreshold2_SetCols(&Threshold, 640);
	XThreshold2_SetMax_h(&Threshold, 140);
	XThreshold2_SetMin_h(&Threshold, 100);

	return XST_SUCCESS;
}