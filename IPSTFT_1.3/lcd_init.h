//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//
//  ��    ��   : IPS TFT 1.3��
//  �� �� ��   : v1.0
//  ��    ��   : Chen wt
//  ��������   : 2020-06-018
//  ����޸�   : 
//  ��������   :��ʾ����(STM32f1ϵ��)
//              ˵��: 
//              ----------------------------------------------------------------
//  			��������ʹ�øߵ�ƽ
//              ----------------------------------------------------------------
// ��    ��   : 
// ��    ��   : Chen wt
//All rights reserved


#ifndef __LCD_INIT_H
#define __LCD_INIT_H

#include "stm32f1xx_hal.h"

#define USE_HORIZONTAL 1  //���ú�������������ʾ 0��1Ϊ���� 2��3Ϊ����


#define LCD_W 240
#define LCD_H 240


#define u8  uint8_t
#define u16 uint16_t
#define u32 uint32_t


//-----------------LCD�˿ڶ���---------------- 

#define LCD_SCLK_Clr() HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_RESET)//SCL=SCLK
#define LCD_SCLK_Set() HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_SET)

#define LCD_MOSI_Clr() HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_RESET)//SDA=MOSI
#define LCD_MOSI_Set() HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_SET)

#define LCD_RES_Clr()  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET)//RES
#define LCD_RES_Set()  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET)

#define LCD_DC_Clr()   HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET)//DC
#define LCD_DC_Set()   HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET)

#define LCD_BLK_Clr()  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_RESET)//BLK
#define LCD_BLK_Set()  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_SET)




void LCD_GPIO_Init(void);//��ʼ��GPIO
void LCD_Writ_Bus(u8 dat);//ģ��SPIʱ��
void LCD_WR_DATA8(u8 dat);//д��һ���ֽ�
void LCD_WR_DATA(u16 dat);//д�������ֽ�
void LCD_WR_REG(u8 dat);//д��һ��ָ��
void LCD_Address_Set(u16 x1,u16 y1,u16 x2,u16 y2);//�������꺯��
void LCD_Init(void);//LCD��ʼ��
#endif




