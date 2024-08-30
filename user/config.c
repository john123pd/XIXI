/*
	文件：config_V0.0.1
	简介：该文件定义XYD_Foundation板的初始化函数
	适用芯片：STM32F407VGT6
	功能：初始化函数
	宏定义：
	注意：
	更新日期：
*/
#include "config.h"

/*
函数功能：初始化LED灯
形参列表：void
函数返回值：void
注意：
	PC4,PC5,PC6,PC7
*/
void LED_config(void)
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;//初始化时钟
	GPIOC->MODER   &= ~((0x03<<(4*2))|(0x03<<(5*2))|(0x03<<(6*2))|(0x03<<(7*2)));   //先清除模式
	GPIOC->MODER   |= ((0x01<<(4*2))|(0x01<<(5*2))|(0x01<<(6*2))|(0x01<<(7*2)));    //再配置输出模式
	GPIOC->OTYPER  &= ~((0x01<<(4))|(0x01<<(5))|(0x01<<(6))|(0x01<<(7)));       //配置推挽
	GPIOC->PUPDR   &= ~((0x03<<(4*2))|(0x03<<(5*2))|(0x03<<(6*2))|(0x03<<(7*2)));   //配置无上下拉
	GPIOC->OSPEEDR &= ~((0x03<<(4*2))|(0x03<<(5*2))|(0x03<<(6*2))|(0x03<<(7*2)));   //清除速度
	GPIOC->OSPEEDR |= ((0x03<<(4*2)) |(0x03<<(5*2))|(0x03<<(6*2))|(0x03<<(7*2)));    //配置最高速度	
	led_illume(GPIOC,4,1,0);
	led_illume(GPIOC,5,1,0);	
	led_illume(GPIOC,6,1,0);	
	led_illume(GPIOC,7,1,0);
}

/*
函数功能：初始化按键
形参列表：void
函数返回值：void
注意：
	PA0,PE2,PE3,PE4
*/
void KEY_config(void)
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN|RCC_AHB1ENR_GPIOEEN;//初始化时钟
	GPIOE->MODER   &= ~(0x03<<(2*2)|(0x03<<(3*2))|(0x03<<(4*2)));   //配置为输入模式
	GPIOE->PUPDR   &= ~(0x03<<(2*2)|(0x03<<(3*2))|(0x03<<(4*2)));   //配置无上下拉	
	GPIOA->MODER   &= ~(0x03<<(2*0));
	GPIOA->PUPDR   &= ~(0x03<<(2*0));
}

/*
函数功能：蜂鸣器
形参列表：void
函数返回值：void
注意：
	PE0
*/
void BUZZER_config(void)
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
	GPIOE->MODER   &= ~(0x03<<(0*2));   //先清除模式
	GPIOE->MODER   |= (0x01<<(0*2));    //再配置输出模式
	GPIOE->OTYPER  &= ~(0x01<<(0));       //配置推挽
	GPIOE->PUPDR   &= ~(0x03<<(0*2));   //配置无上下拉
	GPIOE->OSPEEDR &= ~(0x03<<(0*2));   //清除速度
	GPIOE->OSPEEDR |= (0x03<<(0*2));    //配置最高速度	
	led_illume(GPIOE,0,0,0);
}

