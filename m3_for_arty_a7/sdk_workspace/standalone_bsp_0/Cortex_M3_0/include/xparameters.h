#ifndef XPARAMETERS_H   /* prevent circular inclusions */
#define XPARAMETERS_H   /* by using protection macros */

/* Definition for CPU ID */
#define XPAR_CPU_ID 0U

/* Definitions for peripheral CORTEX_M3_0 */
#define XPAR_CORTEX_M3_0_CPU_CLK_FREQ_HZ 0


/******************************************************************/

/* Canonical definitions for peripheral CORTEX_M3_0 */
#define XPAR_CPU_CORTEXM3_0_CPU_CLK_FREQ_HZ 0


/******************************************************************/

#define STDIN_BASEADDRESS 0x40100000
#define STDOUT_BASEADDRESS 0x40100000

/******************************************************************/

/* Platform specific definitions */
#define PLATFORM_ARM
 
/* Definitions for sleep timer configuration */
#define SLEEP_TIMER_BASEADDR XPAR_AXI_TIMER_0_BASEADDR 
#define SLEEP_TIMER_FREQUENCY XPAR_AXI_TIMER_0_CLOCK_FREQ_HZ 
#define XSLEEP_TIMER_IS_AXI_TIMER
 
 
/******************************************************************/
/* Definitions for driver PROJECTION */
#define XPAR_PROJECTION_NUM_INSTANCES 1

/* Definitions for peripheral OV_CMOS_IMAGE_PROCESS_PROJECTION_0 */
#define XPAR_OV_CMOS_IMAGE_PROCESS_PROJECTION_0_DEVICE_ID 0
#define XPAR_OV_CMOS_IMAGE_PROCESS_PROJECTION_0_CTRL_AXI_BASEADDR 0x44A20000
#define XPAR_OV_CMOS_IMAGE_PROCESS_PROJECTION_0_CTRL_AXI_HIGHADDR 0x44A2FFFF


/******************************************************************/

/* Definitions for driver AXIVDMA */
#define XPAR_XAXIVDMA_NUM_INSTANCES 2U

/* Definitions for peripheral OV_CMOS_AXI_VDMA_0 */
#define XPAR_OV_CMOS_AXI_VDMA_0_DEVICE_ID 0U
#define XPAR_OV_CMOS_AXI_VDMA_0_BASEADDR 0x44A00000U
#define XPAR_OV_CMOS_AXI_VDMA_0_HIGHADDR 0x44A0FFFFU
#define XPAR_OV_CMOS_AXI_VDMA_0_NUM_FSTORES 3U
#define XPAR_OV_CMOS_AXI_VDMA_0_INCLUDE_MM2S 1U
#define XPAR_OV_CMOS_AXI_VDMA_0_INCLUDE_MM2S_DRE 0U
#define XPAR_OV_CMOS_AXI_VDMA_0_M_AXI_MM2S_DATA_WIDTH 64U
#define XPAR_OV_CMOS_AXI_VDMA_0_INCLUDE_S2MM 1U
#define XPAR_OV_CMOS_AXI_VDMA_0_INCLUDE_S2MM_DRE 0U
#define XPAR_OV_CMOS_AXI_VDMA_0_M_AXI_S2MM_DATA_WIDTH 64U
#define XPAR_OV_CMOS_AXI_VDMA_0_AXI_MM2S_ACLK_FREQ_HZ 0U
#define XPAR_OV_CMOS_AXI_VDMA_0_AXI_S2MM_ACLK_FREQ_HZ 0U
#define XPAR_OV_CMOS_AXI_VDMA_0_MM2S_GENLOCK_MODE 3U
#define XPAR_OV_CMOS_AXI_VDMA_0_MM2S_GENLOCK_NUM_MASTERS 1U
#define XPAR_OV_CMOS_AXI_VDMA_0_S2MM_GENLOCK_MODE 2U
#define XPAR_OV_CMOS_AXI_VDMA_0_S2MM_GENLOCK_NUM_MASTERS 1U
#define XPAR_OV_CMOS_AXI_VDMA_0_INCLUDE_SG 0U
#define XPAR_OV_CMOS_AXI_VDMA_0_ENABLE_VIDPRMTR_READS 1U
#define XPAR_OV_CMOS_AXI_VDMA_0_USE_FSYNC 1U
#define XPAR_OV_CMOS_AXI_VDMA_0_FLUSH_ON_FSYNC 1U
#define XPAR_OV_CMOS_AXI_VDMA_0_MM2S_LINEBUFFER_DEPTH 512U
#define XPAR_OV_CMOS_AXI_VDMA_0_S2MM_LINEBUFFER_DEPTH 512U
#define XPAR_OV_CMOS_AXI_VDMA_0_INCLUDE_INTERNAL_GENLOCK 1U
#define XPAR_OV_CMOS_AXI_VDMA_0_S2MM_SOF_ENABLE 1U
#define XPAR_OV_CMOS_AXI_VDMA_0_M_AXIS_MM2S_TDATA_WIDTH 24U
#define XPAR_OV_CMOS_AXI_VDMA_0_S_AXIS_S2MM_TDATA_WIDTH 24U
#define XPAR_OV_CMOS_AXI_VDMA_0_ENABLE_DEBUG_INFO_1 0U
#define XPAR_OV_CMOS_AXI_VDMA_0_ENABLE_DEBUG_INFO_5 0U
#define XPAR_OV_CMOS_AXI_VDMA_0_ENABLE_DEBUG_INFO_6 1U
#define XPAR_OV_CMOS_AXI_VDMA_0_ENABLE_DEBUG_INFO_7 1U
#define XPAR_OV_CMOS_AXI_VDMA_0_ENABLE_DEBUG_INFO_9 0U
#define XPAR_OV_CMOS_AXI_VDMA_0_ENABLE_DEBUG_INFO_13 0U
#define XPAR_OV_CMOS_AXI_VDMA_0_ENABLE_DEBUG_INFO_14 1U
#define XPAR_OV_CMOS_AXI_VDMA_0_ENABLE_DEBUG_INFO_15 1U
#define XPAR_OV_CMOS_AXI_VDMA_0_ENABLE_DEBUG_ALL 0U
#define XPAR_OV_CMOS_AXI_VDMA_0_ADDR_WIDTH 32U


