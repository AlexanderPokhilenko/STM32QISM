#include "stm32extensions.h"

enum OffsetsCR { CRL_OFFSET = 0x00, CRH_OFFSET = 0x08 };

uint32_t GetCR(uint32_t regvalue, uint16_t pins, uint32_t currentmode, OffsetsCR offset)
{
	uint32_t currentpin = 0x00, pinpos = 0x00, crpos = 0x00;
    for (pinpos = 0; pinpos < 8; pinpos++)
    {
      currentpin = pins & (0x01 << (pinpos + offset));
      if (currentpin)
      {
        crpos = pinpos << 2;
        // Clear the corresponding register bits
        regvalue &= ~(0x0F << crpos);
        // Write the mode configuration in the corresponding bits
        regvalue |= (currentmode << crpos);
      }
    }
    return regvalue;
}

GPIO_TypeDef *GetGPIO(const GPIOs GPIO)
{
	return ((GPIO_TypeDef *)(GPIOA_BASE + 0x0400 * GPIO));
}

GPIOs GetEnumFromGPIO(const GPIO_TypeDef *const GPIO)
{
	return ((GPIOs)(((uint32_t)GPIO - GPIOA_BASE) / 0x0400));
}

const GPIOs *CreateEnumsArrFromGPIOs(const GPIO_TypeDef *const GPIO[], uint32_t count)
{
	GPIOs *GPIOsArr = new GPIOs[count];
	for (unsigned int i = 0; i < count; i++) GPIOsArr[i] = GetEnumFromGPIO(GPIO[i]);
	return GPIOsArr;
}

void AssertParams(const GPIO_TypeDef *const GPIOsArr[], const uint16_t pinsArr[], uint32_t count, GPIOMode_TypeDef mode, GPIOSpeed_TypeDef speed)
{
  assert_param(IS_GPIO_MODE(mode));
	assert_param(IS_GPIO_SPEED(speed));
	for(unsigned int i = 0; i < count; i++)
	{
		assert_param(IS_GPIO_ALL_PERIPH(GPIOsArr[i]));
		assert_param(IS_GPIO_PIN(pinsArr[i]));
	}
}

void AssertParams(const GPIOs GPIOsEnumsArr[], const uint16_t pinsArr[], uint32_t count, GPIOMode_TypeDef mode, GPIOSpeed_TypeDef speed)
{
  assert_param(IS_GPIO_MODE(mode));
	assert_param(IS_GPIO_SPEED(speed));
	for(unsigned int i = 0; i < count; i++)
	{
		assert_param(IS_GPIO_ALL_PERIPH(GetGPIO(GPIOsEnumsArr[i])));
		assert_param(IS_GPIO_PIN(pinsArr[i]));
	}
}

void Initialize(GPIOs GPIO, uint16_t pins, GPIOMode_TypeDef mode, GPIOSpeed_TypeDef speed)
{ // Simplified GPIO_Init
	RCC->APB2ENR |= (RCC_APB2ENR_IOPAEN << GPIO);
	GPIO_TypeDef *GPIOx = GetGPIO(GPIO);
	
	uint32_t currentmode = (mode & 0x0F);
	if (mode & 0x10) currentmode |= speed;
  
	// CRL and CRH configuration
  if (pins & 0x00FF) GPIOx->CRL = GetCR(GPIOx->CRL, pins, currentmode, CRL_OFFSET);
  if (pins > 0x00FF) GPIOx->CRH = GetCR(GPIOx->CRH, pins, currentmode, CRH_OFFSET);
	
	if (mode == GPIO_Mode_IPD) GPIOx->BRR = pins; // Reset the corresponding ODR bit
	else if (mode == GPIO_Mode_IPU) GPIOx->BSRR = pins; // Set the corresponding ODR bit
}

uint32_t GetRestoredExceptPinsCR(uint32_t previous, uint32_t reset, uint16_t pins, OffsetsCR offset)
{
	uint32_t pinsMask = GetCR(0, pins, 0x0F, offset);
	return (reset & pinsMask) | (previous & ~pinsMask);
}

void Deinitialize(GPIOs GPIO, uint16_t pins)
{
	GPIO_TypeDef *GPIOx = GetGPIO(GPIO);
	uint32_t previousCRL = GPIOx->CRL;
	uint32_t previousCRH = GPIOx->CRH;
	
	RCC->APB2RSTR |= (RCC_APB2RSTR_IOPARST << GPIO);
	RCC->APB2RSTR &= ~(RCC_APB2RSTR_IOPARST << GPIO);
	
	uint32_t resetCRL = GPIOx->CRL;
	uint32_t resetCRH = GPIOx->CRH;
	
	uint32_t restoredCRL = GetRestoredExceptPinsCR(previousCRL, resetCRL, pins, CRL_OFFSET);
	uint32_t restoredCRH = GetRestoredExceptPinsCR(previousCRH, resetCRH, pins, CRH_OFFSET);
	
	if (restoredCRL == resetCRL && restoredCRH == resetCRH) RCC->APB2ENR &= ~(RCC_APB2ENR_IOPAEN << GPIO);
}
