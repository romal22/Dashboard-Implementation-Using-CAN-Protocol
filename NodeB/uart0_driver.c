/*uart0_d.c*/
/*p0.0-->tx,p0.1-->rx*/

#include"header.h"
#define THRE ((U0LSR>>5)&1)
#define RDR ((U0LSR)&1)

void uart0_init(unsigned int baud)
{
	unsigned int result=0;
	int a[]={15,60,30,15,15};
	unsigned int pclk=a[VPBDIV]*1000000;
	result=pclk/(16*baud);
	PINSEL0|=5;
	U0LCR=0x83;
	U0DLL=result&0xff;
	U0DLM=(result>>8)&0xff;
	U0LCR=0x03;
}

void uart0_tx(unsigned char data)
{
	U0THR=data;
	while(THRE==0);
}

unsigned char uart0_rx(void)
{
	while(RDR==0);
	return(U0RBR);
}

void uart0_tx_string(char *sp)
{
	while(*sp)
	{
		uart0_tx(*sp);
		sp++;
	}
}

void uart0_tx_int(int num)
{
	int n[15],i=0;
	if(num==0)
	{
		uart0_tx('0');
	}
	else if(num<0)
	{
		uart0_tx('-');
		num=-num;
	}
	while(num)
	{
		n[i]=(num%10)+48;
		num=num/10;
		i++;
	}
	for(i=i-1;i>=0;i--)
	{
		uart0_tx(n[i]);
	}
}

void uart0_tx_float(float f)
{
	int num;
	if(f==0)
	{
		uart0_tx_string("0.0\n\r");
	}
	num=f;
	uart0_tx_int(num);
	uart0_tx('.');
	num=(f-num)*100;
	uart0_tx_int(num);	
}