/* Definitions for peripheral OV_CMOS_AXI_VDMA_1 */
#define XPAR_OV_CMOS_AXI_VDMA_1_DEVICE_ID 1U
#define XPAR_OV_CMOS_AXI_VDMA_1_BASEADDR 0x44A30000U
#define XPAR_OV_CMOS_AXI_VDMA_1_HIGHADDR 0x44A3FFFFU
#define XPAR_OV_CMOS_AXI_VDMA_1_NUM_FSTORES 3U
#define XPAR_OV_CMOS_AXI_VDMA_1_INCLUDE_MM2S 1U
#define XPAR_OV_CMOS_AXI_VDMA_1_INCLUDE_MM2S_DRE 0U
#define XPAR_OV_CMOS_AXI_VDMA_1_M_AXI_MM2S_DATA_WIDTH 64U
#define XPAR_OV_CMOS_AXI_VDMA_1_INCLUDE_S2MM 1U
#define XPAR_OV_CMOS_AXI_VDMA_1_INCLUDE_S2MM_DRE 0U
#define XPAR_OV_CMOS_AXI_VDMA_1_M_AXI_S2MM_DATA_WIDTH 64U
#define XPAR_OV_CMOS_AXI_VDMA_1_AXI_MM2S_ACLK_FREQ_HZ 0U
#define XPAR_OV_CMOS_AXI_VDMA_1_AXI_S2MM_ACLK_FREQ_HZ 0U
#define XPAR_OV_CMOS_AXI_VDMA_1_MM2S_GENLOCK_MODE 3U
#define XPAR_OV_CMOS_AXI_VDMA_1_MM2S_GENLOCK_NUM_MASTERS 1U
#define XPAR_OV_CMOS_AXI_VDMA_1_S2MM_GENLOCK_MODE 2U
#define XPAR_OV_CMOS_AXI_VDMA_1_S2MM_GENLOCK_NUM_MASTERS 1U
#define XPAR_OV_CMOS_AXI_VDMA_1_INCLUDE_SG 0U
#define XPAR_OV_CMOS_AXI_VDMA_1_ENABLE_VIDPRMTR_READS 1U
#define XPAR_OV_CMOS_AXI_VDMA_1_USE_FSYNC 1U
#define XPAR_OV_CMOS_AXI_VDMA_1_FLUSH_ON_FSYNC 1U
#define XPAR_OV_CMOS_AXI_VDMA_1_MM2S_LINEBUFFER_DEPTH 512U
#define XPAR_OV_CMOS_AXI_VDMA_1_S2MM_LINEBUFFER_DEPTH 512U
#define XPAR_OV_CMOS_AXI_VDMA_1_INCLUDE_INTERNAL_GENLOCK 1U
#define XPAR_OV_CMOS_AXI_VDMA_1_S2MM_SOF_ENABLE 1U
#define XPAR_OV_CMOS_AXI_VDMA_1_M_AXIS_MM2S_TDATA_WIDTH 24U
#define XPAR_OV_CMOS_AXI_VDMA_1_S_AXIS_S2MM_TDATA_WIDTH 24U
#define XPAR_OV_CMOS_AXI_VDMA_1_ENABLE_DEBUG_INFO_1 0U
#define XPAR_OV_CMOS_AXI_VDMA_1_ENABLE_DEBUG_INFO_5 0U
#define XPAR_OV_CMOS_AXI_VDMA_1_ENABLE_DEBUG_INFO_6 1U
#define XPAR_OV_CMOS_AXI_VDMA_1_ENABLE_DEBUG_INFO_7 1U
#define XPAR_OV_CMOS_AXI_VDMA_1_ENABLE_DEBUG_INFO_9 0U
#define XPAR_OV_CMOS_AXI_VDMA_1_ENABLE_DEBUG_INFO_13 0U
#define XPAR_OV_CMOS_AXI_VDMA_1_ENABLE_DEBUG_INFO_14 1U
#define XPAR_OV_CMOS_AXI_VDMA_1_ENABLE_DEBUG_INFO_15 1U
#define XPAR_OV_CMOS_AXI_VDMA_1_ENABLE_DEBUG_ALL 0U
#define XPAR_OV_CMOS_AXI_VDMA_1_ADDR_WIDTH 32U


/******************************************************************/

