//..............................................................................//
// 	thu vien LCD su dung 4 hoac 8 chan du lieu					     			//
//	Mac dinh khoi tao che do 2 dong. font 5x7									//
//	co the su dung voi tan so thach anh: 4Mhz, 8Mhz, 11,095Mhz, 12Mhz, 20Mhz	//
//	su dung cho pic18f4520														//
//  duoc viet boi Hoang Van Loi													//
//  emai: loi.efy@gmail.com														//
//..............................................................................//
 

#ifndef _LCD_H_
#define _LCD_H_

#include<p18f4520.h>
#include<delays.h>
#include<string.h>

#define FOSC 12000000  // tan so thach anh 20 Mhz


/*---------------------------------------------------------------------
	De su dung che do 4 bit thi them #define FOUR o ben duoi #FOSC 20000000
	Khi su dung che do 4 bit ta chi quan tam den cac chan:
	RS			|
	E			|
	LCD_D7		|
	LCD_D6		|  cac chan nay deu thay doi duoc
	LCD_D5		|
	LCD_D4		|
	--------------------------------------------------------------------
*/
#define FOUR  // dinh nghia su dung 4 bit, neu dung 8 bit thi delete di
//#define USE_RW // dinh nghia su dung chan RW
//
// luu y: khi su dung RW thi ta co the su dung ham Busy_Lcd();
//
//------------------------------------------------------------------
//   cac lenh dua vao Cmd_Lcd();
//------------------------------------------------------------------
#define CLEAR 0x01  // lenh xoa man hinh
#define CURSOR_BACK 0x02	// dua con tro ve dau dong
#define BLINK_ON 0x06	// cho con tro tu dong nhay vi tri
#define CURSOR_OFF_DON 0x0C	// tat con tro, bat man hinh
#define CURSOR_ON_DON 0x0E	// bat con tro, bat man hinh
#define SET_CUR_LINE1 0x80	// dua con tro ve dau dong 1
#define SET_CUR_LINE2 0xC0	// dua con tro ve dau dong 2
#define BIT8_2LINE_5X7 0x38	// lcd 8 bit. 2 dong font 5x7
#define BIT4_2LINE_5X7 0x28	// lcd 4 bit. 2 dong font 5x7


//-----------------------------------------------------------------
//   Dinh nghia cac chan Du Lieu ra va chan Dieu khien
//-----------------------------------------------------------------
#define RS PORTDbits.RD2	// chan dieu khien RS
#define TRISRS TRISDbits.TRISD2

#ifdef USE_RW  // neu da dinh nghia USE_RW thi dinh nghia su dung RW
#define RW PORTCbits.RC1
#define TRISRW TRISCbits.TRISC1
#endif

#define E PORTCbits.RC4		// chan dieu khien E
#define TRISEN	TRISCbits.TRISC4

#define DATA PORTC		// PORT du lieu, chi su dung trong che do 8 bit
#define DATATRIS TRISC

#define LCD_D7 PORTCbits.RC2	// 
#define LCD_D7TRIS	TRISCbits.TRISC2

#define LCD_D6 PORTCbits.RC3	//	4 chan du lieu
#define LCD_D6TRIS	TRISCbits.TRISC3

#define LCD_D5 PORTDbits.RD0	//  chi su dung trong che do 4 bit
#define LCD_D5TRIS	TRISDbits.TRISD0

#define LCD_D4 PORTDbits.RD1	//
#define LCD_D4TRIS	TRISDbits.TRISD1

//-------------------------------------------------------------------

void delay_1_6ms(void); // ham delay 1,6ms
void delay_1ms(void);// ham delay 1ms
void delay_2ms(void); // ham delay 2 miligiay
void delay_37us(void);// ham delay 37 microgiay
void Lcd_Write_Low_Nibble(unsigned char b);// ham gui 4 bit cao
void Lcd_Write_High_Nibble(unsigned char b);// ham gui 4 bit thap

