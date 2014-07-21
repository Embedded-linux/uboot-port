File path: arch/arm/cpu/armv7/am33xx/clock.c
File name: clock.c

 clocks for AM33XX based boards
 
 
 static void core_pll_config(void)
+void core_pll_config(int opp)
 {
 	u32 clkmode, clksel, div_m4, div_m5, div_m6;
 
@@ -254,29 +254,53 @@ static void core_pll_config(void)
 	writel(PLL_BYPASS_MODE, &cmwkup->clkmoddpllcore);
 
 	while (readl(&cmwkup->idlestdpllcore) != ST_MN_BYPASS)
-		;
+			;
+	if (opp == OPP_50) {
+		clksel = clksel & (~CLK_SEL_MASK);
+		clksel = clksel | ((COREPLL_M_OPP50 << CLK_SEL_SHIFT)
+				| COREPLL_N);
+		writel(clksel, &cmwkup->clkseldpllcore);
 
-	clksel = clksel & (~CLK_SEL_MASK);
-	clksel = clksel | ((COREPLL_M << CLK_SEL_SHIFT) | COREPLL_N);
-	writel(clksel, &cmwkup->clkseldpllcore);
+		div_m4 = div_m4 & ~CLK_DIV_MASK;
+		div_m4 = div_m4 | COREPLL_M4_OPP50;
+		writel(div_m4, &cmwkup->divm4dpllcore);
 
-	div_m4 = div_m4 & ~CLK_DIV_MASK;
-	div_m4 = div_m4 | COREPLL_M4;
-	writel(div_m4, &cmwkup->divm4dpllcore);
+		div_m5 = div_m5 & ~CLK_DIV_MASK;
+		div_m5 = div_m5 | COREPLL_M5_OPP50;
+		writel(div_m5, &cmwkup->divm5dpllcore);
 
-	div_m5 = div_m5 & ~CLK_DIV_MASK;
-	div_m5 = div_m5 | COREPLL_M5;
-	writel(div_m5, &cmwkup->divm5dpllcore);
+		div_m6 = div_m6 & ~CLK_DIV_MASK;
+		div_m6 = div_m6 | COREPLL_M6_OPP50;
+		writel(div_m6, &cmwkup->divm6dpllcore);
 
-	div_m6 = div_m6 & ~CLK_DIV_MASK;
-	div_m6 = div_m6 | COREPLL_M6;
-	writel(div_m6, &cmwkup->divm6dpllcore);
+		clkmode = clkmode | CLK_MODE_SEL;
+		writel(clkmode, &cmwkup->clkmoddpllcore);
 
-	clkmode = clkmode | CLK_MODE_SEL;
-	writel(clkmode, &cmwkup->clkmoddpllcore);
+		while (readl(&cmwkup->idlestdpllcore) != ST_DPLL_CLK)
+		;
+	} else {
+		clksel = clksel & (~CLK_SEL_MASK);
+		clksel = clksel | ((COREPLL_M << CLK_SEL_SHIFT) | COREPLL_N);
+		writel(clksel, &cmwkup->clkseldpllcore);
+
+		div_m4 = div_m4 & ~CLK_DIV_MASK;
+		div_m4 = div_m4 | COREPLL_M4;
+		writel(div_m4, &cmwkup->divm4dpllcore);
+
+		div_m5 = div_m5 & ~CLK_DIV_MASK;
+		div_m5 = div_m5 | COREPLL_M5;
+		writel(div_m5, &cmwkup->divm5dpllcore);
+
+		div_m6 = div_m6 & ~CLK_DIV_MASK;
+		div_m6 = div_m6 | COREPLL_M6;
+		writel(div_m6, &cmwkup->divm6dpllcore);
+		clkmode = clkmode | CLK_MODE_SEL;
+		writel(clkmode, &cmwkup->clkmoddpllcore);
 
-	while (readl(&cmwkup->idlestdpllcore) != ST_DPLL_CLK)
+		while (readl(&cmwkup->idlestdpllcore) != ST_DPLL_CLK)
 		;
+	}
 }
 
 
 This Function is called in 
 
 
 static void core_pll_config(void)
{
    u32 clkmode, clksel, div_m4, div_m5, div_m6;

    clkmode = readl(&cmwkup->clkmoddpllcore);
    clksel = readl(&cmwkup->clkseldpllcore);
    div_m4 = readl(&cmwkup->divm4dpllcore);
    div_m5 = readl(&cmwkup->divm5dpllcore);
    div_m6 = readl(&cmwkup->divm6dpllcore);

    /* Set the PLL to bypass Mode */
    writel(PLL_BYPASS_MODE, &cmwkup->clkmoddpllcore);

    while (readl(&cmwkup->idlestdpllcore) != ST_MN_BYPASS)
        ;

    clksel = clksel & (~CLK_SEL_MASK);
    clksel = clksel | ((COREPLL_M << CLK_SEL_SHIFT) | COREPLL_N);
    writel(clksel, &cmwkup->clkseldpllcore);

    div_m4 = div_m4 & ~CLK_DIV_MASK;
    div_m4 = div_m4 | COREPLL_M4;
    writel(div_m4, &cmwkup->divm4dpllcore);

    div_m5 = div_m5 & ~CLK_DIV_MASK;
    div_m5 = div_m5 | COREPLL_M5;
    writel(div_m5, &cmwkup->divm5dpllcore);

    div_m6 = div_m6 & ~CLK_DIV_MASK;
    div_m6 = div_m6 | COREPLL_M6;
    writel(div_m6, &cmwkup->divm6dpllcore);

    clkmode = clkmode | CLK_MODE_SEL;
    writel(clkmode, &cmwkup->clkmoddpllcore);

    while (readl(&cmwkup->idlestdpllcore) != ST_DPLL_CLK)
        ;
}

 ******************************************************************
 

 void pll_init()
 {
 	/* Start at 550MHz, will be tweaked up if possible. */
-	mpu_pll_config(MPUPLL_M_550);
-	core_pll_config();
+	mpu_pll_config(MPUPLL_M_300);
+	core_pll_config(OPP_50);
 	per_pll_config();
 
 
 	
 
 This code is defined inside the function 
 
 /*
 * Configure the PLL/PRCM for necessary peripherals
 */
void pll_init()
{
    /* Start at 550MHz, will be tweaked up if possible. */
    mpu_pll_config(MPUPLL_M_550);
    core_pll_config();
    per_pll_config();

    /* Enable the required interconnect clocks */
    enable_interface_clocks();

    /* Power domain wake up transition */
    power_domain_wkup_transition();

    /* Enable the required peripherals */
    enable_per_clocks();
}




