#include "test.h"

/* 单个综合测试函数 - 包含所有测试项目 */
void Test_Display(void)
{
    uint16_t i;
    
    // 1. 初始化并打开背光
    LCD_Init();
    LCD_BLK_Set();
    
    // 2. 全屏颜色测试
    LCD_Fill(0, 0, LCD_W, LCD_W, RED);
    HAL_Delay(500);
    LCD_Fill(0, 0, LCD_W, LCD_W, GREEN);
    HAL_Delay(500);
    LCD_Fill(0, 0, LCD_W, LCD_W, BLUE);
    HAL_Delay(500);
    LCD_Fill(0, 0, LCD_W, LCD_W, BLACK);
    HAL_Delay(500);
    
    // 3. 线条测试
    for(i = 0; i < LCD_H; i += 10)
    {
        LCD_DrawLine(0, i, LCD_W, i, GREEN);
    }
    for(i = 0; i < LCD_W; i += 10)
    {
        LCD_DrawLine(i, 0, i, LCD_W, GREEN);
    }
    LCD_DrawLine(0, 0, LCD_W, LCD_W, RED);
    LCD_DrawLine(0, LCD_W, LCD_W, 0, RED);
    HAL_Delay(1000);
    
    // 4. 矩形测试
    LCD_Fill(0, 0, LCD_W, LCD_W, BLACK);
    for(i = 0; i < 30; i += 3)
    {
        LCD_DrawRectangle(i, i, LCD_W-i, LCD_W-i, BLUE);
    }
    LCD_Fill(30, 30, 60, 60, RED);
    LCD_Fill(80, 80, 110, 110, GREEN);
    HAL_Delay(1000);
    
    // 5. 圆形测试
    LCD_Fill(0, 0, LCD_W, LCD_W, BLACK);
    Draw_Circle(40, 40, 20, RED);
    Draw_Circle(90, 40, 20, GREEN);
    Draw_Circle(40, 110, 20, BLUE);
    Draw_Circle(90, 110, 20, YELLOW);
    for(i = 5; i < 30; i += 5)
    {
        Draw_Circle(64, 75, i, CYAN);
    }
    HAL_Delay(1000);
    
    // 6. 字符显示测试
    LCD_Fill(0, 0, LCD_W, LCD_W, BLACK);
    LCD_ShowString(10, 10, (uint8_t*)"Hello ST7735!", WHITE, BLACK, 16, 0);
    LCD_ShowString(10, 30, (uint8_t*)"Display Test", GREEN, BLACK, 16, 0);
    
    for(i = 0; i < 10; i++)
    {
        LCD_ShowChar(10 + i*12, 50, '0' + i, YELLOW, BLACK, 12, 0);
    }
    for(i = 0; i < 13; i++)
    {
        LCD_ShowChar(10 + i*12, 70, 'A' + i, CYAN, BLACK, 16, 0);
    }
    HAL_Delay(2000);
    
    // 7. 数字显示测试
    LCD_Fill(0, 0, LCD_W, LCD_W, BLACK);
    LCD_ShowString(10, 10, (uint8_t*)"Integer: 12345", WHITE, BLACK, 16, 0);
    LCD_ShowString(10, 35, (uint8_t*)"Float: 3.14159", GREEN, BLACK, 16, 0);
    LCD_ShowString(10, 60, (uint8_t*)"Power 2^8 = 256", CYAN, BLACK, 16, 0);
    LCD_ShowString(10, 85, (uint8_t*)"Test Complete!", YELLOW, BLACK, 16, 0);
    
    // 显示测试完成后的边框
    LCD_DrawRectangle(0, 0, LCD_W, LCD_W, WHITE);
    LCD_DrawRectangle(1, 1, LCD_W-2, LCD_H-2, WHITE);

}
