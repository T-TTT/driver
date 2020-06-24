#include "oled.h"
#include "codetab.h"



#define u8  uint8_t
#define u32 uint32_t

u8 OLED_GRAM[128][8]; 

void OLED_write_byte(uint8_t date)
{
	uint8_t i;
	for(i=0;i<8;i++)
	{
		if((date<<i)&0x80)
				SPI_MOSI_1;
		else
				SPI_MOSI_0;
		SPI_CLK_1;
		
		SPI_CLK_0;
	}
}
void OLED_WR_Byte(unsigned char dat,unsigned char cmd)
{
	if(cmd)  										//���cmdΪ�ߣ����͵�������
	  	OLED_DC_1;							//��DC����
	else   											//���cmdΪ�ͣ����͵�������
			OLED_DC_0;							//��DC����
		
	SPI_NSS_OLED_0; 						//Ƭѡ���ͣ�ѡͨ����
		
	OLED_write_byte(dat); 			//��������
		
	SPI_NSS_OLED_1; 						//Ƭѡ���ߣ��ر�����
	OLED_DC_1; 									//DC���ߣ�����ʱΪ�ߵ�ƽ
}


void WriteCmd(unsigned char cmd)
{
	OLED_WR_Byte(cmd,OLED_CMD);
}

void WriteData(unsigned char data)
{
	OLED_WR_Byte(data,OLED_DATA);
}


void OLED_Init(void)
{
    SPI_NSS_OLED_1;

 
    //���ϵ絽���濪ʼ��ʼ��Ҫ���㹻��ʱ�䣬���ȴ�RC��λ���
    WriteCmd(0xAE);         // Display Off (0x00)
    WriteCmd(0xD5);
    WriteCmd(0x80);         // Set Clock as 100 Frames/Sec
    WriteCmd(0xA8);
    WriteCmd(0x3F);         // 1/64 Duty (0x0F~0x3F)
    WriteCmd(0xD3);
    WriteCmd(0x00);         // Shift Mapping RAM Counter (0x00~0x3F)
    WriteCmd(0x40 | 0x00);  // Set Mapping RAM Display Start Line (0x00~0x3F)
    WriteCmd(0x8D);
    WriteCmd(0x10 | 0x04);  // Enable Embedded DC/DC Converter (0x00/0x04)
    WriteCmd(0x20);
    WriteCmd(0x02);         // Set Page Addressing Mode (0x00/0x01/0x02)
    WriteCmd(0xA0 | 0x01);  // Set SEG/Column Mapping    
    WriteCmd(0xC0);  // Set COM/x Scan Direction   
    WriteCmd(0xDA);
    WriteCmd(0x02 | 0x10);  // Set Sequential Configuration (0x00/0x10)
    WriteCmd(0x81);
    WriteCmd(0xCF);         // Set SEG Output Current
    WriteCmd(0xD9);
    WriteCmd(0xF1);         // Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
    WriteCmd(0xDB);
    WriteCmd(0x40);         // Set VCOM Deselect Level
    WriteCmd(0xA4 | 0x00);  // Disable Entire Display On (0x00/0x01)
    WriteCmd(0xA6 | 0x00);  // Disable Inverse Display On (0x00/0x01)
    WriteCmd(0xAE | 0x01);  // Display On (0x01)
    OLED_Clear();  //��ʼ����   
}


/*************************************************************************/
/*��������: ��OLED�������л���                                            */
/*************************************************************************/
void OLED_ON(void)
{
    WriteCmd(0X8D);  //���õ�ɱ�
    WriteCmd(0X14);  //������ɱ�
    WriteCmd(0XAF);  //OLED����
		WriteCmd(0XA1);		//��תˮƽ
		WriteCmd(0XC8);		//��ת��ֱ
}
/*************************************************************************/
/*��������: ��OLED���� -- ����ģʽ��,OLED���Ĳ���10uA                      */
/*************************************************************************/
void OLED_OFF(void)
{
    WriteCmd(0X8D);  //���õ�ɱ�
    WriteCmd(0X10);  //�رյ�ɱ�
    WriteCmd(0XAE);  //OLED����
}
 
/*************************************************************************/
/*��������: �����Դ浽OLED                                                 */
/*************************************************************************/
void OLED_Refresh_Gram(void)
{
    u8 i,n;         
    for(i=0;i<8;i++)  
    {  
        WriteCmd(0xb0+i);   //����ҳ��ַ��0~7��
        WriteCmd(0x00);      //������ʾλ�á��е͵�ַ
        WriteCmd(0x10);      //������ʾλ�á��иߵ�ַ   
        for(n=0;n<128;n++)
					WriteData(OLED_GRAM[n][i]); 
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
/*************************************************************************/
/*��������: ����                                                          */
/*��ڲ�����                                                             */
/*                      x��������       0~127                               */
/*                      y��������               0~63                     */
/*                      dot:0,���;1,���                                                                                */             
/*************************************************************************/
void OLED_DrawPoint(u8 x,u8 y,u8 t)
{
    u8 pos,bx,temp=0;
    if(x>127||y>63)return;//������Χ��.
    pos=7-y/8;
    bx=y%8;
    temp=1<<(7-bx);
    if(t)OLED_GRAM[x][pos]|=temp;
    else OLED_GRAM[x][pos]&=~temp;     
}
///*************************************************************************/
///*��������: ���                                                          */
///*��ڲ�����                                                                                                                          */
///*                      x1,y1,x2,y2 �������ĶԽ�����                              */
///*                      ȷ��x1<=x2;y1<=y2 0<=x1<=127 0<=y1<=63                                         */
///*                      dot:0,���;1,���                                                                                */             
///*************************************************************************/
//void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot)  
//{  
//    u8 x,y;  
//    for(x=x1;x<=x2;x++)
//    {
//        for(y=y1;y<=y2;y++)OLED_DrawPoint(x,y,dot);
//    }                                                       
//    OLED_Refresh_Gram();//������ʾ
//}

/*����һ�ַ�ʽ*/
/*��������*/
void OLED_Set_Pos(unsigned char x, unsigned char y) 
{ 
	WriteCmd(0xb0+y);
	WriteCmd(((x&0xf0)>>4)|0x10);		//���ø���λ
	WriteCmd((x&0x0f)|0x01);
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
			WriteData(F8X16[c*16+i]);
		OLED_Set_Pos(x,y+1);
		for(i=0;i<8;i++)
			WriteData(F8X16[c*16+i+8]);
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
		WriteData(F16x16[adder]);	  //����ɨ��
		adder += 1;
	}
	OLED_Set_Pos(x,y + 1);
	for(wm = 0;wm < 16;wm++)     	//��16��
	{
		WriteData(F16x16[adder]);
		adder += 1;
	} 	  	
}

void OLED_BMP(void)  
{  
    u8 i,n;  
    for(i=0;i<8;i++)
			for(n=0;n<128;n++)
				WriteData(BMP[n][i]);
    OLED_Refresh_Gram();//������ʾ
}
































































