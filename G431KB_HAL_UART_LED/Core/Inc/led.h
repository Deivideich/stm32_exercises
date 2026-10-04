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

extern const char * const LED_OFF_MSG;
extern const char * const LED_ON_MSG;

typedef enum led_states_e {
    LED_STATE_OFF,
    LED_STATE_ON,
    LED_STATE_BLINK
} led_states_t;

typedef struct led_config_s{
	led_states_t 	state;
	const char 		*msg;
	uint16_t 		gpio_pin;
	void 			*gpio_port;
} led_config_t;

void led_init(led_config_t *led, uint16_t pin, void *port);
void led_toggle(led_config_t *led);

#endif /* INC_LED_H_ */
