#include "main.h"
#include "ST7735.h"

#include "font.h"


/*
void LCD_DMA_Tx(void)//RAM不够用
{
	LCD_Address_Set(0,0,128-1,160-1);
	LCD_CS_Clr();
	HAL_SPI_Transmit_DMA(&hspi1,  (uint8_t*)LCD_buffer,40960 );
	
}*/





void LCD_Tx(uint8_t Data)//用于发送指令
{
	
//	HAL_SPI_Transmit(&hspi1,&Data,1,100);
	

}


void LCD_Txn(uint8_t *pData,uint16_t n)
{
	
//	HAL_SPI_Transmit(&hspi1,pData,n,100);
	
	
}



void LCD_Write(uint8_t Data) 
{	
	LCD_CS_Clr();
	LCD_Tx(Data);
	LCD_CS_Set();
}



void LCD_Write16(uint16_t Data)
{

	LCD_CS_Clr();
	LCD_Tx(Data>>8);
	LCD_Tx(Data);
	LCD_CS_Set();	
	
	
}


void LCD_Write_CMD(uint8_t Data)
{
	LCD_DC_Clr();//写命令
	LCD_Write(Data);
	LCD_DC_Set();//写数据
}


void LCD_Address_Set(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)
{
	if(USE_HORIZONTAL==0)
	{
		LCD_Write_CMD(0x2a);//列地址设置
		LCD_Write16(x1+2);
		LCD_Write16(x2+2);
		LCD_Write_CMD(0x2b);//行地址设置
		LCD_Write16(y1+1);
		LCD_Write16(y2+1);
		LCD_Write_CMD(0x2c);//储存器写
	}
	else if(USE_HORIZONTAL==1)
	{
		LCD_Write_CMD(0x2a);//列地址设置
		LCD_Write16(x1+2);
		LCD_Write16(x2+2);
		LCD_Write_CMD(0x2b);//行地址设置
		LCD_Write16(y1+1);
		LCD_Write16(y2+1);
		LCD_Write_CMD(0x2c);//储存器写
	}
	else if(USE_HORIZONTAL==2)
	{
		LCD_Write_CMD(0x2a);//列地址设置
		LCD_Write16(x1+1);
		LCD_Write16(x2+1);
		LCD_Write_CMD(0x2b);//行地址设置
		LCD_Write16(y1+2);
		LCD_Write16(y2+2);
		LCD_Write_CMD(0x2c);//储存器写
	}
	else
	{
		LCD_Write_CMD(0x2a);//列地址设置
		LCD_Write16(x1+1);
		LCD_Write16(x2+1);
		LCD_Write_CMD(0x2b);//行地址设置
		LCD_Write16(y1+2);
		LCD_Write16(y2+2);
		LCD_Write_CMD(0x2c);//储存器写
	}
}

void LCD_Init(void)
{

	LCD_RES_Clr();  //复位
	HAL_Delay(100);
	LCD_RES_Set();
	HAL_Delay(100);
	
	LCD_BLK_Set();//打开背光
	HAL_Delay(100);
	
	//************* Start Initial Sequence **********//
	LCD_Write_CMD(0x11); //Sleep out 
	HAL_Delay(120);
	//------------------------------------ST7735S Frame Rate-----------------------------------------// 
	LCD_Write_CMD(0xB1); 
	LCD_Write(0x05); 
	LCD_Write(0x3C); 
	LCD_Write(0x3C); 
	LCD_Write_CMD(0xB2); 
	LCD_Write(0x05);
	LCD_Write(0x3C); 
	LCD_Write(0x3C); 
	LCD_Write_CMD(0xB3); 
	LCD_Write(0x05); 
	LCD_Write(0x3C); 
	LCD_Write(0x3C); 
	LCD_Write(0x05); 
	LCD_Write(0x3C); 
	LCD_Write(0x3C); 
	//------------------------------------End ST7735S Frame Rate---------------------------------// 
	LCD_Write_CMD(0xB4); //Dot inversion 
	LCD_Write(0x03); 
	//------------------------------------ST7735S Power Sequence---------------------------------// 
	LCD_Write_CMD(0xC0); 
	LCD_Write(0x28); 
	LCD_Write(0x08); 
	LCD_Write(0x04); 
	LCD_Write_CMD(0xC1); 
	LCD_Write(0XC0); 
	LCD_Write_CMD(0xC2); 
	LCD_Write(0x0D); 
	LCD_Write(0x00); 
	LCD_Write_CMD(0xC3); 
	LCD_Write(0x8D); 
	LCD_Write(0x2A); 
	LCD_Write_CMD(0xC4); 
	LCD_Write(0x8D); 
	LCD_Write(0xEE); 
	//---------------------------------End ST7735S Power Sequence-------------------------------------// 
	LCD_Write_CMD(0xC5); //VCOM 
	LCD_Write(0x1A); 
	LCD_Write_CMD(0x36); //MX, MY, RGB mode 
	if(USE_HORIZONTAL==0)LCD_Write(0x00);
	else if(USE_HORIZONTAL==1)LCD_Write(0xC0);
	else if(USE_HORIZONTAL==2)LCD_Write(0x70);
	else LCD_Write(0xA0); 
	//------------------------------------ST7735S Gamma Sequence---------------------------------// 
	LCD_Write_CMD(0xE0); 
	LCD_Write(0x04); 
	LCD_Write(0x22); 
	LCD_Write(0x07); 
	LCD_Write(0x0A); 
	LCD_Write(0x2E); 
	LCD_Write(0x30); 
	LCD_Write(0x25); 
	LCD_Write(0x2A); 
	LCD_Write(0x28); 
	LCD_Write(0x26); 
	LCD_Write(0x2E); 
	LCD_Write(0x3A); 
	LCD_Write(0x00); 
	LCD_Write(0x01); 
	LCD_Write(0x03); 
	LCD_Write(0x13); 
	LCD_Write_CMD(0xE1); 
	LCD_Write(0x04); 
	LCD_Write(0x16); 
	LCD_Write(0x06); 
	LCD_Write(0x0D); 
	LCD_Write(0x2D); 
	LCD_Write(0x26); 
	LCD_Write(0x23); 
	LCD_Write(0x27); 
	LCD_Write(0x27); 
	LCD_Write(0x25); 
	LCD_Write(0x2D); 
	LCD_Write(0x3B); 
	LCD_Write(0x00); 
	LCD_Write(0x01); 
	LCD_Write(0x04); 
	LCD_Write(0x13); 
	//------------------------------------End ST7735S Gamma Sequence-----------------------------// 
	LCD_Write_CMD(0x3A); //65k mode 
	LCD_Write(0x05); 
	LCD_Write_CMD(0x29); //Display on 
}






