@REM - Copy the xpseudo_asm_rvct.h and xpseudo_asm_rvct.c to bsp include
copy ..\vivado\Arm_sw_repository\CortexM\bsp\standalone_v6_7\src\arm\cortexm3\armcc\xpseudo_asm_rvct.* .\m3_for_arty_a7\sdk_workspace\standalone_bsp_0\Cortex_M3_0\include\

@REM - Copy the xiic.h to \standalone_bsp_0\Cortex_M3_0\libsrc\iic_v3_4\src\
copy /y .\arm_xilinx_file\xiic.h .\m3_for_arty_a7\sdk_workspace\standalone_bsp_0\Cortex_M3_0\libsrc\iic_v3_4\src\

@REM - Copy the xiic.h to \standalone_bsp_0\Cortex_M3_0\include\
copy /y .\arm_xilinx_file\xiic.h .\m3_for_arty_a7\sdk_workspace\standalone_bsp_0\Cortex_M3_0\include\

@REM - Copy the xil_sleepcommon.c to \standalone_bsp_0\Cortex_M3_0\libsrc\standalone_v6_7\src\
copy /y .\arm_xilinx_file\xil_sleepcommon.c .\m3_for_arty_a7\sdk_workspace\standalone_bsp_0\Cortex_M3_0\libsrc\standalone_v6_7\src\

@REM - Copy the xaxivdma_channel.c to \m3_for_arty_a7\sdk_workspace\standalone_bsp_0\Cortex_M3_0\libsrc\axivdma_v6_5\src\
copy /y .\arm_xilinx_file\xaxivdma_channel.c .\m3_for_arty_a7\sdk_workspace\standalone_bsp_0\Cortex_M3_0\libsrc\axivdma_v6_5\src


