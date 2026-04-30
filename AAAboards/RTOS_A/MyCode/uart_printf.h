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


extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;



// ==================== RX / TX buffer ====================
extern uint8_t U1_RxBuff[];
extern uint8_t U1_TxBuff[];
/*
extern uint8_t U2_RxBuff[];
extern uint8_t U2_TxBuff[];

extern uint8_t U3_RxBuff[];
extern uint8_t U3_TxBuff[];

*/

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


extern UCB  ucb1;
extern UCB  ucb2;
extern UCB  ucb3;





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
