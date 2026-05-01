/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdlib.h>

#include "main3.h"
#include "uart_printf.h"
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
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for led */
osThreadId_t ledHandle;
const osThreadAttr_t led_attributes = {
  .name = "led",
  .stack_size = 300 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for uart */
osThreadId_t uartHandle;
const osThreadAttr_t uart_attributes = {
  .name = "uart",
  .stack_size = 1000 * 4,
  .priority = (osPriority_t) osPriorityRealtime7,
};
/* Definitions for can */
osThreadId_t canHandle;
const osThreadAttr_t can_attributes = {
  .name = "can",
  .stack_size = 700 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for GM6020 */
osThreadId_t GM6020Handle;
const osThreadAttr_t GM6020_attributes = {
  .name = "GM6020",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for uart_Q */
osMessageQueueId_t uart_QHandle;
const osMessageQueueAttr_t uart_Q_attributes = {
  .name = "uart_Q"
};
/* Definitions for canrx_Q */
osMessageQueueId_t canrx_QHandle;
const osMessageQueueAttr_t canrx_Q_attributes = {
  .name = "canrx_Q"
};
/* Definitions for U6RX_DMA */
osSemaphoreId_t U6RX_DMAHandle;
const osSemaphoreAttr_t U6RX_DMA_attributes = {
  .name = "U6RX_DMA"
};
/* Definitions for canfifo0 */
osSemaphoreId_t canfifo0Handle;
const osSemaphoreAttr_t canfifo0_attributes = {
  .name = "canfifo0"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartLed(void *argument);
void StartUart(void *argument);
void StartCan(void *argument);
void StartGM6020(void *argument);

extern void MX_USB_DEVICE_Init(void);
void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* creation of U6RX_DMA */
  U6RX_DMAHandle = osSemaphoreNew(1, 0, &U6RX_DMA_attributes);

  /* creation of canfifo0 */
  canfifo0Handle = osSemaphoreNew(3, 0, &canfifo0_attributes);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* creation of uart_Q */
  uart_QHandle = osMessageQueueNew (10, sizeof(UART_Packet_t*), &uart_Q_attributes);

  /* creation of canrx_Q */
  canrx_QHandle = osMessageQueueNew (16, sizeof(CAN_Packet_t*), &canrx_Q_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of led */
  ledHandle = osThreadNew(StartLed, NULL, &led_attributes);

  /* creation of uart */
  uartHandle = osThreadNew(StartUart, NULL, &uart_attributes);

  /* creation of can */
  canHandle = osThreadNew(StartCan, NULL, &can_attributes);

  /* creation of GM6020 */
  GM6020Handle = osThreadNew(StartGM6020, NULL, &GM6020_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartLed */
/**
  * @brief  Function implementing the led thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartLed */
__weak void StartLed(void *argument)
{
  /* init code for USB_DEVICE */
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN StartLed */
  /* Infinite loop */
  for(;;)
  {






    osDelay(1000);
  }
  /* USER CODE END StartLed */
}

/* USER CODE BEGIN Header_StartUart */
/**
* @brief Function implementing the uart thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartUart */
__weak void StartUart(void *argument)
{
  /* USER CODE BEGIN StartUart */


	UART_Packet_t *pkt;

  /* Infinite loop */
  for(;;)
  {

  	osMessageQueueGet(uart_QHandle, &pkt, NULL, osWaitForever);

  	pkt->data[pkt->len] = '\0';

    u6_printf("RX:%s\r\n", pkt->data);


  	free(pkt);









  }

  /* USER CODE END StartUart */
}

/* USER CODE BEGIN Header_StartCan */
/**
* @brief Function implementing the can thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartCan */
__weak void StartCan(void *argument)
{
  /* USER CODE BEGIN StartCan */





	CAN_Packet_t *pkt;


  /* Infinite loop */
  for(;;)
  {

	u6_printf("can pkt wait \n");

  	osMessageQueueGet(uart_QHandle, &pkt, NULL, osWaitForever);

  	switch(pkt->ID) {









	default:
  			break;

  	}
  	pkt->data[8]=0;
  	u6_printf("CAN  RX:%s\r\n", pkt->data);

  	free(pkt);














    osDelay(1000);
  }
  /* USER CODE END StartCan */
}

/* USER CODE BEGIN Header_StartGM6020 */
/**
* @brief Function implementing the GM6020 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartGM6020 */
void StartGM6020(void *argument)
{
  /* USER CODE BEGIN StartGM6020 */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartGM6020 */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

