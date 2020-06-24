//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//
//  ��    ��   : HX711 ���ӳ�
//  �� �� ��   : v1.0
//  ��    ��   : Chen wt
//  ��������   : 2020-06-018
//  ����޸�   : 
//  ��������   :��ʾ����(STM32f1ϵ��)
//              ˵��: 
//              ----------------------------------------------------------------
//  			ע��������������������ܸ�������ȡƵ�ʲ�����
//              ----------------------------------------------------------------
// ��    ��   : 
// ��    ��   : Chen wt
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
