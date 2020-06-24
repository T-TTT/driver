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
	if(cmd)  										//如果cmd为高，则发送的是数据
	  	OLED_DC_1;							//将DC拉高
	else   											//如果cmd为低，则发送的是命令
			OLED_DC_0;							//将DC拉低
		
	SPI_NSS_OLED_0; 						//片选拉低，选通器件
		
	OLED_write_byte(dat); 			//发送数据
		
	SPI_NSS_OLED_1; 						//片选拉高，关闭器件
	OLED_DC_1; 									//DC拉高，空闲时为高电平
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

 
    //从上电到下面开始初始化要有足够的时间，即等待RC复位完毕
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
    OLED_Clear();  //初始清屏   
}


/*************************************************************************/
/*函数功能: 将OLED从休眠中唤醒                                            */
/*************************************************************************/
void OLED_ON(void)
{
    WriteCmd(0X8D);  //设置电荷泵
    WriteCmd(0X14);  //开启电荷泵
    WriteCmd(0XAF);  //OLED唤醒
		WriteCmd(0XA1);		//反转水平
		WriteCmd(0XC8);		//反转垂直
}
/*************************************************************************/
/*函数功能: 将OLED休眠 -- 休眠模式下,OLED功耗不到10uA                      */
/*************************************************************************/
void OLED_OFF(void)
{
    WriteCmd(0X8D);  //设置电荷泵
    WriteCmd(0X10);  //关闭电荷泵
    WriteCmd(0XAE);  //OLED休眠
}
 
/*************************************************************************/
/*函数功能: 更新显存到OLED                                                 */
/*************************************************************************/
void OLED_Refresh_Gram(void)
{
    u8 i,n;         
    for(i=0;i<8;i++)  
    {  
        WriteCmd(0xb0+i);   //设置页地址（0~7）
        WriteCmd(0x00);      //设置显示位置—列低地址
        WriteCmd(0x10);      //设置显示位置—列高地址   
        for(n=0;n<128;n++)
					WriteData(OLED_GRAM[n][i]); 
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
/*************************************************************************/
/*函数功能: 画点                                                          */
/*入口参数：                                                             */
/*                      x：横坐标       0~127                               */
/*                      y：纵坐标               0~63                     */
/*                      dot:0,清空;1,填充                                                                                */             
/*************************************************************************/
void OLED_DrawPoint(u8 x,u8 y,u8 t)
{
    u8 pos,bx,temp=0;
    if(x>127||y>63)return;//超出范围了.
    pos=7-y/8;
    bx=y%8;
    temp=1<<(7-bx);
    if(t)OLED_GRAM[x][pos]|=temp;
    else OLED_GRAM[x][pos]&=~temp;     
}
///*************************************************************************/
///*函数功能: 填充                                                          */
///*入口参数：                                                                                                                          */
///*                      x1,y1,x2,y2 填充区域的对角坐标                              */
///*                      确保x1<=x2;y1<=y2 0<=x1<=127 0<=y1<=63                                         */
///*                      dot:0,清空;1,填充                                                                                */             
///*************************************************************************/
//void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot)  
//{  
//    u8 x,y;  
//    for(x=x1;x<=x2;x++)
//    {
//        for(y=y1;y<=y2;y++)OLED_DrawPoint(x,y,dot);
//    }                                                       
//    OLED_Refresh_Gram();//更新显示
//}

/*另外一种方式*/
/*设置坐标*/
void OLED_Set_Pos(unsigned char x, unsigned char y) 
{ 
	WriteCmd(0xb0+y);
	WriteCmd(((x&0xf0)>>4)|0x10);		//设置高四位
	WriteCmd((x&0x0f)|0x01);
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
	unsigned int adder=32*N;      //每组里面也32个字符
	OLED_Set_Pos(x , y);
	for(wm = 0;wm < 16;wm++)
	{
		WriteData(F16x16[adder]);	  //竖着扫描
		adder += 1;
	}
	OLED_Set_Pos(x,y + 1);
	for(wm = 0;wm < 16;wm++)     	//第16组
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
    OLED_Refresh_Gram();//更新显示
}
































































