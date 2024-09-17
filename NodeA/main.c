//#include<lpc21xx.h>
//#include"header.h"
//
//unsigned int count0,count1,count2;
//unsigned int f,flag0,flag1,flag2;
//
//#define sw1 ((IOPIN0>>14)&1)
//#define sw2 ((IOPIN0>>15)&1)
//#define sw3 ((IOPIN0>>16)&1)
//
//int main()
//{
//
//	CAN temp,pot,s1,s2,s3;
//
//	pot.id=0x123; pot.rtr=0; pot.dlc=8;
//	temp.id=0x456; temp.rtr=0; temp.dlc=8;
//	s1.id=0x111; s1.rtr=0; s1.dlc=8;
//
//	can_init();
//	adc_init();
//	uart0_init(9600);
//	config_vic_for_eint();
//	config_eint();
//	config_timer();
//	config_vic_for_timer();
//
//	while(1)
//	{
//		if(f==1)
//		{
//			f=0;
//			pot.byteA=adc_read(2);
//			can_tx(pot);
//			delay_ms(1000);
//			temp.byteA=adc_read(1);
//			can_tx(temp);
//		}
//
//		if(flag0==1)
//		{
//			flag0=0;
//			s1.byteA=0x10;
//			can_tx(s1);
//		}
//
//		if(flag1==1)
//		{
//			flag1=0;
//			s1.byteA=0x20;
//			can_tx(s1);
//		}
//
//		if(flag2==1)
//		{
//			flag2=0;
//			s1.byteA=0x30;
//			can_tx(s1);
//		}
//	}
//}


















#include<lpc21xx.h>
#include"header.h"

unsigned int count0,count1,count2;
unsigned int f=0,flag0=0,flag1=0,flag2=0;

#define sw1 ((IOPIN0>>14)&1)
#define sw2 ((IOPIN0>>15)&1)
#define sw3 ((IOPIN0>>16)&1)

int main()
{

	CAN temp,pot,s1,s2,s3;

	pot.id=0x123;	pot.rtr=0;	pot.dlc=8;
	temp.id=0x456;	temp.rtr=0;	temp.dlc=8;
	s1.id=0x111;	s1.rtr=0;	s1.dlc=8;

	can_init();
	adc_init();
	uart0_init(9600);
	config_eint();
	config_vic_for_eint();
	config_timer();
	config_vic_for_timer();

	
	while(1)
	{
		if(f==1)
		{
			uart0_tx_string("\r\n");
			pot.byteA=adc_read(2);
			uart0_tx_int(pot.byteA);
			can_tx(pot);
			delay_ms(500);
			temp.byteA=adc_read(1);
			uart0_tx_string("\r\n");
			uart0_tx_int(temp.byteA);
			can_tx(temp);
			f=0;
		}
		
		if(flag0==1)
		{
			uart0_tx_string("\r\n00000000000");
			flag0=0;
			s1.byteA=0x10;
			can_tx(s1);
		}
		
		if(flag1==1)
		{
			uart0_tx_string("\r\n11111111111");
			flag1=0;
			s1.byteA=0x20;
			can_tx(s1);
		}
		
		if(flag2==1)
		{
			uart0_tx_string("\r\n222222222222");
			flag2=0;
			s1.byteA=0x30;
			can_tx(s1);
		}
	}
}
