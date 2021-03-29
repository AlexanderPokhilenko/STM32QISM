#include "oopfsm.h"

TransitionInfo::TransitionInfo(InputSignal inputSignal, AbstractState *nextState, struct TransitionInfo *nextTransition)
	: input(inputSignal), next(nextState), nextLink(nextTransition) {}

AbstractState::AbstractState(TransitionInfo *first) : firstTransition(first) {}

void AbstractState::PushTransition(InputSignal inputSignal, AbstractState *nextState)
{
	firstTransition = new TransitionInfo(inputSignal, nextState, firstTransition);
}

void AbstractState::PushTransition(TransitionInfo *newTransition)
{
	newTransition->nextLink = firstTransition;
	firstTransition = newTransition;
}

void AbstractState::MergeTransitions(TransitionInfo *transitionsList)
{
	TransitionInfo *lastTransition = transitionsList;
	while (lastTransition->nextLink) lastTransition = lastTransition->nextLink;
	lastTransition->nextLink = firstTransition;
	firstTransition = lastTransition;
}

void AbstractState::PopTransition(void)
{
	if (firstTransition) firstTransition = firstTransition->nextLink;
}

void AbstractState::MakeTransition(InputSignal signal) const
{
	const TransitionInfo *transition = firstTransition;
	while (transition)
	{
		if (transition->input == signal)
		{
			currentState->HandleExit();
			currentState = transition->next;
			currentState->HandleEntry();
			return;
		}
		transition = transition->nextLink;
	}
}

AbstractState::~AbstractState()
{
	const TransitionInfo *transition = firstTransition;
	const TransitionInfo *nextTransition;
	while (transition)
	{
		nextTransition = transition->nextLink;
		delete transition;
		transition = nextTransition;
	}
}
