#ifndef __STM32F4xx_IT_H
#define __STM32F4xx_IT_H

#include "main.h"


void EXTI9_5_IRQHandler(void);
void EXTI0_IRQHandler(void);
void EXTI2_IRQHandler(void);
void EXTI3_IRQHandler(void);
void EXTI4_IRQHandler(void);
void USART1_IRQHandler(void);
void USART2_IRQHandler(void);

extern struct usart_buff usart1,usart2;

struct usart_buff{
	unsigned char TXbuff[1024];
	unsigned char RXbuff[1024];
	unsigned int read;
	unsigned int send;
};




#endif

