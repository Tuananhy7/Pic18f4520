#include <p18f4520.h>
#include <delays.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include<usart.h>

#include"var.h"
#include"lcd.h"
#include"1wire.h"

#pragma config OSC = HS
#pragma config MCLRE = ON
#pragma config WDT = OFF
#pragma config LVP = OFF
#pragma config PBADEN = OFF

#define MODE 		PORTBbits.RB3

#define SPEAKER 	PORTDbits.RD3
#define QUAT 		PORTDbits.RD4
#define DEN 		PORTDbits.RD5
#define MOTOR 		PORTDbits.RD6

char lcd[16];

char *nhietdo = "000.00 C";
volatile int nhietdo_set = 37;			// khoi tao nhiet do setup ở mức 37 độ

uint8_t kiemtra_button = 0;
uint8_t setup_mode = 0;

void get_ds18b20(void);					// đọc nhiệt độ từ ds18b20 xuất ra màn hình lcd
void nhietdo_setup(void);
void __aptrung(const int temp);
int convert_string(char *string);
void keu_coi_chip(void);

void INT0(void);						// hàm phục vụ ngắt ngoài
#pragma code ngat_cao=0x08
void interrupt_ngat_cao(void)
{
	INT0();
}
#pragma code
#pragma interrupt INT0
void INT0(void)
{
	if(INTCONbits.INT0IF==1)
	{
		INTCONbits.INT0IF=0;
	}
	if(INTCON3bits.INT1IF==1)
	{
		
		INTCON3bits.INT1IF=0;
		
		nhietdo_set++;										 	// in gia tri button press
		
		lcd_gotoxy(0,1);
		sprintf(&lcd[0], "NHIET DO: %2d C", nhietdo_set);
		lcd_puts(lcd);
	}
	if(INTCON3bits.INT2IF==1)
	{
		INTCON3bits.INT2IF=0;
		
		nhietdo_set--;											// in gia tri button press
		
		lcd_gotoxy(0,1);
		sprintf(&lcd[0], "NHIET DO: %2d C", nhietdo_set); 
		lcd_puts(lcd);
	}
}

void get_ds18b20(void)
{
	//bat dau doc nhiet do va tra ve cho bien "nhietdo"
	nhietdo = ds18b20_readtemp();
	//di chuyen con tro lcd den hang 0 cot 0
	lcd_gotoxy(0,0);
	// xuat du lieu ra man hinh lcd
	sprintf(&lcd[0],"ds18b20:"); lcd_puts(lcd);
	lcd_puts(nhietdo);                         		// Display temperature
}

void main()
{
	T0CON=0x84; 				//khoi tao timer0
	ADCON1 = 0x0f;
	INTCONbits.GIE=1;
	INTCONbits.PEIE=1;
	RCONbits.IPEN=1; 			// cho phep uu tien ngat
	INTCON3bits.INT1IP=1;
	INTCON3bits.INT2IP=1;
	
	// bat intertupt 0,1,2
	INTCON3bits.INT1IE=1;
	INTCON3bits.INT2IE=1;
	INTCONbits.INT0IE=1;
	// chon suon ngat int
	INTCON2bits.INTEDG0=1;
	INTCON2bits.INTEDG1=1;
	INTCON2bits.INTEDG2=1;
	
	TRISB=0b00001111;
	TRISD=0x00;
	Lcd_Init();
	
	// khoi tao lcd
	lcd_gotoxy(0,0);
	sprintf(&lcd[0],"Starting..."); lcd_puts(lcd);
	delay_ms(500);
	lcd_clear();

	while(1)
	{
		if(!MODE)
		{
			while(!MODE){																// giữ phím để chuyển chế độ
				kiemtra_button++;
				delay_ms(250);
				
				lcd_gotoxy(14,0);
				sprintf(&lcd[0], "-%d", kiemtra_button); lcd_puts(lcd);
				
				if(kiemtra_button > 6) {setup_mode =~ setup_mode; lcd_clear(); break;} 	// cho qua 3 giay
			};
			kiemtra_button = 0;
			keu_coi_chip();
		}
		// vào chế độ SETUP
		if(setup_mode)
		{
			nhietdo_setup();
			continue;
		}
		// doc gia tri cam bien
		get_ds18b20();
		// kiểm soát nhiệt độ đã được set từ hàm nhietdo_setup()
		__aptrung(nhietdo_set);
		// in ra màn hình nhiệt độ ngưỡng đã setup
		lcd_gotoxy(0,1);
		sprintf(&lcd[0], "nhiet do set: %2d", nhietdo_set); lcd_puts(lcd);
		
		delay_ms(2);                               								// Wait 2 mini second
	}
}

void nhietdo_setup(void)
{
	lcd_gotoxy(0,0);
	sprintf(&lcd[0], "SETUP"); lcd_puts(lcd);
	lcd_gotoxy(0,1);
	sprintf(&lcd[0], "NHIET DO: %2d C", nhietdo_set); lcd_puts(lcd);
	delay_ms(100);
}

// ham dieu khiem khiem soat nhiet do ds18b20
void __aptrung(const int temp)
{
	int temp_ds18b20 = convert_string(nhietdo);
	
	if(temp_ds18b20 < temp) 			// nho hon nhiet do setup
	{
		DEN = 1;
		QUAT = 0;
	}
	else if(temp_ds18b20 > temp)		// lon hon nhiet do setup
	{
		DEN = 0;
		QUAT = 1;
	}
	else DEN = QUAT = 0;				// bang nhiet do setup
}

// chuyen du lieu 2 so nhiet do tu string sang int
int convert_string(char *string)
{
	int res = 0;
	
	res += (int)(string[1] - '0') * 10;
	res += (int)(string[2] - '0');
	
	if(string[0] == '1')
		res += (string[0] - '0') * 100;
	
	if(string[0] == '-')
		res=~res;

	return res;
}
// hàm chạy để làm kêu còi chíp trên mạch
void keu_coi_chip(void)
{
	int i=0;
	for(i=0; i<6; i++)
	{
		SPEAKER=~SPEAKER;
		delay_ms(100);
	}
}
/* END OF FILE */