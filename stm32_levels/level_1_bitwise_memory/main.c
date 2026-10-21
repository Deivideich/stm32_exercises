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
    register_sim &= ~(1U << 8); //register sim is now 00000010 

    // Exercise 3: Apply the logical OR (|) operation to activate (set to 1) a configuration bit.
    register_sim |= (1U << 5); //register sim is now 01000010
    
    // Exercise 4: Combine the NOT (~) operator with AND (&) to safely turn off a specific bit.
    register_sim &= ~(1U << 1);

    // Exercise 5: Apply the XOR (^) operator to accurately toggle a status bit.
    register_sim ^= (1U << 1);

    // Exercise 6: Use logical left shifts (<<) to position a multi-bit value within a register field.
    register_sim = 3U; // 0x00000011 which is 3 in binary
    #define TIMER_MODE_SHIFT 12U // bit displacement value
    uint32_t mode_value = 5U; // 0x05 or 00000101

    register_sim |= (mode_value << TIMER_MODE_SHIFT); // 101000000000011
    // Exercise 7: Use logical right shifts (>>) to extract and read a multi-bit field from a register


    // Exercise 8: 
    
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
