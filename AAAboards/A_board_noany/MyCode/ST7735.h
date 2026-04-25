
#ifndef __ST7735_H
#define __ST7735_H

	#include "main.h"
	
	#define USE_HORIZONTAL 1  //设置横屏或者竖屏显示 1默认,

	/*屏幕显示方向设置
	========================================================================
	// 0 - 默认竖屏
	//     ↑
	//     │
	//     │
	//     └───
	// 1 - 横屏（顺时针旋转90°）
	//     ←───
	//         │
	//         │
	//         ↓
	// 2 - 竖屏（顺时针旋转180°）
	//     ───→
	//     │
	//     │
	//     ↑
	// 3 - 横屏（顺时针旋转270°）
	//     ↓
	//     │
	//     │
	//     ───→
	//
	=================================================================================
	// 每增加1，图像相对于屏幕顺时针旋转90°
	*/

	#if USE_HORIZONTAL==0||USE_HORIZONTAL==1
		#define LCD_W 128
		#define LCD_H 160


	#endif//USE_HORIZONTAL

	//-----------------LCD端口定义---------------- 

	#define LCD_RES_Clr()  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,(GPIO_PinState)0)					//RES
	#define LCD_RES_Set()  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,(GPIO_PinState)1)

	#define LCD_DC_Clr()   HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,(GPIO_PinState)0)					//DC
	#define LCD_DC_Set()   HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,(GPIO_PinState)1)
				 
	#define LCD_CS_Clr()   HAL_GPIO_WritePin(GPIOB,GPIO_PIN_10,(GPIO_PinState)0)				//CS
	#define LCD_CS_Set()   HAL_GPIO_WritePin(GPIOB,GPIO_PIN_10,(GPIO_PinState)1)

	#define LCD_BLK_Clr()  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_11,(GPIO_PinState)0)				//BLK
	#define LCD_BLK_Set()  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_11,(GPIO_PinState)1) 




	//传输方式定义转到ST7735.c




	//画笔颜色
	#define WHITE         	 	0xFFFF
	#define BLACK         		0x0000	  
	#define BLUE         	  	0x001F  
	#define BRED        	 	0XF81F
	#define GRED 			    0XFFE0
	#define GBLUE			    0X07FF
	#define RED           	 	0xF800
	#define MAGENTA       	 	0xF81F
	#define GREEN       	  	0x07E0
	#define CYAN         	 	0x7FFF
	#define YELLOW      	  	0xFFE0
	#define BROWN 			    0XBC40 //棕色
	#define BRRED 			    0XFC07 //棕红色
	#define GRAY  			    0X8430 //灰色
	#define DARKBLUE      	 	0X01CF	//深蓝色
	#define LIGHTBLUE      	 	0X7D7C	//浅蓝色  
	#define GRAYBLUE       	 	0X5458 //灰蓝色
	#define LIGHTGREEN     	 	0X841F //浅绿色
	#define LGRAY 			    0XC618 //浅灰色(PANNEL),窗体背景色
	#define LGRAYBLUE        	0XA651 //浅灰蓝色(中间层颜色)
	#define LBBLUE           	0X2B12 //浅棕蓝色(选择条目的反色)






#endif //ST7735_H
/* 基础通信函数 */
void LCD_Tx(uint8_t Data);
void LCD_Txn(uint8_t *pData,uint16_t n);
void LCD_Write(uint8_t Data);
void LCD_Write16(uint16_t Data);
void LCD_Write_CMD(uint8_t Data);

/* 地址与初始化 */
void LCD_Address_Set(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);
void LCD_Init(void);

/* SPI数据宽度控制 */
void SPI_SetDataWidth(uint8_t width);

/* 基础绘图 */
void LCD_Fill(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t color);
void LCD_DrawPoint(uint16_t x,uint16_t y,uint16_t color);
void LCD_DrawLine(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t color);
void LCD_DrawRectangle(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t color);
void Draw_Circle(uint16_t x0,uint16_t y0,uint8_t r,uint16_t color);

/* 图片显示 */
void LCD_ShowPicture(uint16_t x,uint16_t y,uint16_t length,uint16_t width,const uint8_t IMG[]);


void LCD_ShowChar(uint16_t x,
                  uint16_t y,
                  uint8_t chr,
                  uint16_t font_color,
                  uint16_t back_color,
                  uint8_t sizey,
                  uint8_t mode);





void LCD_ShowString(uint16_t x,uint16_t y,const uint8_t *p,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode);

/* 数字显示 */
uint32_t Pow(uint8_t m,uint8_t n);
void LCD_ShowIntNum(uint16_t x,uint16_t y,uint16_t num,uint8_t len,uint16_t fc,uint16_t bc,uint8_t sizey);
void LCD_ShowFloatNum1(uint16_t x,uint16_t y,float num,uint8_t len,uint16_t fc,uint16_t bc,uint8_t sizey);




