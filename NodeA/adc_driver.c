/*adc_D.c*/
/*
p0.27-->AIN0
p0.28-->AIN1
p0.29-->AIN2
p0.30-->AIN3
*/

#include"header.h"

void adc_init(void)
{
	PINSEL1|=0x15400000;
	ADCR=0x00200400;
}

unsigned int adc_read(unsigned char ch_num)
{
	unsigned int result=0;
	ADCR|=(1<<ch_num);
	ADCR|=(1<<24);
	while(((ADDR>>31)&1)==0);
	ADCR^=(1<<24);
	ADCR^=(1<<ch_num);
	result=(ADDR>>6)&0x3ff;
	return result;
}