/* Canonical definitions for peripheral OV_CMOS_AXI_VDMA_0 */
#define XPAR_AXIVDMA_0_DEVICE_ID XPAR_OV_CMOS_AXI_VDMA_0_DEVICE_ID
#define XPAR_AXIVDMA_0_BASEADDR 0x44A00000U
#define XPAR_AXIVDMA_0_HIGHADDR 0x44A0FFFFU
#define XPAR_AXIVDMA_0_NUM_FSTORES 3U
#define XPAR_AXIVDMA_0_INCLUDE_MM2S 1U
#define XPAR_AXIVDMA_0_INCLUDE_MM2S_DRE 0U
#define XPAR_AXIVDMA_0_M_AXI_MM2S_DATA_WIDTH 64U
#define XPAR_AXIVDMA_0_INCLUDE_S2MM 1U
#define XPAR_AXIVDMA_0_INCLUDE_S2MM_DRE 0U
#define XPAR_AXIVDMA_0_M_AXI_S2MM_DATA_WIDTH 64U
#define XPAR_AXIVDMA_0_AXI_MM2S_ACLK_FREQ_HZ 0U
#define XPAR_AXIVDMA_0_AXI_S2MM_ACLK_FREQ_HZ 0U
#define XPAR_AXIVDMA_0_MM2S_GENLOCK_MODE 3U
#define XPAR_AXIVDMA_0_MM2S_GENLOCK_NUM_MASTERS 1U
#define XPAR_AXIVDMA_0_S2MM_GENLOCK_MODE 2U
#define XPAR_AXIVDMA_0_S2MM_GENLOCK_NUM_MASTERS 1U
#define XPAR_AXIVDMA_0_INCLUDE_SG 0U
#define XPAR_AXIVDMA_0_ENABLE_VIDPRMTR_READS 1U
#define XPAR_AXIVDMA_0_USE_FSYNC 1U
#define XPAR_AXIVDMA_0_FLUSH_ON_FSYNC 1U
#define XPAR_AXIVDMA_0_MM2S_LINEBUFFER_DEPTH 512U
#define XPAR_AXIVDMA_0_S2MM_LINEBUFFER_DEPTH 512U
#define XPAR_AXIVDMA_0_INCLUDE_INTERNAL_GENLOCK 1U
#define XPAR_AXIVDMA_0_S2MM_SOF_ENABLE 1U
#define XPAR_AXIVDMA_0_M_AXIS_MM2S_TDATA_WIDTH 24U
#define XPAR_AXIVDMA_0_S_AXIS_S2MM_TDATA_WIDTH 24U
#define XPAR_AXIVDMA_0_ENABLE_DEBUG_INFO_1 0U
#define XPAR_AXIVDMA_0_ENABLE_DEBUG_INFO_5 0U
#define XPAR_AXIVDMA_0_ENABLE_DEBUG_INFO_6 1U
#define XPAR_AXIVDMA_0_ENABLE_DEBUG_INFO_7 1U
#define XPAR_AXIVDMA_0_ENABLE_DEBUG_INFO_9 0U
#define XPAR_AXIVDMA_0_ENABLE_DEBUG_INFO_13 0U
#define XPAR_AXIVDMA_0_ENABLE_DEBUG_INFO_14 1U
#define XPAR_AXIVDMA_0_ENABLE_DEBUG_INFO_15 1U
#define XPAR_AXIVDMA_0_ENABLE_DEBUG_ALL 0U
#define XPAR_AXIVDMA_0_c_addr_width 32U

/* Canonical definitions for peripheral OV_CMOS_AXI_VDMA_1 */
#define XPAR_AXIVDMA_1_DEVICE_ID XPAR_OV_CMOS_AXI_VDMA_1_DEVICE_ID
#define XPAR_AXIVDMA_1_BASEADDR 0x44A30000U
#define XPAR_AXIVDMA_1_HIGHADDR 0x44A3FFFFU
#define XPAR_AXIVDMA_1_NUM_FSTORES 3U
#define XPAR_AXIVDMA_1_INCLUDE_MM2S 1U
#define XPAR_AXIVDMA_1_INCLUDE_MM2S_DRE 0U
#define XPAR_AXIVDMA_1_M_AXI_MM2S_DATA_WIDTH 64U
#define XPAR_AXIVDMA_1_INCLUDE_S2MM 1U
#define XPAR_AXIVDMA_1_INCLUDE_S2MM_DRE 0U
#define XPAR_AXIVDMA_1_M_AXI_S2MM_DATA_WIDTH 64U
#define XPAR_AXIVDMA_1_AXI_MM2S_ACLK_FREQ_HZ 0U
#define XPAR_AXIVDMA_1_AXI_S2MM_ACLK_FREQ_HZ 0U
#define XPAR_AXIVDMA_1_MM2S_GENLOCK_MODE 3U
#define XPAR_AXIVDMA_1_MM2S_GENLOCK_NUM_MASTERS 1U
#define XPAR_AXIVDMA_1_S2MM_GENLOCK_MODE 2U
#define XPAR_AXIVDMA_1_S2MM_GENLOCK_NUM_MASTERS 1U
#define XPAR_AXIVDMA_1_INCLUDE_SG 0U
#define XPAR_AXIVDMA_1_ENABLE_VIDPRMTR_READS 1U
#define XPAR_AXIVDMA_1_USE_FSYNC 1U
#define XPAR_AXIVDMA_1_FLUSH_ON_FSYNC 1U
#define XPAR_AXIVDMA_1_MM2S_LINEBUFFER_DEPTH 512U
#define XPAR_AXIVDMA_1_S2MM_LINEBUFFER_DEPTH 512U
#define XPAR_AXIVDMA_1_INCLUDE_INTERNAL_GENLOCK 1U
#define XPAR_AXIVDMA_1_S2MM_SOF_ENABLE 1U
#define XPAR_AXIVDMA_1_M_AXIS_MM2S_TDATA_WIDTH 24U
#define XPAR_AXIVDMA_1_S_AXIS_S2MM_TDATA_WIDTH 24U
#define XPAR_AXIVDMA_1_ENABLE_DEBUG_INFO_1 0U
#define XPAR_AXIVDMA_1_ENABLE_DEBUG_INFO_5 0U
#define XPAR_AXIVDMA_1_ENABLE_DEBUG_INFO_6 1U
#define XPAR_AXIVDMA_1_ENABLE_DEBUG_INFO_7 1U
#define XPAR_AXIVDMA_1_ENABLE_DEBUG_INFO_9 0U
#define XPAR_AXIVDMA_1_ENABLE_DEBUG_INFO_13 0U
#define XPAR_AXIVDMA_1_ENABLE_DEBUG_INFO_14 1U
#define XPAR_AXIVDMA_1_ENABLE_DEBUG_INFO_15 1U
#define XPAR_AXIVDMA_1_ENABLE_DEBUG_ALL 0U
#define XPAR_AXIVDMA_1_c_addr_width 32U


