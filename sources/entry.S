    .section ivt, "ax"
    .code 32

    .global _start
    .func _start
_start:

    b _reset
    b _undef
    b _swi
    b _pabt
    b _dabt
    b .
    b _irq
    b _fiq

    .align 4
_reset:

    ldr sp, =__stack_end__
    bl __oz_low_init

    @ fill the stack

    ldr r1, =__stack_start__
    ldr r2, =__stack_end__
    ldr r3, =0xbebebebe

1:
    cmp r1, r2
    stmltia r1!, { r3 }
    blt 1b

    ldr sp, =__stack_oz_top__
    msr cpsr_f, 0x40
    bl __oz_entry

wait_forever:
    mov r0, r0
    b wait_forever

    .endfunc

_undef:
    b .
_swi:
    b .
_pabt:
    b .
_dabt:
    b .
_irq:
    b .
_fiq:
    b .

    .end
