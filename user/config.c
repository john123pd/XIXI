/*
	�ļ���config_V0.0.1
	��飺���ļ�����XYD_Foundation��ĳ�ʼ������
	����оƬ��STM32F407VGT6
	���ܣ���ʼ������
	�궨�壺
	ע�⣺
	�������ڣ�
*/
#include "config.h"

/*
�������ܣ���ʼ��LED��
�β��б�void
��������ֵ��void
ע�⣺
	PC4,PC5,PC6,PC7
*/
void LED_config(void)
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;//��ʼ��ʱ��
	GPIOC->MODER   &= ~((0x03<<(4*2))|(0x03<<(5*2))|(0x03<<(6*2))|(0x03<<(7*2)));   //�����ģʽ
	GPIOC->MODER   |= ((0x01<<(4*2))|(0x01<<(5*2))|(0x01<<(6*2))|(0x01<<(7*2)));    //���������ģʽ
	GPIOC->OTYPER  &= ~((0x01<<(4))|(0x01<<(5))|(0x01<<(6))|(0x01<<(7)));       //��������
	GPIOC->PUPDR   &= ~((0x03<<(4*2))|(0x03<<(5*2))|(0x03<<(6*2))|(0x03<<(7*2)));   //������������
	GPIOC->OSPEEDR &= ~((0x03<<(4*2))|(0x03<<(5*2))|(0x03<<(6*2))|(0x03<<(7*2)));   //����ٶ�
	GPIOC->OSPEEDR |= ((0x03<<(4*2)) |(0x03<<(5*2))|(0x03<<(6*2))|(0x03<<(7*2)));    //��������ٶ�	
	led_illume(GPIOC,4,1,0);
	led_illume(GPIOC,5,1,0);	
	led_illume(GPIOC,6,1,0);	
	led_illume(GPIOC,7,1,0);
}

/*
�������ܣ���ʼ������
�β��б�void
��������ֵ��void
ע�⣺
	PA0,PE2,PE3,PE4
*/
void KEY_config(void)
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN|RCC_AHB1ENR_GPIOEEN;//��ʼ��ʱ��
	GPIOE->MODER   &= ~(0x03<<(2*2)|(0x03<<(3*2))|(0x03<<(4*2)));   //����Ϊ����ģʽ
	GPIOE->PUPDR   &= ~(0x03<<(2*2)|(0x03<<(3*2))|(0x03<<(4*2)));   //������������	
	GPIOA->MODER   &= ~(0x03<<(2*0));
	GPIOA->PUPDR   &= ~(0x03<<(2*0));
}

/*
�������ܣ�������
�β��б�void
��������ֵ��void
ע�⣺
	PE0
*/
void BUZZER_config(void)
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
	GPIOE->MODER   &= ~(0x03<<(0*2));   //�����ģʽ
	GPIOE->MODER   |= (0x01<<(0*2));    //���������ģʽ
	GPIOE->OTYPER  &= ~(0x01<<(0));       //��������
	GPIOE->PUPDR   &= ~(0x03<<(0*2));   //������������
	GPIOE->OSPEEDR &= ~(0x03<<(0*2));   //����ٶ�
	GPIOE->OSPEEDR |= (0x03<<(0*2));    //��������ٶ�	
	led_illume(GPIOE,0,0,0);
}

