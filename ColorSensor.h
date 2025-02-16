#ifndef COLORSENSOR_H
#define COLORSENSOR_H

#include <stdint.h>

// Pin definitions for TCS3200
#define S0_PIN GPIO_PIN_0
#define S0_PORT GPIOA
#define S1_PIN GPIO_PIN_1
#define S1_PORT GPIOA
#define S2_PIN GPIO_PIN_2
#define S2_PORT GPIOA
#define S3_PIN GPIO_PIN_3
#define S3_PORT GPIOA
#define OUT_PIN GPIO_PIN_4
#define OUT_PORT GPIOA

// Function prototypes
void ColorSensor_Init(void);
void ColorSensor_SetFilter(uint8_t filter);
uint32_t ColorSensor_ReadFrequency(void);
uint8_t ColorSensor_DetectColor(void);

// Color definitions
#define COLOR_RED 0
#define COLOR_GREEN 1
#define COLOR_UNKNOWN 2

#endif
