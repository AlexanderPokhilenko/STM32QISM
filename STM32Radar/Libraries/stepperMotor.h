#ifndef STEPPERMOTOR_H
#define STEPPERMOTOR_H
#include <stm32f10x.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>
#include "delay.h"

typedef enum
{
	Clockwise,
	Counterclockwise
} StepperMotorDirection;

void InitializeStepperMotor(void);

void TurnOnStepperMotor(void);

void TurnOffStepperMotor(void);

void StepperMotorSetDirection(StepperMotorDirection direction);

void StepperMotorMakeStep(uint32_t tau);

void StepperMotorSetBits(void);

void StepperMotorResetBits(void);

#endif
