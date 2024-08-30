#include "usart.h"

int fputc(int ch, FILE *f)
{      
	while(!(USART1->SR&(0X01<<7)));//循环发送,直到发送完毕
	USART1->DR=ch;//往内部写值
	return ch;//返回
}

//发送一位数据
void send_data(USART_TypeDef * USARTx,unsigned char data)
{
	while(!(USARTx->SR&(0X01<<7)));//循环发送,直到发送完毕
	USARTx->DR=data;//往内部写值
}

//发送多位数据
void USARTx_printf(USART_TypeDef * USARTx,char *str)
{	
	while(*(str) != '\0')
	{
		send_data(USARTx,*(str++));	
	}
}

//发送指定位数数据
void USARTx_send(USART_TypeDef * USARTx,char *str,unsigned int number)
{	
	for(;number;number--)
			send_data(USARTx,*(str++));	

}

