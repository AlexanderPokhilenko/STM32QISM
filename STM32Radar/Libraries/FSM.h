#ifndef FSM_H
#define FSM_H

#define InputSignal char

typedef struct
{
	void (*const handle)(void);
} StateInfo;

typedef struct
{
	const StateInfo *const previous;
	const InputSignal input;
	const StateInfo *const next;
} TransitionInfo;

extern const StateInfo *currentStateInfo;
extern const TransitionInfo transitions[];
extern const int transitionsCount;

void FSM_MakeTransition(InputSignal signal);

void FSM_HandleCurrent(void);

#endif
