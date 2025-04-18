/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  // armed state (initialize to disarm)
  int armed = 0;

  while (1)
  {
	  // check the status of the arm button
	  if (HAL_GPIO_ReadPin(ARMBUTTON_GPIO_Port, ARMBUTTON_Pin) == 0){ // if pushed
		  armed = 1; // arm the system
		  // button was pushed -> turn on LED
		  HAL_GPIO_WritePin(ARMLED_GPIO_Port, ARMLED_Pin, 1);
	  }

	  // check status of disarm button
	  if (HAL_GPIO_ReadPin(DISARMBUTTON_GPIO_Port, DISARMBUTTON_Pin) == 0) { // if pushed
		  armed = 0; // disarm the system
		  HAL_GPIO_WritePin(ARMLED_GPIO_Port, ARMLED_Pin, 0); //turn off armed LED
          HAL_GPIO_WritePin(FRONTALARM_GPIO_Port, FRONTALARM_Pin, 0); // turn off FrontAlarm LED
          HAL_GPIO_WritePin(BACKALARM_GPIO_Port, BACKALARM_Pin, 0); // turn off BackAlarm LED
          HAL_GPIO_WritePin(WINDOWALARM_GPIO_Port, WINDOWALARM_Pin, 0); // turn off WindowAlarm LED
	  }

		// if system is armed, check sensors
		if (armed){
		  // check the FrontSensor
		  if (HAL_GPIO_ReadPin(FRONTSENSOR_GPIO_Port, FRONTSENSOR_Pin) != 0){ // if reed is pulled away
			  // system armed & front door is open:
			  HAL_GPIO_WritePin(FRONTALARM_GPIO_Port, FRONTALARM_Pin, 1); // turn on FrontAlarm LED
		  }

		  // check the BackSensor
		  if (HAL_GPIO_ReadPin(BACKSENSOR_GPIO_Port, BACKSENSOR_Pin) != 0){ // if reed is pulled away
			  // system armed & back door is open:
			  HAL_GPIO_WritePin(BACKALARM_GPIO_Port, BACKALARM_Pin, 1); // turn off BackAlarm LED
		  }

		  // check the WindowSensor
		  if (HAL_GPIO_ReadPin(WINDOWSENSOR_GPIO_Port, WINDOWSENSOR_Pin) != 0){ // if reed is pulled away
			  // system armed & window is open:
			  HAL_GPIO_WritePin(WINDOWALARM_GPIO_Port, WINDOWALARM_Pin, 1); // turn on WindowAlarm LED
		  }
		}


    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 10;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
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
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, ARMLED_Pin|FRONTALARM_Pin|BACKALARM_Pin|WINDOWALARM_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : ARMBUTTON_Pin */
  GPIO_InitStruct.Pin = ARMBUTTON_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(ARMBUTTON_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : DISARMBUTTON_Pin FRONTSENSOR_Pin BACKSENSOR_Pin WINDOWSENSOR_Pin */
  GPIO_InitStruct.Pin = DISARMBUTTON_Pin|FRONTSENSOR_Pin|BACKSENSOR_Pin|WINDOWSENSOR_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : ARMLED_Pin FRONTALARM_Pin BACKALARM_Pin WINDOWALARM_Pin */
  GPIO_InitStruct.Pin = ARMLED_Pin|FRONTALARM_Pin|BACKALARM_Pin|WINDOWALARM_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

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

#ifdef  USE_FULL_ASSERT
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
