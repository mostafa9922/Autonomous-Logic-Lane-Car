#include "ColorSensor.h"
#include "stm32f1xx_hal.h" // Include the appropriate HAL library for your MCU

// Initialize the color sensor pins
void ColorSensor_Init(void) {
    // Configure S0, S1, S2, S3 as output pins
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    __HAL_RCC_GPIOA_CLK_ENABLE(); // Enable GPIOA clock

    GPIO_InitStruct.Pin = S0_PIN | S1_PIN | S2_PIN | S3_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(S0_PORT, &GPIO_InitStruct);

    // Configure OUT as input pin
    GPIO_InitStruct.Pin = OUT_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(OUT_PORT, &GPIO_InitStruct);

    // Set frequency scaling to 20% (S0 = HIGH, S1 = LOW)
    HAL_GPIO_WritePin(S0_PORT, S0_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(S1_PORT, S1_PIN, GPIO_PIN_RESET);
}

// Set the filter for red, green, or blue
void ColorSensor_SetFilter(uint8_t filter) {
    switch (filter) {
        case 0: // Red filter (S2 = LOW, S3 = LOW)
            HAL_GPIO_WritePin(S2_PORT, S2_PIN, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(S3_PORT, S3_PIN, GPIO_PIN_RESET);
            break;
        case 1: // Green filter (S2 = HIGH, S3 = HIGH)
            HAL_GPIO_WritePin(S2_PORT, S2_PIN, GPIO_PIN_SET);
            HAL_GPIO_WritePin(S3_PORT, S3_PIN, GPIO_PIN_SET);
            break;
        case 2: // Blue filter (S2 = LOW, S3 = HIGH)
            HAL_GPIO_WritePin(S2_PORT, S2_PIN, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(S3_PORT, S3_PIN, GPIO_PIN_SET);
            break;
        default:
            break;
    }
}

// Read the frequency from the OUT pin
uint32_t ColorSensor_ReadFrequency(void) {
    uint32_t frequency = 0;
    uint32_t startTime = HAL_GetTick();

    // Count the number of pulses in 100ms
    while (HAL_GetTick() - startTime < 100) {
        if (HAL_GPIO_ReadPin(OUT_PORT, OUT_PIN) == GPIO_PIN_SET) {
            frequency++;
            while (HAL_GPIO_ReadPin(OUT_PORT, OUT_PIN) == GPIO_PIN_SET); // Wait for LOW
        }
    }

    return frequency;
}

// Detect if the color is red or green
uint8_t ColorSensor_DetectColor(void) {
    uint32_t redFrequency = 0, greenFrequency = 0;

    // Measure red frequency
    ColorSensor_SetFilter(0); // Set filter to red
    HAL_Delay(10); // Wait for stabilization
    redFrequency = ColorSensor_ReadFrequency();

    // Measure green frequency
    ColorSensor_SetFilter(1); // Set filter to green
    HAL_Delay(10); // Wait for stabilization
    greenFrequency = ColorSensor_ReadFrequency();

    // Determine the color based on frequencies
    if (redFrequency > greenFrequency) {
        return COLOR_RED;
    } else if (greenFrequency > redFrequency) {
        return COLOR_GREEN;
    } else {
        return COLOR_UNKNOWN;
    }
}
