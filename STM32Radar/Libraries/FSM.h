#ifndef FSM_H
#define FSM_H

typedef enum
{
	movingForward,
	movingBackward,
	rotatingClockwise,
	rotatingCounterclockwise,
	waiting,
	scanning
} MachineState;

typedef enum
{
	forward				= 'W',
	left					= 'A',
	backward			= 'S',
	right					= 'D',
	stop					= ' ',
	observe				= 'O',
	closeDistance	= 'c',
	endScanning		= 'e'
} InputSignal;

void FSM_MakeTransition(InputSignal signal);

void FSM_HandleCurrent(void);

#endif
