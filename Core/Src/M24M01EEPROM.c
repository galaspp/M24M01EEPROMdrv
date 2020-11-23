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

void EEPROMReadIdentificationCodes(uint8_t *stManufacturerData, uint8_t *familyCodeData, uint8_t *densityCodeData)
{
	HAL_I2C_Mem_Read(&hi2c1, deviceIdentAddress, 0x00, I2C_MEMADD_SIZE_16BIT, stManufacturerData, 1, HAL_MAX_DELAY);
	HAL_I2C_Mem_Read(&hi2c1, deviceIdentAddress, 0x01, I2C_MEMADD_SIZE_16BIT, familyCodeData, 1, HAL_MAX_DELAY);
	HAL_I2C_Mem_Read(&hi2c1, deviceIdentAddress, 0x02, I2C_MEMADD_SIZE_16BIT, densityCodeData, 1, HAL_MAX_DELAY);
}

void EEPROMWriteByte(uint8_t byte, uint32_t address)
{
	//HAL_StatusTypeDef HAL_I2C_Mem_Write(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout)

	HAL_I2C_Mem_Write(&hi2c2, deviceAddress, address, I2C_MEMADD_SIZE_16BIT, &byte, 1, HAL_MAX_DELAY);
}

bool EEPROMWriteData(uint8_t *data, uint32_t address, uint16_t length)
{
	uint8_t device = deviceAddress;
	if(address > MAXIMUMMEMORYADDRESS)
	{
		return false;
	}

	if(address & 0x0100)
	{
		device = device | 0x02;
	}

	address = address & 0x00FF;
	HAL_I2C_Mem_Write(&hi2c2, device, address, I2C_MEMADD_SIZE_16BIT, data, length, HAL_MAX_DELAY);

	return true;
}

void EEPROMReadByte(uint8_t *byte, uint32_t address)
{

}

bool EEPROMReadData(uint8_t *data, uint32_t address, uint16_t length)
{
	uint8_t device = deviceAddress;
	if(address > MAXIMUMMEMORYADDRESS)
	{
		return false;
	}

	if(address & 0x0100)
	{
		device = device | 0x02;
	}

	address = address & 0x00FF;
	HAL_I2C_Mem_Read(&hi2c1, device, address, I2C_MEMADD_SIZE_16BIT, data, length, HAL_MAX_DELAY);

	return true;
}

