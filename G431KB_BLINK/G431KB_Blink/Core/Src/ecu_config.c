/*
 * ecu_config.c
 *
 *  Created on: Sep 30, 2026
 *      Author: deivideich
 */

#include "ecu_config.h"

static ecu_config_t config = {0};

void ecu_config_init(void){
	config.adc_threshold = 512;
	config.enabled = 0;
	config.period_ms = 1000;
};

void ecu_config_set_enabled(uint8_t enabled){
	config.enabled = enabled;
}

uint8_t ecu_config_is_enabled(){
	return config.enabled;
}
