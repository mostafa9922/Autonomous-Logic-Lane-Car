#include "motors.h"

// Initialize motor control pins
void Motors_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // Enable GPIOA clock
    __HAL_RCC_GPIOA_CLK_ENABLE();

    // Configure GPIO pins for motor control
    GPIO_InitStruct.Pin = MOTOR_LEFT_FORWARD_PIN | MOTOR_LEFT_BACKWARD_PIN | MOTOR_RIGHT_FORWARD_PIN | MOTOR_RIGHT_BACKWARD_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    // Ensure motors are initially stopped
    Motor_Stop();
}

// Move the car forward
void Motor_Move_Forward(void) {
    HAL_GPIO_WritePin(MOTOR_LEFT_FORWARD_GPIO_PORT, MOTOR_LEFT_FORWARD_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(MOTOR_LEFT_BACKWARD_GPIO_PORT, MOTOR_LEFT_BACKWARD_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_RIGHT_FORWARD_GPIO_PORT, MOTOR_RIGHT_FORWARD_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(MOTOR_RIGHT_BACKWARD_GPIO_PORT, MOTOR_RIGHT_BACKWARD_PIN, GPIO_PIN_RESET);
}

// Move the car backward
void Motor_Move_Backward(void) {
    HAL_GPIO_WritePin(MOTOR_LEFT_FORWARD_GPIO_PORT, MOTOR_LEFT_FORWARD_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_LEFT_BACKWARD_GPIO_PORT, MOTOR_LEFT_BACKWARD_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(MOTOR_RIGHT_FORWARD_GPIO_PORT, MOTOR_RIGHT_FORWARD_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_RIGHT_BACKWARD_GPIO_PORT, MOTOR_RIGHT_BACKWARD_PIN, GPIO_PIN_SET);
}

// Stop the car
void Motor_Stop(void) {
    HAL_GPIO_WritePin(MOTOR_LEFT_FORWARD_GPIO_PORT, MOTOR_LEFT_FORWARD_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_LEFT_BACKWARD_GPIO_PORT, MOTOR_LEFT_BACKWARD_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_RIGHT_FORWARD_GPIO_PORT, MOTOR_RIGHT_FORWARD_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_RIGHT_BACKWARD_GPIO_PORT, MOTOR_RIGHT_BACKWARD_PIN, GPIO_PIN_RESET);
}

// Turn the car left for a specified time
void Motor_Turn_Left(uint32_t turn_time_ms) {
    HAL_GPIO_WritePin(MOTOR_LEFT_FORWARD_GPIO_PORT, MOTOR_LEFT_FORWARD_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_LEFT_BACKWARD_GPIO_PORT, MOTOR_LEFT_BACKWARD_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(MOTOR_RIGHT_FORWARD_GPIO_PORT, MOTOR_RIGHT_FORWARD_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(MOTOR_RIGHT_BACKWARD_GPIO_PORT, MOTOR_RIGHT_BACKWARD_PIN, GPIO_PIN_RESET);

    HAL_Delay(turn_time_ms);  // Wait for the specified time
    Motor_Stop();  // Stop after turning
}

// Turn the car right for a specified time
void Motor_Turn_Right(uint32_t turn_time_ms) {
    HAL_GPIO_WritePin(MOTOR_LEFT_FORWARD_GPIO_PORT, MOTOR_LEFT_FORWARD_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(MOTOR_LEFT_BACKWARD_GPIO_PORT, MOTOR_LEFT_BACKWARD_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_RIGHT_FORWARD_GPIO_PORT, MOTOR_RIGHT_FORWARD_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_RIGHT_BACKWARD_GPIO_PORT, MOTOR_RIGHT_BACKWARD_PIN, GPIO_PIN_SET);

    HAL_Delay(turn_time_ms);  // Wait for the specified time
    Motor_Stop();  // Stop after turning
}
