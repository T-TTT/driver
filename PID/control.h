//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//
//  ��    ��   : PID�㷨
//  �� �� ��   : v1.0
//  ��    ��   : Chen wt
//  ��������   : 2020-06-018
//  ����޸�   : 
//  ��������   :��ʾ����(STM32l0ϵ��)
//              ˵��: 
//              ----------------------------------------------------------------
//  			Ŀ��ֵ������ֵ������һ��������
//				PIDϵ���ɺ궨��Ҳ����ʹ��ȫ�ֱ���
//              ----------------------------------------------------------------
// ��    ��   : 
// ��    ��   : Chen wt
//All rights reserved


#include "stm32l0xx_hal.h"



extern float Velocity_KP,Velocity_KI,Velocity_KD;      //PIDϵ��
extern float Position_KP,Position_KI,Position_KD;

uint16_t Incremental_PID (uint16_t AD_Now,uint16_t AD_Target);
uint16_t Position_PID (int AD_Now,int AD_Target);



