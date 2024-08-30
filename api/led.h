#ifndef __LED_H
#define __LED_H

#define STM32F4xx defined (STM32F40_41xxx) || defined (STM32F427_437xx) || defined (STM32F429_439xx) || defined (STM32F401xx) || defined (STM32F411xE)
#define STM32F10x defined (STM32F10X_LD) || defined (STM32F10X_LD_VL) || defined (STM32F10X_MD) || defined (STM32F10X_MD_VL) || defined (STM32F10X_HD) || defined (STM32F10X_HD_VL) || defined (STM32F10X_XL) || defined (STM32F10X_CL) 

#if STM32F4xx 
	#include "stm32f4xx.h"
#elif STM32F10x
	#include "stm32f10x.h"
#endif

#ifdef USE_BITIO_DRIVER
	#include "bitio.h"	
#endif

#ifdef USE_FIELD_DRIVER
	#include "bitfield.h"	
#endif

/*ÆÕÍ¨LEDµÆ¿ØÖÆº¯Êý*/
void led_illume(GPIO_TypeDef *GPIOx,unsigned int Pin,unsigned int Idle,unsigned char key);
void led_inversion(GPIO_TypeDef *GPIOx,unsigned int Pin);
/*ÉÁË¸µÆ¿ØÖÆº¯Êý*/
void led_while_glint(GPIO_TypeDef *GPIOx,unsigned int Pin,void (*delay)(unsigned int),unsigned int glint_time);
#endif