/******************************************************************/

/* Definitions for driver BRAM */
#define XPAR_XBRAM_NUM_INSTANCES 1U

/* Definitions for peripheral AXI_BRAM_CTRL_0 */
#define XPAR_AXI_BRAM_CTRL_0_DEVICE_ID 0U
#define XPAR_AXI_BRAM_CTRL_0_DATA_WIDTH 32U
#define XPAR_AXI_BRAM_CTRL_0_ECC 0U
#define XPAR_AXI_BRAM_CTRL_0_FAULT_INJECT 0U
#define XPAR_AXI_BRAM_CTRL_0_CE_FAILING_REGISTERS 0U
#define XPAR_AXI_BRAM_CTRL_0_UE_FAILING_REGISTERS 0U
#define XPAR_AXI_BRAM_CTRL_0_ECC_STATUS_REGISTERS 0U
#define XPAR_AXI_BRAM_CTRL_0_CE_COUNTER_WIDTH 0U
#define XPAR_AXI_BRAM_CTRL_0_ECC_ONOFF_REGISTER 0U
#define XPAR_AXI_BRAM_CTRL_0_ECC_ONOFF_RESET_VALUE 0U
#define XPAR_AXI_BRAM_CTRL_0_WRITE_ACCESS 0U
#define XPAR_AXI_BRAM_CTRL_0_S_AXI_BASEADDR 0x80000000U
#define XPAR_AXI_BRAM_CTRL_0_S_AXI_HIGHADDR 0x80001FFFU
#define XPAR_AXI_BRAM_CTRL_0_S_AXI_CTRL_BASEADDR 0xFFFFFFFFU 
#define XPAR_AXI_BRAM_CTRL_0_S_AXI_CTRL_HIGHADDR 0xFFFFFFFFU 


/******************************************************************/

/* Canonical definitions for peripheral AXI_BRAM_CTRL_0 */
#define XPAR_BRAM_0_DEVICE_ID XPAR_AXI_BRAM_CTRL_0_DEVICE_ID
#define XPAR_BRAM_0_DATA_WIDTH 32U
#define XPAR_BRAM_0_ECC 0U
#define XPAR_BRAM_0_FAULT_INJECT 0U
#define XPAR_BRAM_0_CE_FAILING_REGISTERS 0U
#define XPAR_BRAM_0_UE_FAILING_REGISTERS 0U
#define XPAR_BRAM_0_ECC_STATUS_REGISTERS 0U
#define XPAR_BRAM_0_CE_COUNTER_WIDTH 0U
#define XPAR_BRAM_0_ECC_ONOFF_REGISTER 0U
#define XPAR_BRAM_0_ECC_ONOFF_RESET_VALUE 0U
#define XPAR_BRAM_0_WRITE_ACCESS 0U
#define XPAR_BRAM_0_BASEADDR 0x80000000U
#define XPAR_BRAM_0_HIGHADDR 0x80001FFFU


/******************************************************************/

/* Definitions for driver GPIO */
#define XPAR_XGPIO_NUM_INSTANCES 3

/* Definitions for peripheral AXI_GPIO_0 */
#define XPAR_AXI_GPIO_0_BASEADDR 0x40110000
#define XPAR_AXI_GPIO_0_HIGHADDR 0x4011FFFF
#define XPAR_AXI_GPIO_0_DEVICE_ID 0
#define XPAR_AXI_GPIO_0_INTERRUPT_PRESENT 1
#define XPAR_AXI_GPIO_0_IS_DUAL 1


/* Definitions for peripheral DAPLINK_IF_0_AXI_GPIO_0 */
#define XPAR_DAPLINK_IF_0_AXI_GPIO_0_BASEADDR 0x40010000
#define XPAR_DAPLINK_IF_0_AXI_GPIO_0_HIGHADDR 0x4001FFFF
#define XPAR_DAPLINK_IF_0_AXI_GPIO_0_DEVICE_ID 1
#define XPAR_DAPLINK_IF_0_AXI_GPIO_0_INTERRUPT_PRESENT 0
#define XPAR_DAPLINK_IF_0_AXI_GPIO_0_IS_DUAL 0


