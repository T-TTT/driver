/* Define to prevent recursive inclusion -------------------------------------*/
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
//  			ģ��I2C
//              ----------------------------------------------------------------
// ��    ��   : 
// ��    ��   : Chen wt

//All rights reserved

#include "main.h"


#define   OLED_SCK_ON()                 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET)
#define   OLED_SCK_OFF()                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET)
#define   OLED_SCK_TOGGLE()             HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_13)

#define   OLED_SDA_ON()                 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET)
#define   OLED_SDA_OFF()                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET)
#define   OLED_SDA_TOGGLE()             HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14)


void OLED_BMP(void);
void OLED_P16x16Ch(unsigned char x,unsigned char y,unsigned char N);
void OLED_P8x16Str(unsigned char x,unsigned  char y,unsigned char ch[]);
void OLED_Clear(void);
void OLED_Set_Pos(unsigned char x, unsigned char y);
void OLED_Draw_16_16_Hz(uint8_t line,uint8_t column,int Hz_num);
void Delay_us(uint16_t n);
void OLED_Init(void);
void OLED_IIC_Start(void);
void OLED_IIC_Stop(void);
void OLED_Send_Cmd(uint8_t command);
void OLED_Send_Data(uint8_t data);
void OLED_Set_Column(uint8_t column);
void OLED_Set_Page(uint8_t line);
void OLED_ALL_Clear(void);

void OLED_IIC_Write(uint8_t date);
void OLED_Draw_16_8_ASCII(uint8_t line,uint8_t column,char ASCII_num);
void OLED_Draw_String(uint8_t line,char *string);//line:1~4;
void OLED_Draw_String_x(uint8_t line,char *string,float x);//line:1~4;
