#include "led.h"
/*
	�޺궨��Ĭ��Ϊ�Ĵ���������ʽ
	ʹ�ú궨��USE_BITIO_DRIVERΪλ��������ʽ
	ʹ�ú궨��USE_FILED_DRIVERΪλ��������ʽ
	ʹ�ú궨��USE_STDPERIPH_DRIVERΪ��׼��������ʽ
*/
/*
�궨�����ƣ�LED_Write
���ܣ�����״̬���ص�
������
	GPIO_TypeDef *GPIOx:GPIO�Ķ˿�
	unsigned int Pin:�˿�����
	unsigned int Idle:��һ�����ӵ�ѹ  0Ϊ�ͣ���0Ϊ��
	unsigned int Key:0��,��0Ϊ��
����ֵ����
*/

/*
�궨�����ƣ�LED_Toggle
���ܣ���ת��
������
	GPIO_TypeDef *GPIOx:GPIO�Ķ˿�
	unsigned int Pin:�˿�����
����ֵ����
*/
#ifdef USE_BITIO_DRIVER
   //λ��������ʽ
	#define LED_Write(GPIOx,Pin,Idle,Key) \
			(Pout(GPIOx,Pin)=(Key?!Idle:Idle)?1:0)
	#define LED_Toggle(GPIOx,Pin) \
			(Pout(GPIOx,Pin)=!Pout(GPIOx,Pin))
#elif USE_FIELD_DRIVER
   //λ��������ʽ
	#define LED_Write(GPIOx,Pin,Idle,Key) \
			(Pout_Field(GPIOx,Pin)=(Key?!Idle:Idle)?1:0)
	#define LED_Toggle(GPIOx,Pin) \
			(Pout_Field(GPIOx,Pin)=!Pout_Field(GPIOx,Pin))
#elif USE_STDPERIPH_DRIVER
   //��׼��������ʽ
	#define LED_Write(GPIOx,Pin,Idle,Key) \
			GPIO_WriteBit(GPIOx,0x01<<Pin,(Key?!Idle:Idle)?Bit_SET:Bit_RESET)
	#define LED_Toggle(GPIOx,Pin) \
			GPIO_ToggleBits(GPIOx,0x01<<Pin)
#else
	//�Ĵ���������ʽ
	#define LED_Write(GPIOx,Pin,Idle,Key) \
			(GPIOx->BSRR |= 0x01<<(Pin+((Key?!Idle:Idle)?0:16)))
	#define LED_Toggle(GPIOx,Pin) \
			(GPIOx->ODR ^= 0x01<<Pin)
#endif

/*
���ܣ���/������
���ߣ�YKY
������
	GPIO_TypeDef *GPIOx:GPIO�Ķ˿�
	unsigned int Pin:�˿�����
	unsigned int Idle:��һ�����ӵ�ѹ  0Ϊ�ͣ���0Ϊ��
	unsigned int Key:0��,��0Ϊ��
����ֵ����
ע�⣺�ú���Ϊ����ӿ�
*/
void led_illume(GPIO_TypeDef *GPIOx,unsigned int Pin,unsigned int Idle,unsigned char Key)
{
	LED_Write(GPIOx,Pin,Idle,Key);
}


/*
���ܣ���ת��
���ߣ�YKY
������
	GPIO_TypeDef *GPIOx:GPIO�Ķ˿�
	unsigned int Pin:�˿�����
����ֵ����
ע�⣺�ú���Ϊ����ӿ�
*/
void led_inversion(GPIO_TypeDef *GPIOx,unsigned int Pin)
{
	LED_Toggle(GPIOx,Pin);
}

/*
���ܣ���˸�ƣ�while�棩
���ߣ�YKY
������
	GPIO_TypeDef *GPIOx:GPIO�Ķ˿�
	unsigned int Pin:�˿�����
	void (*delay)(unsigned int):��ʱ����ָ��
	unsigned int glint_time:��˸������ʱ�䣨һ�ε�ƽ�仯ʱ�䣩
����ֵ����
ע�⣺�ú���������,ʹ�����������и�ˢʶ��
*/
void led_while_glint(GPIO_TypeDef *GPIOx,unsigned int Pin,void (*delay)(unsigned int),unsigned int glint_time)
{
	led_inversion(GPIOx,Pin);
	delay(glint_time);
}



