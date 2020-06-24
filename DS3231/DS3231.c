#include "DS3231.h"
#include "i2c.h"
#include "stdio.h"
#include "oled.h"
/**设置读地址**/
#define DS3231_ADDRESS1 			0XD0
/**设置写地址**/
#define DS3231_ADDRESS2 			0XD1

#define u8		uint8_t
#define u16 	uint16_t


typedef struct
{
  uint32_t second;      
  uint32_t minute;     
  uint32_t hour;      
  uint32_t week;  
	uint32_t day; 
	uint32_t month; 
	uint32_t year; 
	uint32_t quantity;
} RTC_Time;

RTC_Time Time_ds3231 = {0x55, 0x16, 0x11, 0x05, 0x15, 0x10, 0x19};  //初始化时间结构体变量（设置时间：2019年10月12日 14:59:55  星期六）  
uint8_t  rtc_data[7]={0x50, 0x26, 0x20, 0x03, 0x16, 0x10, 0x19};       //通用数据缓存器  

u8 BCD2DEC(u8 val)   //BCD转换为Byte
{
    u8 i;
    i= val&0x0f;
    val >>= 4;
    val &= 0x0f;
    val *= 10;
    i += val;
    return i;
}

/* 写入时间 */  
void WriteTime(void)
{
	//if (HAL_I2C_Mem_Write(&hi2c2,DS3231_ADDRESS2,0x0,I2C_MEMADD_SIZE_8BIT,&rtc_data[0],7,1)==HAL_OK)
		;
}

/* 读取时间 */  
void read_rtc(void)  
{  
//  uint8_t battery[2];  
	char buffer1[16];
	char buffer2[30];
  if(HAL_I2C_Mem_Read(&hi2c2, DS3231_ADDRESS1, 0x00, I2C_MEMADD_SIZE_8BIT, &rtc_data[0], 7, 1) == HAL_OK) {  
    Time_ds3231.second = BCD2DEC(rtc_data[0] );  

    Time_ds3231.minute = BCD2DEC(rtc_data[1] );  

    Time_ds3231.hour = BCD2DEC(rtc_data[2] );  

    Time_ds3231.week = BCD2DEC(rtc_data[3] );  

    Time_ds3231.day = BCD2DEC(rtc_data[4]);  

    Time_ds3231.month = BCD2DEC(rtc_data[5] );  

    Time_ds3231.year = BCD2DEC(rtc_data[6]);  
		
  }  
  // 电量 0x1a 0x1b  
//  if(HAL_I2C_Mem_Read(&hi2c2, DS3231_ADDRESS1, 0x1b, 1, battery, 2, 1) == HAL_OK) {      
//    Time_ds3231.quantity = (battery[0] >> 7) * 255 + battery[1];  
//    printf("quality:%x\r\n",Time_sd3088.quantity);  
//  }
	printf("20%d-%d-%d,week%d,%d:%d:%d\n",Time_ds3231.year,Time_ds3231.month,Time_ds3231.day,
	Time_ds3231.week,Time_ds3231.hour,Time_ds3231.minute,Time_ds3231.second);
	
	sprintf(buffer1,"20%d-%d-%dweek%d",Time_ds3231.year,Time_ds3231.month,Time_ds3231.day,Time_ds3231.week);
	sprintf(buffer2,"%d : %d : %d ",Time_ds3231.hour,Time_ds3231.minute,Time_ds3231.second);
	OLED_P8x16Str(1,0,buffer1);
	OLED_P8x16Str(1,3,buffer2);
}  
//void write_rtc(RTC_Time *t)  
//{  
//  // 计算星期  
//  uint8_t y, m , d;  

//  y = t->year + 2000;  

//  m = t->month;  

//  d = t->day;  

//  if (m ==1 || m ==2) {  
//   m += 12;  //把一月和二月看成是上一年的十三月和十四月，例：如果是2004-1-10则换算成：2003-13-10来代入公式计算  
//		y--;  
//  }  
//  // 使用基姆拉尔森公式计算星期  

//  uint8_t week = (d + 2 * m + 3 * (m + 1) / 5 + y + y / 4 - y / 100 + y / 400) % 7;  

//  uint8_t data[7];  

//  data[0] = 0;  

//  data[1] = DEC2BCD(t->minute);  

//  data[2] = DEC2BCD(t->hour);  

//  data[3] = week;  

//  data[4] = DEC2BCD(t->day);  

//  data[5] = DEC2BCD(t->month);  

//  data[6] = DEC2BCD(t->year);  

//    

//  if (enable_write()) {  

//      

//    // 写时间数据      

//    if(HAL_I2C_Mem_Write(&hi2c2, DS3231_ADDRESS2, 0x0, 1, &data[0], 7, 1) == HAL_OK) {  

//      printf("saved time successful.\r\n");  

//    }  

//    else  

//      printf("saved time failure.\r\n");      

//    disable_write();  
//  }  
//}  

