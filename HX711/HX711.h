//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//
//  驱    动   : HX711 电子秤
//  版 本 号   : v1.0
//  作    者   : Chen wt
//  生成日期   : 2020-06-018
//  最近修改   : 
//  功能描述   :演示例程(STM32f1系列)
//              说明: 
//              ----------------------------------------------------------------
//  			注意引脚是输入输出，可能该驱动获取频率不够快
//              ----------------------------------------------------------------
// 日    期   : 
// 作    者   : Chen wt
//All rights reserved


#ifndef __HX711_H
#define __HX711_H

#include "stm32f1xx_hal.h"


#define HX711_SCK_1 		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0,GPIO_PIN_SET)
#define HX711_SCK_0 		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0,GPIO_PIN_RESET)
#define HX711_DOUT 			HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1)


extern void Init_HX711pin(void);
extern uint32_t HX711_Read(void);
extern void Get_Maopi(void);
extern void Get_Weight(void);



extern uint32_t HX711_Buffer;
extern uint32_t Weight_Maopi;
extern float Weight_Shiwu;
extern uint8_t Flag_Error;

#endif
