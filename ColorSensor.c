#include "ColorSensor.h"

// Initialize the color sensor pins
void ColorSensor_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    __HAL_RCC_GPIOB_CLK_ENABLE(); // Enable GPIOB clock

    // Configure S0, S1, S2, S3 as output pins
    GPIO_InitStruct.Pin = S0_PIN | S1_PIN | S2_PIN | S3_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(SENSOR_PORT, &GPIO_InitStruct);

    // Configure OUT as input pin
    GPIO_InitStruct.Pin = OUT_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    HAL_GPIO_Init(SENSOR_PORT, &GPIO_InitStruct);

    // Set frequency scaling to 20% (S0 = HIGH, S1 = LOW)
    HAL_GPIO_WritePin(SENSOR_PORT, S0_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(SENSOR_PORT, S1_PIN, GPIO_PIN_RESET);
}

// Set the filter for red, green, or blue
void ColorSensor_SetFilter(uint8_t filter) {
    static const uint16_t filter_settings[3][2] = {
        {GPIO_PIN_RESET, GPIO_PIN_RESET}, // Red filter
        {GPIO_PIN_SET, GPIO_PIN_SET},     // Green filter
        {GPIO_PIN_RESET, GPIO_PIN_SET}    // Blue filter
    };

    HAL_GPIO_WritePin(SENSOR_PORT, S2_PIN, filter_settings[filter][0]);
    HAL_GPIO_WritePin(SENSOR_PORT, S3_PIN, filter_settings[filter][1]);
}

// Read the frequency from the OUT pin
uint32_t ColorSensor_ReadFrequency(void) {
    uint32_t count = 0;
    uint32_t startTime = HAL_GetTick();

    while (HAL_GetTick() - startTime < 100) {
        if (HAL_GPIO_ReadPin(SENSOR_PORT, OUT_PIN) == GPIO_PIN_SET) {
            count++;
            while (HAL_GPIO_ReadPin(SENSOR_PORT, OUT_PIN) == GPIO_PIN_SET); // Wait for LOW
        }
    }

    return count;
}

// Detect if the color is red or green
uint8_t ColorSensor_DetectColor(void) {
    ColorSensor_SetFilter(0); // Red filter
    HAL_Delay(10);
    uint32_t redFrequency = ColorSensor_ReadFrequency();

    ColorSensor_SetFilter(1); // Green filter
    HAL_Delay(10);
    uint32_t greenFrequency = ColorSensor_ReadFrequency();

    return (redFrequency > greenFrequency) ? COLOR_RED : (greenFrequency > redFrequency) ? COLOR_GREEN : COLOR_UNKNOWN;
}
