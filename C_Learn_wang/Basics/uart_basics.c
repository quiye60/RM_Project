#include "uart_basics.h"
#include <stdarg.h>
#include <string.h>
#include <stdio.h>    // 关键！vsnprintf 函数在这里声明
#include <stdlib.h>   // 关键！atoi() 函数的头文件
#include "bsp_can.h"
/* 全局句柄（由CubeMX生成） */
extern UART_HandleTypeDef huart1;
extern DMA_HandleTypeDef hdma_usart1_tx;
extern int final_num ; 
/* 静态缓冲区 */
volatile uint8_t uart_tx_done_flag = 1;
uint8_t uart_tx_buf[UART_PRINTF_BUFFER_SIZE];
uint8_t uart1_rx_buf[128];
uint8_t rx_temp;

#define BUF_SIZE 10
char parse_buf[BUF_SIZE];  // 存储字符： '-', '2', '0'
int parse_index = 0;       // 数组下标
uint8_t rx_byte;          // 临时接收
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART1)
    {
        uart_tx_done_flag = 1;
    }
}

void USART1_IRQHandler(void)
{
    if (__HAL_UART_GET_FLAG(&huart1, UART_FLAG_RXNE) != RESET)
    {
        rx_byte = huart1.Instance->DR;

        // ======================================
        // 你的核心逻辑：遇到 \ 就开始解析
        // ======================================
       if(rx_byte == '\\')  
//		if(rx_byte == '\n' || rx_byte == '\r')
        {
            parse_buf[parse_index] = '\0';
            final_num = atoi(parse_buf);  // 自动转成：-20 / 10 / -5 / 0
            parse_index = 0;
        }
        // 否则把字符存进数组
        else
        {
            if(parse_index < BUF_SIZE-1)
                parse_buf[parse_index++] = rx_byte;
        }

        // 继续接收下一个字节
        HAL_UART_Receive_IT(&huart1, &rx_byte, 1);
    }
    HAL_UART_IRQHandler(&huart1);
}

void uart_dma_send(uint8_t *buf, uint16_t len)
{
    if (len == 0 || !uart_tx_done_flag) 
    {
        // 如果正在发送，直接丢弃这次数据，避免阻塞
        return;
    }

    uart_tx_done_flag = 0; // 标记为正在发送
    HAL_UART_Transmit_DMA(&huart1, buf, len);
}

void uart_printf(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    uint16_t len = vsnprintf((char*)uart_tx_buf, sizeof(uart_tx_buf), fmt, ap);
    if (len > sizeof(uart_tx_buf) - 1)
    {
        len = sizeof(uart_tx_buf) - 1;
    }
    uart_dma_send(uart_tx_buf, len);
    va_end(ap);
}
