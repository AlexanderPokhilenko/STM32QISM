#include "encoder.h"

void InitializeEncoder(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = ENCODER_PIN; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	
	GPIO_Init(ENCODER_PORT, &GPIO_InitStructure);
}

uint8_t ReadEncoder(void)
{
	return GPIO_ReadInputDataBit(ENCODER_PORT, ENCODER_PIN) == 0;
}
