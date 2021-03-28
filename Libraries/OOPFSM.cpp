#include "oopfsm.h"

AbstractState::AbstractState(const TransitionInfo trans[], unsigned int count) : transitions(trans), transitionsCount(count) {}

void AbstractState::MakeTransition(InputSignal signal) const
{
	for(int i = 0; i < transitionsCount; i++)
	{
		if(transitions[i].input == signal)
		{
			currentState->HandleExit();
			currentState = transitions[i].next;
			currentState->HandleEntry();
			return;
		}
	}
}

AbstractState::~AbstractState() {delete[] transitions;}
