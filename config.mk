File path: arch/arm/cpu/armv7/config.mk
File name: config.mk


Config Make file

-PLATFORM_RELFLAGS += -fno-common -ffixed-r8 -msoft-float
+PLATFORM_RELFLAGS += -fno-common -ffixed-r8 -msoft-float -mno-unaligned-access
 
 
