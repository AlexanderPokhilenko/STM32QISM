#include "FSM.h"

AbstractState::AbstractState(const TransitionInfo trans[], const int count) : transitions(trans), transitionsCount(count) {}

void AbstractState::MakeTransition(InputSignal signal) const
{
	for(int i = 0; i < transitionsCount; i++)
	{
		if(transitions[i].input == signal)
		{
			currentState = transitions[i].next;
			return;
		}
	}
}

AbstractState::~AbstractState() {delete[] transitions;}
