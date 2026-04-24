#include "main.h"
#include <stdio.h>
#include "string.h"
#include "stdint.h"
#include "stdarg.h"
#include "stdio.h"
#include <string.h>



UCB  ucb1;
UCB  ucb2;
UCB  ucb3;

uint8_t U1_RxBuff[U1_RX_SIZE]="";
uint8_t U1_TxBuff[U1_TX_SIZE];

uint8_t U2_RxBuff[U2_RX_SIZE];
uint8_t U2_TxBuff[U2_TX_SIZE];

uint8_t U3_RxBuff[U3_RX_SIZE];
uint8_t U3_TxBuff[U3_TX_SIZE];





//uart123的启用

void U1_PtrInit(void){
	ucb1.RxInPtr = &ucb1.RxLocation[0];
	ucb1.RxOutPtr = &ucb1.RxLocation[0];
	ucb1.RxEndPtr = &ucb1.RxLocation[9];
	ucb1.RxCounter = 0;
	ucb1.RxInPtr->start = U1_RxBuff;
	
	ucb1.TxInPtr = &ucb1.TxLocation[0];
	ucb1.TxOutPtr = &ucb1.TxLocation[0];
	ucb1.TxEndPtr = &ucb1.TxLocation[9];
	ucb1.TxCounter = 0;
	ucb1.TxInPtr->start = U1_TxBuff;	

}

void U2_PtrInit(void){
	ucb2.RxInPtr = &ucb2.RxLocation[0];
	ucb2.RxOutPtr = &ucb2.RxLocation[0];
	ucb2.RxEndPtr = &ucb2.RxLocation[9];
	ucb2.RxCounter = 0;
	ucb2.RxInPtr->start = U2_RxBuff;
	
	ucb2.TxInPtr = &ucb2.TxLocation[0];
	ucb2.TxOutPtr = &ucb2.TxLocation[0];
	ucb2.TxEndPtr = &ucb2.TxLocation[9];
	ucb2.TxCounter = 0;
	ucb2.TxInPtr->start = U2_TxBuff;	
	

}




void U3_PtrInit(void){
	ucb3.RxInPtr = &ucb3.RxLocation[0];
	ucb3.RxOutPtr = &ucb3.RxLocation[0];
	ucb3.RxEndPtr = &ucb3.RxLocation[9];
	ucb3.RxCounter = 0;
	ucb3.RxInPtr->start = U3_RxBuff;
	
	ucb3.TxInPtr = &ucb3.TxLocation[0];
	ucb3.TxOutPtr = &ucb3.TxLocation[0];
	ucb3.TxEndPtr = &ucb3.TxLocation[9];
	ucb3.TxCounter = 0;
	ucb3.TxInPtr->start = U3_TxBuff;	
	


}





void u1_printf(char *fmt,...){
	uint8_t tempbuff[256];
	va_list ap;
	va_start(ap,fmt);
	uint16_t len=vsprintf((char *)tempbuff,fmt,ap);
	va_end(ap);
	
	
	
	HAL_UART_Transmit(&huart1,tempbuff,len,100);
	
	
}

void u2_printf(char *fmt,...){
	uint8_t tempbuff[256];
	va_list ap;
	va_start(ap,fmt);
	uint16_t len=vsprintf((char *)tempbuff,fmt,ap);
	va_end(ap);
	
	
	
	HAL_UART_Transmit(&huart2,tempbuff,len,100);
	
	
}





/*

void u3_printf(char *fmt,...){
	uint8_t tempbuff[256];
	va_list ap;
	va_start(ap,fmt);
	uint16_t len=vsprintf((char *)tempbuff,fmt,ap);
	va_end(ap);
	
	
	
	HAL_UART_Transmit(&huart3,tempbuff,len,100);
	
	
}

*/




