#ifndef STM32FSM_H
#define STM32FSM_H
#include "oopfsm.h"
#include "stm32extensions.h"
#include "stm32f10x.h"

class ToggleState : public AbstractState
{
	private:
		const uint16_t *const outputs;
		const GPIOMode_TypeDef outputsMode;
		const GPIOSpeed_TypeDef speed;
	protected:
		const GPIOs *const usedGPIOs;
		const uint32_t GPIOsCount;
		virtual void InitializePins(uint32_t index) const;
		virtual uint16_t GetAllUsedPins(uint32_t index) const;
		virtual void HandleEntry(void) const;
		virtual void HandleExit(void) const;
	public:
		virtual void HandleDo(void) const;
		explicit ToggleState(uint32_t GPIOsCount, const GPIOs inUse[], const uint16_t outputsArr[], GPIOMode_TypeDef mode, GPIOSpeed_TypeDef speed,
			TransitionInfo *firstTransition = 0);
		explicit ToggleState(uint32_t GPIOsCount, const GPIO_TypeDef *GPIOxInUse[], const uint16_t outputsArr[], GPIOMode_TypeDef mode, GPIOSpeed_TypeDef speed,
			TransitionInfo *firstTransition = 0);
		explicit ToggleState(GPIOs GPIO, uint16_t output, GPIOMode_TypeDef mode, GPIOSpeed_TypeDef speed,
			TransitionInfo *firstTransition = 0);
		explicit ToggleState(const GPIO_TypeDef *GPIOx, uint16_t output, GPIOMode_TypeDef mode, GPIOSpeed_TypeDef speed,
			TransitionInfo *firstTransition = 0);
		~ToggleState();
};

class SignalToggleState : public ToggleState
{
	private:
		const uint16_t *const inputs;
		const GPIOMode_TypeDef inputsMode;
		const bool onHigh;
		//const InputSignal *const signals;
	protected:
		virtual void InitializePins(uint32_t index) const;
		virtual uint16_t GetAllUsedPins(uint32_t index) const;
	public:
		virtual void HandleDo(void) const;
		explicit SignalToggleState(uint32_t GPIOsCount, const GPIOs inUse[], const uint16_t outputsArr[], GPIOMode_TypeDef outMode, GPIOSpeed_TypeDef outSpeed,
			const uint16_t inputsArr[], GPIOMode_TypeDef inMode, bool switchOnHigh, //const InputSignal signalsArr[],
			TransitionInfo *firstTransition = 0);
		explicit SignalToggleState(uint32_t GPIOsCount, const GPIO_TypeDef *GPIOxInUse[], const uint16_t outputsArr[], GPIOMode_TypeDef outMode, GPIOSpeed_TypeDef outSpeed,
			const uint16_t inputsArr[], GPIOMode_TypeDef inMode, bool switchOnHigh, //const InputSignal signalsArr[],
			TransitionInfo *firstTransition = 0);
		explicit SignalToggleState(GPIOs GPIO, uint16_t output, GPIOMode_TypeDef outMode, GPIOSpeed_TypeDef outSpeed,
			uint16_t input, GPIOMode_TypeDef inMode, bool switchOnHigh, //InputSignal signal,
			TransitionInfo *firstTransition = 0);
		explicit SignalToggleState(const GPIO_TypeDef *GPIOx, uint16_t output, GPIOMode_TypeDef outMode, GPIOSpeed_TypeDef outSpeed,
			uint16_t input, GPIOMode_TypeDef inMode, bool switchOnHigh, //InputSignal signal,
			TransitionInfo *firstTransition = 0);
		~SignalToggleState();
};

#endif
