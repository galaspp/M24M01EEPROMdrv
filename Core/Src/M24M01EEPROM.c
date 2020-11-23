/*
 * M24M01EEPROM.c
 *
 *  Created on: Nov 23, 2020
 *      Author: My Computer
 */

#include "M24M01EEPROM.h"

I2C_HandleTypeDef hi2c1;
uint8_t deviceAddress;
uint8_t deviceIdentAddress;

void M24M01EEPROMInit(I2C_HandleTypeDef i2c)
{
	hi2c1 = i2c;
	deviceAddress = 0xA0; //1010 (E2)(E1)(A16)(R/W) = 1010 0000 = 0xA0
	deviceIdentAddress = 0xB0; //1011 (E2)(E1)(X)(R/W) = 1011 0000 = 0xB0
}

void EEPROMReadManufacturerCode(uint8_t *pData, uint16_t length)
{
	HAL_I2C_Mem_Read(&hi2c1, deviceIdentAddress, 0x00, I2C_MEMADD_SIZE_16BIT, pData, length, HAL_MAX_DELAY);
}
