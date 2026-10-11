/*
 * ecu.h
 *
 *  Created on: Oct 11, 2026
 *      Author: deivideich
 */

#ifndef INC_ECU_H_
#define INC_ECU_H_

#include "uart.h"

extern const uint8_t ECU_DISABLED_MSG[];
extern const uint8_t ECU_ENABLED_MSG[];

typedef enum ecu_status_e{
	ENABLED,
	DISABLED
} ecu_status_t;

typedef struct ecu_config_s{
	ecu_status_t ecu_status;

} ecu_config_t;

void ecu_init(ecu_config_t *ecu);
void ecu_enable(ecu_config_t *ecu);
void ecu_disable(ecu_config_t *ecu);
void ecu_report_status(ecu_config_t *ecu, uart_config_t *uart);
#endif /* INC_ECU_H_ */
