#ifndef MOTORSL298N_H
#define MOTORSL298N_H

#define MOTORS_PORT				GPIOB

#define MOTORS_ENA_PIN		GPIO_Pin_3
#define MOTORS_IN1_PIN		GPIO_Pin_4
#define MOTORS_IN2_PIN		GPIO_Pin_5

#define MOTORS_ENB_PIN		GPIO_Pin_6
#define MOTORS_IN3_PIN		GPIO_Pin_7
#define MOTORS_IN4_PIN		GPIO_Pin_8

void InitializeMotors(void);

void Motors_TurnOn(void);
void Motors_TurnOff(void);

void Motors_MoveForward(void);
void Motors_MoveBackward(void);
void Motors_RotateClockwise(void);
void Motors_RotateCounterclockwise(void);
#endif
