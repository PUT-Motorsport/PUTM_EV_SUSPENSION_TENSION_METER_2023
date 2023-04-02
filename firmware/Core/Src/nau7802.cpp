/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    nau7802.c
 * @brief   NAU7802 driver
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "nau7802.hpp"

/* Private variables ---------------------------------------------------------*/
uint8_t NAU7802_ADDRESS = 0x2A;

/* Public functions ----------------------------------------------------------*/
void NAU7802_Init(I2C_HandleTypeDef i2c)
{
	int8_t buff;
	uint8_t bufferArray[8];

	bufferArray[0] = 0x00;
	bufferArray[1] = 0x01;
	HAL_I2C_Master_Transmit(&i2c, (NAU7802_ADDRESS << 1), bufferArray, 2, 1E6);

	bufferArray[0] = 0x00;
	bufferArray[1] = 0x02;
	HAL_I2C_Master_Transmit(&i2c, (NAU7802_ADDRESS << 1), bufferArray, 2, 1E6);

	do {
		buff = 0x00;
		HAL_I2C_Master_Transmit(&i2c, (NAU7802_ADDRESS << 1), (uint8_t*)&buff, 1, 1E6);
		HAL_I2C_Master_Receive(&i2c, (NAU7802_ADDRESS << 1), (uint8_t*)&buff, 1, 1E6);
	} while (!(buff & 0x08));

	bufferArray[0] = 0x00;
	bufferArray[1] = 0xAE;
	HAL_I2C_Master_Transmit(&i2c, (NAU7802_ADDRESS << 1), bufferArray, 2, 1E6);

	bufferArray[0] = 0x15;
	bufferArray[1] = 0x30;
	HAL_I2C_Master_Transmit(&i2c, (NAU7802_ADDRESS << 1), bufferArray, 2, 1E6);

	buff = 0x1B;
	HAL_I2C_Master_Transmit(&i2c, (NAU7802_ADDRESS << 1), (uint8_t*)&buff, 1, 1E6);
	HAL_I2C_Master_Receive(&i2c, (NAU7802_ADDRESS << 1), (uint8_t*)&buff, 1, 1E6);

	bufferArray[0] = 0x1B;
	bufferArray[1] = buff | 0x10;
	HAL_I2C_Master_Transmit(&i2c, (NAU7802_ADDRESS << 1), bufferArray, 2, 1E6);

	buff = 0x02;
	HAL_I2C_Master_Transmit(&i2c, (NAU7802_ADDRESS << 1), (uint8_t*)&buff, 1, 1E6);
	HAL_I2C_Master_Receive(&i2c, (NAU7802_ADDRESS << 1), (uint8_t*)&buff, 1, 1E6);

	bufferArray[0] = 0x02;
	bufferArray[1] = buff | 0xF0;
	HAL_I2C_Master_Transmit(&i2c, (NAU7802_ADDRESS << 1), bufferArray, 2, 1E6);
}

void NAU7802_Switch_Channel(I2C_HandleTypeDef i2c, enum NAU7802_CHANNEL channel)
{
	int8_t buffer;
	uint8_t bufferArray[8];

	if (channel == NAU7802_SWITCH)
	{
		buffer = 0x02;
		HAL_I2C_Master_Transmit(&i2c, (NAU7802_ADDRESS << 1), (uint8_t*)&buffer, 1, 1E6);
		HAL_I2C_Master_Receive(&i2c, (NAU7802_ADDRESS << 1), (uint8_t*)&buffer, 1, 1E6);

		bufferArray[0] = 0x02;
		bufferArray[1] = buffer ^ 0x80;
		HAL_I2C_Master_Transmit(&i2c, (NAU7802_ADDRESS << 1), bufferArray, 2, 1E6);
		return;
	} else if (channel == NAU7802_CHANNEL_1) {
		buffer = 0x02;
		HAL_I2C_Master_Transmit(&i2c, (NAU7802_ADDRESS << 1), (uint8_t*)&buffer, 1, 1E6);
		HAL_I2C_Master_Receive(&i2c, (NAU7802_ADDRESS << 1), (uint8_t*)&buffer, 1, 1E6);

		bufferArray[0] = 0x02;
		bufferArray[1] = buffer & ~0x80;
		HAL_I2C_Master_Transmit(&i2c, (NAU7802_ADDRESS << 1), bufferArray, 2, 1E6);
		return;
	}

	buffer = 0x02;
	HAL_I2C_Master_Transmit(&i2c, (NAU7802_ADDRESS << 1), (uint8_t*)&buffer, 1, 1E6);
	HAL_I2C_Master_Receive(&i2c, (NAU7802_ADDRESS << 1), (uint8_t*)&buffer, 1, 1E6);

	bufferArray[0] = 0x02;
	bufferArray[1] = buffer | 0x80;
	HAL_I2C_Master_Transmit(&i2c, (NAU7802_ADDRESS << 1), bufferArray, 2, 1E6);
}

void NAU7802_Read(I2C_HandleTypeDef i2c, uint8_t buffer[8])
{
	uint8_t msg = 0x12;
	HAL_I2C_Master_Transmit(&i2c, (NAU7802_ADDRESS << 1), &msg, 1, 1E6);
	HAL_I2C_Master_Receive(&i2c, (NAU7802_ADDRESS << 1), buffer, 3, 1E6);
}

float NAU7802_Read_Float(I2C_HandleTypeDef i2c)
{
	int result;
	int result2;
	float resultf;
	uint8_t buffer[8];
	NAU7802_Read(i2c, buffer);
	result = buffer[0];
	result = result << 8;
	result |= buffer[1];
	result = result << 8;
	result |= buffer[2];
	result2 = result << 8;
	result2 = result2 >> 8;
	return resultf = ((float)result2 / (float)0x007FFFFF) * 1.65f;
}
