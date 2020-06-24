//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//
//  驱    动   : LCD1602&595
//  版 本 号   : v1.0
//  作    者   : Chen wt
//  生成日期   : 2020-06-018
//  最近修改   : 
//  功能描述   :演示例程(STM32f1系列)
//              说明: 
//              ----------------------------------------------------------------
//  			
//              ----------------------------------------------------------------
// 日    期   : 
// 作    者   : Chen wt
//All rights reserved



#include "stm32f1xx_hal.h"
#ifndef	__LCD1602__H
#define __LCD1602__H
#endif  

void LcdWriteCom(unsigned char com);				//写入命令子函数
void LcdWriteData(unsigned char dat);				//写入数据子函数
void LcdInit(void);													//初始化子函数
void LCD_display(uint8_t adr,char *a);


