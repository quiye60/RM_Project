/*


#include "stm32f1xx_hal.h"
#include "uart_printf.h"

UCB  uart1;
UCB  uart2;
UCB  uart3;

uint8_t U1_RxBuff[U1_RX_SIZE];
uint8_t U1_TxBuff[U1_TX_SIZE];

uint8_t U2_RxBuff[U2_RX_SIZE];
uint8_t U2_TxBuff[U2_TX_SIZE];

uint8_t U3_RxBuff[U3_RX_SIZE];
uint8_t U3_TxBuff[U3_TX_SIZE];



void U1_PtrInit(void){
	uart1.RxInPtr = &uart1.RxLocation[0];
	uart1.RxOutPtr = &uart1.RxLocation[0];
	uart1.RxEndPtr = &uart1.RxLocation[9];
	uart1.RxCounter = 0;
	uart1.RxInPtr->start = U1_RxBuff;
	
	uart1.TxInPtr = &uart1.TxLocation[0];
	uart1.TxOutPtr = &uart1.TxLocation[0];
	uart1.TxEndPtr = &uart1.TxLocation[9];
	uart1.TxCounter = 0;
	uart1.TxInPtr->start = U1_TxBuff;	
	
	__HAL_UART_ENABLE_IT(&uart1.uart, UART_IT_IDLE);
	HAL_UART_Receive_DMA(&uart1.uart,uart1.RxInPtr->start,U1_RX_MAX);
}
void U1_Txdata(uint8_t *data, uint32_t data_len){
	if((U1_TX_SIZE - uart1.TxCounter )>=data_len){
		uart1.TxInPtr->start = &U1_TxBuff[uart1.TxCounter];
	}else{
		uart1.TxCounter = 0;
		uart1.TxInPtr->start = U1_TxBuff;
	}
	memcpy(uart1.TxInPtr->start,data,data_len);
	uart1.TxCounter += data_len;
	uart1.TxInPtr->end = &U1_TxBuff[uart1.TxCounter - 1];
	uart1.TxInPtr++;
	if(uart1.TxInPtr == uart1.TxEndPtr){
		uart1.TxInPtr = &uart1.TxLocation[0];
	}
}
void u1_printf(char *fmt,...){
	uint8_t tempbuff[256];
	uint16_t i;
	va_list ap;
	va_start(ap,fmt);
	vsprintf((char *)tempbuff,fmt,ap);
	va_end(ap);
	
	for(i=0;i<strlen((char *)tempbuff);i++){
		while(!__HAL_UART_GET_FLAG(&uart1.uart, UART_FLAG_TXE));
		uart1.uart.Instance->DR = tempbuff[i];
	}
	while(!__HAL_UART_GET_FLAG(&uart1.uart, UART_FLAG_TC));
}



void U2_PtrInit(void){
	uart2.RxInPtr = &uart2.RxLocation[0];
	uart2.RxOutPtr = &uart2.RxLocation[0];
	uart2.RxEndPtr = &uart2.RxLocation[9];
	uart2.RxCounter = 0;
	uart2.RxInPtr->start = U2_RxBuff;
	
	uart2.TxInPtr = &uart2.TxLocation[0];
	uart2.TxOutPtr = &uart2.TxLocation[0];
	uart2.TxEndPtr = &uart2.TxLocation[9];
	uart2.TxCounter = 0;
	uart2.TxInPtr->start = U2_TxBuff;	
	
	__HAL_UART_ENABLE_IT(&uart2.uart, UART_IT_IDLE);
	HAL_UART_Receive_DMA(&uart2.uart,uart2.RxInPtr->start,U2_RX_MAX);
}



void U2_Txdata(uint8_t *data, uint32_t data_len){
	if((U2_TX_SIZE - uart2.TxCounter )>=data_len){
		uart2.TxInPtr->start = &U2_TxBuff[uart2.TxCounter];
	}else{
		uart2.TxCounter = 0;
		uart2.TxInPtr->start = U2_TxBuff;
	}
	memcpy(uart2.TxInPtr->start,data,data_len);
	uart2.TxCounter += data_len;
	uart2.TxInPtr->end = &U2_TxBuff[uart2.TxCounter - 1];
	uart2.TxInPtr++;
	if(uart2.TxInPtr == uart2.TxEndPtr){
		uart2.TxInPtr = &uart2.TxLocation[0];
	}
}
void u2_printf(char *fmt,...){
	uint8_t tempbuff[256];
	uint16_t i;
	va_list ap;
	va_start(ap,fmt);
	vsprintf((char *)tempbuff,fmt,ap);
	va_end(ap);
	
	for(i=0;i<strlen((char *)tempbuff);i++){
		while(!__HAL_UART_GET_FLAG(&uart2.uart, UART_FLAG_TXE));
		uart2.uart.Instance->DR = tempbuff[i];
	}
	while(!__HAL_UART_GET_FLAG(&uart2.uart, UART_FLAG_TC));
}










void U3_PtrInit(void){
	uart3.RxInPtr = &uart3.RxLocation[0];
	uart3.RxOutPtr = &uart3.RxLocation[0];
	uart3.RxEndPtr = &uart3.RxLocation[9];
	uart3.RxCounter = 0;
	uart3.RxInPtr->start = U3_RxBuff;
	
	uart3.TxInPtr = &uart3.TxLocation[0];
	uart3.TxOutPtr = &uart3.TxLocation[0];
	uart3.TxEndPtr = &uart3.TxLocation[9];
	uart3.TxCounter = 0;
	uart3.TxInPtr->start = U3_TxBuff;	
	
	__HAL_UART_ENABLE_IT(&uart3.uart, UART_IT_IDLE);
	HAL_UART_Receive_DMA(&uart3.uart,uart3.RxInPtr->start,U3_RX_MAX);
}
void U3_Txdata(uint8_t *data, uint32_t data_len){
	if((U3_TX_SIZE - uart3.TxCounter )>=data_len){
		uart3.TxInPtr->start = &U3_TxBuff[uart3.TxCounter];
	}else{
		uart3.TxCounter = 0;
		uart3.TxInPtr->start = U3_TxBuff;
	}
	memcpy(uart3.TxInPtr->start,data,data_len);
	uart3.TxCounter += data_len;
	uart3.TxInPtr->end = &U3_TxBuff[uart3.TxCounter - 1];
	uart3.TxInPtr++;
	if(uart3.TxInPtr == uart3.TxEndPtr){
		uart3.TxInPtr = &uart3.TxLocation[0];
	}
}
void u3_printf(char *fmt,...){
	uint8_t tempbuff[256];
	uint16_t i;
	va_list ap;
	va_start(ap,fmt);
	vsprintf((char *)tempbuff,fmt,ap);
	va_end(ap);
	
	for(i=0;i<strlen((char *)tempbuff);i++){
		while(!__HAL_UART_GET_FLAG(&uart3.uart, UART_FLAG_TXE));
		uart3.uart.Instance->DR = tempbuff[i];
	}
	while(!__HAL_UART_GET_FLAG(&uart3.uart, UART_FLAG_TC));
}





void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == USART1){

	}
}
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == USART1){

	}
}
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{	
	if(huart->Instance == USART1){
		uart1.TxState = 0;
	}else if(huart->Instance == USART2){
		uart2.TxState = 0;
	}else if(huart->Instance == USART3){
		uart3.TxState = 0;
	}
}


void HAL_UART_AbortReceiveCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == USART1){
		uart1.RxInPtr->end = &U1_RxBuff[uart1.RxCounter - 1];
		uart1.RxInPtr++;
		if(uart1.RxInPtr == uart1.RxEndPtr){
			uart1.RxInPtr = &uart1.RxLocation[0];
		}
		if((U1_RX_SIZE - uart1.RxCounter)<U1_RX_MAX){
			uart1.RxCounter = 0;
			uart1.RxInPtr->start = U1_RxBuff;
		}else{
			uart1.RxInPtr->start = &U1_RxBuff[uart1.RxCounter];
		}
		HAL_UART_Receive_DMA(&uart1.uart,uart1.RxInPtr->start,U1_RX_MAX);
	}else if(huart->Instance == USART2){
		uart2.RxInPtr->end = &U2_RxBuff[uart2.RxCounter - 1];
		uart2.RxInPtr++;
		if(uart2.RxInPtr == uart2.RxEndPtr){
			uart2.RxInPtr = &uart2.RxLocation[0];
		}
		if((U2_RX_SIZE - uart2.RxCounter)<U2_RX_MAX){
			uart2.RxCounter = 0;
			uart2.RxInPtr->start = U2_RxBuff;
		}else{
			uart2.RxInPtr->start = &U2_RxBuff[uart2.RxCounter];
		}
		HAL_UART_Receive_DMA(&uart2.uart,uart2.RxInPtr->start,U2_RX_MAX);
	}else if(huart->Instance == USART3){
		uart3.RxInPtr->end = &U3_RxBuff[uart3.RxCounter - 1];
		uart3.RxInPtr++;
		if(uart3.RxInPtr == uart3.RxEndPtr){
			uart3.RxInPtr = &uart3.RxLocation[0];
		}
		if((U3_RX_SIZE - uart3.RxCounter)<U3_RX_MAX){
			uart3.RxCounter = 0;
			uart3.RxInPtr->start = U3_RxBuff;
		}else{
			uart3.RxInPtr->start = &U3_RxBuff[uart3.RxCounter];
		}
		HAL_UART_Receive_DMA(&uart3.uart,uart3.RxInPtr->start,U3_RX_MAX);
	}
}






















		
		//串口1收发
		if(uart1.RxOutPtr != uart1.RxInPtr){
			
			if(((uart1.RxOutPtr->end - uart1.RxOutPtr->start + 1)==6)&&(memcmp(uart1.RxOutPtr->start,"LED_ON",6) == 0)){
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_RESET);
			}else if(((uart1.RxOutPtr->end - uart1.RxOutPtr->start + 1)==7)&&(memcmp(uart1.RxOutPtr->start,"LED_OFF",7) == 0)){
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET);
			}
			
			uart1.RxOutPtr++;
			if(uart1.RxOutPtr == uart1.RxEndPtr){
				uart1.RxOutPtr = &uart1.RxLocation[0];
			}
		}
		if((uart1.TxOutPtr != uart1.TxInPtr)&&(uart1.TxState==0)){
			uart1.TxState = 1;
			HAL_UART_Transmit_DMA(&uart1.uart,uart1.TxOutPtr->start,uart1.TxOutPtr->end - uart1.TxOutPtr->start + 1);
			uart1.TxOutPtr++;
			if(uart1.TxOutPtr == uart1.TxEndPtr){
				uart1.TxOutPtr = &uart1.TxLocation[0];
			}
		}
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		//串口2收发
		if(uart2.RxOutPtr != uart2.RxInPtr){
					
			if(((uart2.RxOutPtr->end - uart2.RxOutPtr->start + 1)==6)&&(memcmp(uart2.RxOutPtr->start,"LED_ON",6) == 0)){
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_RESET);
			}else if(((uart2.RxOutPtr->end - uart2.RxOutPtr->start + 1)==7)&&(memcmp(uart2.RxOutPtr->start,"LED_OFF",7) == 0)){
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET);
			}
			
			uart2.RxOutPtr++;
			if(uart2.RxOutPtr == uart2.RxEndPtr){
				uart2.RxOutPtr = &uart2.RxLocation[0];
			}
		}
		if((uart2.TxOutPtr != uart2.TxInPtr)&&(uart2.TxState==0)){
			uart2.TxState = 1;
			HAL_HalfDuplex_EnableTransmitter(&uart2.uart);
			HAL_UART_Transmit_DMA(&uart2.uart,uart2.TxOutPtr->start,uart2.TxOutPtr->end - uart2.TxOutPtr->start + 1);
			uart2.TxOutPtr++;
			if(uart2.TxOutPtr == uart2.TxEndPtr){
				uart2.TxOutPtr = &uart2.TxLocation[0];
			}
		}
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		

		
		
		
		
		
		//串口3收发
		if(uart3.RxOutPtr != uart3.RxInPtr){
			
			if(((uart3.RxOutPtr->end - uart3.RxOutPtr->start + 1)==6)&&(memcmp(uart3.RxOutPtr->start,"LED_ON",6) == 0)){
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_RESET);
			}else if(((uart3.RxOutPtr->end - uart3.RxOutPtr->start + 1)==7)&&(memcmp(uart3.RxOutPtr->start,"LED_OFF",7) == 0)){
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET);
			}
			
			uart3.RxOutPtr++;
			if(uart3.RxOutPtr == uart3.RxEndPtr){
				uart3.RxOutPtr = &uart3.RxLocation[0];
			}
		}
		if((uart3.TxOutPtr != uart3.TxInPtr)&&(uart3.TxState==0)){
			uart3.TxState = 1;
			HAL_HalfDuplex_EnableTransmitter(&uart3.uart);
			HAL_UART_Transmit_DMA(&uart3.uart,uart3.TxOutPtr->start,uart3.TxOutPtr->end - uart3.TxOutPtr->start + 1);
			uart3.TxOutPtr++;
			if(uart3.TxOutPtr == uart3.TxEndPtr){
				uart3.TxOutPtr = &uart3.TxLocation[0];
			}
		}
	}
	
	
	
	
	
	
	
	
	
	
	





























*/



















