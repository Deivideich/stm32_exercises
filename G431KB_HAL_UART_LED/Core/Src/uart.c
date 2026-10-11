/*
 * uart.c
 *
 *  Created on: Oct 11, 2026
 *      Author: deivideich
 */

#include "uart.h"

void uart_init(UART_HandleTypeDef *uart_handle, uart_config_t *uart_config){
	uart_config->uart_handle = uart_handle;
	uart_config->uart_status = UART_OK;
};


