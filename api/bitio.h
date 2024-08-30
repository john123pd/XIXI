/*
	文件：bitio_V0.0.1
	作者：YKY(QQ:971649457)
	备注：致力于单片机的通用模块化设计、简单化设计
	声明：该文件为免费文件,仅供学习,提供思路;若搬运使用,需备注出处;严禁商业售卖行为,若发现将维权到底;
	简介：该文件为通用位代提供通用宏定义
	适用芯片：STM32F4xx/STM32F1xx
	功能：
		该文件包括位代方式读写
	宏定义：
	注意：
	更新日期：
		V0.0.1|2024.06.01|规范编程,规范命名,编写驱动代码(位代驱动)
*/

#ifndef __BITIO_H
#define __BITIO_H

#define BITBAND(addr,bit) (((addr&0xF0000000)+0x2000000)+((addr&0xFFFFF)*8+bit)*4)//位代计算公式
#define MEMADDR(addr,bit)  *(unsigned int *)BITBAND(addr,bit)//转换为寄存器位代

#define Pin(GPIOx,bit)  MEMADDR((unsigned int)&GPIOx->IDR,bit)//输入寄存器位代
#define Pout(GPIOx,bit)  MEMADDR((unsigned int)&GPIOx->ODR,bit)//输出寄存器位代

#endif


