#ifndef HC_SR04_H
#define HC_SR04_H
// from https://github.com/lukdut/HC-SR04-Stm32
#include "stm32f10x.h"

#define US_TIMER							TIM3

#define US_TRIG_PORT					GPIOB
#define US_TRIG_PIN						GPIO_Pin_0		//TIM Ch3 (trig output)

#define US_ECHO_PORT					GPIOA
#define US_ECHO_PIN						GPIO_Pin_6		//TIM Ch1 (echo input)
#define US_TIMER_TRIG_SOURCE	TIM_TS_TI1FP1


void EnableHCSR04PeriphClock(void);

/**
 * Initialization of HCSR04's peripherals
 */
void InitHCSR04(void);

/**
 * Measure distance and get value in mm.
 */
uint16_t HCSR04GetDistance(void);

#endif /* HC_SR04_H */
