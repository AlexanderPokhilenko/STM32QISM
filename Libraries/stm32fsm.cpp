#include "stm32fsm.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_conf.h"

ToggleState::ToggleState(uint32_t GPIOsSize, const GPIOs inUse[], const uint16_t outputsArr[], GPIOMode_TypeDef GPIOMode, GPIOSpeed_TypeDef GPIOSpeed,
	const TransitionInfo trans[], uint32_t count)
		: AbstractState(trans, count), outputs(outputsArr), outputsMode(GPIOMode), speed(GPIOSpeed), usedGPIOs(inUse), GPIOsCount(GPIOsSize)
{
	AssertParams(usedGPIOs, outputs, GPIOsCount, outputsMode, speed);
}


ToggleState::ToggleState(uint32_t GPIOsSize, const GPIO_TypeDef *GPIOxInUse[], const uint16_t outputsArr[], GPIOMode_TypeDef GPIOMode, GPIOSpeed_TypeDef GPIOSpeed,
	const TransitionInfo trans[], uint32_t count)
		: AbstractState(trans, count), outputs(outputsArr), outputsMode(GPIOMode), speed(GPIOSpeed), usedGPIOs(CreateEnumsArrFromGPIOs(GPIOxInUse, GPIOsSize)), GPIOsCount(GPIOsSize)
{
  AssertParams(usedGPIOs, outputs, GPIOsCount, outputsMode, speed);
}

ToggleState::ToggleState(GPIOs GPIO, uint16_t output, GPIOMode_TypeDef GPIOMode, GPIOSpeed_TypeDef GPIOSpeed,
	const TransitionInfo trans[], uint32_t count)
		: AbstractState(trans, count), outputs(CreateSingleElementArray(output)), outputsMode(GPIOMode), speed(GPIOSpeed), usedGPIOs(CreateSingleElementArray(GPIO)), GPIOsCount(1)
{
	AssertParams(usedGPIOs, outputs, GPIOsCount, outputsMode, speed);
}

ToggleState::ToggleState(const GPIO_TypeDef *GPIO, uint16_t output, GPIOMode_TypeDef GPIOMode, GPIOSpeed_TypeDef GPIOSpeed,
	const TransitionInfo trans[], uint32_t count)
		: AbstractState(trans, count), outputs(CreateSingleElementArray(output)), outputsMode(GPIOMode), speed(GPIOSpeed), usedGPIOs(CreateSingleElementArray(GetEnumFromGPIO(GPIO))), GPIOsCount(1)
{
	AssertParams(usedGPIOs, outputs, GPIOsCount, outputsMode, speed);
}

void ToggleState::InitializePins(uint32_t index) const
{
	GPIOs usedGPIO = usedGPIOs[index];
	uint16_t pins = outputs[index];
	Initialize(usedGPIO, pins, outputsMode, speed);
	GPIO_TypeDef *GPIOx = GetGPIO(usedGPIO);
	GPIOx->BSRR |= pins;
}

uint16_t ToggleState::GetAllUsedPins(uint32_t index) const
{
	return outputs[index];
}

void ToggleState::HandleEntry(void) const
{
	for(uint32_t i = 0; i < GPIOsCount; i++) InitializePins(i);
}

void ToggleState::HandleDo(void) const { __nop(); }

void ToggleState::HandleExit(void) const
{
	GPIOs usedGPIO;
	for(uint32_t i = 0; i < GPIOsCount; i++)
	{
		usedGPIO = usedGPIOs[i];
		GPIO_TypeDef *GPIOx = GetGPIO(usedGPIO);
		GPIOx->BRR |= outputs[i];
		Deinitialize(usedGPIO, GetAllUsedPins(i));
	}
}

ToggleState::~ToggleState() {delete[] usedGPIOs; delete[] outputs;}

