#include<lpc21xx.h>

extern unsigned int count0,count1,count2;
extern unsigned int flag0,flag1,flag2;

void eint0_handler(void) __irq	//p0.16
{
	count0++;
	flag2=1;
	EXTINT|=1;
	VICVectAddr=0;
}

void eint1_handler(void)	__irq  //p0.14
{
	count1++;
	flag0=1;
	flag1=0;
	EXTINT|=0x2;
	VICVectAddr=0;
}

void eint2_handler(void)	__irq  //p0.15
{
	count2++;
	flag1=1;
	flag0=0;
	EXTINT|=0x4;
	VICVectAddr=0;
}

void config_vic_for_eint(void)
{
	VICIntSelect=0;

	VICVectCntl0=14|(1<<5);
	VICVectAddr0=(unsigned int)eint0_handler;

	VICVectCntl1=15|(1<<5);
	VICVectAddr1=(unsigned int)eint1_handler;

	VICVectCntl2=16|(1<<5);
	VICVectAddr2=(unsigned int)eint2_handler;

	VICIntEnable=(1<<14)|(1<<15)|(1<<16);
}

void config_eint(void)
{
	PINSEL1|=1;
	PINSEL0|=0xA0000000;
//	PINSEL0|=(1<<29)|(1<<31);
	EXTMODE=0x7;
	EXTPOLAR=0;
}
