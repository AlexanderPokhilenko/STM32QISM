#include "UART.h"
#include "delay.h"

GPIO_InitTypeDef port;
USART_InitTypeDef usart;

void InitializeUART(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
 
    GPIO_StructInit(&port);
    port.GPIO_Mode = GPIO_Mode_AF_PP;
    port.GPIO_Pin = GPIO_Pin_9;
    port.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOA, &port);
 
    port.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    port.GPIO_Pin = GPIO_Pin_10;
    port.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOA, &port);
 
    USART_StructInit(&usart);
    usart.USART_BaudRate = BAUDRATE;
    USART_Init(USART1, &usart);
    USART_Cmd(USART1, ENABLE);
		USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    NVIC_EnableIRQ(USART1_IRQn);
}

void UART_SendArray(char data[], size_t count)
{
	for(size_t i=0; i<count; i++)
	{
		USART_SendData(USART1,data[i]);
		delay_ms(2);
	}
}

void UART_SendSingle(uint16_t data)
{
	char buff[10]={0,0,0,0,0,0,0,0,0,0};
	sprintf(buff,"%d\r\n",data);
	int i=0;
	while(buff[i]!=0 && i<10)
	{
		USART_SendData(USART1,buff[i]);
		delay_ms(2);
		i++;
	}
}

void UART_SendSingleAsBytes(uint16_t data)
{
	uint8_t lsb = data & 0xff;
	uint8_t msb = data >> 8;
	
	USART_SendData(USART1, lsb);
	delay_ms(2);
	USART_SendData(USART1, msb);
	/*
	delay_ms(2);
	USART_SendData(USART1, '\r');
	delay_ms(2);
	USART_SendData(USART1, '\n');
	*/
}

void USART1_IRQHandler()
{
	if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{	
		UART_HandleReceived(USART_ReceiveData(USART1));
	}
}
