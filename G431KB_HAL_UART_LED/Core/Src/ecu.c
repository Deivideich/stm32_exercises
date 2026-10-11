/*
 * ecu.c
 *
 *  Created on: Oct 11, 2026
 *      Author: deivideich
 */

#include "ecu.h"
#include "led.h"
#include "uart.h"

const uint8_t ECU_DISABLED_MSG[] = "ECU DISABLED\r\n";
const uint8_t ECU_ENABLED_MSG[] = 	"ECU ENABLED\r\n";

void ecu_init(ecu_config_t *ecu){
	ecu->ecu_status = DISABLED;
}

void ecu_enable(ecu_config_t *ecu){
	ecu->ecu_status = ENABLED;
}

void ecu_disable(ecu_config_t *ecu){
	ecu->ecu_status = DISABLED;
}

void ecu_report_status(ecu_config_t *ecu, uart_config_t *uart){
	if (ecu->ecu_status == ENABLED) {
	        HAL_UART_Transmit(uart->uart_handle, ECU_ENABLED_MSG, (uint16_t)(sizeof(ECU_ENABLED_MSG) - 1U), HAL_MAX_DELAY);
	    } else {
	        HAL_UART_Transmit(uart->uart_handle, ECU_DISABLED_MSG, (uint16_t)(sizeof(ECU_DISABLED_MSG) - 1U), HAL_MAX_DELAY);
	    }
};
