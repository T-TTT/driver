#include "oled.h"
#include "stdio.h"
#include "key.h"
#include "codetab.h"

extern uint8_t x_move,y_move,r_move;
const uint8_t OLED_Init_cmd[25]=
{
 0xAE,//�ر���ʾ
 0xD5,//����ʱ�ӷ�Ƶ����,��Ƶ��
 0x80,//[3:0],��Ƶ����;[7:4],��Ƶ��
 0xA8,//��������·��
 0X3F,//Ĭ��0X3F(1/64)
 0xD3,//������ʾƫ��
 0X00,//Ĭ��Ϊ0
 0x40,//������ʾ��ʼ�� [5:0],����
 0x8D,//��ɱ�����
 0x14,//bit2������/�ر�
 0x20,//�����ڴ��ַģʽ
 0x02,//[1:0],00���е�ַģʽ;01���е�ַģʽ;10,ҳ��ַģʽ;Ĭ��10;
 0xA1,//���ض�������,bit0:0,0->0;1,0->127;
 0xC8,//����COMɨ�跽��;bit3:0,��ͨģʽ;1,�ض���ģʽ COM[N-1]->COM0;N:����·��
 0xDA,//����COMӲ����������
 0x12,//[5:4]����
 0x81,//�Աȶ�����
 0x7F,//1~255;Ĭ��0X7F (��������,Խ��Խ��)ԭef
 0xD9,//����Ԥ�������
 0xf1,//[3:0],PHASE 1;[7:4],PHASE 2;
 0xDB,//����VCOMH ��ѹ����
 0x30,//[6:4] 000,0.65*vcc;001,0.77*vcc;011,0.83*vcc;
 0xA4,//ȫ����ʾ����;bit0:1,����;0,�ر�;(����/����)
 0xA6,//������ʾ��ʽ;bit0:1,������ʾ;0,������ʾ
 0xAF,//������ʾ
};

#define u8  uint8_t
#define u32 uint32_t

u8 OLED_GRAM[128][8]; 

void Delay_us(uint16_t n)
{
	for(uint16_t i=0;i<n;i++){
		for(uint16_t j=0;j<10;j++);
		}
	//HAL_Delay(1);
}
void OLED_Init(void)
{
 uint8_t i;
 for(i=0;i<25;i++)
 {
	OLED_Send_Cmd(OLED_Init_cmd[i]);
	HAL_Delay(1); 
 }
}

//I2C��ʼ�ź�
void OLED_IIC_Start(void)
{
	OLED_SDA_ON();
	Delay_us(1);
	OLED_SCK_ON();
	Delay_us(1);
	OLED_SDA_OFF();
	Delay_us(3);
	OLED_SCK_OFF();
	OLED_IIC_Write(0x78);
}
 
//I2Cֹͣ�ź�
void OLED_IIC_Stop(void)
{
	OLED_SDA_OFF();
	Delay_us(1);
	OLED_SCK_ON();
	Delay_us(3);
	OLED_SDA_ON();
}

//OLED����ָ���
void OLED_Send_Cmd(uint8_t command)
{
	OLED_IIC_Start();
	OLED_IIC_Write(0x00); 
	OLED_IIC_Write(command);
	OLED_IIC_Stop();
}

//OLED������ʾ8�����ݺ���
void OLED_Send_Data(uint8_t data)
{
 OLED_IIC_Start();
 OLED_IIC_Write(0x40);
 OLED_IIC_Write(data);
 OLED_IIC_Stop();
}

//OLED�������� 128�� 0~127
void OLED_Set_Column(uint8_t column)
{
 OLED_Send_Cmd(0x10|(column>>4));//�����е�ַ��λ
 OLED_Send_Cmd(0x00|(column&0x0f));//�����е�ַ��λ
}

//OLED���ô����� 8���� 0~7 ÿ������8С�����
void OLED_Set_Page(uint8_t line)
{
 OLED_Send_Cmd(0xb0+line);
}

//OLED�������� ��һ���л�ɫ ����7������ɫ
void OLED_ALL_Full(void)
{
 uint8_t line,column;
 for(line=0;line<8;line++)
 { 
  OLED_Set_Page(line);
  OLED_Set_Column(0);
  for(column=0;column<128;column++)
  {
   OLED_Send_Data(0xff);
  }
 }
}

