#ifndef TCS3200_H
#define TCS3200_H

#include "stm32f1xx_hal.h"

// Macros for Sensor Pins (PA8 to PA12)
#define TCS3200_PORT GPIOA
#define S0_PIN       GPIO_PIN_8
#define S1_PIN       GPIO_PIN_9
#define S2_PIN       GPIO_PIN_11
#define S3_PIN       GPIO_PIN_12
#define OUT_PIN      GPIO_PIN_10  // Frequency Output (TIM1 CH3)

// Color Definitions
typedef enum {
    COLOR_RED,
    COLOR_GREEN,
    COLOR_BLUE,
    COLOR_UNKNOWN
} Color_t;

// Function Prototypes
void TCS3200_Init(void);
uint32_t TCS3200_ReadFrequency(void);
Color_t TCS3200_DetectColor(void);

#endif