/*
�������ܣ��ⲿ�жϳ�ʼ����������
�β��б�void
��������ֵ��void
ע�⣺
	PA0 PE2 PE3 PE4
*/
void EXTI_key_config(void)
{
	RCC->AHB1ENR |=RCC_AHB1ENR_GPIOAEN|RCC_AHB1ENR_GPIOEEN;//��GPIOA,GPIOE��ʱ��
	RCC->APB2ENR|=RCC_APB2ENR_SYSCFGEN;//��SYSCFGʱ��	
	//GPIO������
	GPIOA->MODER &= ~(0X03<<(2*0));//����GPIOA����0����Ϊ����ģʽ
	GPIOA->PUPDR &= ~(0X03<<(2*0));//����GPIOA--0������������
	GPIOE->MODER &= ~((0X03<<(2*2))|(0X03<<(2*3))|(0X03<<(2*4)));//����GPIOE����2����Ϊ����ģʽ
	GPIOE->PUPDR &= ~((0X03<<(2*2))|(0X03<<(2*3))|(0X03<<(2*4)));//����GPIOE--2������������
	//ϵͳ���ÿ�����������
	SYSCFG->EXTICR[0] &=~(((0x0f)<<((0%4)*4))|((0x0f)<<((2%4)*4))|((0x0f)<<((3%4)*4))); //���SYSCFG��EXTI����
	SYSCFG->EXTICR[0] |=((0x04)<<((2%4)*4))|((0x04)<<((3%4)*4));//SYSCFG��EXTI2�������ӵ�GPIOE��
	SYSCFG->EXTICR[4/4] &=~((0x0f)<<((4%4)*4)); //���SYSCFG��EXTI����
	SYSCFG->EXTICR[4/4] |=((0x04)<<((4%4)*4));//SYSCFG��EXTI4�������ӵ�GPIOE��	
	//����EXTI�Ĵ���
	EXTI->IMR |=((0X01<<2)|(0X01<<4)|(0X01<<3)|(0X01<<0));//�ж����μĴ����������жϣ�
	EXTI->EMR &=~((0X01<<2)|(0X01<<4)|(0X01<<3)|(0X01<<0));//�¼����μĴ��������¼���
	EXTI->FTSR |=((0X01<<2)|(0X01<<4)|(0X01<<3)) ;//���½��ؼĴ�������·����������Ϊ�ߣ�����ʱ�Ǹߵ�ƽ�л�Ϊ�͵�ƽ,�½��أ�
	EXTI->RTSR |=((0X01<<0));//��EXTI0�������ؼĴ���(���е�ƽ�ͣ�����Ϊ�ߣ�������)
	//����NVIC
	NVIC_SetPriority(EXTI2_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),2,2));
	NVIC_SetPriority(EXTI3_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),2,2));
	NVIC_SetPriority(EXTI4_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),2,2));
	NVIC_SetPriority(EXTI0_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),2,2));
	//NVIC_GetPriorityGrouping() ��ȡ��ǰ�����ȼ�����
	//NVIC_EncodePriority(NVIC_GetPriorityGrouping(),2,2)//���ݷ��������ռ����Ӧ���ȼ��ı���
	//NVIC_SetPriority(EXTI2_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),2,2));//����EXTI2_IRQn�����ȼ�
	NVIC_EnableIRQ(EXTI2_IRQn);//ʹ���ж�
	NVIC_EnableIRQ(EXTI3_IRQn);//ʹ���ж�	
	NVIC_EnableIRQ(EXTI4_IRQn);//ʹ���ж�	
	NVIC_EnableIRQ(EXTI0_IRQn);//ʹ���ж�
	NVIC_ClearPendingIRQ(EXTI2_IRQn);//���nvic�ı�־λ���ںˣ�
	NVIC_ClearPendingIRQ(EXTI3_IRQn);//���nvic�ı�־λ���ںˣ�
	NVIC_ClearPendingIRQ(EXTI4_IRQn);//���nvic�ı�־λ���ںˣ�
	NVIC_ClearPendingIRQ(EXTI0_IRQn);//���nvic�ı�־λ���ںˣ�
	EXTI->PR |= (0x01<<2)|(0x01<<3)|(0x01<<4)|(0x01<<0);//����жϱ�־λ��ST��
}
/*
�������ܣ�����жϳ�ʼ��
�β��б�void
��������ֵ��void
ע�⣺
	ʹ���ⲿ�ж���5
*/
void EXTI_ruan_config(void)
{
	//����жϵ�����
	EXTI->IMR |=(0X01<<5);//�ж����μĴ����������жϣ�
	EXTI->EMR &=~(0X01<<5);//�¼����μĴ��������¼���
	EXTI->FTSR &=~(0X01<<5) ;//�ر��½��ؼĴ���
	EXTI->RTSR &=~(0X01<<5);//�ر������ؼĴ���
	NVIC_SetPriority(EXTI9_5_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),2,2));
	//NVIC_GetPriorityGrouping() ��ȡ��ǰ�����ȼ�����
	//NVIC_EncodePriority(NVIC_GetPriorityGrouping(),2,2)//���ݷ��������ռ����Ӧ���ȼ��ı���
	//NVIC_SetPriority(EXTI2_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),2,2));//����EXTI2_IRQn�����ȼ�
	NVIC_EnableIRQ(EXTI9_5_IRQn);//ʹ���ж�
	NVIC_ClearPendingIRQ(EXTI9_5_IRQn);//���nvic�ı�־λ���ںˣ�
	EXTI->PR |= (0x01<<5);//����жϱ�־λ��ST��
}

