File path: board/ti/am335x/tps65217.h
File name: tps65217.h

TPS65217 single chip power management IC


 #define USB_INPUT_CUR_LIMIT_1300MA	0x02
 #define USB_INPUT_CUR_LIMIT_1800MA	0x03
 
+#define DCDC_VOLT_SEL_1125MV		0x09
 #define DCDC_VOLT_SEL_1275MV		0x0F
-#define DCDC_VOLT_SEL_135MV		0x12
+#define DCDC_VOLT_SEL_1325MV		0x11
 
 #define LDO_MASK			0x1F
+#define LDO_VOLTAGE_OUT_1_8		0x06
 #define LDO_VOLTAGE_OUT_3_3		0x1F
 
 #define PWR_SRC_USB_BITMASK		0x4
