#include<lpc21xx.h>
#include"header.h"

unsigned int f1,f;
CAN m;

int main()
{
	unsigned char min,hrs,h,date,month,am_pm;
	float vout1,vout2;
	int temperature,t1,i1=0,i2=0,i3=0,h1=0;

	can_init();
	i2c_init();
	uart0_init(9600);
	lcd_init();
	config_vic_for_can2();
	cgram_lcd();
	config_vic_for_timer();
	config_time();


  	i2c_byte_write_frame(0xD0,0x1,0x15);
  	i2c_byte_write_frame(0xD0,0x2,0x08);
  	i2c_byte_write_frame(0xD0,0x4,0x6);
  	i2c_byte_write_frame(0xD0,0x5,0x1);

	while(1)
	{
		min=i2c_byte_read_frame(0xD0,0x1);
		hrs=i2c_byte_read_frame(0xD0,0x2);
		date=i2c_byte_read_frame(0xD0,0x4);
		month=i2c_byte_read_frame(0xD0,0x5);
		
		h=hrs&(0x1F);
		am_pm=(h>>5)&1;
		uart0_tx_int(am_pm);
		uart0_tx_string("\r\n");

		lcd_cmd(0xC0);
		lcd_data((h/0x10)+48);
		lcd_data((h%0x10)+48);
		lcd_data(':');
		lcd_data((min/0x10)+48);
		lcd_data((min%0x10)+48);
		delay_ms(1000);
	
		lcd_cmd(0xC6);
		if(am_pm==1)
			lcd_string("PM");
		else
			lcd_string("AM");
		
		lcd_cmd(0xC9);
		lcd_data((date/10)+48);
		lcd_data((date%10)+48);
		lcd_data('/');
		lcd_data((month/10)+48);
		lcd_data((month%10)+48);

		
		if(f1==1)
		{
			f1=0;
			if(m.rtr==0)
			{
				if(m.id==0x456)
				{
					vout2=(3.3*m.byteA)/1023;
					temperature=(vout2-0.5)/0.01;
					uart0_tx_int(temperature);
					uart0_tx_string("\r\n");
					lcd_cmd(0x80);
					lcd_string("ENG:");
					lcd_int(temperature);
					lcd_cmd(0x86);
					lcd_data('c');
				}
	
				if(m.id==0x123)
				{
					uart0_tx_int(m.byteA);
					uart0_tx_string("\r\n");
					vout1=(3.3*m.byteA)/1023;
					uart0_tx_float(vout1);
					uart0_tx_string("\r\n");
					lcd_cmd(0x88);
					if(vout1>=0&&vout1<=0.66)
					{
						lcd_data(0);
					}
					else if(vout1>0.66&&vout1<=1.32)
					{
						lcd_data(1);
					}
					else if(vout1>1.32&&vout1<=1.98)
					{
						lcd_data(2);
					}
					else if(vout1>1.98&&vout1<=2.64)
					{
						lcd_data(3);
					}
					else if(vout1>2.64&&vout1<=3.3)
					{
						lcd_data(4);
					}
				}
				if(m.id==0x111)
				{
					t1=m.byteA;
					t1=t1&0xff;
		
					if(t1==0x10)
					{
						uart0_tx_string("\r\nswitchhhhhhhhh111111111");
						if(i1==20)
						{
							lcd_cmd(0x8E);
							lcd_data(' ');
						}
						i3^=1;
						if(i3==1)
						{
							i1=10;
						}
						else
						{
							i1=0;
						}
					}
	
					else if(t1==0x20)
					{
						uart0_tx_string("\r\nswitchhhhhhhhh2222222222");
						if(i1==10)
						{
							lcd_cmd(0x8A);
							lcd_data(' ');
						}
						i3^=1;
						if(i3==1)
						{
							i1=20;
						}
						else
						{
							i1=0;
						}
					}
					else if(t1==0x30)
					{
						uart0_tx_string("\r\nswitchhhhhhhhh333333333333");
						lcd_cmd(0x8c);
						h1^=1;
						if(h1==1)
						{
							lcd_data(7);
						}
						else
						{
							lcd_data(' ');
						}
					}
				}
			}	   	
	
			if(f==1)
		 	{
		 		f=0;
		 		if(i1==10)
		 		{
		 			lcd_cmd(0x8A);
		 			i2^=1;
		 			if(i2==1)
		 			{
		 				lcd_data(5);
		 			}
		 			else
		 			{
		 				lcd_data(' ');
		 			}
		 		}
		 		else if(i1==20)
		 		{
		 			lcd_cmd(0x8E);
		 			i2^=1;
		 			if(i2==1)
		 			{
		 				lcd_data(6);
		 			}
		 			else
		 			{
		 				lcd_data(' ');
		 			}
		 		}
	 		}
		}	
	}
}



