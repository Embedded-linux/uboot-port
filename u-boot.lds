File path: board/ti/am335x/u-boot.lds
File name: u-boot.lds


  u-boot.lds -- load descriptor file

+
+OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
+OUTPUT_ARCH(arm)
+ENTRY(_start)
+SECTIONS
+{
+	. = 0x00000000;
+
+	. = ALIGN(4);
+	.text :
+	{
+		__image_copy_start = .;
+		CPUDIR/start.o (.text*)
+		board/ti/am335x/libam335x.o (.text*)
+		*(.text*)
+	}
+
+	. = ALIGN(4);
+	.rodata : { *(SORT_BY_ALIGNMENT(SORT_BY_NAME(.rodata*))) }
+
+	. = ALIGN(4);
+	.data : {
+		*(.data*)
+	}
+
+	. = ALIGN(4);
+
+	. = .;
+
+	. = ALIGN(4);
+	.u_boot_list : {
+	#include <u-boot.lst>
+	}
+
+	. = ALIGN(4);
+
+	__image_copy_end = .;
nsym : {
+		__dynsym_start = .;
+		*(.dynsym)
+	}
+
+	_end = .;
+
+	/*
+	 * Deprecated: this MMU section is used by pxa at present but
+	 * should not be used by new boards/CPUs.
+	 */
+	. = ALIGN(4096);
+	.mmutable : {
+		*(.mmutable)
+	}
+
+	.bss __rel_dyn_start (OVERLAY) : {
+		__bss_start = .;
+		*(.bss*)
+		 . = ALIGN(4);
+		__bss_end__ = .;
+	}
+
+	/DISCARD/ : { *(.dynstr*) }
+	/DISCARD/ : { *(.dynamic*) }
+	/DISCARD/ : { *(.plt*) }
+	/DISCARD/ : { *(.interp*) }
+	/DISCARD/ : { *(.gnu*) }
+}
+
+#if defined(CONFIG_SPL_TEXT_BASE) && defined(CONFIG_SPL_MAX_SIZE)
+ASSERT(__bss_end__ < (CONFIG_SPL_TEXT_BASE + CONFIG_SPL_MAX_SIZE), "SPL image too big");
+#endif



