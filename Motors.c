#include "motors.h"

extern TIM_HandleTypeDef htim2;  // Use extern to reference the variable from main.c

// Initialize PWM Timer
void PWM_Init(void) {
    // No need to redefine htim2, it is now in main.c
    __HAL_RCC_TIM2_CLK_ENABLE();
    htim2.Instance = TIM2;
    htim2.Init.Prescaler = 71;
    htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim2.Init.Period = 19999;
    htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_PWM_Init(&htim2);
}

// Initialize Motor Pins
void Motors_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // Enable GPIOA clock
    __HAL_RCC_GPIOA_CLK_ENABLE();

    // Configure Motor Direction Pins
    GPIO_InitStruct.Pin = MOTOR_LEFT_FORWARD_PIN | MOTOR_LEFT_BACKWARD_PIN |
                          MOTOR_RIGHT_FORWARD_PIN | MOTOR_RIGHT_BACKWARD_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(MOTOR_GPIO_PORT, &GPIO_InitStruct);

    // Configure PWM Pins (PA0, PA1) as Alternate Function
    GPIO_InitStruct.Pin = MOTOR_LEFT_PWM_PIN | MOTOR_RIGHT_PWM_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(MOTOR_GPIO_PORT, &GPIO_InitStruct);

    // Initialize PWM
    PWM_Init();
}

// Set Motor Speed (0 to 100%)
void Motor_SetSpeed(uint16_t left_speed, uint16_t right_speed) {
    if (left_speed > 100) left_speed = 100;
    if (right_speed > 100) right_speed = 100;

    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, (left_speed * 19999) / 100);
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, (right_speed * 19999) / 100);
}

// Move Forward with Speed Control
void Motor_Move_Forward(uint16_t speed) {
    HAL_GPIO_WritePin(MOTOR_GPIO_PORT, MOTOR_LEFT_FORWARD_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(MOTOR_GPIO_PORT, MOTOR_LEFT_BACKWARD_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_GPIO_PORT, MOTOR_RIGHT_FORWARD_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(MOTOR_GPIO_PORT, MOTOR_RIGHT_BACKWARD_PIN, GPIO_PIN_RESET);

    Motor_SetSpeed(speed, speed);
}

// Move Backward with Speed Control
void Motor_Move_Backward(uint16_t speed) {
    HAL_GPIO_WritePin(MOTOR_GPIO_PORT, MOTOR_LEFT_FORWARD_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_GPIO_PORT, MOTOR_LEFT_BACKWARD_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(MOTOR_GPIO_PORT, MOTOR_RIGHT_FORWARD_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_GPIO_PORT, MOTOR_RIGHT_BACKWARD_PIN, GPIO_PIN_SET);

    Motor_SetSpeed(speed, speed);
}

// Stop Motors
void Motor_Stop(void) {
    HAL_GPIO_WritePin(MOTOR_GPIO_PORT, MOTOR_LEFT_FORWARD_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_GPIO_PORT, MOTOR_LEFT_BACKWARD_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_GPIO_PORT, MOTOR_RIGHT_FORWARD_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_GPIO_PORT, MOTOR_RIGHT_BACKWARD_PIN, GPIO_PIN_RESET);

    Motor_SetSpeed(0, 0);
}

// Turn Right with Speed and Time Control
void Motor_Turn_Right(uint16_t speed) {
    HAL_GPIO_WritePin(MOTOR_GPIO_PORT, MOTOR_LEFT_FORWARD_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_GPIO_PORT, MOTOR_LEFT_BACKWARD_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(MOTOR_GPIO_PORT, MOTOR_RIGHT_FORWARD_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(MOTOR_GPIO_PORT, MOTOR_RIGHT_BACKWARD_PIN, GPIO_PIN_RESET);

    Motor_SetSpeed(speed, speed); // Left motor slower, right motor faster
}

// Turn Left with Speed and Time Control
void Motor_Turn_Left(uint16_t speed) {
    HAL_GPIO_WritePin(MOTOR_GPIO_PORT, MOTOR_LEFT_FORWARD_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(MOTOR_GPIO_PORT, MOTOR_LEFT_BACKWARD_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_GPIO_PORT, MOTOR_RIGHT_FORWARD_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_GPIO_PORT, MOTOR_RIGHT_BACKWARD_PIN, GPIO_PIN_SET);

    Motor_SetSpeed(speed, speed); // Right motor slower, left motor faster
}
