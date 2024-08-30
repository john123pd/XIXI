#include "delay.h"

volatile  uint32_t SysTick_Time = 0;  
/*
功能：空操作延时1us
作者：YKY
参数：无
返回值：无
备注：标准1us的延时，支持F4全系列
*/
static void delay_nop_1us(void)
{
	#if defined(STM32F401xx) || defined (STM32F411xE) || defined (STM32F427_437xx) || defined (STM32F429_439xx) || defined (STM32F40_41xxx)
	__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
	__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
	__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
	__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
	__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
	__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
	__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
	__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
	__NOP();__NOP();__NOP();__NOP();
	#endif
	
	#if defined (STM32F411xE) || defined (STM32F427_437xx) || defined (STM32F429_439xx) || defined (STM32F40_41xxx)
	__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
	__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();	
	#endif
	
	#if defined (STM32F427_437xx) || defined (STM32F429_439xx) || defined (STM32F40_41xxx)
	__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
	__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
	__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
	__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
	__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
	__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
	__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();	
	#endif

	#if defined (STM32F429_439xx) || defined (STM32F40_41xxx)
	__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
	__NOP();__NOP();	
	#endif	
}


/*
功能：空操作延时us
作者：YKY
参数：unsigned int time：延时us的时间
返回值：无
备注：非标准
*/
void delay_nop_us(unsigned int time)
{
	while(time--)
		delay_nop_1us();
}

/*
功能：空操作延时ms
作者：YKY
参数：unsigned int time：延时ms的时间
返回值：无
备注：非标准
*/
void delay_nop_ms(unsigned int time)
{
	while(time--)
		delay_nop_us(1000);
}

/*
功能：循环延时us
作者：YKY
参数：unsigned int time：延时us的时间
返回值：无
备注：非标准
*/
void delay_com_us(unsigned int time)
{
	unsigned int i=SystemCoreClock/1000000/4*time;
	while(i--);//4个机械周期+转跳 共4个 1us需执行SystemCoreClock/1000000/4次
}

/*
功能：循环延时ms
作者：YKY
参数：unsigned int time：延时ms的时间
返回值：无
备注：非标准
*/
void delay_com_ms(unsigned int time)
{
	unsigned int i=SystemCoreClock/1000/4*time;
	while(i--);//4个机械周期+转跳 共4个 1us需执行SystemCoreClock/1000000/4次
}



unsigned int Sys_time;
struct time time_slice;//时间片结构体
/*
功能：系统滴答延时us
作者：YKY
参数：unsigned int time：延时us的时间
返回值：无
备注：非标准
*/
void delay_sys_us(unsigned int time)
{
	//打开系统滴答定时器
	SysTick->CTRL |= 0x03<<1;//打开中断，选择时钟源AHB
	SysTick->LOAD |=SystemCoreClock/1000000/(SysTick->CTRL&(0x01<<2)?1:8)    ;//1us
	SysTick->VAL = 0;//手动清除
	NVIC_SetPriority(SysTick_IRQn,\
		NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1,1));//设置优先级
	SysTick->CTRL |=0x01<<0;//开定时器
	Sys_time=time;
	while(Sys_time);
	if(!time_slice.en_falg)
		SysTick->CTRL &=~(0x01<<0);//关定时器
}

/*
功能：系统滴答延时ms
作者：YKY
参数：unsigned int time：延时ms的时间
返回值：无
备注：非标准
*/
void delay_sys_ms(unsigned int time)
{
	SysTick_Config(SystemCoreClock / 1000);
//	//打开系统滴答定时器
//	SysTick->CTRL |= 0x03<<1;//打开中断，选择时钟源AHB
//	SysTick->LOAD |=SystemCoreClock/1000;//赋值
//	SysTick->VAL = 0;//手动清除
//	NVIC_SetPriority(SysTick_IRQn,\
//		NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1,1));//设置优先级
//	SysTick->CTRL |=0x01<<0;//开定时器
//	Sys_time=time;
//	while(Sys_time);
//	if(!time_slice.en_falg)
//		SysTick->CTRL &=~(0x01<<0);//关定时器
}



/*
功能：系统滴答设置时间片
作者：YKY
参数：
unsigned int max:时间片最大值 单位us
返回值：无
备注：非标准
*/
void set_time(unsigned int max)
{
	time_slice.max=max;
	time_slice.en_falg=1;
	time_slice.now=0;
	//打开系统滴答定时器
	SysTick->CTRL |= 0x03<<1;//打开中断，选择时钟源AHB
	SysTick->LOAD |=SystemCoreClock/1000000;//赋值
	SysTick->VAL = 0;//手动清除
	NVIC_SetPriority(SysTick_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1,1));//设置优先级
	SysTick->CTRL |=0x01<<0;//开定时器
}

/*
系统滴答中断函数
包含时间片方式
*/

void SysTick_Handler(void)
{
//	if(time_slice.en_falg)
//	{
//		if(time_slice.now<time_slice.max)
//			time_slice.now++;
//		else
//			time_slice.now=0;
//	}
//	if(Sys_time)
//	
	   SysTick_Time++; 
}
