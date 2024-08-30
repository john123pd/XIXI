#include "stm32f4xx_it.h"

struct usart_buff usart1,usart2;

//�ⲿ�ж�0������
void EXTI0_IRQHandler(void)
{
	if(EXTI->PR & (0x01<<0))//�жϱ�־λ
	{	
		//�����־λ
		EXTI->PR |= 0x01<<0;//����жϱ�־λ��ST��

	}
}


//�ⲿ�ж�2������
void EXTI2_IRQHandler(void)
{
	if(EXTI->PR & (0x01<<2))//�жϱ�־λ
	{	
		//�����־λ
		EXTI->PR |= 0x01<<2;//����жϱ�־λ��ST��

	}
}


//�ⲿ�ж�3������
void EXTI3_IRQHandler(void)
{
	if(EXTI->PR & (0x01<<3))//�жϱ�־λ
	{	
		//�����־λ
		EXTI->PR |= 0x01<<3;//����жϱ�־λ��ST��

	}
}

//�ⲿ�ж�4������
void EXTI4_IRQHandler(void)
{
	if(EXTI->PR & (0x01<<4))//�жϱ�־λ
	{	
		//�����־λ
		EXTI->PR |= 0x01<<4;//����жϱ�־λ��ST��

	}
}



//����1�ж�
void USART1_IRQHandler(void)
{
	static unsigned int i=0;//���徲̬����   ��Ҫ���ڽ���ʱ�������ݷŵ���Ӧ��λ��
	if(USART1->SR&(0x01<<5))//�ж� �Ĵ�����Ϊ�յı�־ �����ж�
	{
			usart1.RXbuff[i++]=USART1->DR; //����ֵ���ŵ���Ӧλ����
	}

	else if(USART1->SR&(0x01<<4)) //�ж� ���� ʱ��֤���������
	{
		USART1->DR; //�����־λ    
		USART1->SR; //�����־λ  
		i=0;        //Ϊ��һ�ν����ж���׼��
		usart1.read=1;  //��־λ����ʾ�Ƿ�������   1    0
	}
}


//����1�ж�
void USART2_IRQHandler(void)
{
	static unsigned int i=0;//���徲̬����   ��Ҫ���ڽ���ʱ�������ݷŵ���Ӧ��λ��
	if(USART2->SR&(0x01<<5))//�ж� �Ĵ�����Ϊ�յı�־ �����ж�
	{
			usart2.RXbuff[i++]=USART2->DR; //����ֵ���ŵ���Ӧλ����
	}

	else if(USART2->SR&(0x01<<4)) //�ж� ���� ʱ��֤���������
	{
		USART2->DR; //�����־λ  
		USART1->SR; //�����־λ  		
		i=0;        //Ϊ��һ�ν����ж���׼��
		usart2.read=1;  //��־λ����ʾ�Ƿ�������   1    0    2��ʾ����
	}
}

