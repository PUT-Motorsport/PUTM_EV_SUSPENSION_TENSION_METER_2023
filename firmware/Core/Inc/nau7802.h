/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    nau7802.c
 * @brief   NAU7802 driver
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes -------------------------------------------------------------------*/
#include "i2c.h"

#ifndef NAU7802_H_
#define NAU7802_H_

/* Public enums ---------------------------------------------------------------*/
enum NAU7802_CHANNEL
{
	NAU7802_CHANNEL_1 = 0, NAU7802_CHANNEL_2 = 1, NAU7802_SWITCH = 2
};

/* Public variables -----------------------------------------------------------*/
extern uint8_t NAU7802_ADDRESS;

/* Public functions -----------------------------------------------------------*/
void NAU7802_Init(I2C_HandleTypeDef i2c);
void NAU7802_Switch_Channel(I2C_HandleTypeDef, enum NAU7802_CHANNEL channel);
void NAU7802_Read(I2C_HandleTypeDef i2c, uint8_t buffer[8]);
float NAU7802_Read_Float(I2C_HandleTypeDef i2c);

#endif /* NAU7802_H_ */
