#include "usart.h"

int fputc(int ch, FILE *f)
{      
	while(!(USART1->SR&(0X01<<7)));//ѭ������,ֱ���������
	USART1->DR=ch;//���ڲ�дֵ
	return ch;//����
}

//����һλ����
void send_data(USART_TypeDef * USARTx,unsigned char data)
{
	while(!(USARTx->SR&(0X01<<7)));//ѭ������,ֱ���������
	USARTx->DR=data;//���ڲ�дֵ
}

//���Ͷ�λ����
void USARTx_printf(USART_TypeDef * USARTx,char *str)
{	
	while(*(str) != '\0')
	{
		send_data(USARTx,*(str++));	
	}
}

//����ָ��λ������
void USARTx_send(USART_TypeDef * USARTx,char *str,unsigned int number)
{	
	for(;number;number--)
			send_data(USARTx,*(str++));	

}

