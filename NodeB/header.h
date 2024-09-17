#include<lpc21xx.h>

/*-------can----------*/
typedef struct CAN_MSG
{
unsigned int id;
unsigned int byteA;
unsigned int byteB;
unsigned char dlc;
unsigned char rtr;
}CAN;

extern void can_init(void);
extern void can_tx(CAN );
extern void can_rx(CAN *);


/*--------can interrupt--------*/
extern void config_vic_for_can2(void);

/*-------i2c----------*/
extern void i2c_init(void);
extern void i2c_byte_write_frame(unsigned char,unsigned char,unsigned char);
extern unsigned char i2c_byte_read_frame(unsigned char,unsigned char);


/*--------uart--------*/
extern void uart0_init(unsigned int);
extern void uart0_tx(unsigned char);
extern void uart0_tx_string(char *);
extern void uart0_tx_int(int);
extern void uart0_tx_float(float);


/*---------delay-------*/
extern void delay_ms(unsigned int);


/*---------lcd----------*/
extern void lcd_data(unsigned char);
extern void lcd_cmd(unsigned char);
extern void lcd_init(void);
extern void lcd_string(char *);
extern void lcd_int(int);
extern void lcd_float(float);

/*---------cgram------------*/
extern void cgram_lcd(void);
//extern void cgram_lcd_p(char *);

/*---------delay------------*/

extern void VIC_config(void);
extern void time1_config(void);


//------------------------------------------------

//#include<lpc21xx.h>
//
//extern void delay_ms(unsigned int);
//
///*__________can-driver__________*/
//
//typedef struct CAN2_MSG
//{
//	unsigned int id;
//	unsigned int byteA;
//	unsigned int byteB;
//	unsigned char dlc;
//	unsigned char rtr;
//}CAN;
//
//extern void can_init(void);
//extern void can_rx(CAN *);
//extern void config_vic_for_can2(void);
//
//
///*_________i2c-driver________*/
//
//extern void i2c_init(void);
//extern void i2c_byte_write_frame(unsigned char,unsigned char,unsigned char);
//extern unsigned char i2c_byte_read_frame(unsigned char,unsigned char);
//
///*__________lcd-driver________*/
//
//extern void lcd_init(void);
//extern void lcd_data(unsigned char);
//extern void lcd_cmd(unsigned char);
//extern void lcd_atoi(unsigned int);
//extern void lcd_string(char *);
//extern void cgram_lcd(void);
//
////extern void cgram_lcd(void);
//
//extern void delay_ms(unsigned int);
//
///*__________uart-driver_________*/
//
//extern void uart0_init(unsigned int);
//extern void uart0_tx_string(char *);
//extern void uart0_tx(unsigned char );
//extern void uart0_tx_int(int);


