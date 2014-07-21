FIle path: board/ti/am335x/board.c
File name: board.c


board am335x board initialization functions

static struct wd_timer *wdtimer = (struct wd_timer *)WDT_BASE;
-#ifdef CONFIG_SPL_BUILD
+#if defined(CONFIG_SPL_BUILD) || (CONFIG_NOR_BOOT)
 static struct uart_sys *uart_base = (struct uart_sys *)DEFAULT_UART_BASE;
 #endif


static int read_eeprom(void)
 }
 
 /* UART Defines */
-#ifdef CONFIG_SPL_BUILD
+#if defined(CONFIG_SPL_BUILD) || defined(CONFIG_NOR_BOOT)


static const struct ddr_data ddr3_data = {
 	.datadldiff0 = PHY_DLL_LOCK_DIFF,
 };
 
+static const struct ddr_data ddr3_beagleblack_data = {
+	.datardsratio0 = MT41K256M16HA125E_RD_DQS,
+ 	.datawdsratio0 = MT41K256M16HA125E_WR_DQS,
+	.datafwsratio0 = MT41K256M16HA125E_PHY_FIFO_WE,
+	.datawrsratio0 = MT41K256M16HA125E_PHY_WR_DATA,
+	.datadldiff0 = PHY_DLL_LOCK_DIFF,
+};
+


static const struct cmd_control ddr3_cmd_ctrl_data = {
 	.cmd2iclkout = MT41J128MJT125_INVERT_CLKOUT,
 };
 
+static const struct cmd_control ddr3_beagleblack_cmd_ctrl_data = {
+	.cmd0csratio = MT41K256M16HA125E_RATIO,
+	.cmd0dldiff = MT41K256M16HA125E_DLL_LOCK_DIFF,
+	.cmd0iclkout = MT41K256M16HA125E_INVERT_CLKOUT,
+
+	.cmd1csratio = MT41K256M16HA125E_RATIO,
+	.cmd1dldiff = MT41K256M16HA125E_DLL_LOCK_DIFF,
+	.cmd1iclkout = MT41K256M16HA125E_INVERT_CLKOUT,
+
+	.cmd2csratio = MT41K256M16HA125E_RATIO,
+	.cmd2dldiff = MT41K256M16HA125E_DLL_LOCK_DIFF,
+	.cmd2iclkout = MT41K256M16HA125E_INVERT_CLKOUT,
+};
+


static struct emif_regs ddr3_emif_reg_data = {
 				PHY_EN_DYN_PWRDN,
 };
 
+static struct emif_regs ddr3_beagleblack_emif_reg_data = {
+	.sdram_config = MT41K256M16HA125E_EMIF_SDCFG,
+	.ref_ctrl = MT41K256M16HA125E_EMIF_SDREF,
+	.sdram_tim1 = MT41K256M16HA125E_EMIF_TIM1,
+	.sdram_tim2 = MT41K256M16HA125E_EMIF_TIM2,
+	.sdram_tim3 = MT41K256M16HA125E_EMIF_TIM3,
+	.zq_config = MT41K256M16HA125E_ZQ_CFG,
+	.emif_ddr_phy_ctlr_1 = MT41K256M16HA125E_EMIF_READ_LATENCY,
+};
+



static struct emif_regs ddr3_evm_emif_reg_data = {
 	.sdram_tim2 = MT41J512M8RH125_EMIF_TIM2,
 	.sdram_tim3 = MT41J512M8RH125_EMIF_TIM3,
 	.zq_config = MT41J512M8RH125_ZQ_CFG,
-	.emif_ddr_phy_ctlr_1 = MT41J512M8RH125_EMIF_READ_LATENCY,
+	.emif_ddr_phy_ctlr_1 = MT41J512M8RH125_EMIF_READ_LATENCY |
+				PHY_EN_DYN_PWRDN,
 };
 
 
 
 
 
 