// SignalToggleState:
SignalToggleState::SignalToggleState(uint32_t GPIOsCount, const GPIOs inUse[], const uint16_t outputsArr[], GPIOMode_TypeDef outMode, GPIOSpeed_TypeDef outSpeed,
	const uint16_t inputsArr[], GPIOMode_TypeDef inMode, bool switchOnHigh, //const InputSignal signalsArr[],
	const TransitionInfo trans[], uint32_t transitionsCount)
		: ToggleState(GPIOsCount, inUse, outputsArr, outMode, outSpeed, trans, transitionsCount), inputs(inputsArr), inputsMode(inMode), onHigh(switchOnHigh)//, signals(signalsArr)
{
	assert_param(IS_GPIO_MODE(inputsMode));
	for (unsigned int i = 0; i < GPIOsCount; i++) assert_param(IS_GPIO_PIN(inputs[i]));
}

SignalToggleState::SignalToggleState(uint32_t GPIOsCount, const GPIO_TypeDef *GPIOxInUse[], const uint16_t outputsArr[], GPIOMode_TypeDef outMode, GPIOSpeed_TypeDef outSpeed,
	const uint16_t inputsArr[], GPIOMode_TypeDef inMode, bool switchOnHigh, //const InputSignal signalsArr[],
	const TransitionInfo trans[], uint32_t transitionsCount)
		: ToggleState(GPIOsCount, GPIOxInUse, outputsArr, outMode, outSpeed, trans, transitionsCount), inputs(inputsArr), inputsMode(inMode), onHigh(switchOnHigh)//, signals(signalsArr)
{
	assert_param(IS_GPIO_MODE(inputsMode));
	for (unsigned int i = 0; i < GPIOsCount; i++) assert_param(IS_GPIO_PIN(inputs[i]));
}

SignalToggleState::SignalToggleState(GPIOs GPIO, uint16_t output, GPIOMode_TypeDef outMode, GPIOSpeed_TypeDef outSpeed,
	uint16_t input, GPIOMode_TypeDef inMode, bool switchOnHigh, //InputSignal signal,
	const TransitionInfo trans[], uint32_t transitionsCount)
		: ToggleState(GPIO, output, outMode, outSpeed, trans, transitionsCount), inputs(CreateSingleElementArray(input)), inputsMode(inMode), onHigh(switchOnHigh)//, signals(CreateSingleElementArray(signal))
{
	assert_param(IS_GPIO_MODE(inputsMode));
	assert_param(IS_GPIO_PIN(input));
}

SignalToggleState::SignalToggleState(const GPIO_TypeDef *GPIOx, uint16_t output, GPIOMode_TypeDef outMode, GPIOSpeed_TypeDef outSpeed,
	uint16_t input, GPIOMode_TypeDef inMode, bool switchOnHigh, //InputSignal signal,
	const TransitionInfo trans[], uint32_t transitionsCount)
		: ToggleState(GPIOx, output, outMode, outSpeed, trans, transitionsCount), inputs(CreateSingleElementArray(input)), inputsMode(inMode), onHigh(switchOnHigh)//, signals(CreateSingleElementArray(signal))
{
	assert_param(IS_GPIO_MODE(inputsMode));
	assert_param(IS_GPIO_PIN(input));
}

void SignalToggleState::InitializePins(uint32_t index) const
{
	ToggleState::InitializePins(index);
	GPIOs usedGPIO = usedGPIOs[index];
	uint16_t pins = inputs[index];
	Initialize(usedGPIO, pins, inputsMode);
}

uint16_t SignalToggleState::GetAllUsedPins(uint32_t index) const
{
	return ToggleState::GetAllUsedPins(index) | inputs[index];
}

void SignalToggleState::HandleDo(void) const
{
	uint16_t currentInputs;
	uint16_t pinpos, pin;
	GPIOs enumGPIO;
	GPIO_TypeDef *GPIOx;
	for (uint32_t i = 0; i < GPIOsCount; i++)
	{
		currentInputs = inputs[i];
		if (currentInputs)
		{
			enumGPIO = usedGPIOs[i];
			GPIOx = GetGPIO(enumGPIO);
			for (pinpos = 0; pinpos < 16; pinpos++)
			{
				pin = 0x01 << pinpos;
				if ((currentInputs & pin) && (onHigh ^ !(GPIOx->IDR & pin)))
				{
					InputSignal signal = (enumGPIO << 4) | pinpos;
					MakeTransition(signal);
					return;
				}
			}
		}
	}
}

SignalToggleState::~SignalToggleState() {delete[] inputs;}