void SPI_SetDataWidth(uint8_t width)
{/*
    if(width == 16 && hspi1.Init.DataSize != SPI_DATASIZE_16BIT)
    {
        __HAL_SPI_DISABLE(&hspi1);
        hspi1.Init.DataSize = SPI_DATASIZE_16BIT;
        HAL_SPI_Init(&hspi1);
    }
    else if(width == 8 && hspi1.Init.DataSize != SPI_DATASIZE_8BIT)
    {
        __HAL_SPI_DISABLE(&hspi1);
        hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
        HAL_SPI_Init(&hspi1);
    }*/
}







void LCD_Fill(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t color)
{          
	uint16_t num;
	num=(x2-x1)*(y2-y1)*2;
	LCD_Address_Set(x1,y1,x2-1,y2-1);//设置显示范围
	LCD_CS_Clr();
	SPI_SetDataWidth(16);//设置SPI16位传输模式
	
	while(num--){( LCD_Write16(color));}
	
	
	SPI_SetDataWidth(8);//设置SPI8位传输模式

}

void LCD_DrawPoint(uint16_t x,uint16_t y,uint16_t color)
{
	LCD_Address_Set(x,y,x,y);//设置光标位置 
	LCD_Write16(color);
} 



void LCD_DrawLine(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t color)
{
	uint16_t t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance;
	int incx,incy,uRow,uCol;
	delta_x=x2-x1; //计算坐标增量 
	delta_y=y2-y1;
	uRow=x1;//画线起点坐标
	uCol=y1;
	if(delta_x>0)incx=1; //设置单步方向 
	else if (delta_x==0)incx=0;//垂直线 
	else {incx=-1;delta_x=-delta_x;}
	if(delta_y>0)incy=1;
	else if (delta_y==0)incy=0;//水平线 
	else {incy=-1;delta_y=-delta_y;}
	if(delta_x>delta_y)distance=delta_x; //选取基本增量坐标轴 
	else distance=delta_y;
	for(t=0;t<distance+1;t++)
	{
		LCD_DrawPoint(uRow,uCol,color);//画点
		xerr+=delta_x;
		yerr+=delta_y;
		if(xerr>distance)
		{
			xerr-=distance;
			uRow+=incx;
		}
		if(yerr>distance)
		{
			yerr-=distance;
			uCol+=incy;
		}
	}
}

void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,uint16_t color)
{
	LCD_DrawLine(x1,y1,x2,y1,color);
	LCD_DrawLine(x1,y1,x1,y2,color);
	LCD_DrawLine(x1,y2,x2,y2,color);
	LCD_DrawLine(x2,y1,x2,y2,color);
}


void Draw_Circle(uint16_t x0,uint16_t y0,uint8_t r,uint16_t color)
{
	int a,b;
	a=0;b=r;	  
	while(a<=b)
	{
		LCD_DrawPoint(x0-b,y0-a,color);             //3           
		LCD_DrawPoint(x0+b,y0-a,color);             //0           
		LCD_DrawPoint(x0-a,y0+b,color);             //1                
		LCD_DrawPoint(x0-a,y0-b,color);             //2             
		LCD_DrawPoint(x0+b,y0+a,color);             //4               
		LCD_DrawPoint(x0+a,y0-b,color);             //5
		LCD_DrawPoint(x0+a,y0+b,color);             //6 
		LCD_DrawPoint(x0-b,y0+a,color);             //7
		a++;
		if((a*a+b*b)>(r*r))//判断要画的点是否过远
		{
			b--;
		}
	}
}

