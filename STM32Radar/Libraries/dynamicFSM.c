#include "dynamicFSM.h"

#define NULL ((void*)0)

struct TransitionInfo *firstTransition = NULL;
struct TransitionInfo *lastTransition = NULL;

void FSM_AddTransition(struct TransitionInfo *transition)
{
	if(lastTransition == NULL)
	{
		firstTransition = transition;
		lastTransition = transition;
	}
	else
	{
		lastTransition->nextLink = transition;
		lastTransition = transition;
	}
	lastTransition->nextLink = NULL;
}

void FSM_MakeTransition(InputSignal signal)
{
	struct TransitionInfo *transition = firstTransition;
	while(transition != NULL)
	{
		if(transition->input == signal && transition->previous == currentStateInfo)
		{
			currentStateInfo = transition->next;
			return;
		}
		transition = transition->nextLink;
	}
}

void FSM_HandleCurrent(void)
{
	currentStateInfo->handle();
}
