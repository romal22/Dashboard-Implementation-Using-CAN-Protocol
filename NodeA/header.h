#include<lpc21xx.h>

extern void delay_ms(unsigned int );


/*--------CAN------*/

typedef struct CAN_MSG
{
	unsigned int id;
	unsigned int byteA;
	unsigned int byteB;
	unsigned char dlc;
	unsigned char rtr;
}CAN;

extern void can_init(void);
extern void can_tx(CAN v);


/*-----adc--------*/
extern void adc_init(void);
extern unsigned int adc_read(unsigned char ch_num);


/*----external interrupt--------*/
extern void config_vic_for_eint(void);
extern void config_eint(void);


/*------uart-----------*/
extern void uart0_init(unsigned int );
extern void uart0_tx(unsigned char );
extern void uart0_tx_string(char *);
extern void uart0_tx_int(int);

/*-----------time interrupt-----------*/

//extern void config_timer(void);
//extern void config_vic_for_timer(void);

