#include "stm32f4xx_it.h"

struct usart_buff usart1,usart2;

//外部中断0处理函数
void EXTI0_IRQHandler(void)
{
	if(EXTI->PR & (0x01<<0))//判断标志位
	{	
		//清除标志位
		EXTI->PR |= 0x01<<0;//清除中断标志位（ST）

	}
}


//外部中断2处理函数
void EXTI2_IRQHandler(void)
{
	if(EXTI->PR & (0x01<<2))//判断标志位
	{	
		//清除标志位
		EXTI->PR |= 0x01<<2;//清除中断标志位（ST）

	}
}


//外部中断3处理函数
void EXTI3_IRQHandler(void)
{
	if(EXTI->PR & (0x01<<3))//判断标志位
	{	
		//清除标志位
		EXTI->PR |= 0x01<<3;//清除中断标志位（ST）

	}
}

//外部中断4处理函数
void EXTI4_IRQHandler(void)
{
	if(EXTI->PR & (0x01<<4))//判断标志位
	{	
		//清除标志位
		EXTI->PR |= 0x01<<4;//清除中断标志位（ST）

	}
}



//串口1中断
void USART1_IRQHandler(void)
{
	static unsigned int i=0;//定义静态变量   主要用于接收时，将数据放到对应的位置
	if(USART1->SR&(0x01<<5))//判断 寄存器不为空的标志 进的中断
	{
			usart1.RXbuff[i++]=USART1->DR; //接收值，放到对应位置上
	}

	else if(USART1->SR&(0x01<<4)) //判断 空闲 时，证明接收完成
	{
		USART1->DR; //清除标志位    
		USART1->SR; //清除标志位  
		i=0;        //为下一次进入中断做准备
		usart1.read=1;  //标志位，表示是否接受完成   1    0
	}
}


//串口1中断
void USART2_IRQHandler(void)
{
	static unsigned int i=0;//定义静态变量   主要用于接收时，将数据放到对应的位置
	if(USART2->SR&(0x01<<5))//判断 寄存器不为空的标志 进的中断
	{
			usart2.RXbuff[i++]=USART2->DR; //接收值，放到对应位置上
	}

	else if(USART2->SR&(0x01<<4)) //判断 空闲 时，证明接收完成
	{
		USART2->DR; //清除标志位  
		USART1->SR; //清除标志位  		
		i=0;        //为下一次进入中断做准备
		usart2.read=1;  //标志位，表示是否接受完成   1    0    2表示接收
	}
}