//OLEDд��1Byte����
void OLED_IIC_Write(uint8_t date)
{
	uint8_t i, temp;
	temp = date;
	for(i=0; i<8; i++)
	{ 
		OLED_SCK_OFF();
		if((temp&0x80) == 0)
		{
			OLED_SDA_OFF();
		}
		else
		{
			OLED_SDA_ON();
		}
	temp = temp << 1;
	Delay_us(1);
	OLED_SCK_ON();
	Delay_us(1);
	}
	OLED_SCK_OFF();
	Delay_us(1);
	OLED_SDA_ON();
	Delay_us(1);
	OLED_SCK_ON();
	Delay_us(1);
	OLED_SCK_OFF();
	Delay_us(1);
}


/*************************************************************************/
/*��������: �����Դ浽OLED                                                 */
/*************************************************************************/
void OLED_Refresh_Gram(void)
{
    u8 i,n;         
    for(i=0;i<8;i++)  
    {  
        OLED_Send_Cmd(0xb0+i);   //����ҳ��ַ��0~7��
        OLED_Send_Cmd(0x00);      //������ʾλ�á��е͵�ַ
        OLED_Send_Cmd(0x10);      //������ʾλ�á��иߵ�ַ   
        for(n=0;n<128;n++)
			OLED_Send_Data(OLED_GRAM[n][i]); 
    }   
}
/*************************************************************************/
/*��������: ����                                                          */
/*************************************************************************/
void OLED_Clear(void)  
{  
    u8 i,n;  
    for(i=0;i<8;i++)
			for(n=0;n<128;n++)
				OLED_GRAM[n][i]=0X00;  
    OLED_Refresh_Gram();//������ʾ
}

/*��������*/
void OLED_Set_Pos(unsigned char x, unsigned char y) 
{ 
	OLED_Send_Cmd(0xb0+y);
	OLED_Send_Cmd(((x&0xf0)>>4)|0x10);		//���ø���λ
	OLED_Send_Cmd((x&0x0f)|0x01);
}
/*******************������������ʾ8*16һ���׼ASCII�ַ���	 ��ʾ�����꣨x,y����yΪҳ��Χ0��7****************/
void OLED_P8x16Str(unsigned char x,unsigned  char y,unsigned char ch[])
{
	unsigned char c=0,i=0,j=0;
	while (ch[j]!='\0')			//�ַ����Ƿ����
	{
		c =ch[j]-32;         
		if(x>120)
			{x=0;y++;}
			OLED_Set_Pos(x,y);
		for(i=0;i<8;i++)
			OLED_Send_Data(F8X16[c*16+i]);
		OLED_Set_Pos(x,y+1);
		for(i=0;i<8;i++)
			OLED_Send_Data(F8X16[c*16+i+8]);
		x+=8;
		j++;
	}
}



void OLED_P16x16Ch(unsigned char x,unsigned char y,unsigned char N)
{
	unsigned char wm=0;
	unsigned int adder=32*N;      //ÿ������Ҳ32���ַ�
	OLED_Set_Pos(x , y);
	for(wm = 0;wm < 16;wm++)
	{
		OLED_Send_Data(jiantou[adder]);	  //����ɨ��
		adder += 1;
	}
	OLED_Set_Pos(x,y + 1);
	for(wm = 0;wm < 16;wm++)     	//��16��
	{
		OLED_Send_Data(jiantou[adder]);
		adder += 1;
	} 	  	
}

void OLED_BMP(void)  
{  
    u8 i,n;
	
	//ʹͼ�����ͷ��
    for(i=0;i<8;i++)  
    {  
        OLED_Send_Cmd(0xb0+i);   //����ҳ��ַ��0~7��
        OLED_Send_Cmd(0x00);      //������ʾλ�á��е͵�ַ
        OLED_Send_Cmd(0x10);      //������ʾλ�á��иߵ�ַ   
        for(n=0;n<128;n++)
			{
				OLED_Send_Data(BMP[i][n]); 
			}
    }
    //OLED_Refresh_Gram();//������ʾ
}




