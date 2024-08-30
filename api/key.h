#ifndef __KEY_H
#define __KEY_H

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

#include "stdarg.h"
#include "stdlib.h"
#include "stdio.h"

/*°´¼üÏû¶¶¼ì²é*/
unsigned int key_press_while_one(GPIO_TypeDef *GPIOx,unsigned int Pin,unsigned int Idle,void (*delay)(unsigned int),unsigned int *temp);
unsigned int key_loose_while_one(GPIO_TypeDef *GPIOx,unsigned int Pin,unsigned int Idle);
unsigned int key_press_while_always(GPIO_TypeDef *GPIOx,unsigned int Pin,unsigned int Idle,void (*delay)(unsigned int));
unsigned int key_pressloose_one(GPIO_TypeDef *GPIOx,unsigned int Pin,unsigned int Idle,unsigned int *temp);

#endif

