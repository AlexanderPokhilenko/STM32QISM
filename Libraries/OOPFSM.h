#ifndef OOPFSM_H
#define OOPFSM_H

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
		virtual void HandleEntry(void) const = 0;
		virtual void HandleExit(void) const = 0;
	public:
		virtual void HandleDo(void) const = 0;
		void MakeTransition(InputSignal signal) const;
		explicit AbstractState(const TransitionInfo transitions[], const int count);
    ~AbstractState();
};

extern const AbstractState *currentState;

#endif
