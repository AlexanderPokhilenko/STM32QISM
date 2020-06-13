#include "dynamicFSM.h"

void Func(void) { __nop(); }

const StateInfo s1 = {Func};
const StateInfo s2 = {Func};
const StateInfo s3 = {Func};

const StateInfo *currentStateInfo = &s1;

struct TransitionInfo transitions[] =
{
	{&s1, 0, &s2},
	{&s2, 0, &s3},
	{&s3, 0, &s1},
	{&s3, 1, &s2},
	{&s2, 1, &s1},
	{&s1, 1, &s3}
};

void InitializeFSM(void)
{
	int transitionsCount = sizeof transitions / sizeof *transitions;
	
	for(int i = 0; i < transitionsCount; i++)
	{
		FSM_AddTransition(&transitions[i]);
	}
}

int main(void)
{	
	InitializeFSM();
	
	while(1)
	{
		FSM_HandleCurrent();
		FSM_MakeTransition(0);
	}
}
