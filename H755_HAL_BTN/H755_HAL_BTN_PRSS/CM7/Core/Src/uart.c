/*
 * uart.c
 *
 *  Created on: May 9, 2026
 *      Author: deivideich
 */


#include "uart.h"
#include "main.h"

extern UART_HandleTypeDef huart3;

void send_uart(char *msg){
	HAL_UART_Transmit(&huart3,(const uint8_t *) msg, strlen(msg),1000);
	HAL_UART_Transmit(&huart3,(const uint8_t *) "\r\n", strlen("\r\n"),1000);
}
