//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//
//  驱    动   : 矩阵键盘
//  版 本 号   : v1.0
//  作    者   : Chen wt
//  生成日期   : 2020-06-018
//  最近修改   : 
//  功能描述   :演示例程(STM32f1系列)
//              说明: 
//              ----------------------------------------------------------------
//  			注意那几个为上拉输入引脚和输出引脚
//              ----------------------------------------------------------------
// 日    期   : 
// 作    者   : Chen wt
//All rights reserved


#ifndef __BOARD_H_
#define __BOARD_H_

#endif /*__BOARD_H_*/

#include "stm32f1xx_hal.h"


#define hang_1_1 		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8,GPIO_PIN_SET)
#define hang_2_1 		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9,GPIO_PIN_SET)
#define hang_3_1 		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10,GPIO_PIN_SET)
#define hang_4_1 		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11,GPIO_PIN_SET)
#define hang_1_0 		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8,GPIO_PIN_RESET)
#define hang_2_0 		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9,GPIO_PIN_RESET)
#define hang_3_0 		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10,GPIO_PIN_RESET)
#define hang_4_0 		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11,GPIO_PIN_RESET)

#define lie_1 		HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5)
#define lie_2 		HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_6)
#define lie_3 		HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_7)
#define lie_4 		HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_8)

uint8_t Key_scan(void);

	

