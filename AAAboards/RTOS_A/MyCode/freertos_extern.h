//
// Created by 30301 on 2026/5/1.
//

#ifndef A_PROJECT_FREERTOS_EXTERN_H
#define A_PROJECT_FREERTOS_EXTERN_H
#include "cmsis_os2.h"
#include "PID.h"


extern osThreadId_t ledHandle;
extern const osThreadAttr_t led_attributes;

extern osThreadId_t uartHandle;
extern const osThreadAttr_t uart_attributes;

extern osThreadId_t canHandle;
extern const osThreadAttr_t can_attributes;

extern osThreadId_t GM6020Handle;
extern const osThreadAttr_t GM6020_attributes;

extern osMessageQueueId_t uart_QHandle;
extern const osMessageQueueAttr_t uart_Q_attributes;

extern osMessageQueueId_t canrx_QHandle;
extern const osMessageQueueAttr_t canrx_Q_attributes;

extern osSemaphoreId_t U6RX_DMAHandle;
extern const osSemaphoreAttr_t U6RX_DMA_attributes;

extern osSemaphoreId_t canfifo0Handle;
extern const osSemaphoreAttr_t canfifo0_attributes;


extern uint8_t U1_RxBuff[];
extern uint8_t U1_TxBuff[];

extern 	uint16_t ang ;
extern int16_t speed;
extern int16_t current;
extern uint8_t update;

extern PID_t pid_6020_speed;
extern PID_t pid_6020_location;

extern int16_t current6020[4];
extern int16_t voltage6020[4];






























#endif //A_PROJECT_FREERTOS_EXTERN_H