void am33xx_spl_board_init(void)
 {
-	if (!strncmp("A335BONE", header.name, 8)) {
+	int mpu_vdd, mpu_pll, sil_rev;
+
+	/* Assume PG 1.0 */
+	mpu_pll = MPUPLL_M_720;
+
+	sil_rev = readl(&cdev->deviceid) >> 28;
+	if (sil_rev == 1)
+		/* PG 2.0, efuse may not be set. */
+		mpu_pll = MPUPLL_M_800;
+	else if (sil_rev >= 2) {
+		/* Check what the efuse says our max speed is. */
+		int efuse_arm_mpu_max_freq;
+		efuse_arm_mpu_max_freq = readl(&cdev->efuse_sma);
+		if ((efuse_arm_mpu_max_freq & DEVICE_ID_MASK) ==
+				AM335X_ZCZ_1000)
+			mpu_pll = MPUPLL_M_1000;
+		else if ((efuse_arm_mpu_max_freq & DEVICE_ID_MASK) ==
+				AM335X_ZCZ_800)
+			mpu_pll = MPUPLL_M_800;
+	}
+
+	/*
+	 * HACK: PG 2.0 should have max of 800MHz but Beaglebone Black
+	 * can work at 1GHz.
+	 */
+	if (board_is_bone_lt())
+		mpu_pll = MPUPLL_M_1000;
+
+	if (board_is_bone() || board_is_bone_lt()) {
 		/* BeagleBone PMIC Code */
 		uchar pmic_status_reg;
+		int usb_cur_lim;
+
+		/* Only perform PMIC configurations if board rev > A1 */
+		if (board_is_bone() && !strncmp(header.version, "00A1", 4))
+			return;
 
 		if (i2c_probe(TPS65217_CHIP_PM))
 			return;
 			
 			
 			
 			
 			void am33xx_spl_board_init(void)
 		if (tps65217_reg_read(STATUS, &pmic_status_reg))
 			return;
 
-		/* Increase USB current limit to 1300mA */
+		/*
+		 * Increase USB current limit to 1300mA or 1800mA and set
+		 * the MPU voltage controller as needed.
+		 */
+		if (mpu_pll == MPUPLL_M_1000) {
+			usb_cur_lim = USB_INPUT_CUR_LIMIT_1800MA;
+			mpu_vdd = DCDC_VOLT_SEL_1325MV;
+		} else {
+			usb_cur_lim = USB_INPUT_CUR_LIMIT_1300MA;
+			mpu_vdd = DCDC_VOLT_SEL_1275MV;
+		}
+
 		if (tps65217_reg_write(PROT_LEVEL_NONE, POWER_PATH,
-				       USB_INPUT_CUR_LIMIT_1300MA,
-				       USB_INPUT_CUR_LIMIT_MASK))
+				       usb_cur_lim, USB_INPUT_CUR_LIMIT_MASK))
 			printf("tps65217_reg_write failure\n");
 			-		/* Only perform PMIC configurations if board rev > A1 */
-		if (!strncmp(header.version, "00A1", 4))
+
+		/* Set DCDC3 (CORE) voltage to 1.125V */
+		if (tps65217_voltage_update(DEFDCDC3, DCDC_VOLT_SEL_1125MV)) {
+			printf("tps65217_voltage_update failure\n");
 			return;
+		}
+
+		/* Set CORE Frequency to what we detected */
+		core_pll_config(OPP_100);
 
 		/* Set DCDC2 (MPU) voltage to 1.275V */
-		if (tps65217_voltage_update(DEFDCDC2,
-					     DCDC_VOLT_SEL_1275MV)) {
+		if (tps65217_voltage_update(DEFDCDC2, mpu_vdd)) {
 			printf("tps65217_voltage_update failure\n");
 			return;
 		}
 		 
-		/* Set LDO3, LDO4 output voltage to 3.3V */
-		if (tps65217_reg_write(PROT_LEVEL_2, DEFLS1,
+		/* Set MPU Frequency to what we detected */
+		mpu_pll_config(mpu_pll);
+
+		/* 
+		 * Set LDO3, LDO4 output voltage to 3.3V for Beaglebone.
+		 * Set LDO3 to 1.8V and LDO4 to 3.3V for Beaglebone Black.
+		 */
+		if (board_is_bone()) {
+			if (tps65217_reg_write(PROT_LEVEL_2, DEFLS1,
 				       LDO_VOLTAGE_OUT_3_3, LDO_MASK))
-			printf("tps65217_reg_write failure\n");
+				printf("tps65217_reg_write failure\n");
+		} else {
+			if (tps65217_reg_write(PROT_LEVEL_2, DEFLS1,
+				       LDO_VOLTAGE_OUT_1_8, LDO_MASK))
+				printf("tps65217_reg_write failure\n");
+		}


-		if (!(pmic_status_reg & PWR_SRC_AC_BITMASK)) {
+		/* Only Beaglebone needs the AC power, not Beaglebone Black */
+		if (board_is_bone() &&
+				 !(pmic_status_reg & PWR_SRC_AC_BITMASK)) {
 			printf("No AC power, disabling frequency switch\n");
 			return;
 		}
-
-		/* Set MPU Frequency to 720MHz */
-		mpu_pll_config(MPUPLL_M_720);
 	} else {
 		uchar buf[4];
+
 		/*
 		-		 * EVM PMIC code.  All boards currently want an MPU voltage
-		 * of 1.2625V and CORE voltage of 1.1375V to operate at
-		 * 720MHz.
+		 * The GP EVM, IDK and EVM SK use a TPS65910 PMIC.  For all
+		 * MPU frequencies we support we use a CORE voltage of
+		 * 1.1375V.  For 1GHz we need to use an MPU voltage of
+		 * 1.3250V and for 720MHz or 800MHz we use 1.2625V.
 		 */
 		if (i2c_probe(PMIC_CTRL_I2C_ADDR))
 			return;
 			oid am33xx_spl_board_init(void)
 		if (i2c_write(PMIC_CTRL_I2C_ADDR, PMIC_DEVCTRL_REG, 1, buf, 1))
 			return;
 
-		if (!voltage_update(MPU, PMIC_OP_REG_SEL_1_2_6) &&
-				!voltage_update(CORE, PMIC_OP_REG_SEL_1_1_3)) {
-			if (board_is_evm_15_or_later())
-				mpu_pll_config(MPUPLL_M_800);
-			else
-				mpu_pll_config(MPUPLL_M_720);
-		}
+		/*
+		 * Unless we're running at 1GHz we use thesame VDD for
+		 * all other frequencies we switch to (currently 720MHz,
+		 * 800MHz or 1GHz).
+		 */
+		if (mpu_pll == MPUPLL_M_1000)
+			mpu_vdd = PMIC_OP_REG_SEL_1_3_2_5;
+		else
+			mpu_vdd = PMIC_OP_REG_SEL_1_2_6;
+
+		if (!voltage_update(CORE, PMIC_OP_REG_SEL_1_1_3))
+			core_pll_config(OPP_100);
+		if (!voltage_update(MPU, mpu_vdd))
+			mpu_pll_config(mpu_pll);
 	}
 }
 #endif
 void s_init(void)
 {
+	__maybe_unused struct am335x_baseboard_id header;
+#ifdef CONFIG_NOR_BOOT
+	asm("stmfd      sp!, {r2 - r4}");
+	asm("movw       r4, #0x8A4");
+	asm("movw       r3, #0x44E1");
+	asm("orr        r4, r4, r3, lsl #16");
+	asm("mov        r2, #9");
+	asm("mov        r3, #8");
+	asm("gpmc_mux:  str     r2, [r4], #4");
+	asm("subs       r3, r3, #1");
+	asm("bne        gpmc_mux");
+	asm("ldmfd      sp!, {r2 - r4}");
+#endif
+


void s_init(void)
 	while (readl(&wdtimer->wdtwwps) != 0x0)
 		;
 
-#ifdef CONFIG_SPL_BUILD
+#if defined(CONFIG_SPL_BUILD) || defined(CONFIG_NOR_BOOT)
 	/* Setup the PLLs and the clocks for the peripherals */
 	pll_init();
 
@@ -524,18 +639,59 @@ void s_init(void)
 	regVal |= UART_SMART_IDLE_EN;
 	writel(regVal, &uart_base->uartsyscfg);
 
+#if defined(CONFIG_NOR_BOOT)
+	gd = (gd_t *) ((CONFIG_SYS_INIT_SP_ADDR) & ~0x07);
+	gd->baudrate = CONFIG_BAUDRATE;
+	serial_init();
+	gd->have_console = 1;
+#else
gd = &gdata;
 
 	preloader_console_init();
+#endif
 
 	/* Initalize the board header */
 	enable_i2c0_pin_mux();
 	i2c_init(CONFIG_SYS_I2C_SPEED, CONFIG_SYS_I2C_SLAVE);
+#ifndef CONFIG_NOR_BOOT
 	if (read_eeprom() < 0)
 		puts("Could not get board ID.\n");
+#endif
+
+	/* Check if baseboard eeprom is available */
+	if (i2c_probe(CONFIG_SYS_I2C_EEPROM_ADDR)) {
+		puts("Could not probe the EEPROM; something fundamentally "
+			"wrong on the I2C bus.\n");
+	}
+
+	/* read the eeprom using i2c */
+	if (i2c_read(CONFIG_SYS_I2C_EEPROM_ADDR, 0, 2, (uchar *)&header,
+							sizeof(header))) {
+		puts("Could not read the EEPROM; something fundamentally"
+			" wrong on the I2C bus.\n");
+	}
+
+	if (header.magic != 0xEE3355AA) {
+		/*
+		 * read the eeprom using i2c again,
+		 * but use only a 1 byte address
+		 */
+		if (i2c_read(CONFIG_SYS_I2C_EEPROM_ADDR, 0, 1,
+					(uchar *)&header, sizeof(header))) {
+			puts("Could not read the EEPROM; something "
+				"fundamentally wrong on the I2C bus.\n");
+			hang();
+		}
+
+		if (header.magic != 0xEE3355AA) {
+			printf("Incorrect magic number (0x%x) in EEPROM\n",
+					header.magic);
+			hang();
+		}
+	}
 	enable_board_pin_mux(&header);
-	if (board_is_evm_sk()) {
+	if (!strncmp("A335X_SK", header.name, HDR_NAME_LEN)) {
 		/*
 		 * EVM SK 1.2A and later use gpio0_7 to enable DDR3.
 		 * This is safe enough to do on older revs.
 		 
 		 
 		 @@ -544,10 +700,20 @@ void s_init(void)
 		gpio_direction_output(GPIO_DDR_VTT_EN, 1);
 	}
 
-	if (board_is_evm_sk() || board_is_bone_lt())
+#ifdef CONFIG_NOR_BOOT
+	am33xx_spl_board_init();
+#endif
+
+	if (!strncmp("A335X_SK", header.name, HDR_NAME_LEN))
 		config_ddr(303, MT41J128MJT125_IOCTRL_VALUE, &ddr3_data,
 			   &ddr3_cmd_ctrl_data, &ddr3_emif_reg_data);
-	else if (board_is_evm_15_or_later())
+	else if  (!strncmp("A335BNLT", header.name, 8))
+		config_ddr(400, MT41K256M16HA125E_IOCTRL_VALUE,
+			   &ddr3_beagleblack_data,
+			   &ddr3_beagleblack_cmd_ctrl_data,
+			   &ddr3_beagleblack_emif_reg_data);
+	else if (!strncmp("A33515BB", header.name, 8) &&
+				strncmp("1.5", header.version, 3) <= 0)
 		config_ddr(303, MT41J512M8RH125_IOCTRL_VALUE, &ddr3_evm_data,
 			   &ddr3_evm_cmd_ctrl_data, &ddr3_evm_emif_reg_data);


 
 

 		
 			
 			
 			
 			