/* Definitions for peripheral OV_CMOS_AXI_GPIO_1 */
#define XPAR_OV_CMOS_AXI_GPIO_1_BASEADDR 0x40120000
#define XPAR_OV_CMOS_AXI_GPIO_1_HIGHADDR 0x4012FFFF
#define XPAR_OV_CMOS_AXI_GPIO_1_DEVICE_ID 2
#define XPAR_OV_CMOS_AXI_GPIO_1_INTERRUPT_PRESENT 1
#define XPAR_OV_CMOS_AXI_GPIO_1_IS_DUAL 1


/******************************************************************/

/* Canonical definitions for peripheral AXI_GPIO_0 */
#define XPAR_GPIO_0_BASEADDR 0x40110000
#define XPAR_GPIO_0_HIGHADDR 0x4011FFFF
#define XPAR_GPIO_0_DEVICE_ID XPAR_AXI_GPIO_0_DEVICE_ID
#define XPAR_GPIO_0_INTERRUPT_PRESENT 1
#define XPAR_GPIO_0_IS_DUAL 1

/* Canonical definitions for peripheral DAPLINK_IF_0_AXI_GPIO_0 */
#define XPAR_GPIO_1_BASEADDR 0x40010000
#define XPAR_GPIO_1_HIGHADDR 0x4001FFFF
#define XPAR_GPIO_1_DEVICE_ID XPAR_DAPLINK_IF_0_AXI_GPIO_0_DEVICE_ID
#define XPAR_GPIO_1_INTERRUPT_PRESENT 0
#define XPAR_GPIO_1_IS_DUAL 0

/* Canonical definitions for peripheral OV_CMOS_AXI_GPIO_1 */
#define XPAR_GPIO_2_BASEADDR 0x40120000
#define XPAR_GPIO_2_HIGHADDR 0x4012FFFF
#define XPAR_GPIO_2_DEVICE_ID XPAR_OV_CMOS_AXI_GPIO_1_DEVICE_ID
#define XPAR_GPIO_2_INTERRUPT_PRESENT 1
#define XPAR_GPIO_2_IS_DUAL 1


/******************************************************************/

/* Definitions for driver IIC */
#define XPAR_XIIC_NUM_INSTANCES 2

/* Definitions for peripheral AXI_IIC_1 */
#define XPAR_AXI_IIC_1_DEVICE_ID 0
#define XPAR_AXI_IIC_1_BASEADDR 0x40810000
#define XPAR_AXI_IIC_1_HIGHADDR 0x4081FFFF
#define XPAR_AXI_IIC_1_TEN_BIT_ADR 0
#define XPAR_AXI_IIC_1_GPO_WIDTH 1


/* Definitions for peripheral OV_CMOS_AXI_IIC_0 */
#define XPAR_OV_CMOS_AXI_IIC_0_DEVICE_ID 1
#define XPAR_OV_CMOS_AXI_IIC_0_BASEADDR 0x40800000
#define XPAR_OV_CMOS_AXI_IIC_0_HIGHADDR 0x4080FFFF
#define XPAR_OV_CMOS_AXI_IIC_0_TEN_BIT_ADR 0
#define XPAR_OV_CMOS_AXI_IIC_0_GPO_WIDTH 1


/******************************************************************/

/* Canonical definitions for peripheral AXI_IIC_1 */
#define XPAR_IIC_0_DEVICE_ID XPAR_AXI_IIC_1_DEVICE_ID
#define XPAR_IIC_0_BASEADDR 0x40810000
#define XPAR_IIC_0_HIGHADDR 0x4081FFFF
#define XPAR_IIC_0_TEN_BIT_ADR 0
#define XPAR_IIC_0_GPO_WIDTH 1

/* Canonical definitions for peripheral OV_CMOS_AXI_IIC_0 */
#define XPAR_IIC_1_DEVICE_ID XPAR_OV_CMOS_AXI_IIC_0_DEVICE_ID
#define XPAR_IIC_1_BASEADDR 0x40800000
#define XPAR_IIC_1_HIGHADDR 0x4080FFFF
#define XPAR_IIC_1_TEN_BIT_ADR 0
#define XPAR_IIC_1_GPO_WIDTH 1


/******************************************************************/

/* Definitions for driver MIG_7SERIES */
#define XPAR_XMIG7SERIES_NUM_INSTANCES 1U

/* Definitions for peripheral OV_CMOS_MIG_7SERIES_0 */
#define XPAR_OV_CMOS_MIG_7SERIES_0_DEVICE_ID 0U
#define XPAR_OV_CMOS_MIG_7SERIES_0_DDR2_ROW_WIDTH 13U
#define XPAR_OV_CMOS_MIG_7SERIES_0_DDR2_COL_WIDTH 0U
#define XPAR_OV_CMOS_MIG_7SERIES_0_DDR2_BANK_WIDTH 3U
#define XPAR_OV_CMOS_MIG_7SERIES_0_DDR2_DQ_WIDTH 16U


/******************************************************************/


/* Definitions for peripheral OV_CMOS_MIG_7SERIES_0 */
#define XPAR_OV_CMOS_MIG_7SERIES_0_BASEADDR 0x60000000
#define XPAR_OV_CMOS_MIG_7SERIES_0_HIGHADDR 0x67FFFFFF


