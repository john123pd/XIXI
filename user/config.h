#ifndef __CONFIG_H
#define __CONFIG_H

#include "main.h"

void LED_config(void);
void KEY_config(void);
void BUZZER_config(void);
void EXTI_key_config(void);
void EXTI_ruan_config(void);
void USART1_config(unsigned int band);
void USART2_config(unsigned int band);


#endif

