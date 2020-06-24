#include "oled.h"
#include "stdio.h"
#include "key.h"
#include "codetab.h"

extern uint8_t x_move,y_move,r_move;
const uint8_t OLED_Init_cmd[25]=
{
 0xAE,//关闭显示
 0xD5,//设置时钟分频因子,震荡频率
 0x80,//[3:0],分频因子;[7:4],震荡频率
 0xA8,//设置驱动路数
 0X3F,//默认0X3F(1/64)
 0xD3,//设置显示偏移
 0X00,//默认为0
 0x40,//设置显示开始行 [5:0],行数
 0x8D,//电荷泵设置
 0x14,//bit2，开启/关闭
 0x20,//设置内存地址模式
 0x02,//[1:0],00，列地址模式;01，行地址模式;10,页地址模式;默认10;
 0xA1,//段重定义设置,bit0:0,0->0;1,0->127;
 0xC8,//设置COM扫描方向;bit3:0,普通模式;1,重定义模式 COM[N-1]->COM0;N:驱动路数
 0xDA,//设置COM硬件引脚配置
 0x12,//[5:4]配置
 0x81,//对比度设置
 0x7F,//1~255;默认0X7F (亮度设置,越大越亮)原ef
 0xD9,//设置预充电周期
 0xf1,//[3:0],PHASE 1;[7:4],PHASE 2;
 0xDB,//设置VCOMH 电压倍率
 0x30,//[6:4] 000,0.65*vcc;001,0.77*vcc;011,0.83*vcc;
 0xA4,//全局显示开启;bit0:1,开启;0,关闭;(白屏/黑屏)
 0xA6,//设置显示方式;bit0:1,反相显示;0,正常显示
 0xAF,//开启显示
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

//I2C开始信号
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
 
//I2C停止信号
void OLED_IIC_Stop(void)
{
	OLED_SDA_OFF();
	Delay_us(1);
	OLED_SCK_ON();
	Delay_us(3);
	OLED_SDA_ON();
}

//OLED发送指令函数
void OLED_Send_Cmd(uint8_t command)
{
	OLED_IIC_Start();
	OLED_IIC_Write(0x00); 
	OLED_IIC_Write(command);
	OLED_IIC_Stop();
}

//OLED发送显示8点数据函数
void OLED_Send_Data(uint8_t data)
{
 OLED_IIC_Start();
 OLED_IIC_Write(0x40);
 OLED_IIC_Write(data);
 OLED_IIC_Stop();
}

//OLED设置列数 128列 0~127
void OLED_Set_Column(uint8_t column)
{
 OLED_Send_Cmd(0x10|(column>>4));//设置列地址高位
 OLED_Send_Cmd(0x00|(column&0x0f));//设置列地址低位
}

//OLED设置大行数 8大行 0~7 每大行由8小行组成
void OLED_Set_Page(uint8_t line)
{
 OLED_Send_Cmd(0xb0+line);
}

//OLED清屏函数 第一大行黄色 其他7大行蓝色
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

//OLED写入1Byte数据
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
/*函数功能: 更新显存到OLED                                                 */
/*************************************************************************/
void OLED_Refresh_Gram(void)
{
    u8 i,n;         
    for(i=0;i<8;i++)  
    {  
        OLED_Send_Cmd(0xb0+i);   //设置页地址（0~7）
        OLED_Send_Cmd(0x00);      //设置显示位置—列低地址
        OLED_Send_Cmd(0x10);      //设置显示位置—列高地址   
        for(n=0;n<128;n++)
			OLED_Send_Data(OLED_GRAM[n][i]); 
    }   
}
/*************************************************************************/
/*函数功能: 清屏                                                          */
/*************************************************************************/
void OLED_Clear(void)  
{  
    u8 i,n;  
    for(i=0;i<8;i++)
			for(n=0;n<128;n++)
				OLED_GRAM[n][i]=0X00;  
    OLED_Refresh_Gram();//更新显示
}

/*设置坐标*/
void OLED_Set_Pos(unsigned char x, unsigned char y) 
{ 
	OLED_Send_Cmd(0xb0+y);
	OLED_Send_Cmd(((x&0xf0)>>4)|0x10);		//设置高四位
	OLED_Send_Cmd((x&0x0f)|0x01);
}
/*******************功能描述：显示8*16一组标准ASCII字符串	 显示的坐标（x,y），y为页范围0～7****************/
void OLED_P8x16Str(unsigned char x,unsigned  char y,unsigned char ch[])
{
	unsigned char c=0,i=0,j=0;
	while (ch[j]!='\0')			//字符串是否结束
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
	unsigned int adder=32*N;      //每组里面也32个字符
	OLED_Set_Pos(x , y);
	for(wm = 0;wm < 16;wm++)
	{
		OLED_Send_Data(jiantou[adder]);	  //竖着扫描
		adder += 1;
	}
	OLED_Set_Pos(x,y + 1);
	for(wm = 0;wm < 16;wm++)     	//第16组
	{
		OLED_Send_Data(jiantou[adder]);
		adder += 1;
	} 	  	
}

void OLED_BMP(void)  
{  
    u8 i,n;
	
	//使图像与箭头或
    for(i=0;i<8;i++)  
    {  
        OLED_Send_Cmd(0xb0+i);   //设置页地址（0~7）
        OLED_Send_Cmd(0x00);      //设置显示位置—列低地址
        OLED_Send_Cmd(0x10);      //设置显示位置—列高地址   
        for(n=0;n<128;n++)
			{
				OLED_Send_Data(BMP[i][n]); 
			}
    }
    //OLED_Refresh_Gram();//更新显示
}




