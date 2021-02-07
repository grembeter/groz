OUTPUT_FORMAT("elf32-littlearm", "elf32-bigarm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(_start)

OZ_STACK_SIZE = 1024 + 1024 + 1024;
SVC_STACK_SIZE = 128;
ABT_STACK_SIZE = 128;
UND_STACK_SIZE = 128;
IRQ_STACK_SIZE = 128;
FIQ_STACK_SIZE = 512;

MEMORY {
        ROM   (rx)  : ORIGIN = 0xffff0000, LENGTH = 64K
        OCRAM (rwx) : ORIGIN = 0x00001000, LENGTH = 128K
        SDRAM (rwx) : ORIGIN = 0x40000000, LENGTH = 128M
}

SECTIONS {
        .reset 0x1000 : {
                . = ALIGN(4);
                *(ivt)
        } > OCRAM

        .rodata : {
                . = ALIGN(4);
                *(.rodata*)
        } > OCRAM

        .text : {
                . = ALIGN(4);
                *(.text*)
        } > OCRAM

        .data : {
                *(.data*)
        } > OCRAM

        .bss : {
                . = ALIGN(4);
                __bss_start = .;
                *(.bss*)
                __bss_end = .;
        } > OCRAM

        .cmd_tab : {
                . = ALIGN(4);
                __cmd_tab_start = .;
                KEEP(*(SORT(.cmd_tab*)))
                __cmd_tab_end = .;
        } > OCRAM

        .stack 0x1f000 : {
                __stack_start__ = .;

                . = ALIGN(4);
                . += OZ_STACK_SIZE;
                __stack_oz_top__ = .;

                . = ALIGN(4);
                . += FIQ_STACK_SIZE;
                __stack_fiq_top__ = .;

                . = ALIGN(4);
                . += IRQ_STACK_SIZE;
                __stack_irq_top__ = .;

                . = ALIGN(4);
                . += SVC_STACK_SIZE;
                __stack_svc_top__ = .;

                . = ALIGN(4);
                . += UND_STACK_SIZE;
                __stack_und_top__ = .;

                . = ALIGN(4);
                . += ABT_STACK_SIZE;
                __stack_abt_top__ = .;

                __stack_end__ = .;
        } > OCRAM
}
