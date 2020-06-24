//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//
//  驱    动   : key
//  版 本 号   : v1.0
//  作    者   : Chen wt
//  生成日期   : 2020-06-018
//  最近修改   : 
//  功能描述   :演示例程(STM32l0系列)
//              说明: 
//              ----------------------------------------------------------------
//  			
//              ----------------------------------------------------------------
// 日    期   : 
// 作    者   : Chen wt
//All rights reserved

#include "stm32l0xx_hal.h"

#define KEY1 		HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_2)
#define KEY2 		HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_1)


#define KEY1_PR		1
#define KEY2_PR		2


uint8_t Key_scan(void);

