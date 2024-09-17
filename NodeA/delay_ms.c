#include"header.h"

void delay_ms(unsigned int ms)
{
	int a[]={15,60,30,15,15};
	unsigned int pclk;
	T0PC=0;
	T0PR=(pclk*1000)-1;
	T0TC=0;
	T0TCR=1;
	while(T0TC<ms);
	T0TCR=0;
}

