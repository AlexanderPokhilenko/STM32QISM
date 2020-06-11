#include "FSM.h"

void FSM_MakeTransition(InputSignal signal)
{
	for(int i = 0; i < transitionsCount; i++)
	{
		if(transitions[i].input == signal && transitions[i].previous == currentStateInfo)
		{
			currentStateInfo = transitions[i].next;
			return;
		}
	}
}

void FSM_HandleCurrent(void)
{
	currentStateInfo->handle();
}
