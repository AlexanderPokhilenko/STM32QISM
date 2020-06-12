#include "implementationFSM.h"
extern "C" {
#include "RURS.h"
#include "UART.h"
#include "motorsL298N.h"
#include "HCSR04.h"
}
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

MovingForwardState::MovingForwardState(const TransitionInfo trans[], const int count) : AbstractState(trans, count) {}
void MovingForwardState::Handle(void) const { RURS_ResetPosition(); Motors_TurnOn(); Motors_MoveForward(); if(HCSR04_GetDistance() < MIN_DIST)MakeTransition(closeDistance); }

MovingBackwardState::MovingBackwardState(const TransitionInfo trans[], const int count) : AbstractState(trans, count) {}
void MovingBackwardState::Handle(void) const { RURS_MakeHalfTurn(); Motors_TurnOn(); Motors_MoveBackward(); if(HCSR04_GetDistance() < MIN_DIST) MakeTransition(closeDistance); }

RotatingClockwiseState::RotatingClockwiseState(const TransitionInfo trans[], const int count) : AbstractState(trans, count) {}
void RotatingClockwiseState::Handle(void) const { Motors_TurnOn(); Motors_RotateClockwise(); }

RotatingCounterclockwiseState::RotatingCounterclockwiseState(const TransitionInfo trans[], const int count) : AbstractState(trans, count) {}
void RotatingCounterclockwiseState::Handle(void) const { Motors_TurnOn(); Motors_RotateCounterclockwise(); }
	
WaitingState::WaitingState(const TransitionInfo trans[], const int count) : AbstractState(trans, count) {}
void WaitingState::Handle(void) const { Motors_TurnOff(); RURS_ResetPosition(); }

ScanningState::ScanningState(const TransitionInfo trans[], const int count) : AbstractState(trans, count) {}
void ScanningState::Handle(void) const { uint16_t dist = RURS_TakeNextMeasurement(); UART_SendSingleAsBytes(dist); if(RURS_GetCurrentSteps() == 0) MakeTransition(endScanning); }

extern const MovingForwardState movingForward;
extern const MovingBackwardState movingBackward;
extern const RotatingClockwiseState rotatingClockwise;
extern const RotatingCounterclockwiseState rotatingCounterclockwise;
extern const WaitingState waiting;
extern const ScanningState scanning;

const TransitionInfo movingTransitions[] = { {stop, &waiting}, {closeDistance, &waiting} };
const TransitionInfo rotatingTransitions[] = { {stop, &waiting} };
const TransitionInfo waitingTransitions[] = { {forward, &movingForward}, {backward, &movingBackward}, {left, &rotatingCounterclockwise}, {right, &rotatingClockwise}, {observe, &scanning} };
const TransitionInfo scanningTransitions[] = { {endScanning, &waiting} };

const MovingForwardState movingForward (movingTransitions, sizeof movingTransitions / sizeof *movingTransitions);
const MovingBackwardState movingBackward(movingTransitions, sizeof movingTransitions / sizeof *movingTransitions);
const RotatingClockwiseState rotatingClockwise(rotatingTransitions, sizeof rotatingTransitions / sizeof *rotatingTransitions);
const RotatingCounterclockwiseState rotatingCounterclockwise(rotatingTransitions, sizeof rotatingTransitions / sizeof *rotatingTransitions);
const WaitingState waiting(waitingTransitions, sizeof waitingTransitions / sizeof *waitingTransitions);
const ScanningState scanning(scanningTransitions, sizeof scanningTransitions / sizeof *scanningTransitions);

const AbstractState *currentState = &waiting;
