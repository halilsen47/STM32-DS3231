/*
 * eeprom.h
 *
 *  Created on: 6 Mar 2026
 *      Author: senha
 */

#ifndef INC_EEPROM_H_
#define INC_EEPROM_H_


#define EEPROM_WRİTE_ADRESS 			0xAE
#define EEPROM_READ_ADRESS				0xAF

#include "stm32f4xx_hal.h"
//  HAL_I2C_Mem_Write(hi2c, DevAddress, MemAddress, MemAddSize, pData, Size, Timeout)

void Write_EEPROM(uint16_t MemAdress, uint8_t *pdata, uint8_t size);

void Read_EEPROM(uint16_t MemAdress, uint8_t *pdata, uint8_t size);












#endif /* INC_EEPROM_H_ */
