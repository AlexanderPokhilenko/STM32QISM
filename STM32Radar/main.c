#include "FSM.h"

void Func(void) { __nop(); }

const StateInfo s1 = {Func};
const StateInfo s2 = {Func};
const StateInfo s3 = {Func};

const StateInfo *currentStateInfo = &s1;

const TransitionInfo transitions[] =
{
	{&s1, 0, &s2},
	{&s2, 0, &s3},
	{&s3, 0, &s1},
	{&s3, 1, &s2},
	{&s2, 1, &s1},
	{&s1, 1, &s3}
};

const int transitionsCount = sizeof transitions / sizeof *transitions;

int main(void)
{	
	while(1)
	{
		FSM_HandleCurrent();
		FSM_MakeTransition(0);
	}
}
