#include "led.h"
/*
	无宏定义默认为寄存器驱动方式
	使用宏定义USE_BITIO_DRIVER为位代驱动方式
	使用宏定义USE_FILED_DRIVER为位域驱动方式
	使用宏定义USE_STDPERIPH_DRIVER为标准库驱动方式
*/
/*
宏定义名称：LED_Write
功能：根据状态开关灯
参数：
	GPIO_TypeDef *GPIOx:GPIO的端口
	unsigned int Pin:端口引脚
	unsigned int Idle:另一端所接电压  0为低，非0为高
	unsigned int Key:0关,非0为开
返回值：无
*/

/*
宏定义名称：LED_Toggle
功能：反转灯
参数：
	GPIO_TypeDef *GPIOx:GPIO的端口
	unsigned int Pin:端口引脚
返回值：无
*/
#ifdef USE_BITIO_DRIVER
   //位代驱动方式
	#define LED_Write(GPIOx,Pin,Idle,Key) \
			(Pout(GPIOx,Pin)=(Key?!Idle:Idle)?1:0)
	#define LED_Toggle(GPIOx,Pin) \
			(Pout(GPIOx,Pin)=!Pout(GPIOx,Pin))
#elif USE_FIELD_DRIVER
   //位域驱动方式
	#define LED_Write(GPIOx,Pin,Idle,Key) \
			(Pout_Field(GPIOx,Pin)=(Key?!Idle:Idle)?1:0)
	#define LED_Toggle(GPIOx,Pin) \
			(Pout_Field(GPIOx,Pin)=!Pout_Field(GPIOx,Pin))
#elif USE_STDPERIPH_DRIVER
   //标准库驱动方式
	#define LED_Write(GPIOx,Pin,Idle,Key) \
			GPIO_WriteBit(GPIOx,0x01<<Pin,(Key?!Idle:Idle)?Bit_SET:Bit_RESET)
	#define LED_Toggle(GPIOx,Pin) \
			GPIO_ToggleBits(GPIOx,0x01<<Pin)
#else
	//寄存器驱动方式
	#define LED_Write(GPIOx,Pin,Idle,Key) \
			(GPIOx->BSRR |= 0x01<<(Pin+((Key?!Idle:Idle)?0:16)))
	#define LED_Toggle(GPIOx,Pin) \
			(GPIOx->ODR ^= 0x01<<Pin)
#endif

/*
功能：点/关亮灯
作者：YKY
参数：
	GPIO_TypeDef *GPIOx:GPIO的端口
	unsigned int Pin:端口引脚
	unsigned int Idle:另一端所接电压  0为低，非0为高
	unsigned int Key:0关,非0为开
返回值：无
注意：该函数为对外接口
*/
void led_illume(GPIO_TypeDef *GPIOx,unsigned int Pin,unsigned int Idle,unsigned char Key)
{
	LED_Write(GPIOx,Pin,Idle,Key);
}


/*
功能：反转灯
作者：YKY
参数：
	GPIO_TypeDef *GPIOx:GPIO的端口
	unsigned int Pin:端口引脚
返回值：无
注意：该函数为对外接口
*/
void led_inversion(GPIO_TypeDef *GPIOx,unsigned int Pin)
{
	LED_Toggle(GPIOx,Pin);
}

/*
功能：闪烁灯（while版）
作者：YKY
参数：
	GPIO_TypeDef *GPIOx:GPIO的端口
	unsigned int Pin:端口引脚
	void (*delay)(unsigned int):延时函数指针
	unsigned int glint_time:闪烁半周期时间（一次电平变化时间）
返回值：无
注意：该函数卡程序,使用主函数进行高刷识别
*/
void led_while_glint(GPIO_TypeDef *GPIOx,unsigned int Pin,void (*delay)(unsigned int),unsigned int glint_time)
{
	led_inversion(GPIOx,Pin);
	delay(glint_time);
}



