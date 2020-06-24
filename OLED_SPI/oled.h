//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//
//  驱    动   : oled
//  版 本 号   : v1.0
//  作    者   : Chen wt
//  生成日期   : 2020-06-018
//  最近修改   : 
//  功能描述   :演示例程(STM32f1系列)
//              说明: 
//              ----------------------------------------------------------------
//  			模拟SPI驱动OLED
//              ----------------------------------------------------------------
// 日    期   : 
// 作    者   : Chen wt
//All rights reserved



#include "stm32f1xx_hal.h"
#ifndef	__OLED__H
#define __OLED__H

#endif  

#define SPI_MOSI_0  		 HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7,GPIO_PIN_RESET)
#define SPI_MOSI_1  		 HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7,GPIO_PIN_SET)

#define SPI_CLK_0   		 HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5,GPIO_PIN_RESET)
#define SPI_CLK_1  			 HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5,GPIO_PIN_SET)

#define SPI_NSS_OLED_0 	 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12,GPIO_PIN_RESET)
#define SPI_NSS_OLED_1   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12,GPIO_PIN_SET)

#define OLED_DC_0   	 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13,GPIO_PIN_RESET)
#define OLED_DC_1   	 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13,GPIO_PIN_SET)


#define OLED_CMD  0					//写命令为低
#define OLED_DATA 1					//写数据为高
 
#define SIZE 		16					//定义显示字符的大小
//#define Max_Column	128			//定义最大列数
//#define Max_Row		64		    //定义最大行数
//#define X_WIDTH 	128				//定义X轴的宽度
//#define Y_WIDTH 	64	   	  //定义Y轴的宽度	

void OLED_Init(void);//初始化OLED
void OLED_ON(void);//唤醒OLED
void OLED_OFF(void);//OLED休眠
void OLED_Refresh_Gram(void);//更新显存到OLED
void OLED_Clear(void);//清屏
void OLED_DrawPoint(uint8_t x,uint8_t y,uint8_t t);//画点
void OLED_Fill(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2,uint8_t dot);//填充

void OLED_Set_Pos(unsigned char x, unsigned char y);    //设置坐标
void OLED_P8x16Str(unsigned char x,unsigned  char y,unsigned char ch[]); //8*16字符串
void OLED_P16x16Ch(unsigned char x,unsigned char y,unsigned char N);
void OLED_BMP(void);

