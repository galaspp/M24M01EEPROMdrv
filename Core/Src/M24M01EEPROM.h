/*
 * M24M01EEPROM.h
 *
 *  Created on: Nov 23, 2020
 *      Author: My Computer
 */

#ifndef SRC_M24M01EEPROM_H_
#define SRC_M24M01EEPROM_H_

#include <stdint.h>
#include "main.h"

void M24M01EEPROMInit(I2C_HandleTypeDef i2c);
void EEPROMReadManufacturerCode(uint8_t *pData, uint16_t length);

#endif /* SRC_M24M01EEPROM_H_ */
