#include "stepperMotor.h"

void InitializeStepperMotor(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = STEPPER_STEP_PIN | STEPPER_DIR_PIN | STEPPER_ENABLE_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(STEPPER_PORT, &GPIO_InitStructure);
}

void TurnOnStepperMotor(void)
{
	GPIO_ResetBits(STEPPER_PORT, STEPPER_ENABLE_PIN);
}

void TurnOffStepperMotor(void)
{
	GPIO_SetBits(STEPPER_PORT, STEPPER_ENABLE_PIN);
}

void StepperMotorSetDirection(StepperMotorDirection direction)
{
	if(direction == Clockwise)
	{
		GPIO_SetBits(STEPPER_PORT, STEPPER_DIR_PIN);
	}
	else
	{
		GPIO_ResetBits(STEPPER_PORT, STEPPER_DIR_PIN);
	}
}

void StepperMotorMakeStep(uint32_t tau)
{
	GPIO_SetBits(STEPPER_PORT, STEPPER_STEP_PIN);
	delay_ms(tau);
	GPIO_ResetBits(STEPPER_PORT, STEPPER_STEP_PIN);
}

void StepperMotorSetBits(void)
{
	GPIO_SetBits(STEPPER_PORT, STEPPER_STEP_PIN);
}

void StepperMotorResetBits(void)
{
	GPIO_ResetBits(STEPPER_PORT, STEPPER_STEP_PIN);
}
