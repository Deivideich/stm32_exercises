/* Memory layout configuration for STM32G431KB */
MEMORY
{
    FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 128K
    SRAM      (rwx) : ORIGIN = 0x20000000, LENGTH = 0x4000   /* 16K: 0x20000000-0x20003FFF */
    STOPWATCH (rw)  : ORIGIN = 0x20004000, LENGTH = 0x10     /* 16 bytes  */
    SRAM2     (rwx) : ORIGIN = 0x20004010, LENGTH = 0x3FF0   /* The rest: up to 0x20008000 */
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

    .stopwatch_block (NOLOAD) :
    {
        . = ALIGN(4);
        . = . + 16;
        . = ALIGN(4);
    } > STOPWATCH

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
    _estack = ORIGIN(SRAM2) + LENGTH(SRAM2);  
}