/******************************************************************/

/* Canonical definitions for peripheral OV_CMOS_MIG_7SERIES_0 */
#define XPAR_MIG7SERIES_0_DEVICE_ID XPAR_OV_CMOS_MIG_7SERIES_0_DEVICE_ID
#define XPAR_MIG7SERIES_0_DDR_ROW_WIDTH 13U
#define XPAR_MIG7SERIES_0_DDR_COL_WIDTH 0U
#define XPAR_MIG7SERIES_0_DDR_BANK_WIDTH 3U
#define XPAR_MIG7SERIES_0_DDR_DQ_WIDTH 16U
#define XPAR_MIG7SERIES_0_BASEADDR 0x60000000U
#define XPAR_MIG7SERIES_0_HIGHADDR 0x67FFFFFFU


/******************************************************************/

/* Definitions for driver SPI */
#define XPAR_XSPI_NUM_INSTANCES 4U

/* Definitions for peripheral AXI_QUAD_SPI_0 */
#define XPAR_AXI_QUAD_SPI_0_DEVICE_ID 0U
#define XPAR_AXI_QUAD_SPI_0_BASEADDR 0x40130000U
#define XPAR_AXI_QUAD_SPI_0_HIGHADDR 0x4013FFFFU
#define XPAR_AXI_QUAD_SPI_0_FIFO_DEPTH 256U
#define XPAR_AXI_QUAD_SPI_0_FIFO_EXIST 1U
#define XPAR_AXI_QUAD_SPI_0_SPI_SLAVE_ONLY 0U
#define XPAR_AXI_QUAD_SPI_0_NUM_SS_BITS 1U
#define XPAR_AXI_QUAD_SPI_0_NUM_TRANSFER_BITS 8U
#define XPAR_AXI_QUAD_SPI_0_SPI_MODE 2U
#define XPAR_AXI_QUAD_SPI_0_TYPE_OF_AXI4_INTERFACE 0U
#define XPAR_AXI_QUAD_SPI_0_AXI4_BASEADDR 0U
#define XPAR_AXI_QUAD_SPI_0_AXI4_HIGHADDR 0U
#define XPAR_AXI_QUAD_SPI_0_XIP_MODE 0U

/* Canonical definitions for peripheral AXI_QUAD_SPI_0 */
#define XPAR_SPI_0_DEVICE_ID 0U
#define XPAR_SPI_0_BASEADDR 0x40130000U
#define XPAR_SPI_0_HIGHADDR 0x4013FFFFU
#define XPAR_SPI_0_FIFO_DEPTH 256U
#define XPAR_SPI_0_FIFO_EXIST 1U
#define XPAR_SPI_0_SPI_SLAVE_ONLY 0U
#define XPAR_SPI_0_NUM_SS_BITS 1U
#define XPAR_SPI_0_NUM_TRANSFER_BITS 8U
#define XPAR_SPI_0_SPI_MODE 2U
#define XPAR_SPI_0_TYPE_OF_AXI4_INTERFACE 0U
#define XPAR_SPI_0_AXI4_BASEADDR 0U
#define XPAR_SPI_0_AXI4_HIGHADDR 0U
#define XPAR_SPI_0_XIP_MODE 0U
#define XPAR_SPI_0_USE_STARTUP 1U



/* Definitions for peripheral DAPLINK_IF_0_AXI_QUAD_SPI_0 */
#define XPAR_DAPLINK_IF_0_AXI_QUAD_SPI_0_DEVICE_ID 1U
#define XPAR_DAPLINK_IF_0_AXI_QUAD_SPI_0_BASEADDR 0x40020000U
#define XPAR_DAPLINK_IF_0_AXI_QUAD_SPI_0_HIGHADDR 0x4002FFFFU
#define XPAR_DAPLINK_IF_0_AXI_QUAD_SPI_0_FIFO_DEPTH 256U
#define XPAR_DAPLINK_IF_0_AXI_QUAD_SPI_0_FIFO_EXIST 1U
#define XPAR_DAPLINK_IF_0_AXI_QUAD_SPI_0_SPI_SLAVE_ONLY 0U
#define XPAR_DAPLINK_IF_0_AXI_QUAD_SPI_0_NUM_SS_BITS 1U
#define XPAR_DAPLINK_IF_0_AXI_QUAD_SPI_0_NUM_TRANSFER_BITS 8U
#define XPAR_DAPLINK_IF_0_AXI_QUAD_SPI_0_SPI_MODE 2U
#define XPAR_DAPLINK_IF_0_AXI_QUAD_SPI_0_TYPE_OF_AXI4_INTERFACE 0U
#define XPAR_DAPLINK_IF_0_AXI_QUAD_SPI_0_AXI4_BASEADDR 0U
#define XPAR_DAPLINK_IF_0_AXI_QUAD_SPI_0_AXI4_HIGHADDR 0U
#define XPAR_DAPLINK_IF_0_AXI_QUAD_SPI_0_XIP_MODE 0U

