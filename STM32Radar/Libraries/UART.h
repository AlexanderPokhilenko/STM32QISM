#ifndef UART_H
#define UART_H
#include <stdio.h>
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"

#define BAUDRATE 9600

void InitializeUART(void);
void UART_SendSingle(uint16_t data);
void UART_SendSingleAsBytes(uint16_t data);
void UART_SendArray(char data[], size_t count);
extern void UART_HandleReceived(uint16_t data);
#endif
