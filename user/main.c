#include "main.h"

void key_while_one(unsigned int key,void (*p)(void),unsigned int* flag,unsigned int* one)
{
		if(key && *flag==0 && *one==0)
		{
			*flag=1;
			*one=1;
		}
		else if(*flag && *one)
		{
			(*p)();
			*one=0;
		}
		else if(*flag && *one==0 && key==0)
		{
			*flag=0;
		}
}


//����PE2���ⲿ�ж�����������
int main(void)
{
	NVIC_SetPriorityGrouping(7-2);
	LED_config();
	USART2_config(115200);
	EXTI_key_config();
 // EXTI_ruan_config();
	USART1_config(115200);
	BUZZER_config();//��������ʼ��
//	set_time(1000000);//����1s��1000000��ѭ��
	delay_sys_ms(1);
	USARTx_printf(USART1,"���");
	while(1)
	{		
		
		
		static uint32_t last_tick_task1 = 0;
        static uint32_t last_tick_task2 = 0;
        uint32_t current_tick = SysTick_Time;  // ��ȡ��ǰϵͳʱ��

        if (current_tick - last_tick_task1 >= 5000) 
		{  // ����1��ÿ1000 msִ��һ��
            last_tick_task1 = current_tick;
            led_inversion(GPIOC,4);  // ִ������1
			printf("444\r\n");
        }

        if (current_tick - last_tick_task2 >= 1000)
		{  // ����2��ÿ500 msִ��һ��
            last_tick_task2 = current_tick;
            led_inversion(GPIOC,5);  // ִ������2
			printf("555\r\n");
        }
//		if(!(time_slice.now%999999))
//		{
//			printf("1s��\r\n");
//		}
//		
//		if(!(time_slice.now%499999))
//		{
//			led_inversion(GPIOC,4);
//		}
		
	}
	
}


