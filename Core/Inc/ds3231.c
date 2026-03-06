#include "ds3231.h";
extern I2C_HandleTypeDef hi2c1;

extern DS3231_Time_t ds3231_Time;
extern DS3231_Alarm_t ds3231_Alarm;
extern uint8_t val;
extern uint8_t control_reg_val; // INTCN=1, A1IE=1
extern uint8_t status_reg_reset ;


uint8_t DEC_TO_BCD(uint8_t val)
{

	return (uint8_t)((val / 10 * 16) + (val % 10));
}

uint8_t BCD_TO_DEC(uint8_t val)
{
	return (uint8_t)((val / 16 * 10) + (val % 16));
}

void DS3231_Set_Time(uint8_t sec,uint8_t min, uint8_t hour,uint8_t weekOfDay,uint8_t monthOfDay,uint8_t month,uint8_t year)
{
	uint8_t time_data[6] = {0};
	time_data[0] = DEC_TO_BCD(sec);
	time_data[1] = DEC_TO_BCD(min);
	time_data[2] = DEC_TO_BCD(hour);
	time_data[3] = DEC_TO_BCD(weekOfDay);
	time_data[4] = DEC_TO_BCD(monthOfDay);
	time_data[5] = DEC_TO_BCD(month);
	time_data[6] = DEC_TO_BCD(year);

	HAL_I2C_Mem_Write(&hi2c1, DS3231_WRİTE_ADRESS, 0x00, 1, time_data, 7, 100);
}

DS3231_Time_t DS3231_Get_Time(void)
{
	DS3231_Time_t dsTime = {0};
	uint8_t recive_time[7] = {0};

	if(HAL_I2C_Mem_Read(&hi2c1, DS3231_READ_ADRESS, 0X00, 1, recive_time, 7, 100) == HAL_OK)
	{
		dsTime.sec = BCD_TO_DEC(recive_time[0]);
		dsTime.min = BCD_TO_DEC(recive_time[1]);
		dsTime.hour = BCD_TO_DEC(recive_time[2]);
		dsTime.weekOfDay = BCD_TO_DEC(recive_time[3]);
		dsTime.MonthOfDay = BCD_TO_DEC(recive_time[4]);
		dsTime.month = BCD_TO_DEC(recive_time[5]);
		dsTime.year = 2000 + BCD_TO_DEC(recive_time[6]);
	}
	else
	{
		HAL_I2C_DeInit(&hi2c1);
		HAL_I2C_Init(&hi2c1);
	}

	return dsTime;
}


//0x07 to 0x0A alarm registers
DS3231_Alarm_t DS3231_Get_Alarm(void)
{
	DS3231_Alarm_t dsAlarm = {0};
	uint8_t reciveData[4] = {0};
	ds3231_Alarm.sec= 1;
	if(HAL_I2C_Mem_Read(&hi2c1, DS3231_READ_ADRESS, 0X07, 1, reciveData, 4, 100) == HAL_OK)
	{
		dsAlarm.sec = BCD_TO_DEC(reciveData[0]);
		dsAlarm.min = BCD_TO_DEC(reciveData[1]);
		dsAlarm.hour = BCD_TO_DEC(reciveData[2]);
		dsAlarm.weekOfDay = BCD_TO_DEC(reciveData[3] & 0x0F) ;
	}

	return dsAlarm;
}

void DS3231_Set_Alarm(uint8_t sec,uint8_t min,uint8_t hour,uint8_t weekOfDay)
{
	uint8_t transmitData[4] = {0};

	transmitData[0] = DEC_TO_BCD(sec);
	transmitData[1] = DEC_TO_BCD(min);
	transmitData[2] = DEC_TO_BCD(hour);
	transmitData[3] = (uint8_t)(1 << 6) | DEC_TO_BCD(weekOfDay) ;

	HAL_I2C_Mem_Write(&hi2c1, DS3231_WRİTE_ADRESS, 0x07, 1, transmitData, 4, 100);

}

