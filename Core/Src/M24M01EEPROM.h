/*
 * M24M01EEPROM.h
 *
 *  Created on: Nov 23, 2020
 *      Author: My Computer
 */

#ifndef SRC_M24M01EEPROM_H_
#define SRC_M24M01EEPROM_H_

#include <stdint.h>
#include <stdbool.h>
#include "main.h"

#define MAXIMUMMEMORYADDRESS 1000000

void M24M01EEPROMInit(I2C_HandleTypeDef i2c);
void EEPROMReadIdentificationCodes(uint8_t *stManufacturerData, uint8_t *familyCodeData, uint8_t *densityCodeData);
void EEPROMWriteByte(uint8_t byte, uint32_t address);
bool EEPROMWriteData(uint8_t *data, uint32_t address, uint16_t length);
void EEPROMReadByte(uint8_t *byte, uint32_t address);
bool EEPROMReadData(uint8_t *data, uint32_t address, uint16_t length);
#endif /* SRC_M24M01EEPROM_H_ */
