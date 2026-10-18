#include "hardware.h"

void delay(volatile uint32_t count) {
    while (count--) {
        __asm("nop");
    }
}

int main(void) {
    /* 1. Habilitar reloj para el GPIOB (Bit 1 del registro AHB2ENR) */
    RCC->AHB2ENR |= (1UL << 1); 
    
    /* Sincronización del bus AHB2 leyendo el registro recién modificado */
    volatile uint32_t dummy;
    dummy = RCC->AHB2ENR;
    dummy = RCC->AHB2ENR;
    (void)dummy;

    /* 2. Configurar el Pin PB8 como Salida Push-Pull */
    GPIOB->MODER &= ~(3UL << (8 * 2));
    GPIOB->MODER |=  (1UL << (8 * 2));
    
    GPIOB->OTYPER &= ~(1UL << 8);
    GPIOB->OSPEEDR |= (3UL << (8 * 2));

    /* 3. Bucle de parpadeo */
    while (1) {
        GPIOB->BSRR = (1UL << 8); // Encender LED
        delay(1000000);

        GPIOB->BSRR = (1UL << (8 + 16)); // Apagar LED
        delay(1000000);
    }

    return 0;
}
