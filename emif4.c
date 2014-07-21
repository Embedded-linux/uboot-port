File path: arch/arm/cpu/armv7/am33xx/emif4.c
File name: emif4.c

AM33XX emif4 configuration file



-#ifdef CONFIG_SPL_BUILD
+#if defined(CONFIG_SPL_BUILD) || defined(CONFIG_NOR_BOOT)


The macro is defined in the following scenario

#if defined(CONFIG_SPL_BUILD) || defined(CONFIG_NOR_BOOT)
static struct vtp_reg *vtpreg = (struct vtp_reg *)VTP0_CTRL_ADDR;
static struct ddr_ctrl *ddrctrl = (struct ddr_ctrl *)DDR_CTRL_ADDR;
