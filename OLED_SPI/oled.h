//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//
//  ��    ��   : oled
//  �� �� ��   : v1.0
//  ��    ��   : Chen wt
//  ��������   : 2020-06-018
//  ����޸�   : 
//  ��������   :��ʾ����(STM32f1ϵ��)
//              ˵��: 
//              ----------------------------------------------------------------
//  			ģ��SPI����OLED
//              ----------------------------------------------------------------
// ��    ��   : 
// ��    ��   : Chen wt
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


#define OLED_CMD  0					//д����Ϊ��
#define OLED_DATA 1					//д����Ϊ��
 
#define SIZE 		16					//������ʾ�ַ��Ĵ�С
//#define Max_Column	128			//�����������
//#define Max_Row		64		    //�����������
//#define X_WIDTH 	128				//����X��Ŀ��
//#define Y_WIDTH 	64	   	  //����Y��Ŀ��	

void OLED_Init(void);//��ʼ��OLED
void OLED_ON(void);//����OLED
void OLED_OFF(void);//OLED����
void OLED_Refresh_Gram(void);//�����Դ浽OLED
void OLED_Clear(void);//����
void OLED_DrawPoint(uint8_t x,uint8_t y,uint8_t t);//����
void OLED_Fill(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2,uint8_t dot);//���

void OLED_Set_Pos(unsigned char x, unsigned char y);    //��������
void OLED_P8x16Str(unsigned char x,unsigned  char y,unsigned char ch[]); //8*16�ַ���
void OLED_P16x16Ch(unsigned char x,unsigned char y,unsigned char N);
void OLED_BMP(void);

