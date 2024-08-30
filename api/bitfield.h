/*
error
*/
#ifndef __BITIO_H
#define __BITIO_H


#define Pout_Field(GPIOx,Pin) 	(((struct Register*)(&(GPIOx->ODR)))->IODR##pin)
#define Pin_Field(GPIOx,Pin) 	(((struct Register*)(&(GPIOx->IDR)))->IODR##pin)


struct Register{
	union
	{
		volatile unsigned int BitALL :32;
		struct{
			volatile unsigned int PinL :16;
			volatile unsigned int PinH :16;
		};
		struct{
			volatile unsigned short Pin0 :1;
			volatile unsigned short Pin1 :1;
			volatile unsigned short Pin2 :1;
			volatile unsigned short Pin3 :1;
			volatile unsigned short Pin4 :1;
			volatile unsigned short Pin5 :1;
			volatile unsigned short Pin6 :1;
			volatile unsigned short Pin7 :1;
			volatile unsigned short Pin8 :1;
			volatile unsigned short Pin9 :1;
			volatile unsigned short Pin10 :1;
			volatile unsigned short Pin11 :1;
			volatile unsigned short Pin12 :1;
			volatile unsigned short Pin13 :1;
			volatile unsigned short Pin14 :1;
			volatile unsigned short Pin15 :1;
			volatile unsigned short Pin16 :1;
			volatile unsigned short Pin17 :1;
			volatile unsigned short Pin18 :1;
			volatile unsigned short Pin19 :1;
			volatile unsigned short Pin20 :1;
			volatile unsigned short Pin21 :1;
			volatile unsigned short Pin22 :1;
			volatile unsigned short Pin23 :1;
			volatile unsigned short Pin24 :1;
			volatile unsigned short Pin25 :1;
			volatile unsigned short Pin26 :1;
			volatile unsigned short Pin27 :1;
			volatile unsigned short Pin28 :1;
			volatile unsigned short Pin29 :1;
			volatile unsigned short Pin30 :1;
			volatile unsigned short Pin31 :1;
		};
	};
};

#endif


