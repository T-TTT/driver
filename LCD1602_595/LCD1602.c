




#include "LCD1602.h"
#include "74HC595.h"

void LcdWriteCom(unsigned char com)		//写入命令子函数
{
		
		HC595Send_Data(0x00);		//使能清零，选择写入命令
	
		HC595Send_Data((com>>2)&0xfc);//右移两位使595中间四位发送高四位数据，与运算是为了保持EN和RS始终为0，
		HAL_Delay(1);							//对应595低二位为0，以此来保证是写入命令。	
		HC595Send_Data(((com>>2)|0x02)&0xfe);	//写入时序使EN为1，同时也必须使595中间四位保持不变。
		HAL_Delay(5);									//延时5ms
		HC595Send_Data((com>>2)&0xfc);//使EN为0，产生了一个下降沿，同时也必须使595中间四位保持不变，这样高四位命令写入1602

		HC595Send_Data((com<<2)&0xfc); //左移发送低四位，低四位与高四位同样的原理
		HAL_Delay(1);
		HC595Send_Data(((com<<2)|0x02)&0xfe);
		HAL_Delay(5);
		HC595Send_Data((com<<2)&0xfc);
																												//与运算：与上0，0的还是0，1的便为0；与上1，原数不变
																												//或运算：或上0，原数不变；或上1，1的还是1，0的变为1		
}
																												//协入数据与写入命令的原理相同
void LcdWriteData(unsigned char dat)						//写入数据子函数
{
		HC595Send_Data(0x01);						//使能清零，选择写入数据
	
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

void LcdInit(void)						  	//LCD初始化子程序
{
		LcdWriteCom(0x32);	 				//将8位总线转为4位总线
		LcdWriteCom(0x28);	 				//在四位线下的初始化
		LcdWriteCom(0x0c);  				//开显示不显示光标
		LcdWriteCom(0x06);  				//写一个指针加1
		LcdWriteCom(0x01);  				//清屏
		LcdWriteCom(0x80);  				//设置数据指针起点
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
		LcdWriteCom(adr);		//第一行首地址
		while(*a!='\0')
		{
			LcdWriteData(*a);
			a++;
		}
}

