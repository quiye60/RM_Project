/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN2_H
#define __MAIN2_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "stm32f1xx_hal_spi.h"
#include "stm32f1xx_hal.h"
	
#include "main.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "ST7735.h"
#include "uart_printf.h"	
#include "font.h"
#include "can_user.h"
#include "string.h"
#include "stdint.h"
#include "stdarg.h"
#include "stdio.h"
#include "stm32f1xx_hal_uart.h"
#include "stm32f1xx_hal_dma.h"
#include "main.h"
#include <stdio.h>
#include "stm32f1xx_hal.h"
#include "string.h"
#include "stdint.h"
#include "stdarg.h"
#include "stdio.h"
#include "stm32f1xx_hal_uart.h"









	
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

/* USER CODE BEGIN Private defines */
















/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN2_H */
