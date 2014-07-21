File path: arch/arm/include/asm/arch-am33xx/sys_proto.h
File name: sys_proto.h


System information header


 void mpu_pll_config(int mpupll_M);
+void core_pll_config(int opp);
 void sdelay(unsigned long);
 void gpmc_init(void);
 void omap_nand_switch_ecc(int);