/*
�������ܣ�����1��ʼ��
�β��б�
	unsigned int band��������
��������ֵ��void
ע�⣺
		PA9 PA10
		�����ж�
*/
void USART1_config(unsigned int band)
{
	//���ڳ�ʼ��
	RCC->AHB1ENR|=RCC_AHB1ENR_GPIOAEN;//��GPIOA��ʱ��
	RCC->APB2ENR|=RCC_APB2ENR_USART1EN;//��USART1ʱ��
	GPIOA->MODER &=~((0x03<<(9*2))|(0x03<<(10*2)));//���PA9��PA10��ģʽ
	GPIOA->MODER |=((0x02<<(9*2))|(0x02<<(10*2)));//����PA9��PA10�ĸ���ģʽ
	GPIOA->PUPDR &= ~((0x03<<(9*2))|(0x03<<(10*2)));//����PA9��PA10��������
	GPIOA->OTYPER &= ~((0x03<<(9*2))|(0x03<<(10*2)));//����PA9��PA10Ϊ����ģʽ
	//���ø���������PA9-PA10������USART1
	GPIOA->AFR[9/8] &= ~(0x0f<<((9%8)*4));
	GPIOA->AFR[10/8] &= ~(0x0f<<((10%8)*4));	//����USART1
	GPIOA->AFR[9/8] |= (0x07<<((9%8)*4));
	GPIOA->AFR[10/8] |= (0x07<<((10%8)*4));		//����USART1
	//��������
	USART1->CR1&=~(0x01<<12);//8λ����λ
	USART1->CR1&=~(0x01<<10);//����żУ��
	USART1->CR2&=~(0x03<<12);//1λֹͣλ
	USART1->CR1&=~(0x01<<15);//16��������
	//���ò�����
	USART1->BRR=((SystemCoreClock/2.0)/((8*(2-((USART2->CR1&(0x01<<15))?1:0))*band)))*16;
	//ʹ���ж�
	USART1->CR1 |=0x03<<4;
	//�ж�����
	NVIC_SetPriority(USART1_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),2,2));
	NVIC_EnableIRQ(USART1_IRQn);
	NVIC_ClearPendingIRQ(USART1_IRQn);
	//��USART1ʹ��
	USART1->CR1|=(0X03<<2);//���������뷢����ʹ��
	USART1->CR1|=(0X01<<13);//��USART1ʹ��
}


/*
�������ܣ�����2��ʼ��
�β��б�
	unsigned int band��������
��������ֵ��void
ע�⣺
		PA3 PA2
		�����ж�
*/
void USART2_config(unsigned int band)
{
	//���ڳ�ʼ��
	RCC->AHB1ENR|=RCC_AHB1ENR_GPIOAEN;//��GPIOA��ʱ��
	RCC->APB1ENR|=RCC_APB1ENR_USART2EN;//��USART2ʱ��
	GPIOA->MODER &=~((0x03<<(3*2))|(0x03<<(2*2)));//���PA9��PA10��ģʽ
	GPIOA->MODER |=((0x02<<(3*2))|(0x02<<(2*2)));//����PA9��PA10�ĸ���ģʽ
	GPIOA->PUPDR &= ~((0x03<<(3*2))|(0x03<<(2*2)));//����PA9��PA10��������
	GPIOA->OTYPER &= ~((0x03<<(3*2))|(0x03<<(2*2)));//����PA9��PA10Ϊ����ģʽ
	//���ø���������PA9-PA10������USART1
	GPIOA->AFR[3/8] &= ~(0x0f<<((3%8)*4));
	GPIOA->AFR[2/8] &= ~(0x0f<<((2%8)*4));	//����USART1
	GPIOA->AFR[3/8] |= (0x07<<((3%8)*4));
	GPIOA->AFR[2/8] |= (0x07<<((2%8)*4));		//����USART1
	//��������
	USART2->CR1&=~(0x01<<12);//8λ����λ
	USART2->CR1&=~(0x01<<10);//����żУ��
	USART2->CR2&=~(0x03<<12);//1λֹͣλ
	USART2->CR1&=~(0x01<<15);//16��������
	//���ò�����
	USART2->BRR=((SystemCoreClock/4.0)/((8*(2-((USART2->CR1&(0x01<<15))?1:0))*band)))*16;
	
	//ʹ���ж�
	USART2->CR1 |=0x03<<4;
	//�ж�����
	NVIC_SetPriority(USART2_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1,1));
	NVIC_EnableIRQ(USART2_IRQn);
	NVIC_ClearPendingIRQ(USART2_IRQn);
	//��USART2ʹ��
	USART2->CR1|=(0X03<<2);//���������뷢����ʹ��
	USART2->CR1|=(0X01<<13);//��USART2ʹ��
}