/*

void u2_printf(char *fmt,...){
	uint8_t tempbuff[256];
	uint16_t i;
	va_list ap;
	va_start(ap,fmt);
	vsprintf((char *)tempbuff,fmt,ap);
	va_end(ap);
	
	for(i=0;i<strlen((char *)tempbuff);i++){
		while(!__HAL_UART_GET_FLAG(&ucb2.uart, UART_FLAG_TXE));
		ucb2.uart.Instance->DR = tempbuff[i];
	}
	while(!__HAL_UART_GET_FLAG(&ucb2.uart, UART_FLAG_TC));
}





void u3_printf(char *fmt,...){
	uint8_t tempbuff[256];
	uint16_t i;
	va_list ap;
	va_start(ap,fmt);
	vsprintf((char *)tempbuff,fmt,ap);
	va_end(ap);
	
	for(i=0;i<strlen((char *)tempbuff);i++){
		while(!__HAL_UART_GET_FLAG(&ucb3.uart, UART_FLAG_TXE));
		ucb3.uart.Instance->DR = tempbuff[i];
	}
	while(!__HAL_UART_GET_FLAG(&ucb3.uart, UART_FLAG_TC));
}



*///uart123的启用



/***************************************
*
*	uart中断服务函数
*
***************************************/

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
		ucb1.TxState=0;
	}else if(huart->Instance == USART2){
		ucb2.TxState=0;
	}else if(huart->Instance == USART3){
		ucb3.TxState=0;
	}
}


/*
void USART1_IRQHandler(void)
{

	if(__HAL_UART_GET_FLAG(&huart1, UART_FLAG_IDLE) != RESET)
	{
		__HAL_UART_CLEAR_IDLEFLAG(&huart1);


		HAL_UART_DMAStop(&huart1);


		// rx_len = RX_SIZE - __HAL_DMA_GET_COUNTER(huart1.hdmarx);
		//time=10;


		HAL_UART_Receive_DMA(&huart1,U1_RxBuff,256);
	}

	HAL_UART_IRQHandler(&huart1);
}

*/





/*
void HAL_UART_AbortReceiveCpltCallback(UART_HandleTypeDef *huart)
{




	time=9999;


	if(huart->Instance == USART1){
		ucb1.RxInPtr->end = &U1_RxBuff[ucb1.RxCounter - 1];
		ucb1.RxInPtr++;
		if(ucb1.RxInPtr == ucb1.RxEndPtr){
			ucb1.RxInPtr = &ucb1.RxLocation[0];
		}
		if((U1_RX_SIZE - ucb1.RxCounter)<U1_RX_MAX){
			ucb1.RxCounter = 0;
			ucb1.RxInPtr->start = U1_RxBuff;
		}else{
			ucb1.RxInPtr->start = &U1_RxBuff[ucb1.RxCounter];
		}
		HAL_UART_Receive_DMA(&ucb1.uart,ucb1.RxInPtr->start,U1_RX_MAX);
	}else if(huart->Instance == USART2){
		ucb2.RxInPtr->end = &U2_RxBuff[ucb2.RxCounter - 1];
		ucb2.RxInPtr++;
		if(ucb2.RxInPtr == ucb2.RxEndPtr){
			ucb2.RxInPtr = &ucb2.RxLocation[0];
		}
		if((U2_RX_SIZE - ucb2.RxCounter)<U2_RX_MAX){
			ucb2.RxCounter = 0;
			ucb2.RxInPtr->start = U2_RxBuff;
		}else{
			ucb2.RxInPtr->start = &U2_RxBuff[ucb2.RxCounter];
		}
		HAL_UART_Receive_DMA(&ucb2.uart,ucb2.RxInPtr->start,U2_RX_MAX);
	}else if(huart->Instance == USART3){
		ucb3.RxInPtr->end = &U3_RxBuff[ucb3.RxCounter - 1];
		ucb3.RxInPtr++;
		if(ucb3.RxInPtr == ucb3.RxEndPtr){
			ucb3.RxInPtr = &ucb3.RxLocation[0];
		}
		if((U3_RX_SIZE - ucb3.RxCounter)<U3_RX_MAX){
			ucb3.RxCounter = 0;
			ucb3.RxInPtr->start = U3_RxBuff;
		}else{
			ucb3.RxInPtr->start = &U3_RxBuff[ucb3.RxCounter];
		}
		HAL_UART_Receive_DMA(&ucb3.uart,ucb3.RxInPtr->start,U3_RX_MAX);
	}
}
*/