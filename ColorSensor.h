#ifndef COLORSENSOR_H
#define COLORSENSOR_H

#include <stdint.h>
#include "stm32f1xx_hal.h"

// Define a single macro for the sensor port
#define SENSOR_PORT GPIOB

// Pin definitions for TCS3200
#define S0_PIN  GPIO_PIN_6
#define S1_PIN  GPIO_PIN_7
#define S2_PIN  GPIO_PIN_8
#define S3_PIN  GPIO_PIN_9
#define OUT_PIN GPIO_PIN_10

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
