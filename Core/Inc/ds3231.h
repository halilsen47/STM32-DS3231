/*
 * ds3231.h
 *
 *  Created on: 6 Mar 2026
 *      Author: senha
 */

#ifndef INC_DS3231_H_
#define INC_DS3231_H_



#include "stm32f4xx_hal.h"

#define DS3231_WRİTE_ADRESS				0xD0
#define DS3231_READ_ADRESS 				0xD1


//my structers
typedef struct
{
	uint8_t sec;
	uint8_t min;
	uint8_t hour;
	uint8_t weekOfDay;
	uint8_t MonthOfDay;
	uint8_t month;
	uint16_t year;

}DS3231_Time_t;

typedef struct
{
	uint8_t sec;
	uint8_t min;
	uint8_t hour;
	uint8_t weekOfDay;

}DS3231_Alarm_t;


//funciton prototypes

uint8_t DEC_TO_BCD(uint8_t val);

uint8_t BCD_TO_DEC(uint8_t val);

void DS3231_Set_Time(uint8_t sec,uint8_t min, uint8_t hour,uint8_t weekOfDay,uint8_t monthOfDay,uint8_t month,uint8_t year);

DS3231_Time_t DS3231_Get_Time(void);

void DS3231_Set_Alarm(uint8_t sec,uint8_t min,uint8_t hour,uint8_t weekOfDay);

DS3231_Alarm_t DS3231_Get_Alarm(void);

#endif /* INC_DS3231_H_ */
