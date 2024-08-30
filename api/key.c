#include "key.h"

/*
	�޺궨��Ĭ��Ϊ�Ĵ���������ʽ
	ʹ�ú궨��USE_BITIO_DRIVERΪλ��������ʽ
	ʹ�ú궨��USE_FILED_DRIVERΪλ��������ʽ
	ʹ�ú궨��USE_STDPERIPH_DRIVERΪ��׼��������ʽ
*/
/*
�궨�����ƣ�Key_Read
���ܣ���ȡ�����Ƿ���
������
	GPIO_TypeDef *GPIOx:GPIO�Ķ˿�
	unsigned int Pin:�˿�����
	unsigned int Idle:���е�ƽ
����ֵ��0Ϊδ����  ��0Ϊ����
*/
#ifdef USE_BITIO_DRIVER
   //λ��������ʽ
	#define Key_Read(GPIOx,Pin,Idle)\
		((Idle?1:0)!=Pin(GPIOx,Pin))
#elif USE_FIELD_DRIVER
   //λ��������ʽ
	#define Key_Read(GPIOx,Pin,Idle)\
		((Idle?1:0)!=Pin_Field(GPIOx,Pin))
#elif USE_STDPERIPH_DRIVER
   //��׼��������ʽ
	#define Key_Read(GPIOx,Pin,Idle)\
		((Idle?1:0)!=GPIO_ReadInputDataBit(GPIOx,0x01<<Pin))
#else
	//�Ĵ���������ʽ
	#define Key_Read(GPIOx,Pin,Idle)\
	((Idle?1:0)!=	((GPIOx->IDR & (0x01<<Pin))?1:0))
#endif

/*
���ܣ���ȡ���������Ƿ񱻰��£����´���һ�λص���������棩
���ߣ�YKY
������
	GPIO_TypeDef *GPIOx:GPIO�Ķ˿�
	unsigned int Pin:���ź�
	unsigned int Idle:���е�ѹ  0Ϊ�ͣ���0Ϊ��
	void (*delay)(unsigned int):��ʱ����ָ��
	unsigned int *temp:	��ʱ�����洢����ֹ��ε���״̬���ǣ������쳣��
����ֵ��0Ϊδ���� 1Ϊ����
ע�⣺
*/
/*
��һ�ΰ���ʱ ����û�з���һ��ֵʱ��
	����ֵ��
�������£��з���һ��ֵʱ��
	��������
���ɿ�ʱ���з��ص�ʱ��
	����һ�·���һ�ε�ֵ��Ϊ��һ�ν�����׼��
*/
unsigned int key_press_while_one(GPIO_TypeDef *GPIOx,unsigned int Pin,unsigned int Idle,void (*delay)(unsigned int),unsigned int *temp)
{
	unsigned int back_data=0;
	if(Key_Read(GPIOx,Pin,Idle) && !*temp)//�������
	{
		(*delay)(15);
		if(Key_Read(GPIOx,Pin,Idle))
		{
			back_data=1;//����ֵ��ֵ
			*temp=1;
		}
	}
	else if(!Key_Read(GPIOx,Pin,Idle) && *temp)
	{
		*temp=0;
	}
	return back_data;//����
}

/*
���ܣ���ȡ���������Ƿ񱻰��£��ɿ������ص���������棩
���ߣ�YKY
������
	GPIO_TypeDef *GPIOx:GPIO�Ķ˿�
	unsigned int Pin:���ź�
	unsigned int Idle:���е�ѹ  0Ϊ�ͣ���0Ϊ��
����ֵ��0Ϊδ���� 1Ϊ����
ע�⣺
*/
unsigned int key_loose_while_one(GPIO_TypeDef *GPIOx,unsigned int Pin,unsigned int Idle)
{
	unsigned int back_data=0;
	if(Key_Read(GPIOx,Pin,Idle))//�������
	{
		while(Key_Read(GPIOx,Pin,Idle));
		back_data=1;
	}
	return back_data;//����
}

/*
���ܣ���ȡ���������Ƿ񱻰��£�����һֱ�����ص���������棩
���ߣ�YKY
������
	GPIO_TypeDef *GPIOx:GPIO�Ķ˿�
	unsigned int Pin:���ź�
	unsigned int Idle:���е�ѹ  0Ϊ�ͣ���0Ϊ��
	void (*delay)(unsigned int):��ʱ����ָ��
����ֵ��0Ϊδ���� 1Ϊ����
ע�⣺�̶�������ʱ15ms
*/
unsigned int key_press_while_always(GPIO_TypeDef *GPIOx,unsigned int Pin,unsigned int Idle,void (*delay)(unsigned int))
{	
	unsigned int back_data=0;
	if(Key_Read(GPIOx,Pin,Idle))//�������
	{
		(*delay)(15);
		if(Key_Read(GPIOx,Pin,Idle))
			back_data=1;//����ֵ��ֵ
		else//û�з���0
			back_data=0;
	}
	else//û�з���0
		back_data=0;
	return back_data;//����
}

/*
���ܣ���ȡ��������״̬�Ƿ�ı䣨�����ɿ�������һ�λص���
���ߣ�YKY
������
	GPIO_TypeDef *GPIOx:GPIO�Ķ˿�
	unsigned int Pin:���ź�
	unsigned int Idle:���е�ѹ  0Ϊ�ͣ���0Ϊ��
	unsigned int *temp:	��ʱ�����洢����ֹ��ε���״̬���ǣ������쳣��
����ֵ��0Ϊδ����״̬  1Ϊ����״̬
ע�⣺
*/
unsigned int key_pressloose_one(GPIO_TypeDef *GPIOx,unsigned int Pin,unsigned int Idle,unsigned int *temp)
{	
	unsigned int back_data=0;//���巵��ֵ
	if(Key_Read(GPIOx,Pin,Idle)!= *temp)//��ǰ״̬��������һ�ε�״̬
	{
		back_data=1;
		*temp=Key_Read(GPIOx,Pin,Idle);//����״̬
	}
	return back_data;//����
}





















