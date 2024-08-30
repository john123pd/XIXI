#ifndef __USART_H
#define __USART_H

#define STM32F4xx defined (STM32F40_41xxx) || defined (STM32F427_437xx) || defined (STM32F429_439xx) || defined (STM32F401xx) || defined (STM32F411xE)
#define STM32F10x defined (STM32F10X_LD) || defined (STM32F10X_LD_VL) || defined (STM32F10X_MD) || defined (STM32F10X_MD_VL) || defined (STM32F10X_HD) || defined (STM32F10X_HD_VL) || defined (STM32F10X_XL) || defined (STM32F10X_CL) 

#if STM32F4xx 
	#include "stm32f4xx.h"
#elif STM32F10x
	#include "stm32f10x.h"
#endif

#include "stdio.h"
#include "string.h" //字符串操作函数
#include "stdlib.h"  //空间类操作函数




void send_data(USART_TypeDef * USARTx,unsigned char data);
void USARTx_printf(USART_TypeDef * USARTx,char *str);
void USARTx_send(USART_TypeDef * USARTx,char *str,unsigned int number);




#endif

