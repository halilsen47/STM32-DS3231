/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "ds3231.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define DS3231_WRİTE_ADRESS				0xD0
#define DS3231_READ_ADRESS 				0xD1


/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

/* USER CODE BEGIN PV */

DS3231_Time_t ds3231_Time;
DS3231_Alarm_t ds3231_Alarm;
uint8_t val = 0;
uint8_t control_reg_val = 0x05; // INTCN=1, A1IE=1
uint8_t status_reg_reset = 0x00;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
/*
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
*/

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */


  //control Reg write for activate the alarm 1 and other config

  HAL_I2C_Mem_Write(&hi2c1, 0xD0, 0x0E, 1, &control_reg_val, 1, HAL_MAX_DELAY);
  //status Reg write for set the alarm1 flag 0
  HAL_I2C_Mem_Write(&hi2c1, 0xD0, 0x0F, 1, &status_reg_reset, 1, HAL_MAX_DELAY);


  DS3231_Set_Time(50, 59, 23, 7, 31, 12, 26);
  DS3231_Set_Alarm(10,0, 0, 1);

  ds3231_Alarm = DS3231_Get_Alarm();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */


	 ds3231_Time = DS3231_Get_Time();





  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin : PB1 */
  GPIO_InitStruct.Pin = GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI1_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
