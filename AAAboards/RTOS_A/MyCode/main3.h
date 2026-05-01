#ifndef A_PROJECT_MAIN3_H
#define A_PROJECT_MAIN3_H
#include <stdint.h>

#include "stm32f4xx_hal_dma.h"


//结构体定义,联合体定义




typedef struct {
	uint8_t data[9];
	uint32_t ID;
}CAN_Packet_t;





typedef struct
{
	uint8_t data[128];
	uint16_t len;
} UART_Packet_t;









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










#endif //A_PROJECT_MAIN3_H