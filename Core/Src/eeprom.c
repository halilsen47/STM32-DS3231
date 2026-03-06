#include "eeprom.h"

extern I2C_HandleTypeDef hi2c1;

void Write_EEPROM(uint16_t MemAdress, uint8_t *pdata, uint8_t size)
{
	HAL_I2C_Mem_Write(&hi2c1, EEPROM_WRİTE_ADRESS, MemAdress, I2C_MEMADD_SIZE_16BIT, pdata, size, 100);
	HAL_Delay(5);

}


void Read_EEPROM(uint16_t MemAdress, uint8_t *pdata, uint8_t size)
{
	HAL_I2C_Mem_Read(&hi2c1, EEPROM_READ_ADRESS, MemAdress, I2C_MEMADD_SIZE_16BIT, pdata, size, 100);
}



