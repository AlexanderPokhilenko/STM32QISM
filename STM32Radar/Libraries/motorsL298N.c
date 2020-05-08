#include "motorsL298N.h"
#include <stm32f10x.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>

void InitializeMotors(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = MOTORS_ENA_PIN | MOTORS_IN1_PIN | MOTORS_IN2_PIN | MOTORS_ENB_PIN | MOTORS_IN3_PIN | MOTORS_IN4_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(MOTORS_PORT, &GPIO_InitStructure);
}

void Motors_TurnOn(void)
{
	GPIO_SetBits(MOTORS_PORT, MOTORS_ENA_PIN);
	GPIO_SetBits(MOTORS_PORT, MOTORS_ENB_PIN);
}

void Motors_TurnOff(void)
{
	GPIO_ResetBits(MOTORS_PORT, MOTORS_ENA_PIN);
	GPIO_ResetBits(MOTORS_PORT, MOTORS_ENB_PIN);
	GPIO_ResetBits(MOTORS_PORT, MOTORS_IN1_PIN);
	GPIO_ResetBits(MOTORS_PORT, MOTORS_IN2_PIN);
	GPIO_ResetBits(MOTORS_PORT, MOTORS_IN3_PIN);
	GPIO_ResetBits(MOTORS_PORT, MOTORS_IN4_PIN);
}

void Motors_MoveForward(void)
{
	GPIO_SetBits  (MOTORS_PORT, MOTORS_IN1_PIN);
	GPIO_ResetBits(MOTORS_PORT, MOTORS_IN2_PIN);
	GPIO_SetBits  (MOTORS_PORT, MOTORS_IN4_PIN);
	GPIO_ResetBits(MOTORS_PORT, MOTORS_IN3_PIN);
}

void Motors_MoveBackward(void)
{
	GPIO_ResetBits(MOTORS_PORT, MOTORS_IN1_PIN);
	GPIO_SetBits  (MOTORS_PORT, MOTORS_IN2_PIN);
	GPIO_ResetBits(MOTORS_PORT, MOTORS_IN4_PIN);
	GPIO_SetBits  (MOTORS_PORT, MOTORS_IN3_PIN);
}

void Motors_RotateClockwise(void)
{
	GPIO_SetBits  (MOTORS_PORT, MOTORS_IN1_PIN);
	GPIO_ResetBits(MOTORS_PORT, MOTORS_IN2_PIN);
	GPIO_ResetBits(MOTORS_PORT, MOTORS_IN4_PIN);
	GPIO_SetBits  (MOTORS_PORT, MOTORS_IN3_PIN);
}

void Motors_RotateCounterclockwise(void)
{
	GPIO_ResetBits(MOTORS_PORT, MOTORS_IN1_PIN);
	GPIO_SetBits  (MOTORS_PORT, MOTORS_IN2_PIN);
	GPIO_SetBits  (MOTORS_PORT, MOTORS_IN4_PIN);
	GPIO_ResetBits(MOTORS_PORT, MOTORS_IN3_PIN);
}
