#include "key.h"

uint8_t Key_scan(void)
{
	uint8_t key = 2;
	if(KEY1 == 0||KEY2 == 0)
	{
		HAL_Delay(10);
		if(KEY1==0)		key = 0;	
		if(KEY2==0)		key = 1;	
	}
	
	return key;	
}