/*
函数功能：外部中断初始化（按键）
形参列表：void
函数返回值：void
注意：
	PA0 PE2 PE3 PE4
*/
void EXTI_key_config(void)
{
	RCC->AHB1ENR |=RCC_AHB1ENR_GPIOAEN|RCC_AHB1ENR_GPIOEEN;//开GPIOA,GPIOE的时钟
	RCC->APB2ENR|=RCC_APB2ENR_SYSCFGEN;//打开SYSCFG时钟	
	//GPIO口配置
	GPIOA->MODER &= ~(0X03<<(2*0));//设置GPIOA——0引脚为输入模式
	GPIOA->PUPDR &= ~(0X03<<(2*0));//设置GPIOA--0引脚无上下拉
	GPIOE->MODER &= ~((0X03<<(2*2))|(0X03<<(2*3))|(0X03<<(2*4)));//设置GPIOE——2引脚为输入模式
	GPIOE->PUPDR &= ~((0X03<<(2*2))|(0X03<<(2*3))|(0X03<<(2*4)));//设置GPIOE--2引脚无上下拉
	//系统配置控制器的配置
	SYSCFG->EXTICR[0] &=~(((0x0f)<<((0%4)*4))|((0x0f)<<((2%4)*4))|((0x0f)<<((3%4)*4))); //清除SYSCFG的EXTI配置
	SYSCFG->EXTICR[0] |=((0x04)<<((2%4)*4))|((0x04)<<((3%4)*4));//SYSCFG的EXTI2个，链接到GPIOE上
	SYSCFG->EXTICR[4/4] &=~((0x0f)<<((4%4)*4)); //清除SYSCFG的EXTI配置
	SYSCFG->EXTICR[4/4] |=((0x04)<<((4%4)*4));//SYSCFG的EXTI4个，链接到GPIOE上	
	//配置EXTI寄存器
	EXTI->IMR |=((0X01<<2)|(0X01<<4)|(0X01<<3)|(0X01<<0));//中断屏蔽寄存器（开启中断）
	EXTI->EMR &=~((0X01<<2)|(0X01<<4)|(0X01<<3)|(0X01<<0));//事件屏蔽寄存器（关事件）
	EXTI->FTSR |=((0X01<<2)|(0X01<<4)|(0X01<<3)) ;//开下降沿寄存器（电路按键，空闲为高，按下时是高电平切换为低电平,下降沿）
	EXTI->RTSR |=((0X01<<0));//打开EXTI0的上升沿寄存器(空闲电平低，按下为高，上升沿)
	//配置NVIC
	NVIC_SetPriority(EXTI2_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),2,2));
	NVIC_SetPriority(EXTI3_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),2,2));
	NVIC_SetPriority(EXTI4_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),2,2));
	NVIC_SetPriority(EXTI0_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),2,2));
	//NVIC_GetPriorityGrouping() 获取当前的优先级分组
	//NVIC_EncodePriority(NVIC_GetPriorityGrouping(),2,2)//根据分组输出抢占和响应优先级的编码
	//NVIC_SetPriority(EXTI2_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),2,2));//设置EXTI2_IRQn的优先级
	NVIC_EnableIRQ(EXTI2_IRQn);//使能中断
	NVIC_EnableIRQ(EXTI3_IRQn);//使能中断	
	NVIC_EnableIRQ(EXTI4_IRQn);//使能中断	
	NVIC_EnableIRQ(EXTI0_IRQn);//使能中断
	NVIC_ClearPendingIRQ(EXTI2_IRQn);//清除nvic的标志位（内核）
	NVIC_ClearPendingIRQ(EXTI3_IRQn);//清除nvic的标志位（内核）
	NVIC_ClearPendingIRQ(EXTI4_IRQn);//清除nvic的标志位（内核）
	NVIC_ClearPendingIRQ(EXTI0_IRQn);//清除nvic的标志位（内核）
	EXTI->PR |= (0x01<<2)|(0x01<<3)|(0x01<<4)|(0x01<<0);//清除中断标志位（ST）
}
/*
函数功能：软件中断初始化
形参列表：void
函数返回值：void
注意：
	使用外部中断线5
*/
void EXTI_ruan_config(void)
{
	//软件中断的配置
	EXTI->IMR |=(0X01<<5);//中断屏蔽寄存器（开启中断）
	EXTI->EMR &=~(0X01<<5);//事件屏蔽寄存器（关事件）
	EXTI->FTSR &=~(0X01<<5) ;//关闭下降沿寄存器
	EXTI->RTSR &=~(0X01<<5);//关闭上升沿寄存器
	NVIC_SetPriority(EXTI9_5_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),2,2));
	//NVIC_GetPriorityGrouping() 获取当前的优先级分组
	//NVIC_EncodePriority(NVIC_GetPriorityGrouping(),2,2)//根据分组输出抢占和响应优先级的编码
	//NVIC_SetPriority(EXTI2_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),2,2));//设置EXTI2_IRQn的优先级
	NVIC_EnableIRQ(EXTI9_5_IRQn);//使能中断
	NVIC_ClearPendingIRQ(EXTI9_5_IRQn);//清除nvic的标志位（内核）
	EXTI->PR |= (0x01<<5);//清除中断标志位（ST）
}

