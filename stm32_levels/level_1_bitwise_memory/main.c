#include "hardware.h"

void delay(volatile uint32_t count) {
    while (count--) {
        __asm("nop");
    }
}

void test_bloque1(void) {
    volatile uint32_t register_sim = 0x00000000U;

    // 001 and 003: Turn on bits 1 and 8 using OR
    register_sim |= (1U << 1);
    register_sim |= (1U << 8);
    // Current value: 0x00000102

    // 002 and 004: Turn off bit 1 only using AND and NOT
    register_sim &= ~(1U << 1);
    // Current value: 0x00000100

    // 005: Toggle bit 8 using XOR
    register_sim ^= (1U << 8);
    // Current value: 0x00000000

    register_sim ^= (1U << 8);
    // Current value: 0x00000100
}


int main(void) {

    test_bloque1();

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
