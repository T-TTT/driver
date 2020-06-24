#include "74HC595.h"

void HC595Send_Data(uint8_t date)
{
	uint8_t i;
	for(i=0;i<8;i++)
	{
		if ((date<<i)&0x80)
			SPI_MOSI_1;
		else 
			SPI_MOSI_0;
		
		SPI_CLK_0;
		SPI_CLK_1;
		SPI_CLK_0;
	}
	SPI_NSS_LCD_0;
	SPI_NSS_LCD_1;
	SPI_NSS_LCD_0;
}