/* Canonical definitions for peripheral DAPLINK_IF_0_AXI_QUAD_SPI_0 */
#define XPAR_SPI_1_DEVICE_ID 1U
#define XPAR_SPI_1_BASEADDR 0x40020000U
#define XPAR_SPI_1_HIGHADDR 0x4002FFFFU
#define XPAR_SPI_1_FIFO_DEPTH 256U
#define XPAR_SPI_1_FIFO_EXIST 1U
#define XPAR_SPI_1_SPI_SLAVE_ONLY 0U
#define XPAR_SPI_1_NUM_SS_BITS 1U
#define XPAR_SPI_1_NUM_TRANSFER_BITS 8U
#define XPAR_SPI_1_SPI_MODE 2U
#define XPAR_SPI_1_TYPE_OF_AXI4_INTERFACE 0U
#define XPAR_SPI_1_AXI4_BASEADDR 0U
#define XPAR_SPI_1_AXI4_HIGHADDR 0U
#define XPAR_SPI_1_XIP_MODE 0U
#define XPAR_SPI_1_USE_STARTUP 0U



/* Definitions for peripheral DAPLINK_IF_0_AXI_SINGLE_SPI_0 */
#define XPAR_DAPLINK_IF_0_AXI_SINGLE_SPI_0_DEVICE_ID 2U
#define XPAR_DAPLINK_IF_0_AXI_SINGLE_SPI_0_BASEADDR 0x40030000U
#define XPAR_DAPLINK_IF_0_AXI_SINGLE_SPI_0_HIGHADDR 0x4003FFFFU
#define XPAR_DAPLINK_IF_0_AXI_SINGLE_SPI_0_FIFO_DEPTH 256U
#define XPAR_DAPLINK_IF_0_AXI_SINGLE_SPI_0_FIFO_EXIST 1U
#define XPAR_DAPLINK_IF_0_AXI_SINGLE_SPI_0_SPI_SLAVE_ONLY 0U
#define XPAR_DAPLINK_IF_0_AXI_SINGLE_SPI_0_NUM_SS_BITS 1U
#define XPAR_DAPLINK_IF_0_AXI_SINGLE_SPI_0_NUM_TRANSFER_BITS 8U
#define XPAR_DAPLINK_IF_0_AXI_SINGLE_SPI_0_SPI_MODE 0U
#define XPAR_DAPLINK_IF_0_AXI_SINGLE_SPI_0_TYPE_OF_AXI4_INTERFACE 0U
#define XPAR_DAPLINK_IF_0_AXI_SINGLE_SPI_0_AXI4_BASEADDR 0U
#define XPAR_DAPLINK_IF_0_AXI_SINGLE_SPI_0_AXI4_HIGHADDR 0U
#define XPAR_DAPLINK_IF_0_AXI_SINGLE_SPI_0_XIP_MODE 0U

/* Canonical definitions for peripheral DAPLINK_IF_0_AXI_SINGLE_SPI_0 */
#define XPAR_SPI_2_DEVICE_ID 2U
#define XPAR_SPI_2_BASEADDR 0x40030000U
#define XPAR_SPI_2_HIGHADDR 0x4003FFFFU
#define XPAR_SPI_2_FIFO_DEPTH 256U
#define XPAR_SPI_2_FIFO_EXIST 1U
#define XPAR_SPI_2_SPI_SLAVE_ONLY 0U
#define XPAR_SPI_2_NUM_SS_BITS 1U
#define XPAR_SPI_2_NUM_TRANSFER_BITS 8U
#define XPAR_SPI_2_SPI_MODE 0U
#define XPAR_SPI_2_TYPE_OF_AXI4_INTERFACE 0U
#define XPAR_SPI_2_AXI4_BASEADDR 0U
#define XPAR_SPI_2_AXI4_HIGHADDR 0U
#define XPAR_SPI_2_XIP_MODE 0U
#define XPAR_SPI_2_USE_STARTUP 0U



/* Definitions for peripheral DAPLINK_IF_0_AXI_XIP_QUAD_SPI_0 */
#define XPAR_DAPLINK_IF_0_AXI_XIP_QUAD_SPI_0_DEVICE_ID 3U
#define XPAR_DAPLINK_IF_0_AXI_XIP_QUAD_SPI_0_BASEADDR 0x40000000U
#define XPAR_DAPLINK_IF_0_AXI_XIP_QUAD_SPI_0_HIGHADDR 0x4000FFFFU
#define XPAR_DAPLINK_IF_0_AXI_XIP_QUAD_SPI_0_FIFO_DEPTH 16U
#define XPAR_DAPLINK_IF_0_AXI_XIP_QUAD_SPI_0_FIFO_EXIST 1U
#define XPAR_DAPLINK_IF_0_AXI_XIP_QUAD_SPI_0_SPI_SLAVE_ONLY 0U
#define XPAR_DAPLINK_IF_0_AXI_XIP_QUAD_SPI_0_NUM_SS_BITS 1U
#define XPAR_DAPLINK_IF_0_AXI_XIP_QUAD_SPI_0_NUM_TRANSFER_BITS 8U
#define XPAR_DAPLINK_IF_0_AXI_XIP_QUAD_SPI_0_SPI_MODE 2U
#define XPAR_DAPLINK_IF_0_AXI_XIP_QUAD_SPI_0_TYPE_OF_AXI4_INTERFACE 1U
#define XPAR_DAPLINK_IF_0_AXI_XIP_QUAD_SPI_0_AXI4_BASEADDR 0x00000000U
#define XPAR_DAPLINK_IF_0_AXI_XIP_QUAD_SPI_0_AXI4_HIGHADDR 0x000FFFFFU
#define XPAR_DAPLINK_IF_0_AXI_XIP_QUAD_SPI_0_XIP_MODE 1U

