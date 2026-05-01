#ifndef UART_PRINTF_H
#define UART_PRINTF_H




#define U1_TX_SIZE 2048
#define U1_RX_SIZE 2048
#define U1_RX_MAX  256

#define U2_TX_SIZE 2048
#define U2_RX_SIZE 2048
#define U2_RX_MAX  256


#define U3_TX_SIZE 2048
#define U3_RX_SIZE 2048
#define U3_RX_MAX  256
#include "main3.h"
#include "stm32f4xx_hal_uart.h"


extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;



// ==================== RX / TX buffer ====================

/*
extern uint8_t U2_RxBuff[];
extern uint8_t U2_TxBuff[];

extern uint8_t U3_RxBuff[];
extern uint8_t U3_TxBuff[];

*/









extern UCB  ucb1;
extern UCB  ucb2;
extern UCB  ucb3;

extern uint8_t U1_RxBuff[U1_RX_SIZE];
extern uint8_t U1_TxBuff[U1_TX_SIZE];



// ==================== printf封装 ====================
void u1_printf(char *fmt, ...);
void u2_printf(char *fmt, ...);
void u3_printf(char *fmt, ...);

void u6_printf(char *fmt, ...);





// ==================== 初始化函数 ====================
void U1_PtrInit(void);
void U2_PtrInit(void);
void U3_PtrInit(void);

void U6_PtrInit(void);



// ==================== HAL回调函数 ====================



#endif
