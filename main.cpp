#include "stm32fsm.h"

AbstractState *currentState;

int main(void)
{
	SignalToggleState *s1 = new SignalToggleState(GPIO_B, GPIO_Pin_6,
		GPIO_Mode_Out_PP, GPIO_Speed_50MHz,
		GPIO_Pin_9 | GPIO_Pin_10, GPIO_Mode_IPU, false); // Create state 1
	
	currentState = s1; // Set initial state
	currentState->HandleEntry();
	
	for (uint32_t i = 0; i < 0xFF; i++) currentState->HandleDo(); // Do something for a while
	
	SignalToggleState *s2 = new SignalToggleState(GPIO_B, GPIO_Pin_7,
		GPIO_Mode_Out_PP, GPIO_Speed_50MHz,
		GPIO_Pin_11 | GPIO_Pin_12, GPIO_Mode_IPU, false); // Create state 2
	
	s1->PushTransition(0x19, s2); // From state 1 to state 2 on signal from pin 9 of GPIOB
	s2->PushTransition(0x1C, s1); // From state 2 to state 1 on signal from pin 12 of GPIOB
	
	for (uint32_t i = 0; i < 0xFF; i++) currentState->HandleDo(); // Do something for a while
	
	SignalToggleState *s3 = new SignalToggleState(GPIO_B, GPIO_Pin_8,
		GPIO_Mode_Out_PP, GPIO_Speed_50MHz,
		GPIO_Pin_13 | GPIO_Pin_14, GPIO_Mode_IPU, false); // Create state 3
	
	s1->PushTransition(0x1A, s3); // From state 1 to state 3 on signal from pin 10 of GPIOB
	s2->PushTransition(0x1B, s3); // From state 2 to state 3 on signal from pin 11 of GPIOB
	s3->PushTransition(0x1D, s1); // From state 3 to state 1 on signal from pin 13 of GPIOB
	s3->PushTransition(0x1E, s2); // From state 3 to state 2 on signal from pin 14 of GPIOB
	
	while(1) currentState->HandleDo();
}
