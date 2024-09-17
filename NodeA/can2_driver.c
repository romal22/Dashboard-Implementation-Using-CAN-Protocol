#include "header.h"
void can_init(void)
{
	PINSEL1|=0x14000;//P0.23,P0.24-->RD1
	VPBDIV=1;//PCLK=60kHz
	C2MOD=1;//resent mode select
	C2BTR=0x001c001d;//125 kbps bade
	AFMR=0x2;//ACCBP 
	C2MOD=0;//relese resent mode
}
#define TCS ((C2GSR>>3)&1)

void can_tx(CAN v)
{
	C2TID1=v.id;
	C2TFI1=(v.dlc<<16);//select dlc
										 //select rtr=0,pl=0
	if(v.rtr==0)//if data frame
	{
		C2TDA1=v.byteA;
		C2TDB1=v.byteB;
	}
	else//if remote frame
	{
		C2TFI1|=(1<<30);//rtr=1
	}
	C2CMR=1|(1<<5);//start xmission
	while(TCS==0);
}
#define RBR ((C2GSR)&1)

void can_rx(CAN *p)
{
	while(RBR==0);
	p->id=C1RID;
	p->dlc=(C2RFS>>16)&0xf;
	p->rtr=(C2RFS>>30)&1;
	
	if(p->rtr==0)//if data frame
	{
		p->byteA=C2RDA;
		p->byteB=C2RDB;
	}
	C2CMR=(1<<2);//*relese rx buffer
}
