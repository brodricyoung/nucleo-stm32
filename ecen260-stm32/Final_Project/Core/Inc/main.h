/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define CHANNEL1_Pin GPIO_PIN_0
#define CHANNEL1_GPIO_Port GPIOA
#define CHANNEL2_Pin GPIO_PIN_1
#define CHANNEL2_GPIO_Port GPIOA
#define FGEN_OUT_Pin GPIO_PIN_4
#define FGEN_OUT_GPIO_Port GPIOA
#define REVERSE_Pin GPIO_PIN_8
#define REVERSE_GPIO_Port GPIOA
#define REVERSE_EXTI_IRQn EXTI9_5_IRQn
#define FREQ_BIG_Pin GPIO_PIN_10
#define FREQ_BIG_GPIO_Port GPIOA
#define FREQ_BIG_EXTI_IRQn EXTI15_10_IRQn
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define FREQ_SMALL_Pin GPIO_PIN_3
#define FREQ_SMALL_GPIO_Port GPIOB
#define FREQ_SMALL_EXTI_IRQn EXTI3_IRQn
#define VPP_SMALL_Pin GPIO_PIN_4
#define VPP_SMALL_GPIO_Port GPIOB
#define VPP_SMALL_EXTI_IRQn EXTI4_IRQn
#define VPP_BIG_Pin GPIO_PIN_5
#define VPP_BIG_GPIO_Port GPIOB
#define VPP_BIG_EXTI_IRQn EXTI9_5_IRQn

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
