#include "hardware.h"

void delay(volatile uint32_t count) {
    while (count--) {
        __asm("nop");
    }
}

void bitwise_operations(void) {
    // Initialize an arbitrary 32 bit register
    volatile uint32_t register_sim = 0x00000000U;

    // Exercise 1: Manually calculate a binary and hexadecimal mask to isolate a specific bit
    volatile uint32_t calculated_hexadecimal_mask = 0x100U; // 256 in decimal, 100000000 in binary
    volatile uint32_t calculated_binary_mask = (1U << 1); //0x00000010 mask in binary;
    register_sim |= calculated_binary_mask; //register_sim is now 00000010 in binary  
    register_sim |= calculated_hexadecimal_mask; //register sim is now 1000000010, or 0x00000102
    
    // Exercise 2: Apply the logical AND (&) operation to clear (set to 0) a register bit without altering the others.
    register_sim &= ~(1U << 8); //register sim is now 0x00000010 
}


int main(void) {

    bitwise_operations();

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
