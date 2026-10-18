#include <stdint.h>

/* Symbols exported by the linker.ld */
extern uint32_t _estack;
extern uint32_t _sidata;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;

/* Prototype of the main C function */
extern int main(void);

/* Prototypes of exception handlers */
void Reset_Handler(void);
void Default_Handler(void);

/* Define the correct data type for a function pointer (ARM-Thumb Handler) */
typedef void(*const IRQHandler_t)(void);

/* Vector table mapped explicitly onto the .isr_vector section */
__attribute__((section(".isr_vector")))
IRQHandler_t vector_table[] = {
    (IRQHandler_t)&_estack,     /* Vector 0: Initial Stack Pointer address */
    Reset_Handler,              /* Vector 1: Reset (GCC enables the Thumb bit natively) */
    Default_Handler,            /* Vector 2: NMI */
    Default_Handler             /* Vector 3: HardFault */
};

void Reset_Handler(void) {
    /* 1. Copy initial values of .data from FLASH to SRAM */
    uint32_t *pSrc = &_sidata;
    uint32_t *pDst = &_sdata;

    while (pDst < &_edata) {
        *pDst++ = *pSrc++;
    }

    /* 2. Clear the .bss section in SRAM (fill with zeros) */
    pDst = &_sbss;
    while (pDst < &_ebss) {
        *pDst++ = 0;
    }

    /* 3. Jump to main() */
    main();

    /* Safety infinite loop */
    while (1) {
    }
}

void Default_Handler(void) {
    while (1) {
    }
}
