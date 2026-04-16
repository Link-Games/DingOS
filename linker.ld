ENTRY(_start)

SECTIONS
{
    . = 0x7E00; 

    .text :
    {
        KEEP(*(.text._start))   /*  FORCE _start FIRST */
        *(.text*)
    }

    .rodata : { *(.rodata*) }
    .data   : { *(.data*) }
    .bss    :
    {
        *(COMMON)
        *(.bss*)
    }
}
