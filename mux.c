File path: board/ti/am335x/mux.c
File name: mux.c


NOR Chip pinmuxing


+#if defined(CONFIG_NOR) && !defined(CONFIG_NOR_BOOT)
+static struct module_pin_mux bone_norcape_pin_mux[] = {
+	{OFFSET(lcd_data0), MODE(1) | PULLUDEN | RXACTIVE},     /* NOR_A0 */
+	{OFFSET(lcd_data1), MODE(1) | PULLUDEN | RXACTIVE},     /* NOR_A1 */
+	{OFFSET(lcd_data2), MODE(1) | PULLUDEN | RXACTIVE},     /* NOR_A2 */
+	{OFFSET(lcd_data3), MODE(1) | PULLUDEN | RXACTIVE},     /* NOR_A3 */
+	{OFFSET(lcd_data4), MODE(1) | PULLUDEN | RXACTIVE},     /* NOR_A4 */
+	{OFFSET(lcd_data5), MODE(1) | PULLUDEN | RXACTIVE},     /* NOR_A5 */
+	{OFFSET(lcd_data6), MODE(1) | PULLUDEN | RXACTIVE},     /* NOR_A6 */
+	{OFFSET(lcd_data7), MODE(1) | PULLUDEN | RXACTIVE},     /* NOR_A7 */
+	{OFFSET(lcd_vsync), MODE(1) | PULLUDEN | RXACTIVE},     /* NOR_A8 */
+	{OFFSET(lcd_hsync), MODE(1) | PULLUDEN | RXACTIVE},     /* NOR_A9 */
+	{OFFSET(lcd_pclk), MODE(1)| PULLUDEN | RXACTIVE},       /* NOR_A10 */
+	{OFFSET(lcd_ac_bias_en), MODE(1)| PULLUDEN | RXACTIVE}, /* NOR_A11 */
+	{OFFSET(lcd_data8), MODE(1) | PULLUDEN | RXACTIVE},     /* NOR_A12 */
+	{OFFSET(lcd_data9), MODE(1) | PULLUDEN | RXACTIVE},     /* NOR_A13 */
+	{OFFSET(lcd_data10), MODE(1) | PULLUDEN | RXACTIVE},    /* NOR_A14 */
+	{OFFSET(lcd_data11), MODE(1) | PULLUDEN | RXACTIVE},    /* NOR_A15 */
+	{OFFSET(lcd_data12), MODE(1) | PULLUDEN | RXACTIVE},    /* NOR_A16 */
+	{OFFSET(lcd_data13), MODE(1) | PULLUDEN | RXACTIVE},    /* NOR_A17 */
+	{OFFSET(lcd_data14), MODE(1) | PULLUDEN | RXACTIVE},    /* NOR_A18 */
+	{OFFSET(lcd_data15), MODE(1) | PULLUDEN | RXACTIVE},    /* NOR_A19 */
+	{OFFSET(gpmc_ad0), MODE(0) | PULLUDEN | RXACTIVE},      /* NOR_AD0 */
+	{OFFSET(gpmc_ad1), MODE(0) | PULLUDEN | RXACTIVE},      /* NOR_AD1 */
+	{OFFSET(gpmc_ad2), MODE(0) | PULLUDEN | RXACTIVE},      /* NOR_AD2 */
+	{OFFSET(gpmc_ad3), MODE(0) | PULLUDEN | RXACTIVE},      /* NOR_AD3 */
+	{OFFSET(gpmc_ad4), MODE(0) | PULLUDEN | RXACTIVE},      /* NOR_AD4 */
+	{OFFSET(gpmc_ad5), MODE(0) | PULLUDEN | RXACTIVE},      /* NOR_AD5 */
+	{OFFSET(gpmc_ad6), MODE(0) | PULLUDEN | RXACTIVE},      /* NOR_AD6 */
+	{OFFSET(gpmc_ad7), MODE(0) | PULLUDEN | RXACTIVE},      /* NOR_AD7 */
+	{OFFSET(gpmc_ad8), MODE(0) | PULLUDEN | RXACTIVE},      /* NOR_AD8 */
+	{OFFSET(gpmc_ad9), MODE(0) | PULLUDEN | RXACTIVE},      /* NOR_AD9 */
+	{OFFSET(gpmc_ad10), MODE(0) | PULLUDEN | RXACTIVE},     /* NOR_AD10 */
+	{OFFSET(gpmc_ad11), MODE(0) | PULLUDEN | RXACTIVE},     /* NOR_AD11 */
+	{OFFSET(gpmc_ad12), MODE(0) | PULLUDEN | RXACTIVE},     /* NOR_AD12 */
+	{OFFSET(gpmc_ad13), MODE(0) | PULLUDEN | RXACTIVE},     /* NOR_AD13 */
+	{OFFSET(gpmc_ad14), MODE(0) | PULLUDEN | RXACTIVE},     /* NOR_AD14 */
+	{OFFSET(gpmc_ad15), MODE(0) | PULLUDEN | RXACTIVE},     /* NOR_AD15 */
+
+	{OFFSET(gpmc_csn0), (MODE(0) | PULLUDEN) | RXACTIVE},   /* NOR_CE */
+	{OFFSET(gpmc_advn_ale), (MODE(0) | PULLUDEN) | RXACTIVE}, /* NOR_ADVN_ALE */
+	{OFFSET(gpmc_oen_ren), (MODE(0) | PULLUDEN | RXACTIVE)},/* NOR_OE */
+	{OFFSET(gpmc_be0n_cle), (MODE(0) | PULLUDEN | RXACTIVE)},/* NOR_BE0N_CLE */
+	{OFFSET(gpmc_wen), (MODE(0) | PULLUDEN | RXACTIVE)},    /* NOR_WEN */
+	{OFFSET(gpmc_wait0), (MODE(0) | RXACTIVE | PULLUDEN)}, /* NOR WAIT */
+	{-1},
+};
+#endif
+
+





