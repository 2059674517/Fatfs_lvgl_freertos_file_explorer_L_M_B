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
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "string.h"
#include "lcd_init.h"
#include "lcd.h"
//#include "pic.h"
#include "CST816T.h"
#include "lv_port_disp.h"
#include "lv_port_indev.h"
#include "core_delay.h" 
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

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED0_Pin GPIO_PIN_9
#define LED0_GPIO_Port GPIOF
#define LED1_Pin GPIO_PIN_10
#define LED1_GPIO_Port GPIOF
#define LCD_CS_Pin GPIO_PIN_0
#define LCD_CS_GPIO_Port GPIOA
#define LCD_DC_Pin GPIO_PIN_1
#define LCD_DC_GPIO_Port GPIOA
#define LCD_BLK_Pin GPIO_PIN_2
#define LCD_BLK_GPIO_Port GPIOA
#define LCD_RST_Pin GPIO_PIN_3
#define LCD_RST_GPIO_Port GPIOA
#define TOUCH_INT_Pin GPIO_PIN_5
#define TOUCH_INT_GPIO_Port GPIOB
#define TOUCH_INT_EXTI_IRQn EXTI9_5_IRQn
#define TOUCH_TRST_Pin GPIO_PIN_8
#define TOUCH_TRST_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
#define u8 uint8_t
#define u16 uint16_t
#define u32 uint32_t
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