/* Canonical definitions for peripheral DAPLINK_IF_0_AXI_XIP_QUAD_SPI_0 */
#define XPAR_SPI_3_DEVICE_ID 3U
#define XPAR_SPI_3_BASEADDR 0x40000000U
#define XPAR_SPI_3_HIGHADDR 0x4000FFFFU
#define XPAR_SPI_3_FIFO_DEPTH 16U
#define XPAR_SPI_3_FIFO_EXIST 1U
#define XPAR_SPI_3_SPI_SLAVE_ONLY 0U
#define XPAR_SPI_3_NUM_SS_BITS 1U
#define XPAR_SPI_3_NUM_TRANSFER_BITS 8U
#define XPAR_SPI_3_SPI_MODE 2U
#define XPAR_SPI_3_TYPE_OF_AXI4_INTERFACE 1U
#define XPAR_SPI_3_AXI4_BASEADDR 0x00000000U
#define XPAR_SPI_3_AXI4_HIGHADDR 0x000FFFFFU
#define XPAR_SPI_3_XIP_MODE 1U
#define XPAR_SPI_3_USE_STARTUP 0U



/******************************************************************/

/* Definitions for driver THRESHOLD2_TOP */
#define XPAR_XTHRESHOLD2_NUM_INSTANCES 1

/* Definitions for peripheral OV_CMOS_IMAGE_PROCESS_THRESHOLD2_1 */
#define XPAR_OV_CMOS_IMAGE_PROCESS_THRESHOLD2_1_DEVICE_ID 0
#define XPAR_OV_CMOS_IMAGE_PROCESS_THRESHOLD2_1_S_AXI_CONTROL_BUS_BASEADDR 0x44A10000
#define XPAR_OV_CMOS_IMAGE_PROCESS_THRESHOLD2_1_S_AXI_CONTROL_BUS_HIGHADDR 0x44A1FFFF


/******************************************************************/

/* Canonical definitions for peripheral OV_CMOS_IMAGE_PROCESS_THRESHOLD2_1 */
#define XPAR_XTHRESHOLD2_0_DEVICE_ID XPAR_OV_CMOS_IMAGE_PROCESS_THRESHOLD2_1_DEVICE_ID
#define XPAR_XTHRESHOLD2_0_S_AXI_CONTROL_BUS_BASEADDR 0x44A10000
#define XPAR_XTHRESHOLD2_0_S_AXI_CONTROL_BUS_HIGHADDR 0x44A1FFFF


/******************************************************************/

/* Definitions for driver TMRCTR */
#define XPAR_XTMRCTR_NUM_INSTANCES 1U

/* Definitions for peripheral AXI_TIMER_0 */
#define XPAR_AXI_TIMER_0_DEVICE_ID 0U
#define XPAR_AXI_TIMER_0_BASEADDR 0x41C00000U
#define XPAR_AXI_TIMER_0_HIGHADDR 0x41C0FFFFU
#define XPAR_AXI_TIMER_0_CLOCK_FREQ_HZ 50000000U


/******************************************************************/

/* Canonical definitions for peripheral AXI_TIMER_0 */
#define XPAR_TMRCTR_0_DEVICE_ID 0U
#define XPAR_TMRCTR_0_BASEADDR 0x41C00000U
#define XPAR_TMRCTR_0_HIGHADDR 0x41C0FFFFU
#define XPAR_TMRCTR_0_CLOCK_FREQ_HZ XPAR_AXI_TIMER_0_CLOCK_FREQ_HZ

/******************************************************************/

/* Definitions for driver UARTLITE */
#define XPAR_XUARTLITE_NUM_INSTANCES 1

/* Definitions for peripheral DAPLINK_IF_0_AXI_UARTLITE_0 */
#define XPAR_DAPLINK_IF_0_AXI_UARTLITE_0_BASEADDR 0x40100000
#define XPAR_DAPLINK_IF_0_AXI_UARTLITE_0_HIGHADDR 0x4010FFFF
#define XPAR_DAPLINK_IF_0_AXI_UARTLITE_0_DEVICE_ID 0
#define XPAR_DAPLINK_IF_0_AXI_UARTLITE_0_BAUDRATE 115200
#define XPAR_DAPLINK_IF_0_AXI_UARTLITE_0_USE_PARITY 0
#define XPAR_DAPLINK_IF_0_AXI_UARTLITE_0_ODD_PARITY 0
#define XPAR_DAPLINK_IF_0_AXI_UARTLITE_0_DATA_BITS 8


/******************************************************************/

/* Canonical definitions for peripheral DAPLINK_IF_0_AXI_UARTLITE_0 */
#define XPAR_UARTLITE_0_DEVICE_ID XPAR_DAPLINK_IF_0_AXI_UARTLITE_0_DEVICE_ID
#define XPAR_UARTLITE_0_BASEADDR 0x40100000
#define XPAR_UARTLITE_0_HIGHADDR 0x4010FFFF
#define XPAR_UARTLITE_0_BAUDRATE 115200
#define XPAR_UARTLITE_0_USE_PARITY 0
#define XPAR_UARTLITE_0_ODD_PARITY 0
#define XPAR_UARTLITE_0_DATA_BITS 8


/******************************************************************/

#endif  /* end of protection macro */
