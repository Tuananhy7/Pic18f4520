#ifndef __DELAY_TIMER0__
#define __DELAY_TIMER0__

//code su dung FOSC 8000000 tan so thach anh 8 Mhz

#include <p18f4520.h>
#include <delays.h>

// C program for implementation of ftoa() 
#include <math.h> 
#include <stdio.h> 

#define delay_timer0_us(time)		\
{									\
		TMR0L = (65536 - time)%256;	\
		TMR0H = (65536 - time)/256;	\
		T0CONbits.TMR0ON = 1;		\
		while(!INTCONbits.TMR0IF);	\
		T0CONbits.TMR0ON = 0;		\
		INTCONbits.TMR0IF = 0;		\
}						

//1ms voi thach anh 8MHz
void delay_ms(unsigned int time);

void delay_init_timer0(void);

void reverse(char* str, int len);
int intToStr(int x, char str[], int d);
void ftoa(float n, char* res, int afterpoint); 

//void out_console(char array[], int index);

#endif