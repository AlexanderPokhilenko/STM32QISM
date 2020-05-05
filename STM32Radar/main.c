#include "hcsr04.h"
#include "UART.h"
#include "delay.h"
#include "stepperMotor.h"
#include "encoder.h"

int main(void)
{
	InitHCSR04();
	InitializeUART();
	InitializeStepperMotor();
	InitializeEncoder();
	
	TurnOnStepperMotor();
	StepperMotorSetDirection(Clockwise);
	
	while(!ReadEncoder())
	{
		StepperMotorMakeStep(2);
	}
	/*
	uint16_t maxSteps = 0;
	do
	{
		StepperMotorMakeStep(2);
		maxSteps++;
	} while(!ReadEncoder() || maxSteps < 4);
	
	UART_SendSingleAsBytes(maxSteps);
	*/
	while(1)
	{
		uint16_t dist = HCSR04GetDistance();
		UART_SendSingleAsBytes(dist);
		StepperMotorMakeStep(2);
	}
}

void UART_HandleReceived(uint16_t data)
{
	//TODO: FSM
}
