File path: arch/arm/include/asm/arch-am33xx/cpu.h
File name: cpu.h

 AM33xx specific header file


 /* cpu-id for AM33XX family */
 #define AM335X				0xB944
 #define DEVICE_ID			0x44E10600
+#define DEVICE_ID_MASK			0x1FFF
+
+/* MPU max frequencies */
+#define AM335X_ZCZ_800			0x1E2F
+#define AM335X_ZCZ_1000			0x1C2F


struct ctrl_dev {
 	unsigned int macid1h;		/* offset 0x3c */
 	unsigned int resv4[4];
 	unsigned int miisel;		/* offset 0x50 */
+	unsigned int resv5[106];
+	unsigned int efuse_sma;		/* offset 0x1FC */
 };
 #endif /* __ASSEMBLY__ */
 #endif /* __KERNEL_STRICT_NAMES */



These variables are defined in 

/* Control Device Register */
struct ctrl_dev {
    unsigned int deviceid;      /* offset 0x00 */
    unsigned int resv1[7];
    unsigned int usb_ctrl0;     /* offset 0x20 */
    unsigned int resv2;
    unsigned int usb_ctrl1;     /* offset 0x28 */
    unsigned int resv3;
    unsigned int macid0l;       /* offset 0x30 */
    unsigned int macid0h;       /* offset 0x34 */
    unsigned int macid1l;       /* offset 0x38 */
    unsigned int macid1h;       /* offset 0x3c */
    unsigned int resv4[4];
    unsigned int miisel;        /* offset 0x50 */
};




