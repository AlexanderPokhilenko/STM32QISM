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
	backward			= 'S',
	left					= 'A',
	right					= 'D',
	stop					= ' ',
	observe				= 'O',
	closeDistance	= 'C',
	endScanning		= 'E'
} InputSignal;

void FSM_MakeTransition(InputSignal signal);

void FSM_HandleCurrent(void);

#endif
