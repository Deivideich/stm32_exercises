/* Memory layout configuration for STM32G431KB */
MEMORY
{
    FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 128K
    SRAM  (rwx) : ORIGIN = 0x20000000, LENGTH = 32K
}

/* Output sections mapping */
SECTIONS
{
    /* Interrupt vector table placed at the beginning of FLASH */
    .isr_vector :
    {
        . = ALIGN(4);
        KEEP(*(.isr_vector))
        . = ALIGN(4);
    } > FLASH

    /* Application code and read-only data */
    .text :
    {
        . = ALIGN(4);
        *(.text*)
        *(.rodata*)
        . = ALIGN(4);
        _etext = .;        /* Define global symbol for end of text section */
    } > FLASH

    /* ARM exception unwinding sections (required for standard libraries) */
    .ARM.extab : 
    { 
        . = ALIGN(4);
        *(.ARM.extab* .gnu.linkonce.armextab.*) 
        . = ALIGN(4);
    } > FLASH
    
    .ARM.exidx : 
    {
        . = ALIGN(4);
        *(.ARM.exidx* .gnu.linkonce.armexidx.*)
        . = ALIGN(4);
    } > FLASH

    /* Load address of the .data section in FLASH */
    _sidata = LOADADDR(.data);

    /* Initialized data section copied into SRAM at startup */
    .data :
    {
        . = ALIGN(4);
        _sdata = .;        /* Define global symbol for start of data section */
        *(.data*)
        . = ALIGN(4);
        _edata = .;        /* Define global symbol for end of data section */
    } > SRAM AT > FLASH

    /* Uninitialized data section cleared to zero at startup */
    .bss :
    {
        . = ALIGN(4);
        _sbss = .;        /* Define global symbol for start of bss section */
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        _ebss = .;        /* Define global symbol for end of bss section */
    } > SRAM

    /* Initial Stack Pointer address set to the top of SRAM */
    _estack = ORIGIN(SRAM) + LENGTH(SRAM);
}