void Cmd_Lcd(unsigned char a);// ham ghi lenh ra lcd 
void Write_Data(unsigned char b);// ham ghi du lieu ra lcd 

#ifdef USE_RW
char Busy_Lcd(void);
#endif

void Lcd_Init(void);// ham khoi tao lcd
void Put_String(char *);// ham hien thi 1 xau ki tu ra lcd
void lcd_gotoxy(unsigned char x, unsigned char y);// di den cot x, dong y
void Put_String_Add(unsigned char x, unsigned char y, char *a);// ham hien thi xau ki tu tai cot x, dong y
void Put_Char_Add(unsigned char x, unsigned char y, char a);// ham hien thi ki tu tai cot x, dong y
void lcd_clear(void);// ham xoa man hinh
void lcd_puts(char *string);
void delay_ms(unsigned int time);

/*
//------------------------------------------------------
// dinh nghia lai cac chan
//--------------------------------------------------------
#define A0 PORTAbits.RA0
#define A1 PORTAbits.RA1
#define A2 PORTAbits.RA2
#define A3 PORTAbits.RA3
#define A4 PORTAbits.RA4
#define A5 PORTAbits.RA5

#define B0 PORTBbits.RB0
#define B1 PORTBbits.RB1
#define B2 PORTBbits.RB2
#define B3 PORTBbits.RB3
#define B4 PORTBbits.RB4
#define B5 PORTBbits.RB5
#define B6 PORTBbits.RB6
#define B7 PORTBbits.RB7

#define C0 PORTCbits.RC0
#define C1 PORTCbits.RC1
#define C2 PORTCbits.RC2
#define C3 PORTCbits.RC3
#define C4 PORTCbits.RC4
#define C5 PORTCbits.RC5
#define C6 PORTCbits.RC6
#define C7 PORTCbits.RC7

#define D0 PORTDbits.RD0
#define D1 PORTDbits.RD1
#define D2 PORTDbits.RD2
#define D3 PORTDbits.RD3
#define D4 PORTDbits.RD4
#define D5 PORTDbits.RD5
#define D6 PORTDbits.RD6
#define D7 PORTDbits.RD7

#define E0 PORTEbits.RE0
#define E1 PORTEbits.RE1
#define E2 PORTEbits.RE2
#define E3 PORTEbits.RE3

#define TA0 TRISAbits.TRISA0
#define TA1 TRISAbits.TRISA1
#define TA2 TRISAbits.TRISA2
#define TA3 TRISAbits.TRISA3
#define TA4 TRISAbits.TRISA4
#define TA5 TRISAbits.TRISA5

#define TB0 TRISBbits.TRISB0
#define TB1 TRISBbits.TRISB1
#define TB2 TRISBbits.TRISB2
#define TB3 TRISBbits.TRISB3
#define TB4 TRISBbits.TRISB4
#define TB5 TRISBbits.TRISB5
#define TB6 TRISBbits.TRISB6
#define TB7 TRISBbits.TRISB7

#define TC0 TRISCbits.TRISC0
#define TC1 TRISCbits.TRISC1
#define TC2 TRISCbits.TRISC2
#define TC3 TRISCbits.TRISC3
#define TC4 TRISCbits.TRISC4
#define TC5 TRISCbits.TRISC5
#define TC6 TRISCbits.TRISC6
#define TC7 TRISCbits.TRISC7

#define TD0 TRISDbits.TRISD0
#define TD1 TRISDbits.TRISD1
#define TD2 TRISDbits.TRISD2
#define TD3 TRISDbits.TRISD3
#define TD4 TRISDbits.TRISD4
#define TD5 TRISDbits.TRISD5
#define TD6 TRISDbits.TRISD6
#define TD7 TRISDbits.TRISD7

#define TE0 TRISEbits.TRISE0
#define TE1 TRISEbits.TRISE1
#define TE2 TRISEbits.TRISE2
#define TE3 TRISEbits.TRISE3

*/

#endif
