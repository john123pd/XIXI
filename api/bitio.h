/*
	�ļ���bitio_V0.0.1
	���ߣ�YKY(QQ:971649457)
	��ע�������ڵ�Ƭ����ͨ��ģ�黯��ơ��򵥻����
	���������ļ�Ϊ����ļ�,����ѧϰ,�ṩ˼·;������ʹ��,�豸ע����;�Ͻ���ҵ������Ϊ,�����ֽ�άȨ����;
	��飺���ļ�Ϊͨ��λ���ṩͨ�ú궨��
	����оƬ��STM32F4xx/STM32F1xx
	���ܣ�
		���ļ�����λ����ʽ��д
	�궨�壺
	ע�⣺
	�������ڣ�
		V0.0.1|2024.06.01|�淶���,�淶����,��д��������(λ������)
*/

#ifndef __BITIO_H
#define __BITIO_H

#define BITBAND(addr,bit) (((addr&0xF0000000)+0x2000000)+((addr&0xFFFFF)*8+bit)*4)//λ�����㹫ʽ
#define MEMADDR(addr,bit)  *(unsigned int *)BITBAND(addr,bit)//ת��Ϊ�Ĵ���λ��

#define Pin(GPIOx,bit)  MEMADDR((unsigned int)&GPIOx->IDR,bit)//����Ĵ���λ��
#define Pout(GPIOx,bit)  MEMADDR((unsigned int)&GPIOx->ODR,bit)//����Ĵ���λ��

#endif


