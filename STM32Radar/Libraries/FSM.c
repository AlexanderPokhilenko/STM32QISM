#include "FSM.h"
#include "RURS.h"
#include "UART.h"
#include "motorsL298N.h"
#include "delay.h"

void MoveForward(void) { Motors_TurnOn(); Motors_MoveForward(); }
void MoveBackward(void) { Motors_TurnOn(); Motors_MoveBackward(); }
void RotateClockwise(void) { Motors_TurnOn(); Motors_RotateClockwise(); }
void RotateCounterclockwise(void) { Motors_TurnOn(); Motors_RotateCounterclockwise(); }
void Wait(void) {  Motors_TurnOff(); delay_ms(2); }
void Scan(void)
{
	uint16_t dist = RURS_TakeNextMeasurement();
	UART_SendSingleAsBytes(dist);
	if(RURS_GetCurrentSteps() == 0) FSM_MakeTransition(endScanning);
}

typedef struct
{
	const MachineState state;
	void (*const handle)(void);
} StateInfo;

typedef struct
{
	const MachineState previousState;
	const InputSignal input;
	const StateInfo *const current;
} TransitionInfo;

const StateInfo movingForwardInfo = {movingForward, MoveForward};
const StateInfo movingBackwardInfo = {movingBackward, MoveBackward};
const StateInfo rotatingClockwiseInfo = {rotatingClockwise, RotateClockwise};
const StateInfo rotatingCounterclockwiseInfo = {rotatingCounterclockwise, RotateCounterclockwise};
const StateInfo waitingInfo = {waiting, Wait};
const StateInfo scanningInfo = {scanning, Scan};

const TransitionInfo transitions[] =
{
	//moving:
	{waiting, forward, &movingForwardInfo},
	{waiting, backward, &movingBackwardInfo},
	{waiting, left, &rotatingCounterclockwiseInfo},
	{waiting, right, &rotatingClockwiseInfo},
	{waiting, observe, &scanningInfo},
	//stopping:
	{movingForward, stop, &waitingInfo},
	{movingBackward, stop, &waitingInfo},
	{rotatingClockwise, stop, &waitingInfo},
	{rotatingCounterclockwise, stop, &waitingInfo},
	//close distance stopping:
	{movingForward, closeDistance, &waitingInfo},
	{movingBackward, closeDistance, &waitingInfo},
	//end scanning:
	{scanning, endScanning, &waitingInfo}
};

const int transitionsCount = sizeof transitions / sizeof *transitions;

const StateInfo *currentStateInfo = &waitingInfo;

void FSM_MakeTransition(InputSignal signal)
{
	for(int i = 0; i < transitionsCount; i++)
	{
		if(transitions[i].input == signal && transitions[i].previousState == currentStateInfo->state)
		{
			currentStateInfo = transitions[i].current;
			return;
		}
	}
}

void FSM_HandleCurrent(void)
{
	currentStateInfo->handle();
}
