//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//
//  驱    动   : lcd12864
//  版 本 号   : v1.0
//  作    者   : Chen wt
//  生成日期   : 2020-06-24
//  最近修改   : 
//  功能描述   :演示例程(STM32f1系列)
//              说明: 
//              ----------------------------------------------------------------
//  			引脚频率要高速
//				显示图片数组外部声明是以extern uint8_t XX[]的形式，否则会图片显示为乱码
//				RS：CS	
//				RW：SDA
//				CLK：EN
//				RST：RST
//              ----------------------------------------------------------------
// 日    期   : 
// 作    者   : Chen wt
//All rights reserved

#include "stm32l0xx_hal.h"
#define CS_ON HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8,GPIO_PIN_SET)
#define CS_OFF HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8,GPIO_PIN_RESET)

#define RST_ON HAL_GPIO_WritePin(GPIOC,GPIO_PIN_5,GPIO_PIN_SET)
#define RST_OFF HAL_GPIO_WritePin(GPIOC,GPIO_PIN_5,GPIO_PIN_RESET)

#define CLK_ON HAL_GPIO_WritePin(GPIOC,GPIO_PIN_6,GPIO_PIN_SET)
#define CLK_OFF HAL_GPIO_WritePin(GPIOC,GPIO_PIN_6,GPIO_PIN_RESET)

#define SDA_ON HAL_GPIO_WritePin(GPIOC,GPIO_PIN_9,GPIO_PIN_SET)
#define SDA_OFF HAL_GPIO_WritePin(GPIOC,GPIO_PIN_9,GPIO_PIN_RESET)



void delay(uint16_t time);
void lcd_write(uint8_t cd,uint8_t dat);
void LCDInit(void);
void LCDClear(void);
void LCDAddress(uint8_t x, uint8_t y);
void LCD_display(uint8_t x,uint8_t y,char *a);
void LCD_IMG(uint8_t *img);
void Clear_Draw(void);
void Set_Reverse(unsigned char y,unsigned char x,unsigned char width);

