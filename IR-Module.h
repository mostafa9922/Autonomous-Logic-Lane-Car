#ifndef INC_IRModule_H_
#define INC_IRModule_H_

#include "stm32f1xx_hal.h"

#define IR_SENSOR_PORT GPIOB        // Adjust based on your wiring
#define IR_SENSOR_1_PIN GPIO_PIN_12  // Adjust as needed
#define IR_SENSOR_2_PIN GPIO_PIN_13  // Adjust as needed
#define IR_SENSOR_3_PIN GPIO_PIN_14  // Adjust as needed
#define IR_SENSOR_4_PIN GPIO_PIN_15  // Adjust as needed

void IR_Sensor_Init(void);
uint8_t IR_Sensor1_Read(void);
uint8_t IR_Sensor2_Read(void);
uint8_t IR_Sensor3_Read(void);
uint8_t IR_Sensor4_Read(void);

#endif
