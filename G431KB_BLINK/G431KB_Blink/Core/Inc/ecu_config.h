/*
 * ecu_config.h
 *
 *  Created on: Sep 30, 2026
 *      Author: deivideich
 */

#ifndef INC_ECU_CONFIG_H_
#define INC_ECU_CONFIG_H_

#include "main.h"
#include <stdbool.h>

typedef struct{
    uint16_t adc_threshold;
    uint32_t period_ms;
    bool enabled;
} ecu_config_t;

void ecu_config_init(void);
void ecu_config_set_enabled(uint8_t enabled);
uint8_t ecu_config_is_enabled(void);

#endif /* INC_ECU_CONFIG_H_ */
