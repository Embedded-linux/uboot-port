File path: include/configs/am335x_evm.h
File name: am335x_evm.h

Configurations of am335x board


+/* Custom script for NOR */
+#define CONFIG_SYS_LDSCRIPT		"board/ti/am335x/u-boot.lds"
+


+#ifndef CONFIG_NOR_BOOT
 /* Defines for SPL */
 #define CONFIG_SPL
 #define CONFIG_SPL_FRAMEWORK
 
  #define CONFIG_SPL_NAND_ECC
+#endif
+


 .
  */
+#ifdef CONFIG_NOR_BOOT
+#define CONFIG_SYS_TEXT_BASE		0x08000000
+#else
 #define CONFIG_SYS_TEXT_BASE		0x80800000
+#endif
 #define CONFIG_SYS_SPL_MALLOC_START	0x80208000
 #define CONFIG_SYS_SPL_MALLOC_SIZE	0x100000
 
 
 /* Since SPL did pll and ddr initialization for us,
  * we don't need to do it twice.
  */
-#ifndef CONFIG_SPL_BUILD
+#if !defined(CONFIG_SPL_BUILD) && ! defined(CONFIG_NOR_BOOT)
 #define CONFIG_SKIP_LOWLEVEL_INIT
 #endif
 
 #define CONFIG_SYS_MAX_NAND_DEVICE	1		/* Max number of NAND
 							   devices */
-#if !defined(CONFIG_SPI_BOOT)
+#if !defined(CONFIG_SPI_BOOT) && !defined(CONFIG_NOR_BOOT)
 #undef CONFIG_ENV_IS_NOWHERE
 #define CONFIG_ENV_IS_IN_NAND
 #define CONFIG_ENV_OFFSET		0x260000 /* environment starts here */
@@ -512,4 +522,40 @@
 #endif
 #endif
 
 
 
 +/*
+ *  * NOR Size = 16 MB
+ *   * No.Of Sectors/Blocks = 128
+ *    * Sector Size = 128 KB
+ *     * Word lenght = 16 bits
+ *      */
+#if defined(CONFIG_NOR)
+#undef CONFIG_SYS_NO_FLASH
+#undef CONFIG_SYS_MALLOC_LEN
+#define CONFIG_SYS_FLASH_USE_BUFFER_WRITE 1
+#define CONFIG_SYS_FLASH_PROTECTION
+#define CONFIG_SYS_MALLOC_LEN		(0x100000)
+#define CONFIG_SYS_FLASH_CFI
+#define CONFIG_FLASH_CFI_DRIVER
+#define CONFIG_FLASH_CFI_MTD
+#define CONFIG_SYS_MAX_FLASH_SECT	128
+#define CONFIG_SYS_MAX_FLASH_BANKS	1
+#define CONFIG_SYS_FLASH_BASE		(0x08000000)
+#define CONFIG_SYS_FLASH_CFI_WIDTH	FLASH_CFI_16BIT
+#define CONFIG_SYS_MONITOR_BASE CONFIG_SYS_FLASH_BASE
+#define NOR_SECT_SIZE			(128 * 1024)
+#ifdef CONFIG_NOR_BOOT
+#undef CONFIG_ENV_IS_NOWHERE
+#define CONFIG_ENV_IS_IN_FLASH  1
+#define CONFIG_SYS_ENV_SECT_SIZE	(2 * NOR_SECT_SIZE)
+#define CONFIG_ENV_SECT_SIZE		(2 * NOR_SECT_SIZE)
+#undef CONFIG_ENV_SIZE
+#define CONFIG_ENV_SIZE			CONFIG_ENV_SECT_SIZE
+#define CONFIG_ENV_OFFSET		(2 * NOR_SECT_SIZE) /* After 1 MB */
+#define CONFIG_ENV_ADDR		(CONFIG_SYS_FLASH_BASE + \
+         CONFIG_ENV_OFFSET)
+#endif
+#define CONFIG_MTD_DEVICE
+#define CONFIG_CMD_FLASH
+#endif  /* NOR support */
+


 
 
 
 
