/*
 * uart.h
 *
 *  Created on: Oct 11, 2026
 *      Author: deivideich
 */

#ifndef INC_UART_H_
#define INC_UART_H_

#include <stdlib.h>
#include <stdbool.h>

#include "stm32g4xx_hal.h"



typedef enum uart_status_e{
	UART_OK = 0,
	UART_ERROR,
	UART_TIMEOUT
} uart_status_t;

typedef struct uart_config_s{
	UART_HandleTypeDef 	*uart_handle;
	uart_status_t 		uart_status;
	uint8_t 			rx_buffer[32];
	uint8_t				character;
} uart_config_t;

void uart_init(UART_HandleTypeDef *uart_handle, uart_config_t *uart_config);
void uart_rx(uart_config_t *uart_config);
void uart_tx(uart_config_t *uart_config);
void uart_receive_and_process(uart_config_t *uart_config);

#endif /* INC_UART_H_ */
