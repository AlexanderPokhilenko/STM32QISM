#include "stepperMotor.h"

void InitializeStepperMotor(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//Driver A4988: A2 - step, A3 - dir, A4 - enable
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void TurnOnStepperMotor(void)
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_4);
}

void TurnOffStepperMotor(void)
{
	GPIO_SetBits(GPIOA, GPIO_Pin_4);
}

void StepperMotorSetDirection(StepperMotorDirection direction)
{
	if(direction == Clockwise)
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_3);
	}
	else
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin_3);
	}
}

void StepperMotorMakeStep(uint32_t tau)
{
	GPIO_SetBits(GPIOA, GPIO_Pin_2);
	delay_ms(tau);
	GPIO_ResetBits(GPIOA, GPIO_Pin_2);
}

void StepperMotorSetBits(void)
{
	GPIO_SetBits(GPIOA, GPIO_Pin_2);
}

void StepperMotorResetBits(void)
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_2);
}
