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
#include "can.h"
#include "dma.h"
#include "usart.h"
#include "gpio.h"

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
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */








void CAN_DebugDump(void)
{
	u6_printf("\r\n===== CAN DEBUG DUMP =====\r\n");

	// 1. HAL状态
	u6_printf("State: %d\r\n", hcan1.State);
	u6_printf("Error: 0x%08lX\r\n", HAL_CAN_GetError(&hcan1));

	// 2. CAN关键寄存器
	u6_printf("MSR   : 0x%08lX\r\n", hcan1.Instance->MSR);
	u6_printf("ESR   : 0x%08lX\r\n", hcan1.Instance->ESR);
	u6_printf("BTR   : 0x%08lX\r\n", hcan1.Instance->BTR);

	// 3. TX状态
	u6_printf("TSR   : 0x%08lX\r\n", hcan1.Instance->TSR);

	// 4. FIFO状态
	u6_printf("RF0R  : 0x%08lX\r\n", hcan1.Instance->RF0R);
	u6_printf("RF1R  : 0x%08lX\r\n", hcan1.Instance->RF1R);

	// 5. 错误计数（非常关键）
	u6_printf("ESR_LEC: %lu\r\n", (hcan1.Instance->ESR & 0x70) >> 4);

	u6_printf("==========================\r\n\r\n");
}


















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






	U6_PtrInit();


	const uint8_t txtx[]="nihaoya!";


	uint32_t tt=0;










  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_USART6_UART_Init();
  MX_CAN1_Init();
  MX_CAN2_Init();
  /* USER CODE BEGIN 2 */








	CAN_Filter_FIFO0_AllPass_Init();   // 先配置滤波器
	HAL_CAN_Start(&hcan1);       // 再启动CAN
	u6_printf("MSR after start = 0x%08lX\r\n", hcan1.Instance->MSR);
	HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);




	HAL_UART_Receive_DMA(&huart6,U1_RxBuff,256);
	__HAL_UART_ENABLE_IT(&huart6, UART_IT_IDLE);








	//===========================================
	//变量声明
	uint16_t current6020[4]={2000,2000,2000,2000};























  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

  	CAN_DebugDump();








  	if (HAL_CAN_GetError(&hcan1) & HAL_CAN_ERROR_BOF)
  	{
  		HAL_CAN_Stop(&hcan1);
  		HAL_CAN_Init(&hcan1);
  		HAL_CAN_Start(&hcan1);
  	}


	HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_1);
  	HAL_Delay(50);
  	HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_2);
  	HAL_Delay(50);
  	HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_3);
  	HAL_Delay(50);
  	HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_4);
  	HAL_Delay(50);
  	HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_5);
  	HAL_Delay(50);
  	HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_6);
  	HAL_Delay(50);
  	HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_7);
  	HAL_Delay(50);
  	HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_8);
  	HAL_Delay(50);






  	u6_printf("time: %d\n",tt++);


  	u6_printf("$$$\n");
  	//HAL_UART_Transmit(&huart1,U1_RxBuff,256,1000);
  	u6_printf("$$$\n\n");

  	CAN_TxData(txtx,8);
  	//	CAN_RxData(U1_RxBuff);

	uint8_t AAA[8];
	CAN_GM6020_Current(current6020);
  	CAN_RxData(AAA);

  	u6_printf("HAL_CAN_IsActive:%d\n",hcan1.State);



  	u6_printf("CAN_STATE=%d\r\n", hcan1.State);
  	u6_printf("CAN_ERROR=0x%08lX\r\n", HAL_CAN_GetError(&hcan1));
	HAL_Delay(5000);



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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 6;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
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
