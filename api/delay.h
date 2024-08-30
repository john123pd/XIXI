#ifndef __DELAY_H
#define __DELAY_H

#define STM32F4xx defined (STM32F40_41xxx) || defined (STM32F427_437xx) || defined (STM32F429_439xx) || defined (STM32F401xx) || defined (STM32F411xE)
#define STM32F10x defined (STM32F10X_LD) || defined (STM32F10X_LD_VL) || defined (STM32F10X_MD) || defined (STM32F10X_MD_VL) || defined (STM32F10X_HD) || defined (STM32F10X_HD_VL) || defined (STM32F10X_XL) || defined (STM32F10X_CL) 

#if STM32F4xx 
	#include "stm32f4xx.h"
#elif STM32F10x
	#include "stm32f10x.h"
#endif

/*时间片结构体*/
struct time{
	unsigned int now;//当前时间
	unsigned int max;//时间片最大值
	unsigned int en_falg;//是否启用时间片
};

extern struct time time_slice;

void set_time(unsigned int max);

void delay_nop_us(unsigned int time);
void delay_nop_ms(unsigned int time);

void delay_com_us(unsigned int time);
void delay_com_ms(unsigned int time);

void delay_sys_us(unsigned int time);
void delay_sys_ms(unsigned int time);


extern volatile uint32_t SysTick_Time;


#endif

