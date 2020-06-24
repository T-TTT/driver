#include "LEDMatrix.h"
#include "stm32l0xx_hal.h"

//д�����������
void MBI_WriteData(uint16_t data)
{
	uint8_t i;
	for(i = 0;i < 16;i++)
	{
		if((data >> 15) & 1)		
		HAL_GPIO_WritePin(DATA_GPIO_Port, DATA_Pin, GPIO_PIN_SET);
		else 	HAL_GPIO_WritePin(DATA_GPIO_Port, DATA_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(CLK_GPIO_Port, CLK_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(CLK_GPIO_Port, CLK_Pin, GPIO_PIN_RESET);
		data <<= 1;
	}
	HAL_GPIO_WritePin(LE_GPIO_Port, LE_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LE_GPIO_Port, LE_Pin, GPIO_PIN_RESET);
}

//д�����������
void Matrix_595(uint16_t data)
{
	uint8_t i;

	for(i = 0;i<16;i++)
	{
		if(((data >> 15) & 1 )== 1)
			HAL_GPIO_WritePin(DATA_GPIO_Port, DATA_Pin, GPIO_PIN_SET);
		else 	HAL_GPIO_WritePin(DATA_GPIO_Port, DATA_Pin, GPIO_PIN_RESET);
		
		data <<= 1;
		
		HAL_GPIO_WritePin(CLK_GPIO_Port, CLK_Pin, GPIO_PIN_SET);

		HAL_GPIO_WritePin(CLK_GPIO_Port, CLK_Pin, GPIO_PIN_RESET);

	}
	HAL_GPIO_WritePin(DZ_LOAD_GPIO_Port, DZ_LOAD_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(DZ_LOAD_GPIO_Port, DZ_LOAD_Pin, GPIO_PIN_RESET);
}

//���Ե���
void test(void)
{
	uint8_t i;
	MBI_WriteData(0xffff);
	for(i = 0;i < 16;i++)
	{
		Matrix_595(1<<i);

		HAL_Delay(50);
	}
	Matrix_595(0xffff);
	for(i = 0;i < 16;i++)
	{
		MBI_WriteData(1<<i);

		HAL_Delay(50);
	}
}

