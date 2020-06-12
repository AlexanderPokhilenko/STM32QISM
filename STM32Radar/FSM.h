#ifndef FSM_H
#define FSM_H

#define InputSignal char
	
class AbstractState;

typedef struct
{
	const InputSignal input;
	const AbstractState *const next;
} TransitionInfo;

class AbstractState {
	private:
		const TransitionInfo *const transitions;
		const int transitionsCount;
	public:
		virtual void Handle(void) const = 0;
		virtual void MakeTransition(InputSignal signal) const;
		explicit AbstractState(const TransitionInfo transitions[], const int count);
    ~AbstractState();
};

extern const AbstractState *currentState;

#endif
