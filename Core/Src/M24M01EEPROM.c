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
uint8_t errorCount;
uint32_t timeout;

void M24M01EEPROMInit(I2C_HandleTypeDef i2c)
{
	hi2c1 = i2c;
	deviceAddress = 0xA0; //1010 (E2)(E1)(A16)(R/W) = 1010 0000 = 0xA0
	deviceIdentAddress = 0xB0; //1011 (E2)(E1)(X)(R/W) = 1011 0000 = 0xB0
	errorCount = 0;
	timeout = 0;
}

void EEPROMReadIdentificationCodes(uint8_t *stManufacturerData, uint8_t *familyCodeData, uint8_t *densityCodeData)
{
	HAL_I2C_Mem_Read(&hi2c1, deviceIdentAddress, 0x00, I2C_MEMADD_SIZE_16BIT, stManufacturerData, 1, HAL_MAX_DELAY);
	HAL_I2C_Mem_Read(&hi2c1, deviceIdentAddress, 0x01, I2C_MEMADD_SIZE_16BIT, familyCodeData, 1, HAL_MAX_DELAY);
	HAL_I2C_Mem_Read(&hi2c1, deviceIdentAddress, 0x02, I2C_MEMADD_SIZE_16BIT, densityCodeData, 1, HAL_MAX_DELAY);
}

bool EEPROMWriteData(uint8_t *data, uint32_t address, uint16_t length)
{
	uint8_t device = deviceAddress;
	while(HAL_I2C_IsDeviceReady(&hi2c1, device, 10, 300) == HAL_TIMEOUT);
	if(address > MAXIMUMMEMORYADDRESS)
	{
		return false;
	}

	if((address & 0x00010000) >> 16)
	{
		device = device | 0x02;
	}

	address = address & 0x0000FFFF;
	if(HAL_I2C_Mem_Write(&hi2c1, device, address, I2C_MEMADD_SIZE_16BIT, data, length, HAL_MAX_DELAY) != HAL_OK)
	{
		return false;
	}

	return true;
}


bool EEPROMReadData(uint8_t *data, uint32_t address, uint16_t length)
{
	uint8_t device = deviceAddress;
	HAL_StatusTypeDef status = HAL_ERROR;
	errorCount = 0;
//	uint8_t deviceArray[2];
	if(address > MAXIMUMMEMORYADDRESS)
	{
		return false;
	}

	if((address & 0x00010000) >> 16)
	{
		device = device | 0x02;
	}
	address = address & 0x0000FFFF;

//	deviceArray[0] = (address & 0x0000FF00) >> 8;
//	deviceArray[1] = (address & 0x000000FF);
//	HAL_I2C_Master_Transmit(&hi2c1, device, deviceArray, 2, HAL_MAX_DELAY);
//	HAL_I2C_Master_Receive(&hi2c1, device, data, length, HAL_MAX_DELAY);
//  Do two reads to ensure the data is present
	while(status != HAL_OK)
	{
		while(HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY);
		while(HAL_I2C_IsDeviceReady(&hi2c1, device, 10, 1000) == HAL_TIMEOUT);
//		HAL_Delay(1);
		timeout = getTimeoutUS();
		//EEPROM or I2C module has problems with reading if we request to fast
		while(!hasTimedOutUS(750, timeout));
		status = HAL_I2C_Mem_Read(&hi2c1, device, address, I2C_MEMADD_SIZE_16BIT, data, length, HAL_MAX_DELAY);
		if((status != HAL_OK && status != HAL_TIMEOUT) || errorCount == MAXNUMOFERRORS) return false;
		errorCount++;
	}

	return true;
}

