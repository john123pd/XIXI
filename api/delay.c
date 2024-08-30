#include "delay.h"

volatile  uint32_t SysTick_Time = 0;  
/*
���ܣ��ղ�����ʱ1us
���ߣ�YKY
��������
����ֵ����
��ע����׼1us����ʱ��֧��F4ȫϵ��
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
���ܣ��ղ�����ʱus
���ߣ�YKY
������unsigned int time����ʱus��ʱ��
����ֵ����
��ע���Ǳ�׼
*/
void delay_nop_us(unsigned int time)
{
	while(time--)
		delay_nop_1us();
}

/*
���ܣ��ղ�����ʱms
���ߣ�YKY
������unsigned int time����ʱms��ʱ��
����ֵ����
��ע���Ǳ�׼
*/
void delay_nop_ms(unsigned int time)
{
	while(time--)
		delay_nop_us(1000);
}

/*
���ܣ�ѭ����ʱus
���ߣ�YKY
������unsigned int time����ʱus��ʱ��
����ֵ����
��ע���Ǳ�׼
*/
void delay_com_us(unsigned int time)
{
	unsigned int i=SystemCoreClock/1000000/4*time;
	while(i--);//4����е����+ת�� ��4�� 1us��ִ��SystemCoreClock/1000000/4��
}

/*
���ܣ�ѭ����ʱms
���ߣ�YKY
������unsigned int time����ʱms��ʱ��
����ֵ����
��ע���Ǳ�׼
*/
void delay_com_ms(unsigned int time)
{
	unsigned int i=SystemCoreClock/1000/4*time;
	while(i--);//4����е����+ת�� ��4�� 1us��ִ��SystemCoreClock/1000000/4��
}



unsigned int Sys_time;
struct time time_slice;//ʱ��Ƭ�ṹ��
/*
���ܣ�ϵͳ�δ���ʱus
���ߣ�YKY
������unsigned int time����ʱus��ʱ��
����ֵ����
��ע���Ǳ�׼
*/
void delay_sys_us(unsigned int time)
{
	//��ϵͳ�δ�ʱ��
	SysTick->CTRL |= 0x03<<1;//���жϣ�ѡ��ʱ��ԴAHB
	SysTick->LOAD |=SystemCoreClock/1000000/(SysTick->CTRL&(0x01<<2)?1:8)    ;//1us
	SysTick->VAL = 0;//�ֶ����
	NVIC_SetPriority(SysTick_IRQn,\
		NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1,1));//�������ȼ�
	SysTick->CTRL |=0x01<<0;//����ʱ��
	Sys_time=time;
	while(Sys_time);
	if(!time_slice.en_falg)
		SysTick->CTRL &=~(0x01<<0);//�ض�ʱ��
}

/*
���ܣ�ϵͳ�δ���ʱms
���ߣ�YKY
������unsigned int time����ʱms��ʱ��
����ֵ����
��ע���Ǳ�׼
*/
void delay_sys_ms(unsigned int time)
{
	SysTick_Config(SystemCoreClock / 1000);
//	//��ϵͳ�δ�ʱ��
//	SysTick->CTRL |= 0x03<<1;//���жϣ�ѡ��ʱ��ԴAHB
//	SysTick->LOAD |=SystemCoreClock/1000;//��ֵ
//	SysTick->VAL = 0;//�ֶ����
//	NVIC_SetPriority(SysTick_IRQn,\
//		NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1,1));//�������ȼ�
//	SysTick->CTRL |=0x01<<0;//����ʱ��
//	Sys_time=time;
//	while(Sys_time);
//	if(!time_slice.en_falg)
//		SysTick->CTRL &=~(0x01<<0);//�ض�ʱ��
}



/*
���ܣ�ϵͳ�δ�����ʱ��Ƭ
���ߣ�YKY
������
unsigned int max:ʱ��Ƭ���ֵ ��λus
����ֵ����
��ע���Ǳ�׼
*/
void set_time(unsigned int max)
{
	time_slice.max=max;
	time_slice.en_falg=1;
	time_slice.now=0;
	//��ϵͳ�δ�ʱ��
	SysTick->CTRL |= 0x03<<1;//���жϣ�ѡ��ʱ��ԴAHB
	SysTick->LOAD |=SystemCoreClock/1000000;//��ֵ
	SysTick->VAL = 0;//�ֶ����
	NVIC_SetPriority(SysTick_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1,1));//�������ȼ�
	SysTick->CTRL |=0x01<<0;//����ʱ��
}

/*
ϵͳ�δ��жϺ���
����ʱ��Ƭ��ʽ
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
