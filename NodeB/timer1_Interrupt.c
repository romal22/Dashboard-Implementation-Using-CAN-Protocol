/*timer1_interrupt.c*/
#include"header.h"
extern char f;
void time1_hdl(void)__irq
{
	f=1;
	T1IR=1;
	VICVectAddr=0;	
}

void config_vic_for_timer(void)
{
	VICIntSelect=0;//for irq selecct

	VICVectCntl1=5|(1<<5);//stor valu

	VICVectAddr1=(unsigned int)time1_hdl;//store add

	VICIntEnable=(1<<5);//enabal EINT0 in vic
}

void config_time(void)
{
	T1PC=0x0;//prescaler counter
	T1PR=60000-1;//prescaler register
	//T1PR=15000-1;//prescaler register
	T1TC=0;//timer counter
	T1MR0=1000;
	T1MCR=3;
	T1TCR=1;//stert timer
}
