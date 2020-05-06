#include "RURS.h"
#include "stepperMotor.h"
#include "hcsr04.h"
#include "encoder.h"

uint16_t steps = 0;

void InitializeRURS(void)
{
	InitializeStepperMotor();
	InitializeEncoder();
	InitializeHCSR04();
}

void RURS_TurnOn(void)
{
	TurnOnStepperMotor();
	StepperMotorSetDirection(Clockwise);
}

void RURS_ResetPosition(void)
{
	while(!ReadEncoder())
	{
		StepperMotorMakeStep(2);
	}
	
	steps = 0;
}

uint16_t RURS_TakeNextMeasurement(void)
{
	uint16_t dist = HCSR04_GetDistance();
	StepperMotorMakeStep(2);
	
	steps++;
	if(steps == MAX_STEPS) steps = 0;
	
	return dist;
}

uint16_t RURS_GetCurrentSteps(void)
{
	return steps;
}
