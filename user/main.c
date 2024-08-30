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


//按键PE2，外部中断驱动蜂鸣器
int main(void)
{
	NVIC_SetPriorityGrouping(7-2);
	LED_config();
	USART2_config(115200);
	EXTI_key_config();
 // EXTI_ruan_config();
	USART1_config(115200);
	BUZZER_config();//蜂鸣器初始化
//	set_time(1000000);//设置1s有1000000份循环
	delay_sys_ms(1);
	USARTx_printf(USART1,"你好");
	while(1)
	{		
		
		
		static uint32_t last_tick_task1 = 0;
        static uint32_t last_tick_task2 = 0;
        uint32_t current_tick = SysTick_Time;  // 获取当前系统时间

        if (current_tick - last_tick_task1 >= 5000) 
		{  // 任务1：每1000 ms执行一次
            last_tick_task1 = current_tick;
            led_inversion(GPIOC,4);  // 执行任务1
			printf("444\r\n");
        }

        if (current_tick - last_tick_task2 >= 1000)
		{  // 任务2：每500 ms执行一次
            last_tick_task2 = current_tick;
            led_inversion(GPIOC,5);  // 执行任务2
			printf("555\r\n");
        }
//		if(!(time_slice.now%999999))
//		{
//			printf("1s到\r\n");
//		}
//		
//		if(!(time_slice.now%499999))
//		{
//			led_inversion(GPIOC,4);
//		}
		
	}
	
}


