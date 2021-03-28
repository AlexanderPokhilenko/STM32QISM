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
		const unsigned int transitionsCount;
	public:
		virtual void HandleEntry(void) const = 0;
		virtual void HandleDo(void) const = 0;
		virtual void HandleExit(void) const = 0;
		void MakeTransition(InputSignal signal) const;
		explicit AbstractState(const TransitionInfo transitions[], unsigned int count);
    ~AbstractState();
};

extern const AbstractState *currentState;

#endif
