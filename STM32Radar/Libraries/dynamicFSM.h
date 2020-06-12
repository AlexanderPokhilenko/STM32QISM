#ifndef DYNAMICFSM_H
#define DYNAMICFSM_H

#define InputSignal char

typedef struct
{
	void (*const handle)(void);
} StateInfo;

struct TransitionInfo
{
	const StateInfo *const previous;
	const InputSignal input;
	const StateInfo *const next;
	struct TransitionInfo *nextLink;
};

extern const StateInfo *currentStateInfo;

void FSM_AddTransition(struct TransitionInfo *transition);
void FSM_MakeTransition(InputSignal signal);
void FSM_HandleCurrent(void);

#endif
