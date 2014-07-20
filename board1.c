File path: arch/arm/cpu/armv7/am33xx/board.c
File name: board.c


 Common board functions for AM33XX based boards
 

+
+#if 0
+void s_init(void)
+{
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
+	s1_init();
+}
+#endif


The above function is called in 

/*
 * early system init of muxing and clocks.
 */
void s_init(void)
{
    __maybe_unused struct am335x_baseboard_id header;

#ifdef CONFIG_NOR_BOOT
    asm("stmfd  sp!, {r2 - r4}");
    asm("movw   r4, #0x8A4");
    asm("movw   r3, #0x44E1");
    asm("orr    r4, r4, r3, lsl #16");
    asm("mov    r2, #9");
    asm("mov    r3, #8");
    asm("gpmc_mux:  str r2, [r4], #4");
    asm("subs   r3, r3, #1");
    asm("bne    gpmc_mux");
    asm("ldmfd  sp!, {r2 - r4}");
#endif

    /* WDT1 is already running when the bootloader gets control
     * Disable it to avoid "random" resets
     */
    writel(0xAAAA, &wdtimer->wdtwspr);
    while (readl(&wdtimer->wdtwwps) != 0x0)
        ;
    writel(0x5555, &wdtimer->wdtwspr);
    while (readl(&wdtimer->wdtwwps) != 0x0)
        ;

#if defined(CONFIG_SPL_BUILD) || defined(CONFIG_NOR_BOOT)
    /* Setup the PLLs and the clocks for the peripherals */
    pll_init();

    /* Enable RTC32K clock */
    rtc32k_enable();

    /* UART softreset */
    u32 regVal;

    enable_uart0_pin_mux();

    regVal = readl(&uart_base->uartsyscfg);
    regVal |= UART_RESET;
    .....................................................
    .....................................................
    .....................................................
}



