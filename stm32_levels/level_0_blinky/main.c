#include "hardware.h"

void delay(volatile uint32_t count) {
    while (count--) {
        __asm("nop");
    }
}

int main(void) {
    /* 1. Enable clock for GPIOB (Bit 1 of the AHB2ENR register) */
    RCC->AHB2ENR |= (1UL << 1); 
    
    /* AHB2 bus synchronization by reading the newly modified register */
    volatile uint32_t dummy;
    dummy = RCC->AHB2ENR;
    dummy = RCC->AHB2ENR;
    (void)dummy;

    /* 2. Configure Pin PB8 as Push-Pull Output */
    GPIOB->MODER &= ~(3UL << (8 * 2));
    GPIOB->MODER |=  (1UL << (8 * 2));
    
    GPIOB->OTYPER &= ~(1UL << 8);
    GPIOB->OSPEEDR |= (3UL << (8 * 2));

    /* 3. Blinking loop */
    while (1) {
        GPIOB->BSRR = (1UL << 8); // Turn on LED
        delay(1000000);

        GPIOB->BSRR = (1UL << (8 + 16)); // Turn off LED
        delay(1000000);
    }

    return 0;
}
