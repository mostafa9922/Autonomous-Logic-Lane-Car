#include "IR-Module.h"

// Initialize the GPIO pins for IR sensors
void IR_Sensor_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    __HAL_RCC_GPIOA_CLK_ENABLE();  // Enable clock for GPIOA

    GPIO_InitStruct.Pin = IR_SENSOR_1_PIN | IR_SENSOR_2_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;  // No pull-up or pull-down
    HAL_GPIO_Init(IR_SENSOR_PORT, &GPIO_InitStruct);
}

// Read first sensor
uint8_t IR_Sensor1_Read(void) {
    return HAL_GPIO_ReadPin(IR_SENSOR_PORT, IR_SENSOR_1_PIN);
}

// Read second sensor
uint8_t IR_Sensor2_Read(void) {
    return HAL_GPIO_ReadPin(IR_SENSOR_PORT, IR_SENSOR_2_PIN);
}


uint8_t Check_Obstacle(void) {
    uint8_t sensor1 = IR_Sensor1_Read();
    uint8_t sensor2 = IR_Sensor2_Read();

    if (sensor1 == 0) {
            return 1;  // Sensor 1 detects an obstacle
        } else if (sensor2 == 0) {
            return 2;  // Sensor 2 detects an obstacle
        }
        return 0;  // No obstacle detected
}
