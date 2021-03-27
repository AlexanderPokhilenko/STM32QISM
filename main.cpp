#include "OOPFSM.h"

extern const TransitionInfo s1Transitions[2];
extern const TransitionInfo s2Transitions[2];
extern const TransitionInfo s3Transitions[2];

class State1 : public AbstractState
{
	private:
		virtual void HandleEntry(void) const { __nop(); };
		virtual void HandleExit(void) const { __nop(); };
	public:
		virtual void HandleDo(void) const { __nop(); };
		explicit State1(const TransitionInfo trans[], const int count): AbstractState(trans, count) {};
} s1(s1Transitions, sizeof s1Transitions / sizeof *s1Transitions);

class State2 : public AbstractState
{
	private:
		virtual void HandleEntry(void) const { __nop(); };
		virtual void HandleExit(void) const { __nop(); };
	public:
		virtual void HandleDo(void) const { __nop(); };
		explicit State2(const TransitionInfo trans[], const int count): AbstractState(trans, count) {};
} s2(s2Transitions, sizeof s2Transitions / sizeof *s2Transitions);

class State3 : public AbstractState
{
	private:
		virtual void HandleEntry(void) const { __nop(); };
		virtual void HandleExit(void) const { __nop(); };
	public:
		virtual void HandleDo(void) const { __nop(); };
		explicit State3(const TransitionInfo trans[], const int count): AbstractState(trans, count) {};
} s3(s3Transitions, sizeof s3Transitions / sizeof *s3Transitions);

const AbstractState *currentState = &s1;

const TransitionInfo s1Transitions[] =  { {0, &s2}, {1, &s3} };
const TransitionInfo s2Transitions[] =  { {0, &s3}, {1, &s1} };
const TransitionInfo s3Transitions[] =  { {0, &s1}, {1, &s2} };

int main(void)
{
	while(1)
	{
		currentState->HandleDo();
		currentState->MakeTransition(0);
	}
}
