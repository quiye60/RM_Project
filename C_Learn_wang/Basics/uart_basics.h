#ifndef __UART_BASICS_H
#define __UART_BASICS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx.h"  // 根据你的芯片系列修改，如 stm32f4xx.h

/************************* 配置区 *************************/
#define UART_PRINTF_BUFFER_SIZE  256
/**********************************************************/

extern uint8_t uart1_rx_buf[128];
/**
 * @brief  串口DMA格式化打印
 * @param  fmt: 格式化字符串
 * @param  ...: 可变参数
 */
void uart_printf(const char *fmt, ...);

#ifdef __cplusplus
}
#endif

#endif /* __UART_BASICS_H */
