#include "HX711.h"


uint32_t HX711_Buffer;
uint32_t Weight_Maopi;
float Weight_Shiwu;
uint8_t Flag_Error = 0;


//����ʵ���ʵ������
//��Ϊ��ͬ�Ĵ������������߲�һ������ˣ�ÿһ����������Ҫ���������716���������
//�����ֲ��Գ���������ƫ��ʱ�����Ӹ���ֵ��
//������Գ���������ƫСʱ����С����ֵ��

void delay_us(uint8_t value)
{
	uint8_t i;
	for(i=value;i>0;i--);
}
#define GapValue 412

//****************************************************
//��ȡHX711
//****************************************************
uint32_t HX711_Read(void)	//����128
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
    count=count^0x800000;//��25�������½�����ʱ��ת������
	delay_us(1);
	HX711_SCK_0;  
	return(count);
}

//****************************************************
//��ȡëƤ����
//****************************************************
void Get_Maopi(void)
{
	Weight_Maopi = HX711_Read();	
} 

//****************************************************
//����
//****************************************************
void Get_Weight(void)
{
	HX711_Buffer = HX711_Read();
	if(HX711_Buffer > Weight_Maopi)			
	{
		Weight_Shiwu = HX711_Buffer;
		Weight_Shiwu = Weight_Shiwu - Weight_Maopi;				//��ȡʵ���AD������ֵ��
	
		Weight_Shiwu = (Weight_Shiwu/GapValue+0.005); 	//����ʵ���ʵ������
																		//��Ϊ��ͬ�Ĵ������������߲�һ������ˣ�ÿһ����������Ҫ���������GapValue���������
																		//�����ֲ��Գ���������ƫ��ʱ�����Ӹ���ֵ��
																		//������Գ���������ƫСʱ����С����ֵ��
																		//����ֵһ����4.0-5.0֮�䡣�򴫸�����ͬ������
																		//+0.05��Ϊ����������ٷ�λ
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
