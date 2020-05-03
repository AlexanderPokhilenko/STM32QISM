#include "hcsr04.h"
#include "UART.h"
#include "delay.h"
#include "stepperMotor.h"
#include "encoder.h"

int main(void)
{
	InitHCSR04();
	UART_init();
	InitializeStepperMotor();
	InitializeEncoder();
	
	TurnOnStepperMotor();
	StepperMotorSetDirection(Clockwise);
	
	while(!ReadEncoder())
	{
		StepperMotorMakeStep(2);
		delay_ms(2);
	}
	
	while(1)
	{
		int32_t dist = HCSR04GetDistance();
		UART_dec(dist);
		StepperMotorMakeStep(2);
	}
}
