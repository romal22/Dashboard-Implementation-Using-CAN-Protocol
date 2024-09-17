#include"header.h"

void delay_ms(unsigned int ms)
{
unsigned int pclk;
int a[]={15,60,30,15,15};
T0PC=0;
pclk=a[VPBDIV]*1000;
T0PR=pclk-1;
T0TC=0;
T0TCR=1;
while(T0TC<ms);
T0TCR=0;
}


#define RS (1<<17)
#define RW (1<<18)
#define EN (1<<19)

void lcd_data(unsigned char ch)
{
IOCLR1|=0xFE<<16;
IOSET1|=(ch&0xF0)<<16;
IOSET1|=RS;
IOCLR1|=RW;
IOSET1|=EN;
delay_ms(2);
IOCLR1|=EN;

IOCLR1|=0xFE<<16;
IOSET1|=(ch&0x0F)<<20;
IOSET1|=RS;
IOCLR1|=RW;
IOSET1|=EN;
delay_ms(2);
IOCLR1|=EN;
}

void lcd_cmd(unsigned char cmd)
{
IOCLR1|=0xFE<<16;
IOSET1|=(cmd&0xF0)<<16;
IOCLR1|=RS;
IOCLR1|=RW;
IOSET1|=EN;
delay_ms(2);
IOCLR1|=EN;

IOCLR1|=0xFE<<16;
IOSET1|=(cmd&0x0F)<<20;
IOCLR1|=RS;
IOCLR1|=RW;
IOSET1|=EN;
delay_ms(2);
IOCLR1|=EN;
}

void lcd_init()
{
IODIR1|=0xFE<<16;
IOCLR1|=EN;
PINSEL2|=0x0;
lcd_cmd(0x02);
lcd_cmd(0x28);
lcd_cmd(0x0C);
lcd_cmd(0x01);
}

void lcd_string(char *p)
{
while(*p)
{
lcd_data(*p);
p++;
}
}

void lcd_int(int num)
{
int n[15],i=0;
if(num==0)
{
lcd_data('0');
}
else if(num<0)
{
lcd_data('-');
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
lcd_data(n[i]);
}
}

void lcd_float(float num)
{
int t;
t=num;
lcd_int(t);
lcd_data('.');
t=(num-t)*10;
lcd_int(t);
}







//////#include"header.h"
//////
//////void delay_ms(unsigned int ms)
//////{
//////	T0PC=0;
//////	T0PR=15000-1;
//////	T0TC=0;
//////	T0TCR=1;
//////	while(T0TC<ms);
//////	T0TCR=0;
//////}
//////
//////
//////#define RS (1<<17)
//////#define RW (1<<18)
//////#define EN (1<<19)
//////
//////void lcd_data(unsigned char ch)
//////{
//////	IOCLR1|=0xFE<<16;
//////	IOSET1|=(ch&0xF0)<<16;
//////	IOSET1|=RS;
//////	IOCLR1|=RW;
//////	IOSET1|=EN;
//////	delay_ms(2);
//////	IOCLR1|=EN;
//////	
//////	IOCLR1|=0xFE<<16;
//////	IOSET1|=(ch&0x0F)<<20;
//////	IOSET1|=RS;
//////	IOCLR1|=RW;
//////	IOSET1|=EN;
//////	delay_ms(2);
//////	IOCLR1|=EN;
//////}
//////
//////void lcd_cmd(unsigned char cmd)
//////{
//////	IOCLR1|=0xFE<<16;
//////	IOSET1|=(cmd&0xF0)<<16;
//////	IOCLR1|=RS;
//////	IOCLR1|=RW;
//////	IOSET1|=EN;
//////	delay_ms(2);
//////	IOCLR1|=EN;
//////	
//////	IOCLR1|=0xFE<<16;
//////	IOSET1|=(cmd&0x0F)<<20;
//////	IOCLR1|=RS;
//////	IOCLR1|=RW;
//////	IOSET1|=EN;
//////	delay_ms(2);
//////	IOCLR1|=EN;
//////}
//////
//////void lcd_init()
//////{
//////	IODIR1|=0xFE<<16;
//////	IOCLR1|=EN;
//////	PINSEL2|=0x0;
//////	lcd_cmd(0x02);
//////	lcd_cmd(0x28);
//////	lcd_cmd(0x0C);
//////	lcd_cmd(0x01);
//////}
//////
//////void lcd_string(char *p)
//////{
//////	while(*p)
//////	{
//////		lcd_data(*p);
//////		p++;
//////	}
//////}
//////
//////void lcd_atoi(unsigned int temp)
//////{
//////	
//////}
