File path: arch/arm/cpu/armv7/am33xx/mem.c
File name: mem.c


GPMC Intialazation [NOR, NAND]

+#if defined(CONFIG_CMD_FLASH)
+static const u32 gpmc_nor[GPMC_MAX_REG] = {
+	STNOR_GPMC_CONFIG1,
+	STNOR_GPMC_CONFIG2,
+	STNOR_GPMC_CONFIG3,
+	STNOR_GPMC_CONFIG4,
+	STNOR_GPMC_CONFIG5,
+	STNOR_GPMC_CONFIG6,
+	STNOR_GPMC_CONFIG7
+};
+
+#define GPMC_CS 0
+#endif



*************************************************************


void gpmc_init(void)
 	/* putting a blanket check on GPMC based on ZeBu for now */
 	gpmc_cfg = (struct gpmc *)GPMC_BASE;
 
-#ifdef CONFIG_CMD_NAND
+#if defined(CONFIG_CMD_NAND) || defined(CONFIG_NOR)
 	const u32 *gpmc_config = NULL;
 	u32 base = 0;
 	u32 size = 0;
 #endif
 	/* global settings */
 	writel(0x00000008, &gpmc_cfg->sysconfig);
+#ifdef CONFIG_NOR
+	writel(0x00000000, &gpmc_cfg->irqstatus);
+	writel(0x00000000, &gpmc_cfg->irqenable);
+	writel(0x00000A00, &gpmc_cfg->config);
+#else
 	writel(0x00000100, &gpmc_cfg->irqstatus);
 	writel(0x00000200, &gpmc_cfg->irqenable);
 	writel(0x00000012, &gpmc_cfg->config);
+#endif
 	/*
 	
 The above function is called in gpmc_init function
 
 /*****************************************************
 * gpmc_init(): init gpmc bus
 * Init GPMC for x16, MuxMode (SDRAM in x32).
 * This code can only be executed from SRAM or SDRAM.
 *****************************************************/
void gpmc_init(void)
{
    /* putting a blanket check on GPMC based on ZeBu for now */
    gpmc_cfg = (struct gpmc *)GPMC_BASE;

#if defined(CONFIG_CMD_NAND) || defined(CONFIG_NOR)
    const u32 *gpmc_config = NULL;
    u32 base = 0;
    u32 size = 0;
#endif
    /* global settings */
    writel(0x00000008, &gpmc_cfg->sysconfig);
#ifdef CONFIG_NOR
    writel(0x00000000, &gpmc_cfg->irqstatus);
    writel(0x00000000, &gpmc_cfg->irqenable);
    writel(0x00000A00, &gpmc_cfg->config);
#else
    writel(0x00000100, &gpmc_cfg->irqstatus);
    writel(0x00000200, &gpmc_cfg->irqenable);
    writel(0x00000012, &gpmc_cfg->config);
#endif
    /*
     * Disable the GPMC0 config set by ROM code
     */
    writel(0, &gpmc_cfg->cs[0].config7);
    sdelay(1000);

#ifdef CONFIG_CMD_NAND
    gpmc_config = gpmc_m_nand;

    base = PISMO1_NAND_BASE;
    size = PISMO1_NAND_SIZE;
    enable_gpmc_cs_config(gpmc_config, &gpmc_cfg->cs[0], base, size);
#endif
 ...........................................................
 ...........................................................
 ...........................................................
}
 
 
 
 
 	
 	
 	
