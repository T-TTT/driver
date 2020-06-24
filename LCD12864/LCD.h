//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//
//  ��    ��   : lcd12864
//  �� �� ��   : v1.0
//  ��    ��   : Chen wt
//  ��������   : 2020-06-24
//  ����޸�   : 
//  ��������   :��ʾ����(STM32f1ϵ��)
//              ˵��: 
//              ----------------------------------------------------------------
//  			����Ƶ��Ҫ����
//				��ʾͼƬ�����ⲿ��������extern uint8_t XX[]����ʽ�������ͼƬ��ʾΪ����
//				RS��CS	
//				RW��SDA
//				CLK��EN
//				RST��RST
//              ----------------------------------------------------------------
// ��    ��   : 
// ��    ��   : Chen wt
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

