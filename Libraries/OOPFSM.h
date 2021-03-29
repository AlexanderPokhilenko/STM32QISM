#ifndef OOPFSM_H
#define OOPFSM_H

#define InputSignal char

class AbstractState;

typedef struct TransitionInfo
{
	const InputSignal input;
	AbstractState *const next;
	struct TransitionInfo *nextLink;
	TransitionInfo(InputSignal inputSignal, AbstractState *nextState, struct TransitionInfo *nextTransition = 0);
} TransitionInfo;

class AbstractState {
	private:
		TransitionInfo *firstTransition;
	public:
		void PushTransition(InputSignal inputSignal, AbstractState *nextState);
		void PushTransition(TransitionInfo *newTransition);
		void MergeTransitions(TransitionInfo *transitionsList);
		void PopTransition(void);
		virtual void HandleEntry(void) const = 0;
		virtual void HandleDo(void) const = 0;
		virtual void HandleExit(void) const = 0;
		void MakeTransition(InputSignal signal) const;
		explicit AbstractState(TransitionInfo *firstTransition = 0);
    ~AbstractState();
};

extern AbstractState *currentState;

#endif
