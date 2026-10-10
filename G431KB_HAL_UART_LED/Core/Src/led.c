/*
 * led.c
 *
 *  Created on: Oct 4, 2026
 *      Author: deivideich
 */

#include "led.h"
#include "main.h"

#include <stddef.h>

void led_init(led_config_t *led, uint16_t pin, GPIO_TypeDef *port){
	led->gpio_pin = pin;
	led->gpio_port = port;
	led->state = LED_STATE_OFF;
	led->last_tick = 1000;
	HAL_GPIO_WritePin(port, pin, GPIO_PIN_RESET);
};

void led_toggle(led_config_t *led){
	if(led != NULL){
		if(led->state == LED_STATE_ON){
			led->state = LED_STATE_OFF;
			HAL_GPIO_WritePin(led->gpio_port, led->gpio_pin, GPIO_PIN_RESET);
		}
		else{
			led->state = LED_STATE_ON;
			HAL_GPIO_WritePin(led->gpio_port, led->gpio_pin, GPIO_PIN_SET);
		}
	}
}

void led_turn_on(led_config_t *led){
	HAL_GPIO_WritePin(led->gpio_port, led->gpio_pin, GPIO_PIN_SET);
	led->state = LED_STATE_ON;
}

void led_turn_off(led_config_t *led){
	HAL_GPIO_WritePin((GPIO_TypeDef*) led->gpio_port, led->gpio_pin, GPIO_PIN_RESET);
	led->state = LED_STATE_OFF;
}

void led_blink(led_config_t *led, uint32_t period){
	uint32_t now = HAL_GetTick();
	if(now - led->last_tick >= period){
		led_toggle(led);
		led->last_tick = now;
	};
}
