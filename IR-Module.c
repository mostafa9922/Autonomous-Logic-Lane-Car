#include "IR-Module.h"

// Initialize the GPIO pins for IR sensors
void IR_Sensor_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    __HAL_RCC_GPIOA_CLK_ENABLE();  // Enable clock for GPIOA

    GPIO_InitStruct.Pin = IR_SENSOR_1_PIN | IR_SENSOR_2_PIN|IR_SENSOR_3_PIN | IR_SENSOR_4_PIN;
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
// Read first sensor
uint8_t IR_Sensor3_Read(void) {
    return HAL_GPIO_ReadPin(IR_SENSOR_PORT, IR_SENSOR_3_PIN);
}

// Read second sensor
uint8_t IR_Sensor4_Read(void) {
    return HAL_GPIO_ReadPin(IR_SENSOR_PORT, IR_SENSOR_4_PIN);
}
