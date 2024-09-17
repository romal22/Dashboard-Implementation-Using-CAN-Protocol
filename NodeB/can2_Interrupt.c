/*can2_Interrupt.c*/
#include "header.h"
extern unsigned int f1;
extern CAN m;
void can2_handaler(void)__irq
{
	f1=1;
	m.id=C2RID;
	m.dlc=((C2RFS>>16)&0xf);
	m.rtr=(C2RFS>>30)&1;
	if(m.rtr==0)//if data frame
	{
		m.byteA=C2RDA;
		m.byteB=C2RDB;
	}
	C2CMR=(1<<2);//*relese rx buffer
	VICVectAddr=0;	
}
void config_vic_for_can2(void)
{
	VICIntSelect=0;//for irq selecct

	VICVectCntl0=27|(1<<5);//stor valu

	VICVectAddr0=(unsigned int)can2_handaler;//store add

	VICIntEnable|=(1<<27);//enabal EINT0 in vic

	C2IER=1;//EN CAN2 RX int in CAN2peripheral

}
