#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

static void delay(uint32_t count) {
    for (volatile uint32_t i = 0; i < count; i++) {
        __asm__("nop");
    }
}

int main(void) {
    // Configura el reloj a 16 MHz usando el oscilador interno HSI
    rcc_clock_setup_pll(&rcc_hsi_configs[RCC_CLOCK_3V3_170MHZ]);

    // Habilita el reloj para el periférico GPIOB
    rcc_periph_clock_enable(RCC_GPIOB);

    // Configura PB8 como salida digital
    gpio_mode_setup(GPIOB, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO8);

    while (1) {
        gpio_toggle(GPIOB, GPIO8); // Alterna el estado de PB8
        delay(7000000);              // Retardo aproximado para 500ms
    }
    return 0;
}
