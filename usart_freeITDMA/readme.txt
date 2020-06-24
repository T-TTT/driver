此例程为串口中断DMA接收

空闲中断是一包数据结束会触发的中断。
DMA buf 接收数据（实现高速运转）
串口buf转存数据（便于用户处理）
可以保留两条数据的缓存（相对保证数据不丢包）


	memset(Usart2type.Usart2RecBuffer,0,USART2_REC_SIE);
        	HAL_UART_Transmit(&huart2,(uint8_t*)"AT+CSQ\r\n",8,0xff);
	printf("发送数据: AT+CSQ\r\n");
      	HAL_Delay(500);
      	if(Usart2type.UsartRecFlag == 1)
       	 {
            	printf("接收数据:%s\r\n",Usart2type.Usart2RecBuffer);
            	Usart2type.UsartRecFlag = 0;  //清空接收标志位
            	Usart2type.UsartRecLen = 0;   //清空接收长度
        	}