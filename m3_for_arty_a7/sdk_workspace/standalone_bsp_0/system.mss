
 PARAMETER VERSION = 2.2.0


BEGIN OS
 PARAMETER OS_NAME = standalone
 PARAMETER OS_VER = 6.7
 PARAMETER PROC_INSTANCE = Cortex_M3_0
 PARAMETER sleep_timer = axi_timer_0
 PARAMETER stdin = axi_uartlite_0
 PARAMETER stdout = axi_uartlite_0
END


BEGIN PROCESSOR
 PARAMETER DRIVER_NAME = cpu_cortexm3
 PARAMETER DRIVER_VER = 1.0
 PARAMETER HW_INSTANCE = Cortex_M3_0
END


BEGIN DRIVER
 PARAMETER DRIVER_NAME = gpio
 PARAMETER DRIVER_VER = 4.3
 PARAMETER HW_INSTANCE = LCD_axi_gpio_1
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = spi
 PARAMETER DRIVER_VER = 4.4
 PARAMETER HW_INSTANCE = LCD_axi_quad_spi_0
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = bram
 PARAMETER DRIVER_VER = 4.2
 PARAMETER HW_INSTANCE = axi_bram_ctrl_0
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = gpio
 PARAMETER DRIVER_VER = 4.3
 PARAMETER HW_INSTANCE = axi_gpio_0
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = tmrctr
 PARAMETER DRIVER_VER = 4.4
 PARAMETER HW_INSTANCE = axi_timer_0
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = uartns550
 PARAMETER DRIVER_VER = 3.5
 PARAMETER HW_INSTANCE = axi_uart16550_0
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = uartlite
 PARAMETER DRIVER_VER = 3.2
 PARAMETER HW_INSTANCE = axi_uartlite_0
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = uartlite
 PARAMETER DRIVER_VER = 3.2
 PARAMETER HW_INSTANCE = axi_uartlite_keyboard
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = contrast_hls_rom
 PARAMETER DRIVER_VER = 1.4
 PARAMETER HW_INSTANCE = ov_cmos_Image_Process_contrast_contrast_hls_rom_0
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = judge
 PARAMETER DRIVER_VER = 1.0
 PARAMETER HW_INSTANCE = ov_cmos_Image_Process_contrast_judge_1
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = draw_line_hls
 PARAMETER DRIVER_VER = 1.2
 PARAMETER HW_INSTANCE = ov_cmos_Image_Process_drawlines_draw_line_hls_0
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = gpio
 PARAMETER DRIVER_VER = 4.3
 PARAMETER HW_INSTANCE = ov_cmos_Image_Process_gpio_ap_ctrl
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = mask
 PARAMETER DRIVER_VER = 2.3
 PARAMETER HW_INSTANCE = ov_cmos_Image_Process_mask_0
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = projection1_hls
 PARAMETER DRIVER_VER = 4.4
 PARAMETER HW_INSTANCE = ov_cmos_Image_Process_projection1_projection1_hls_0
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = projection_mul_hls
 PARAMETER DRIVER_VER = 1.1
 PARAMETER HW_INSTANCE = ov_cmos_Image_Process_projection_mul_hls_0
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = reorder_resize
 PARAMETER DRIVER_VER = 1.1
 PARAMETER HW_INSTANCE = ov_cmos_Image_Process_resize_reorder_resize_0
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = threshold2
 PARAMETER DRIVER_VER = 1.6
 PARAMETER HW_INSTANCE = ov_cmos_Image_Process_threshold2_0
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = axivdma
 PARAMETER DRIVER_VER = 6.5
 PARAMETER HW_INSTANCE = ov_cmos_axi_vdma_0
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = axis_switch
 PARAMETER DRIVER_VER = 1.2
 PARAMETER HW_INSTANCE = ov_cmos_axis_switch_0
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = axis_switch
 PARAMETER DRIVER_VER = 1.2
 PARAMETER HW_INSTANCE = ov_cmos_axis_switch_1
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = gpio
 PARAMETER DRIVER_VER = 4.3
 PARAMETER HW_INSTANCE = ov_cmos_cmos2axis_axi_gpio_1
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = iic
 PARAMETER DRIVER_VER = 3.4
 PARAMETER HW_INSTANCE = ov_cmos_cmos2axis_axi_iic_0
END

BEGIN DRIVER
 PARAMETER DRIVER_NAME = mig_7series
 PARAMETER DRIVER_VER = 2.1
 PARAMETER HW_INSTANCE = ov_cmos_mig_7series_0
END


