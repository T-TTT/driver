/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usart.h"
#include "gpio.h"
#include "lcd.h"
#include "stdio.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE BEGIN Includes */
extern uint8_t data[];
extern uint8_t data2[];
#define LEDON	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET);
#define LEDOFF	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);
#define buffersize  11
#define REC_LENGTH  1
#define MAX_REC_LENGTH  1024 
//uint8_t aRxBuffer[100];
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
int fputc (int ch, FILE *fp)
{
		HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, 10);
		return ch;
}
uint8_t aTxBuffer[]={"hello world\r\n"};
uint8_t aTx1Buffer[]={"led open\r\n"};
uint8_t aTx2Buffer[]={"led close\r\n"};
uint8_t aRxBuffer;
uint8_t aRxBuffer1[MAX_REC_LENGTH];
uint8_t size = 0;
uint8_t flag = 0;
//UART.c
unsigned char UART1_Rx_Buf[MAX_REC_LENGTH] = {0}; //USART1存储接收数据
unsigned char UART1_Rx_flg = 0;                   //USART1接收完成标志
unsigned int  UART1_Rx_cnt = 0;                   //USART1接受数据计数器
unsigned char UART1_temp[REC_LENGTH] = {0};       //USART1接收数据缓存


/* USER CODE END PTD */
//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
//	if(huart -> Instance == USART2 ) {
//		if(aRxBuffer == 'a')
//		{
//			LEDON;
//			printf("%s",aTx1Buffer);
//		}
//		else if(aRxBuffer == 0xa2)
//		{
//			LEDOFF;
//			printf("%s",aTx2Buffer);

//		}
//			HAL_UART_Receive_IT(&huart2, &aRxBuffer, 1);		
//}
//}

//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
//	if(huart -> Instance == USART2 ) {
//		if(aRxBuffer == 0xa1)
//		{
//			LEDON;
//			printf("%s",aTx1Buffer);
//		}
//		else if(aRxBuffer == 0xa2)
//		{
//			LEDOFF;
//			printf("%s",aTx2Buffer);

//		}
//		HAL_UART_Receive_IT(&huart2, &aRxBuffer, 1);		
//}
//}

//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {

//	UNUSED(huart);
//	
//	HAL_UART_Transmit(&huart2,(uint8_t*)aRxBuffer1,10,0xFFFF);
//	HAL_UART_Receive_IT(&huart2,(uint8_t*)aRxBuffer1,10);
//}

//字符串
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if(huart->Instance==USART2)
  {
    UART1_Rx_Buf[UART1_Rx_cnt] = UART1_temp[0];
    UART1_Rx_cnt++;
    if(0x0a == UART1_temp[0])
    {
      UART1_Rx_flg = 1;
    }
    HAL_UART_Receive_IT(&huart2,(uint8_t *)UART1_temp,REC_LENGTH);
  }
}
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
	LCDInit();
  /* USER CODE END 2 */
	LCD_IMG(data2);
	
	Clear_Draw();
	LCD_display(0,0,"haha");
	//字符
	printf("%s",aTxBuffer);
	//HAL_UART_Receive_IT(&huart2, &aRxBuffer, 1);

	
	//字符串
	HAL_UART_Receive_IT(&huart2,(uint8_t *)UART1_temp,REC_LENGTH);
	
//	HAL_UART_Receive_IT(&huart2,(uint8_t*)aRxBuffer1,10);
  /* Infinite loop */
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
	//字符串
    if(UART1_Rx_flg)
    {
      HAL_UART_Transmit(&huart2,UART1_Rx_Buf,UART1_Rx_cnt,0x10);    //发送接收到的数据
      for(int i = 0;i<UART1_Rx_cnt;i++)
        UART1_Rx_Buf[i] = 0;
      UART1_Rx_cnt = 0;
      UART1_Rx_flg = 0;
    }   
    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Configure the main internal regulator output voltage 
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLLMUL_8;
  RCC_OscInitStruct.PLL.PLLDIV = RCC_PLLDIV_2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART2;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
