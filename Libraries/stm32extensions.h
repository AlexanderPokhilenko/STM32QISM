#ifndef STM32EXTENSIONS_H
#define STM32EXTENSIONS_H
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"

enum GPIOs { GPIO_A, GPIO_B, GPIO_C, GPIO_D, GPIO_E, GPIO_F, GPIO_G };

template <typename T>
const T * CreateSingleElementArray(T value)
{
	T *arr = new T[1];
	arr[0] = value;
	return arr;
}

GPIO_TypeDef *GetGPIO(const GPIOs GPIO);
GPIOs GetEnumFromGPIO(const GPIO_TypeDef *const GPIO);
void AssertParams(const GPIO_TypeDef *const GPIOsArr[], const uint16_t pinsArr[], uint32_t count, GPIOMode_TypeDef mode, GPIOSpeed_TypeDef speed);
void AssertParams(const GPIOs GPIOsArr[], const uint16_t pinsArr[], uint32_t count, GPIOMode_TypeDef mode, GPIOSpeed_TypeDef speed);
const GPIOs *CreateEnumsArrFromGPIOs(const GPIO_TypeDef *const GPIO[], uint32_t count);
void Initialize(GPIOs GPIO, uint16_t pins, GPIOMode_TypeDef mode, GPIOSpeed_TypeDef speed = (GPIOSpeed_TypeDef)0);
void Deinitialize(GPIOs GPIO, uint16_t pins);

#endif
