
/*
#ifndef __UART_PRINTF_H
#define __UART_PRINTF_H

#include "string.h"
#include "stdint.h"
#include "stdarg.h"
#include "stdio.h"
#include "stm32f1xx_hal_uart.h"
#include "stm32f1xx_hal_dma.h"

#define U1_TX_SIZE 2048
#define U1_RX_SIZE 2048
#define U1_RX_MAX  256

#define U2_TX_SIZE 2048
#define U2_RX_SIZE 2048
#define U2_RX_MAX  256


#define U3_TX_SIZE 2048
#define U3_RX_SIZE 2048
#define U3_RX_MAX  256


typedef struct{
	uint8_t  *start;
	uint8_t  *end;
}LCB;

typedef struct{
	uint32_t  RxCounter;
	uint32_t  TxCounter;
	uint32_t  TxState;
	LCB       RxLocation[10];
	LCB       TxLocation[10];
	LCB      *RxInPtr;
	LCB      *RxOutPtr;
	LCB      *RxEndPtr;
	LCB      *TxInPtr;
	LCB      *TxOutPtr;
	LCB      *TxEndPtr;
	UART_HandleTypeDef uart;
	DMA_HandleTypeDef dmatx;
	DMA_HandleTypeDef dmarx;
	
}UCB;


void U1_Init(uint32_t bandrate);
void U2_Init(uint32_t bandrate);
void U3_Init(uint32_t bandrate);




void U1_PtrInit(void);
void U2_PtrInit(void);
void U3_PtrInit(void);


void U1_Txdata(uint8_t *data, uint32_t data_len);
void U2_Txdata(uint8_t *data, uint32_t data_len);
void U3_Txdata(uint8_t *data, uint32_t data_len);


void u1_printf(char *fmt,...);
void u2_printf(char *fmt,...);
void u3_printf(char *fmt,...);


extern UCB  uart1;
extern UCB  uart2;
extern UCB  uart3;


#endif
*/