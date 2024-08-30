#include "key.h"

/*
	无宏定义默认为寄存器驱动方式
	使用宏定义USE_BITIO_DRIVER为位代驱动方式
	使用宏定义USE_FILED_DRIVER为位域驱动方式
	使用宏定义USE_STDPERIPH_DRIVER为标准库驱动方式
*/
/*
宏定义名称：Key_Read
功能：获取按键是否按下
参数：
	GPIO_TypeDef *GPIOx:GPIO的端口
	unsigned int Pin:端口引脚
	unsigned int Idle:空闲电平
返回值：0为未按下  非0为按下
*/
#ifdef USE_BITIO_DRIVER
   //位代驱动方式
	#define Key_Read(GPIOx,Pin,Idle)\
		((Idle?1:0)!=Pin(GPIOx,Pin))
#elif USE_FIELD_DRIVER
   //位域驱动方式
	#define Key_Read(GPIOx,Pin,Idle)\
		((Idle?1:0)!=Pin_Field(GPIOx,Pin))
#elif USE_STDPERIPH_DRIVER
   //标准库驱动方式
	#define Key_Read(GPIOx,Pin,Idle)\
		((Idle?1:0)!=GPIO_ReadInputDataBit(GPIOx,0x01<<Pin))
#else
	//寄存器驱动方式
	#define Key_Read(GPIOx,Pin,Idle)\
	((Idle?1:0)!=	((GPIOx->IDR & (0x01<<Pin))?1:0))
#endif

/*
功能：获取单个按键是否被按下（按下触发一次回弹，卡程序版）
作者：YKY
参数：
	GPIO_TypeDef *GPIOx:GPIO的端口
	unsigned int Pin:引脚号
	unsigned int Idle:空闲电压  0为低，非0为高
	void (*delay)(unsigned int):延时函数指针
	unsigned int *temp:	临时变量存储（防止多次调用状态覆盖，出现异常）
返回值：0为未按下 1为按下
注意：
*/
/*
第一次按下时 并且没有返回一次值时，
	返回值，
后续摁下，有返回一次值时，
	就跳过，
到松开时，有返回的时候
	更新一下返回一次的值，为下一次进入做准备
*/
unsigned int key_press_while_one(GPIO_TypeDef *GPIOx,unsigned int Pin,unsigned int Idle,void (*delay)(unsigned int),unsigned int *temp)
{
	unsigned int back_data=0;
	if(Key_Read(GPIOx,Pin,Idle) && !*temp)//如果按下
	{
		(*delay)(15);
		if(Key_Read(GPIOx,Pin,Idle))
		{
			back_data=1;//返回值赋值
			*temp=1;
		}
	}
	else if(!Key_Read(GPIOx,Pin,Idle) && *temp)
	{
		*temp=0;
	}
	return back_data;//返回
}

/*
功能：获取单个按键是否被按下（松开触发回弹，卡程序版）
作者：YKY
参数：
	GPIO_TypeDef *GPIOx:GPIO的端口
	unsigned int Pin:引脚号
	unsigned int Idle:空闲电压  0为低，非0为高
返回值：0为未按下 1为按下
注意：
*/
unsigned int key_loose_while_one(GPIO_TypeDef *GPIOx,unsigned int Pin,unsigned int Idle)
{
	unsigned int back_data=0;
	if(Key_Read(GPIOx,Pin,Idle))//如果按下
	{
		while(Key_Read(GPIOx,Pin,Idle));
		back_data=1;
	}
	return back_data;//返回
}

/*
功能：获取单个按键是否被按下（按下一直触发回弹，卡程序版）
作者：YKY
参数：
	GPIO_TypeDef *GPIOx:GPIO的端口
	unsigned int Pin:引脚号
	unsigned int Idle:空闲电压  0为低，非0为高
	void (*delay)(unsigned int):延时函数指针
返回值：0为未按下 1为按下
注意：固定消抖延时15ms
*/
unsigned int key_press_while_always(GPIO_TypeDef *GPIOx,unsigned int Pin,unsigned int Idle,void (*delay)(unsigned int))
{	
	unsigned int back_data=0;
	if(Key_Read(GPIOx,Pin,Idle))//如果按下
	{
		(*delay)(15);
		if(Key_Read(GPIOx,Pin,Idle))
			back_data=1;//返回值赋值
		else//没有返回0
			back_data=0;
	}
	else//没有返回0
		back_data=0;
	return back_data;//返回
}

/*
功能：获取单个按键状态是否改变（按下松开各触发一次回弹）
作者：YKY
参数：
	GPIO_TypeDef *GPIOx:GPIO的端口
	unsigned int Pin:引脚号
	unsigned int Idle:空闲电压  0为低，非0为高
	unsigned int *temp:	临时变量存储（防止多次调用状态覆盖，出现异常）
返回值：0为未更新状态  1为更新状态
注意：
*/
unsigned int key_pressloose_one(GPIO_TypeDef *GPIOx,unsigned int Pin,unsigned int Idle,unsigned int *temp)
{	
	unsigned int back_data=0;//定义返回值
	if(Key_Read(GPIOx,Pin,Idle)!= *temp)//当前状态不等于上一次的状态
	{
		back_data=1;
		*temp=Key_Read(GPIOx,Pin,Idle);//更新状态
	}
	return back_data;//返回
}





















