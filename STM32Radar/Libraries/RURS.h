#ifndef RURS_H
#define RURS_H
#include "stm32f10x.h"

#define MAX_STEPS 200

//Rotating Ultrasonic Range Sensor
void InitializeRURS(void);
void RURS_TurnOn(void);
void RURS_ResetPosition(void);
void RURS_MakeHalfTurn(void);
uint16_t RURS_TakeNextMeasurement(void);
uint16_t RURS_GetCurrentSteps(void);
#endif
