




#include "LCD1602.h"
#include "74HC595.h"

void LcdWriteCom(unsigned char com)		//д�������Ӻ���
{
		
		HC595Send_Data(0x00);		//ʹ�����㣬ѡ��д������
	
		HC595Send_Data((com>>2)&0xfc);//������λʹ595�м���λ���͸���λ���ݣ���������Ϊ�˱���EN��RSʼ��Ϊ0��
		HAL_Delay(1);							//��Ӧ595�Ͷ�λΪ0���Դ�����֤��д�����	
		HC595Send_Data(((com>>2)|0x02)&0xfe);	//д��ʱ��ʹENΪ1��ͬʱҲ����ʹ595�м���λ���ֲ��䡣
		HAL_Delay(5);									//��ʱ5ms
		HC595Send_Data((com>>2)&0xfc);//ʹENΪ0��������һ���½��أ�ͬʱҲ����ʹ595�м���λ���ֲ��䣬��������λ����д��1602

		HC595Send_Data((com<<2)&0xfc); //���Ʒ��͵���λ������λ�����λͬ����ԭ��
		HAL_Delay(1);
		HC595Send_Data(((com<<2)|0x02)&0xfe);
		HAL_Delay(5);
		HC595Send_Data((com<<2)&0xfc);
																												//�����㣺����0��0�Ļ���0��1�ı�Ϊ0������1��ԭ������
																												//�����㣺����0��ԭ�����䣻����1��1�Ļ���1��0�ı�Ϊ1		
}
																												//Э��������д�������ԭ����ͬ
void LcdWriteData(unsigned char dat)						//д�������Ӻ���
{
		HC595Send_Data(0x01);						//ʹ�����㣬ѡ��д������
	
		HC595Send_Data(((dat>>2)|0x01)&0xfd);
		HAL_Delay(1);		
		HC595Send_Data((dat>>2)|0x03);
		HAL_Delay(1);
		HC595Send_Data(((dat>>2)|0x01)&0xfd);

		HC595Send_Data(((dat<<2)|0x01)&0xfd);
		HAL_Delay(1);
		HC595Send_Data((dat<<2)|0x03);
		HAL_Delay(1);
		HC595Send_Data(((dat<<2)|0x01)&0xfd);		
}

void LcdInit(void)						  	//LCD��ʼ���ӳ���
{
		LcdWriteCom(0x32);	 				//��8λ����תΪ4λ����
		LcdWriteCom(0x28);	 				//����λ���µĳ�ʼ��
		LcdWriteCom(0x0c);  				//����ʾ����ʾ���
		LcdWriteCom(0x06);  				//дһ��ָ���1
		LcdWriteCom(0x01);  				//����
		LcdWriteCom(0x80);  				//��������ָ�����
}
void lcd_xy(uint8_t x,uint8_t y)
{
    LcdWriteCom(0x80+(0x40*y)+x);
}

void lcd_char(uint8_t x,uint8_t y,uint8_t data)
{
    lcd_xy(x,y);
    LcdWriteData(data);
}


void LCD_display(uint8_t adr,char *a)
{
		LcdWriteCom(adr);		//��һ���׵�ַ
		while(*a!='\0')
		{
			LcdWriteData(*a);
			a++;
		}
}

