#ifndef INC_IRModule_H_
#define INC_IRModule_H_

#include "stm32f1xx_hal.h"

#define IR_SENSOR_1_PIN GPIO_PIN_0  // Adjust as needed
#define IR_SENSOR_2_PIN GPIO_PIN_1  // Adjust as needed
#define IR_SENSOR_PORT GPIOA        // Adjust based on your wiring

void IR_Sensor_Init(void);
uint8_t IR_Sensor1_Read(void);
uint8_t IR_Sensor2_Read(void);
uint8_t Check_Obstacle(void);


#endif
