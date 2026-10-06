/*
 * led.c
 *
 *  Created on: Oct 4, 2026
 *      Author: deivideich
 */

#include "led.h"
#include "main.h"

#include <stddef.h>

const char * const LED_OFF_MSG = "LED_OFF";
const char * const LED_ON_MSG  = "LED_ON";

void led_init(led_config_t *led, uint16_t pin, void *port){
	led->gpio_pin = pin;
	led->gpio_port = port;
	led->msg = LED_OFF_MSG;
	led->state = LED_STATE_OFF;
	HAL_GPIO_WritePin((GPIO_TypeDef*)port, pin, GPIO_PIN_RESET);
};

void led_toggle(led_config_t *led){
	if(led != NULL){
		if(led->state == LED_STATE_ON){
			led->state = LED_STATE_OFF;
			led->msg = LED_OFF_MSG;
			HAL_GPIO_WritePin((GPIO_TypeDef*)led->gpio_port, led->gpio_pin, GPIO_PIN_RESET);
		}
		else{
			led->state = LED_STATE_ON;
			led->msg = LED_ON_MSG;
			HAL_GPIO_WritePin((GPIO_TypeDef*)led->gpio_port, led->gpio_pin, GPIO_PIN_SET);
		}
	}
}
