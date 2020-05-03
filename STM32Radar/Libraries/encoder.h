#ifndef ENCODER_H
#define ENCODER_H
#include <stm32f10x.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>

#define ENCODER_PORT	GPIOA
#define ENCODER_PIN		GPIO_Pin_1

void InitializeEncoder(void);
uint8_t ReadEncoder(void);
#endif
