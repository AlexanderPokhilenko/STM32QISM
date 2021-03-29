#include "stm32fsm.h"

extern const TransitionInfo ts1Transitions[2];
extern const TransitionInfo ts2Transitions[2];
extern const TransitionInfo ts3Transitions[2];
const SignalToggleState s1 = SignalToggleState(GPIO_B, GPIO_Pin_6,
	GPIO_Mode_Out_PP, GPIO_Speed_50MHz,
	GPIO_Pin_9 | GPIO_Pin_10, GPIO_Mode_IPU, false,
	ts1Transitions, sizeof ts1Transitions / sizeof *ts1Transitions);
const SignalToggleState s2 = SignalToggleState(GPIO_B, GPIO_Pin_7,
	GPIO_Mode_Out_PP, GPIO_Speed_50MHz,
	GPIO_Pin_11 | GPIO_Pin_12, GPIO_Mode_IPU, false,
	ts2Transitions, sizeof ts2Transitions / sizeof *ts2Transitions);
const SignalToggleState s3 = SignalToggleState(GPIO_B, GPIO_Pin_8,
	GPIO_Mode_Out_PP, GPIO_Speed_50MHz,
	GPIO_Pin_13 | GPIO_Pin_14, GPIO_Mode_IPU, false,
	ts3Transitions, sizeof ts3Transitions / sizeof *ts3Transitions);
const TransitionInfo ts1Transitions[2] = { {0x19, &s2}, {0x1A, &s3} };
const TransitionInfo ts2Transitions[2] = { {0x1B, &s3}, {0x1C, &s1} };
const TransitionInfo ts3Transitions[2] = { {0x1D, &s1}, {0x1E, &s2} };
const AbstractState *currentState = &s1;

int main(void)
{
	currentState->HandleEntry();
	while(1)
	{
		currentState->HandleDo();
	}
}
