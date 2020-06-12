#include "implDynamicFSM.h"
#include "dynamicFSM.h"
#include "RURS.h"
#include "UART.h"
#include "motorsL298N.h"
#include "HCSR04.h"

#define MIN_DIST 150 //mm
#undef InputSignal

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

void MoveForward(void) { RURS_ResetPosition(); Motors_TurnOn(); Motors_MoveForward(); if(HCSR04_GetDistance() < MIN_DIST)FSM_MakeTransition(closeDistance); }
void MoveBackward(void) { RURS_MakeHalfTurn(); Motors_TurnOn(); Motors_MoveBackward(); if(HCSR04_GetDistance() < MIN_DIST)FSM_MakeTransition(closeDistance); }
void RotateClockwise(void) { Motors_TurnOn(); Motors_RotateClockwise(); }
void RotateCounterclockwise(void) { Motors_TurnOn(); Motors_RotateCounterclockwise(); }
void Wait(void) { Motors_TurnOff(); RURS_ResetPosition(); }
void Scan(void)
{
	uint16_t dist = RURS_TakeNextMeasurement();
	UART_SendSingleAsBytes(dist);
	if(RURS_GetCurrentSteps() == 0) FSM_MakeTransition(endScanning);
}

const StateInfo movingForward = {MoveForward};
const StateInfo movingBackward = {MoveBackward};
const StateInfo rotatingClockwise = {RotateClockwise};
const StateInfo rotatingCounterclockwise = {RotateCounterclockwise};
const StateInfo waiting = {Wait};
const StateInfo scanning = {Scan};

const StateInfo *currentStateInfo = &waiting;

struct TransitionInfo transitions[] =
{
	//moving:
	{&waiting, forward, &movingForward},
	{&waiting, backward, &movingBackward},
	{&waiting, left, &rotatingCounterclockwise},
	{&waiting, right, &rotatingClockwise},
	{&waiting, observe, &scanning},
	//stopping:
	{&movingForward, stop, &waiting},
	{&movingBackward, stop, &waiting},
	{&rotatingClockwise, stop, &waiting},
	{&rotatingCounterclockwise, stop, &waiting},
	//close distance stopping:
	{&movingForward, closeDistance, &waiting},
	{&movingBackward, closeDistance, &waiting},
	//end scanning:
	{&scanning, endScanning, &waiting}
};

void InitializeFSM(void)
{
	int transitionsCount = sizeof transitions / sizeof *transitions;
	
	for(int i = 0; i < transitionsCount; i++)
	{
		FSM_AddTransition(&transitions[i]);
	}
}
