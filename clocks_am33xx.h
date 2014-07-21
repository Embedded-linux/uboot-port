File path: arch/arm/include/asm/arch-am33xx/clocks_am33xx.h
File name: clcoks_am33xx.h

AM33xx clock define



+#define OPP_50	50
+#define OPP_100	100
+
 #define OSC	(V_OSCK/1000000)
 
-/* MAIN PLL Fdll = 550MHz, 720MHz or 800MHz */
+/* MAIN PLL Fdll = 550MHz, 720MHz, 800MHz or 1GHz */
+#define MPUPLL_M_1000	1000
 #define MPUPLL_M_800	800
 #define MPUPLL_M_720	720
 #define MPUPLL_M_550	550
+#define MPUPLL_M_300	300
 #define MPUPLL_N	(OSC-1)
 #define MPUPLL_M2	1
 
 /* Core PLL Fdll = 1 GHZ, */
 #define COREPLL_M	1000
+#define COREPLL_M_OPP50 50
 #define COREPLL_N	(OSC-1)
 
 #define COREPLL_M4	10	/* CORE_CLKOUTM4 = 200 MHZ */
 #define COREPLL_M5	8	/* CORE_CLKOUTM5 = 250 MHZ */
 #define COREPLL_M6	4	/* CORE_CLKOUTM6 = 500 MHZ */
 
+#define COREPLL_M4_OPP50	1
+#define COREPLL_M5_OPP50	1
+#define COREPLL_M6_OPP50	1
+