void LCD_ShowPicture(uint16_t x,uint16_t y,uint16_t length,uint16_t width,const uint8_t IMG[])
{
	uint16_t num;
	num=length*width*2;
	LCD_Address_Set(x,y,x+length-1,y+width-1);
	LCD_CS_Clr();
	SPI_SetDataWidth(16);
	
	
	LCD_Txn((uint8_t*)IMG,num);
	
	SPI_SetDataWidth(8);
	
	LCD_CS_Set();
}

void LCD_ShowChar(uint16_t x,
                  uint16_t y,
                  uint8_t chr,
                  uint16_t font_color,
                  uint16_t back_color,
                  uint8_t sizey,
				  uint8_t mode			)
{
	
	
	
	
	
	
	if(mode)	
	{		
		uint8_t  temp;
		uint8_t  sizex = sizey / 2;
		uint16_t row, col;
		uint16_t bytes_per_row;

		uint8_t  color_buf[2];

		chr = chr - ' ';

		/* 每行占多少字节 */
		bytes_per_row = (sizex + 7) / 8;

		/* SPI 始终 8bit */
		SPI_SetDataWidth(8);

		/* 设置窗口 */
		LCD_Address_Set(x, y, x + sizex - 1, y + sizey - 1);

		LCD_CS_Clr();

		for(row = 0; row < sizey; row++)
		{
			for(col = 0; col < sizex; col++)
			{
				uint16_t byte_index = row * bytes_per_row + col / 8;

				if(sizey == 12)      temp = ascii_1206[chr][byte_index];
				else if(sizey == 16) temp = ascii_1608[chr][byte_index];
				else if(sizey == 24) temp = ascii_2412[chr][byte_index];
				else if(sizey == 32) temp = ascii_3216[chr][byte_index];
				else
				{
					LCD_CS_Set();
					return;
				}

				/* 判断像素 */
				if(temp & (1 << (col % 8)))   // 如果左右反，改成 0x80 >> (col % 8)
				{
					color_buf[0] = font_color >> 8;      // 高字节
					color_buf[1] = font_color & 0xFF;    // 低字节
				}
				else
				{
					color_buf[0] = back_color >> 8;
					color_buf[1] = back_color & 0xFF;
				}

//				HAL_SPI_Transmit(&hspi1, color_buf, 2, 10);
			}
		}

		LCD_CS_Set();

	}else
	{
		
		uint8_t  temp;
		uint8_t  sizex = sizey / 2;
		uint16_t row, col;
		uint16_t bytes_per_row;

		uint16_t x0 = x;

		chr = chr - ' ';
		bytes_per_row = (sizex + 7) / 8;

		for(row = 0; row < sizey; row++)
		{
			for(col = 0; col < sizex; col++)
			{
				uint16_t byte_index = row * bytes_per_row + col / 8;

				if(sizey == 12)      temp = ascii_1206[chr][byte_index];
				else if(sizey == 16) temp = ascii_1608[chr][byte_index];
				else if(sizey == 24) temp = ascii_2412[chr][byte_index];
				else if(sizey == 32) temp = ascii_3216[chr][byte_index];
				else return;

				/* 如果左右反，改成 0x80 >> (col % 8) */
				if(temp & (1 << (col % 8)))  // LSB first
				{
					LCD_DrawPoint(x, y, font_color);
				}

				x++;
			}

			x = x0;
			y++;
		}

	}
	
	
	
	
	
	
	
	
	
	
	
	
}






void LCD_ShowString(uint16_t x,uint16_t y,const uint8_t *p,
					uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode)
{  
	
	while(*p!='\0')
	{  
		
		LCD_ShowChar(x,y,*p,fc,bc,sizey,0);
		x+=sizey/2;
		p++;
	}  
	
}




uint32_t Pow(uint8_t m,uint8_t n)
{
	
	uint32_t result=1;	 
	while(n--)result*=m;
	return result;
}



void LCD_ShowIntNum(uint16_t x,uint16_t y,uint16_t num,uint8_t len,uint16_t fc,uint16_t bc,uint8_t sizey)
{         	
	uint8_t t,temp;
	uint8_t enshow=0;
	uint8_t sizex=sizey/2;
	
	for(t=0;t<len;t++)
	{
		temp=(num/Pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				LCD_ShowChar(x+t*sizex,y,' ',fc,bc,sizey,0);
				continue;
			}else enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x+t*sizex,y,temp+48,fc,bc,sizey,0);
	}
} 



void LCD_ShowFloatNum1(uint16_t x,uint16_t y,float num,uint8_t len,
						uint16_t fc,uint16_t bc,uint8_t sizey)
{         	
	uint8_t t,temp,sizex;
	uint16_t num1;
	sizex=sizey/2;
	num1=num*100;
	
	for(t=0;t<len;t++)
	{
		temp=(num1/Pow(10,len-t-1))%10;
		if(t==(len-2))
		{
			LCD_ShowChar(x+(len-2)*sizex,y,'.',fc,bc,sizey,0);
			t++;
			len+=1;
		}
	 	LCD_ShowChar(x+t*sizex,y,temp+48,fc,bc,sizey,0);
	}
}






