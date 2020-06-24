//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//
//  驱    动   : PID算法
//  版 本 号   : v1.0
//  作    者   : Chen wt
//  生成日期   : 2020-06-018
//  最近修改   : 
//  功能描述   :演示例程(STM32l0系列)
//              说明: 
//              ----------------------------------------------------------------
//  			目标值和理想值尽量是一个量级的
//				PID系数可宏定义也可以使用全局变量
//              ----------------------------------------------------------------
// 日    期   : 
// 作    者   : Chen wt
//All rights reserved


#include "stm32l0xx_hal.h"



extern float Velocity_KP,Velocity_KI,Velocity_KD;      //PID系数
extern float Position_KP,Position_KI,Position_KD;

uint16_t Incremental_PID (uint16_t AD_Now,uint16_t AD_Target);
uint16_t Position_PID (int AD_Now,int AD_Target);



