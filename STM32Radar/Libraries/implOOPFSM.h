#ifndef IMPLOOPFSM_H
#define IMPLOOPFSM_H
#include "OOPFSM.h"

class MovingForwardState : public AbstractState
{
	public:
		void Handle(void) const;
		explicit MovingForwardState(const TransitionInfo transitions[], const int count);
};

class MovingBackwardState : public AbstractState
{
	public:
		void Handle(void) const;
		explicit MovingBackwardState(const TransitionInfo transitions[], const int count);
};

class RotatingClockwiseState : public AbstractState
{
	public:
		void Handle(void) const;
		explicit RotatingClockwiseState(const TransitionInfo transitions[], const int count);
};

class RotatingCounterclockwiseState : public AbstractState
{
	public:
		void Handle(void) const;
		explicit RotatingCounterclockwiseState(const TransitionInfo transitions[], const int count);
};

class WaitingState : public AbstractState
{
	public:
		void Handle(void) const;
		explicit WaitingState(const TransitionInfo transitions[], const int count);
};

class ScanningState : public AbstractState
{
	public:
		void Handle(void) const;
		explicit ScanningState(const TransitionInfo transitions[], const int count);
};

#endif
