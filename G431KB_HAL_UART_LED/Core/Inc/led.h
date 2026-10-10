/*
 * led.h
 *
 *  Created on: Oct 4, 2026
 *      Author: deivideich
 */

#ifndef INC_LED_H_
#define INC_LED_H_
#include <stdint.h>
#include <stdbool.h>
#include "stm32g4xx_hal.h"

typedef enum led_states_e {
    LED_STATE_OFF,
    LED_STATE_ON,
} led_states_t;

typedef struct led_config_s{
	led_states_t 	state;
	uint16_t 		gpio_pin;
	GPIO_TypeDef	*gpio_port;
	uint32_t 		last_tick;
} led_config_t;

void led_init(led_config_t *led, uint16_t pin, GPIO_TypeDef *port);
void led_toggle(led_config_t *led);
void led_turn_on(led_config_t *led);
void led_turn_off(led_config_t *led);
void led_blink(led_config_t *led, uint32_t period);

#endif /* INC_LED_H_ */
