#include "HX711.h"


uint32_t HX711_Buffer;
uint32_t Weight_Maopi;
float Weight_Shiwu;
uint8_t Flag_Error = 0;


//计算实物的实际重量
//因为不同的传感器特性曲线不一样，因此，每一个传感器需要矫正这里的716这个除数。
//当发现测试出来的重量偏大时，增加该数值。
//如果测试出来的重量偏小时，减小改数值。

void delay_us(uint8_t value)
{
	uint8_t i;
	for(i=value;i>0;i--);
}
#define GapValue 412

//****************************************************
//读取HX711
//****************************************************
uint32_t HX711_Read(void)	//增益128
{
	unsigned long count; 
	unsigned char i; 
  HX711_DOUT==1; 
	delay_us(1);
  HX711_SCK_0; 
  count=0; 
  while(HX711_DOUT); 
  	for(i=0;i<24;i++)
	{ 
	  HX711_SCK_1; 
	  count=count<<1; 
		delay_us(1);
		HX711_SCK_0; 
	  	if(HX711_DOUT)
				count++; 
		delay_us(1);
	} 
 	HX711_SCK_1; 
    count=count^0x800000;//第25个脉冲下降沿来时，转换数据
	delay_us(1);
	HX711_SCK_0;  
	return(count);
}

//****************************************************
//获取毛皮重量
//****************************************************
void Get_Maopi(void)
{
	Weight_Maopi = HX711_Read();	
} 

//****************************************************
//称重
//****************************************************
void Get_Weight(void)
{
	HX711_Buffer = HX711_Read();
	if(HX711_Buffer > Weight_Maopi)			
	{
		Weight_Shiwu = HX711_Buffer;
		Weight_Shiwu = Weight_Shiwu - Weight_Maopi;				//获取实物的AD采样数值。
	
		Weight_Shiwu = (Weight_Shiwu/GapValue+0.005); 	//计算实物的实际重量
																		//因为不同的传感器特性曲线不一样，因此，每一个传感器需要矫正这里的GapValue这个除数。
																		//当发现测试出来的重量偏大时，增加该数值。
																		//如果测试出来的重量偏小时，减小改数值。
																		//该数值一般在4.0-5.0之间。因传感器不同而定。
																		//+0.05是为了四舍五入百分位
	}


	if(Weight_Shiwu > 5000 || HX711_Buffer < Weight_Maopi - 5000)
	{
		Flag_Error = 1;
	}
	else
	{
		Flag_Error = 0;
	}

	
}
