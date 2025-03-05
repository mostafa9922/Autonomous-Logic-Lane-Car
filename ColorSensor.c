#include "ColorSensor.h"

extern TIM_HandleTypeDef htim1;  // Using TIM1 CH3 on PA10

// Initialize the TCS3200 Sensor
void TCS3200_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // Enable GPIOA clock
    __HAL_RCC_GPIOA_CLK_ENABLE();

    // Configure Control Pins (S0, S1, S2, S3)
    GPIO_InitStruct.Pin = S0_PIN | S1_PIN | S2_PIN | S3_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(TCS3200_PORT, &GPIO_InitStruct);

    // Set Frequency Scaling to 20% (S0 = HIGH, S1 = LOW)
    HAL_GPIO_WritePin(TCS3200_PORT, S0_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(TCS3200_PORT, S1_PIN, GPIO_PIN_RESET);

    // Configure Output Pin (OUT) as Input Capture on TIM1 CH3 (PA10)
    GPIO_InitStruct.Pin = OUT_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(TCS3200_PORT, &GPIO_InitStruct);

    // Enable Timer Input Capture Mode
    HAL_TIM_IC_Start(&htim1, TIM_CHANNEL_3);
}

// Read Frequency from Sensor
uint32_t TCS3200_ReadFrequency(void) {
    uint32_t start = __HAL_TIM_GET_COUNTER(&htim1);
    HAL_Delay(10); // Small delay to get frequency sample
    uint32_t end = __HAL_TIM_GET_COUNTER(&htim1);

    return (end > start) ? (end - start) : (0xFFFF - start + end);
}

// Detect Color
Color_t TCS3200_DetectColor(void) {
    uint32_t freq_red, freq_green, freq_blue;

    // Select Red Filter (S2 = LOW, S3 = LOW)
    HAL_GPIO_WritePin(TCS3200_PORT, S2_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(TCS3200_PORT, S3_PIN, GPIO_PIN_RESET);
    HAL_Delay(100);
    freq_red = TCS3200_ReadFrequency();

    // Select Green Filter (S2 = HIGH, S3 = HIGH)
    HAL_GPIO_WritePin(TCS3200_PORT, S2_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(TCS3200_PORT, S3_PIN, GPIO_PIN_SET);
    HAL_Delay(100);
    freq_green = TCS3200_ReadFrequency();

    // Select Blue Filter (S2 = LOW, S3 = HIGH)
    HAL_GPIO_WritePin(TCS3200_PORT, S2_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(TCS3200_PORT, S3_PIN, GPIO_PIN_SET);
    HAL_Delay(100);
    freq_blue = TCS3200_ReadFrequency();

    // Determine Color Based on Highest Frequency
    if (freq_red < freq_green && freq_red < freq_blue) {
        return COLOR_RED;
    } else if (freq_green < freq_red && freq_green < freq_blue) {
        return COLOR_GREEN;
    } else if (freq_blue < freq_red && freq_blue < freq_green) {
        return COLOR_BLUE;
    } else {
        return COLOR_UNKNOWN;
    }
}
