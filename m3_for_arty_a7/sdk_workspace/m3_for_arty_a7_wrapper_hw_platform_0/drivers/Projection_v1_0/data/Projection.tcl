

proc generate {drv_handle} {
	xdefine_include_file $drv_handle "xparameters.h" "Projection" "NUM_INSTANCES" "DEVICE_ID"  "C_Ctrl_AXI_BASEADDR" "C_Ctrl_AXI_HIGHADDR"
}
