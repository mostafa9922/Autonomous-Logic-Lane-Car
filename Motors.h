#ifndef MOTORS_H
#define MOTORS_H

#include "stm32f1xx_hal.h"  // Include the STM32F1 HAL library

// Define motor control pins
#define MOTOR_LEFT_FORWARD_GPIO_PORT  GPIOA
#define MOTOR_LEFT_FORWARD_PIN        GPIO_PIN_0
#define MOTOR_LEFT_BACKWARD_GPIO_PORT GPIOA
#define MOTOR_LEFT_BACKWARD_PIN       GPIO_PIN_1
#define MOTOR_RIGHT_FORWARD_GPIO_PORT GPIOA
#define MOTOR_RIGHT_FORWARD_PIN       GPIO_PIN_2
#define MOTOR_RIGHT_BACKWARD_GPIO_PORT GPIOA
#define MOTOR_RIGHT_BACKWARD_PIN      GPIO_PIN_3

// Function prototypes
void Motors_Init(void);
void Motor_Move_Forward(void);
void Motor_Move_Backward(void);
void Motor_Stop(void);
void Motor_Turn_Left(uint32_t turn_time_ms);
void Motor_Turn_Right(uint32_t turn_time_ms);

#endif // MOTORS_H
