/* EFR32FG25 memory layout */
MEMORY
{
    FLASH (rx)  : ORIGIN = 0x00000000, LENGTH = 1152K
    RAM   (rwx) : ORIGIN = 0x20000000, LENGTH = 256K
}

SECTIONS
{
    .text :
    {
        KEEP(*(.vectors))
        *(.text*)
        *(.rodata*)
        _etext = .;
    } > FLASH

    .data : AT(_etext)
    {
        _sdata = .;
        *(.data*)
        _edata = .;
    } > RAM

    .bss :
    {
        _sbss = .;
        *(.bss*)
        *(COMMON)
        _ebss = .;
    } > RAM

    .stack (COPY):
    {
        . = . + 8K;
    } > RAM

    .heap (COPY):
    {
        . = . + 32K;
    } > RAM
}
