#ifndef ENCODER_H
#define ENCODER_H
#include <stm32f10x.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>

void InitializeEncoder(void);
uint8_t ReadEncoder(void);
#endif
