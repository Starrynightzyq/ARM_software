/*
 * vdma_driver.h
 *
 *  Created on: 2019年1月16日
 *      Author: admin
 */

#ifndef SRC_VDMA_DRIVER_VDMA_DRIVER_H_
#define SRC_VDMA_DRIVER_VDMA_DRIVER_H_

#include "xaxivdma.h"

int run_triple_due_frame_buffer(XAxiVdma* InstancePtr, int DeviceId, int hsize,
		int vsize, int rx_buf_base_addr, int tx_buf_base_addr, int number_frame_count,
		int enable_frm_cnt_intr);

#endif /* SRC_VDMA_DRIVER_VDMA_DRIVER_H_ */
