#include "stm32fsm.h"

extern const TransitionInfo ts1Transitions[1];
extern const TransitionInfo ts2Transitions[1];
const SignalToggleState s1 = SignalToggleState(GPIO_B, GPIO_Pin_1 | GPIO_Pin_12,
	GPIO_Mode_Out_PP, GPIO_Speed_50MHz,
	GPIO_Pin_9, GPIO_Mode_IPD, true,
	ts1Transitions, sizeof ts1Transitions / sizeof *ts1Transitions);
const SignalToggleState s2 = SignalToggleState(GPIO_B, GPIO_Pin_8 | GPIO_Pin_12,
	GPIO_Mode_Out_PP, GPIO_Speed_50MHz,
	GPIO_Pin_10, GPIO_Mode_IPD, true,
	ts2Transitions, sizeof ts2Transitions / sizeof *ts2Transitions);
const TransitionInfo ts1Transitions[1] = { {0x19, &s2} };
const TransitionInfo ts2Transitions[1] = { {0x1A, &s1} };
const AbstractState *currentState = &s1;

int main(void)
{
	currentState->HandleEntry();
	while(1)
	{
		currentState->HandleDo();
		//currentState->MakeTransition(0);
	}
}
