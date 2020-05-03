#ifndef STEPPERMOTOR_H
#define STEPPERMOTOR_H
#include <stm32f10x.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>
#include "delay.h"

#define STEPPER_PORT				GPIOA
#define STEPPER_STEP_PIN		GPIO_Pin_2
#define STEPPER_DIR_PIN			GPIO_Pin_3
#define STEPPER_ENABLE_PIN	GPIO_Pin_4

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
