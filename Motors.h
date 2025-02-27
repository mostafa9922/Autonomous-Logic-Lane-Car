#ifndef MOTORS_H
#define MOTORS_H

#include "stm32f1xx_hal.h"

extern TIM_HandleTypeDef htim2; // Use extern to avoid multiple definitions

#define MOTOR_GPIO_PORT               GPIOA
#define MOTOR_LEFT_FORWARD_PIN        GPIO_PIN_2
#define MOTOR_LEFT_BACKWARD_PIN       GPIO_PIN_3
#define MOTOR_RIGHT_FORWARD_PIN       GPIO_PIN_4
#define MOTOR_RIGHT_BACKWARD_PIN      GPIO_PIN_5
#define MOTOR_LEFT_PWM_PIN            GPIO_PIN_0
#define MOTOR_RIGHT_PWM_PIN           GPIO_PIN_1

void Motors_Init(void);
void Motor_SetSpeed(uint16_t left_speed, uint16_t right_speed);
void Motor_Move_Forward(uint16_t speed);
void Motor_Move_Backward(uint16_t speed);
void Motor_Stop(void);
void Motor_Turn_Left(uint16_t speed, uint32_t turn_time_ms);
void Motor_Turn_Right(uint16_t speed, uint32_t turn_time_ms);

#endif // MOTORS_H