/*
函数功能：串口1初始化
形参列表：
	unsigned int band：波特率
函数返回值：void
注意：
		PA9 PA10
		串口中断
*/
void USART1_config(unsigned int band)
{
	//串口初始化
	RCC->AHB1ENR|=RCC_AHB1ENR_GPIOAEN;//开GPIOA的时钟
	RCC->APB2ENR|=RCC_APB2ENR_USART1EN;//开USART1时钟
	GPIOA->MODER &=~((0x03<<(9*2))|(0x03<<(10*2)));//清除PA9和PA10的模式
	GPIOA->MODER |=((0x02<<(9*2))|(0x02<<(10*2)));//设置PA9和PA10的复用模式
	GPIOA->PUPDR &= ~((0x03<<(9*2))|(0x03<<(10*2)));//设置PA9和PA10无上下拉
	GPIOA->OTYPER &= ~((0x03<<(9*2))|(0x03<<(10*2)));//设置PA9和PA10为推挽模式
	//设置复用器，将PA9-PA10复用至USART1
	GPIOA->AFR[9/8] &= ~(0x0f<<((9%8)*4));
	GPIOA->AFR[10/8] &= ~(0x0f<<((10%8)*4));	//复用USART1
	GPIOA->AFR[9/8] |= (0x07<<((9%8)*4));
	GPIOA->AFR[10/8] |= (0x07<<((10%8)*4));		//复用USART1
	//串口设置
	USART1->CR1&=~(0x01<<12);//8位数据位
	USART1->CR1&=~(0x01<<10);//关奇偶校验
	USART1->CR2&=~(0x03<<12);//1位停止位
	USART1->CR1&=~(0x01<<15);//16倍过采样
	//设置波特率
	USART1->BRR=((SystemCoreClock/2.0)/((8*(2-((USART2->CR1&(0x01<<15))?1:0))*band)))*16;
	//使能中断
	USART1->CR1 |=0x03<<4;
	//中断配置
	NVIC_SetPriority(USART1_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),2,2));
	NVIC_EnableIRQ(USART1_IRQn);
	NVIC_ClearPendingIRQ(USART1_IRQn);
	//开USART1使能
	USART1->CR1|=(0X03<<2);//开接收器与发生器使能
	USART1->CR1|=(0X01<<13);//开USART1使能
}


/*
函数功能：串口2初始化
形参列表：
	unsigned int band：波特率
函数返回值：void
注意：
		PA3 PA2
		串口中断
*/
void USART2_config(unsigned int band)
{
	//串口初始化
	RCC->AHB1ENR|=RCC_AHB1ENR_GPIOAEN;//开GPIOA的时钟
	RCC->APB1ENR|=RCC_APB1ENR_USART2EN;//开USART2时钟
	GPIOA->MODER &=~((0x03<<(3*2))|(0x03<<(2*2)));//清除PA9和PA10的模式
	GPIOA->MODER |=((0x02<<(3*2))|(0x02<<(2*2)));//设置PA9和PA10的复用模式
	GPIOA->PUPDR &= ~((0x03<<(3*2))|(0x03<<(2*2)));//设置PA9和PA10无上下拉
	GPIOA->OTYPER &= ~((0x03<<(3*2))|(0x03<<(2*2)));//设置PA9和PA10为推挽模式
	//设置复用器，将PA9-PA10复用至USART1
	GPIOA->AFR[3/8] &= ~(0x0f<<((3%8)*4));
	GPIOA->AFR[2/8] &= ~(0x0f<<((2%8)*4));	//复用USART1
	GPIOA->AFR[3/8] |= (0x07<<((3%8)*4));
	GPIOA->AFR[2/8] |= (0x07<<((2%8)*4));		//复用USART1
	//串口设置
	USART2->CR1&=~(0x01<<12);//8位数据位
	USART2->CR1&=~(0x01<<10);//关奇偶校验
	USART2->CR2&=~(0x03<<12);//1位停止位
	USART2->CR1&=~(0x01<<15);//16倍过采样
	//设置波特率
	USART2->BRR=((SystemCoreClock/4.0)/((8*(2-((USART2->CR1&(0x01<<15))?1:0))*band)))*16;
	
	//使能中断
	USART2->CR1 |=0x03<<4;
	//中断配置
	NVIC_SetPriority(USART2_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1,1));
	NVIC_EnableIRQ(USART2_IRQn);
	NVIC_ClearPendingIRQ(USART2_IRQn);
	//开USART2使能
	USART2->CR1|=(0X03<<2);//开接收器与发生器使能
	USART2->CR1|=(0X01<<13);//开USART2使能
}



