#ifndef MAIN2_H_
#define MAIN2_H_



#if 0		//c8t6 学习期间使用

#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_spi.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_uart.h"
#include "stm32f1xx_hal_dma.h"
#include "stm32f1xx_hal_uart.h"
#include "stm32f1xx_hal.h"
#include "spi.h"
#endif


#include "main.h"
#include "usart.h"
#include "gpio.h"
#include  "can.h"
#include "cmsis_os.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>



/*=====================================*/

/*My_code start*/
#include "can_user.h"
#include "font.h"
#include "PID.h"
#include "ST7735.h"
#include "uart_printf.h"	
#include "test.h"

/*My_code end*/



//extern

extern 	uint16_t ang ;
extern int16_t speed;
extern int16_t current;
extern uint8_t update;

extern PID_t pid_6020_speed;
extern PID_t pid_6020_location;

extern int16_t current6020[4];
extern int16_t voltage6020[4];

;








#endif








