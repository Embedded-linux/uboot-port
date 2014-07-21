File path: board/ti/am335x/Makefile
File name: Makefile



-ifdef CONFIG_SPL_BUILD
+ifeq ($(CONFIG_SPL_BUILD)$(CONFIG_NOR_BOOT),y)


It is defined in Makefile for including NOR Boot compilation.

ifeq ($(CONFIG_SPL_BUILD)$(CONFIG_NOR_BOOT),y)
COBJS   := mux.o
endif

SRCS    := $(SOBJS:.o=.S) $(COBJS:.o=.c)
OBJS    := $(addprefix $(obj),$(COBJS))
SOBJS   := $(addprefix $(obj),$(SOBJS))

