//..............................................................................//
// 	thu vien LCD su dung 4 hoac 8 chan du lieu					     			//
//	Mac dinh khoi tao che do 2 dong. font 5x7									//
//	co the su dung voi tan so thach anh: 4Mhz, 8Mhz, 11,095Mhz, 12Mhz, 20Mhz	//
//	su dung cho pic18f4520														//
//  duoc viet boi Hoang Van Loi													//
//  emai: loi.efy@gmail.com														//
//..............................................................................//
 


#include"LCD.h"


typedef struct
{
	unsigned DT0:1;
	unsigned DT1:1;
	unsigned DT2:1;
	unsigned DT3:1;
	unsigned DT4:1;
	unsigned DT5:1;
	unsigned DT6:1;
	unsigned DT7:1;
} byte;



#ifdef USE_RW
char Busy_Lcd(void)
{
	byte KT;
	LCD_D7 = 1;			// Read data
	E=1;
	RS = 0;
	RW = 1;			// Read
	while(LCD_D7)
	{
		E=0;
		delay_1ms();
		E=1;
	}
}

#endif


#if(FOSC == 20000000)// FOSC = 20 MHZ
	void delay_2ms(void)
	{
		Delay1KTCYx(10);
	}
	void delay_1_6ms(void)
	{
		Delay1KTCYx(8);
	}
	
	void delay_1ms(void)
	{
		Delay1KTCYx(5);
	}
	
	void delay_37us(void)
	{
		Delay10TCYx(19);	
	}
	
#elif(FOSC == 11059200)// FOSC = 11059200 HZ
	void delay_2ms(void)
	{
		Delay1KTCYx(5);
		Delay10TCYx(60);
	}
	
	void delay_37us(void)
	{
		Delay10TCYx(11);	
	}
	void delay_1_6ms(void)
	{
		Delay1KTCYx(5);
	}
	
	void delay_1ms(void)
	{
		Delay1KTCYx(3);
	}

#elif(FOSC == 12000000)// FOSC = 12 MHZ
	void delay_2ms(void)
	{
		Delay1KTCYx(6);
	}
	
	void delay_37us(void)
	{
		Delay10TCYx(12);
		
	}
	void delay_1_6ms(void)
	{
		Delay1KTCYx(5);
	}
	
	void delay_1ms(void)
	{
		Delay1KTCYx(3);
	}
#elif(FOSC == 8000000)// FOSC = 8 MHZ
	void delay_2ms(void)
	{
		Delay1KTCYx(4);
	}
	
	void delay_37us(void)
	{
		Delay10TCYx(8);
		
	}
	void delay_1_6ms(void)
	{
		Delay1KTCYx(3);
		Delay10TCYx(20);
	}
	
	void delay_1ms(void)
	{
		Delay1KTCYx(2);
	}

#elif(FOSC == 4000000)// FOSC = 4 MHZ
	void delay_2ms(void)
	{
	
		Delay1KTCYx(2);
	}
	
	void delay_37us(void)
	{
		Delay10TCYx(4);
		
	}
	void delay_1_6ms(void)
	{
		Delay1KTCYx(16);
	}
	
	void delay_1ms(void)
	{
		Delay1KTCYx(10);
	}
#elif(FOSC == 32000000)// FOSC = 32000000 HZ
	void delay_2ms(void)
	{
		Delay1KTCYx(16);
	}
	
	void delay_37us(void)
	{
		Delay10TCYx(30);	
	}
	void delay_1_6ms(void)
	{
		Delay1KTCYx(12);
		Delay10TCYx(80);
	}
	
	void delay_1ms(void)
	{
		Delay1KTCYx(8);
	}

#else
	#error "Khong co ham Delay_ms nao tuong ung"
#endif



/*-------------------------------------*-
	Lcd_Write_High_Nibble - Local Function
-*-------------------------------------*/
#ifdef FOUR
void Lcd_Write_High_Nibble(unsigned char b)
{
	/*
	byte Data;
	char dulieu[8]={0,0,0,0,0,0,0,0},i, du;
	i=0;
	while(b!=0)
	{
		du= b % 2;
		dulieu[i]= du;
		i++;
		b= b/2;
	}
	
	if (dulieu[7]==0) Data.DT7= 0; else Data.DT7=1;
	if (dulieu[6]==0) Data.DT6= 0; else Data.DT6=1;
	if (dulieu[5]==0) Data.DT5= 0; else Data.DT5=1;
	if (dulieu[4]==0) Data.DT4= 0; else Data.DT4=1;

	
	LCD_D7= Data.DT7;
	LCD_D6= Data.DT6;
	LCD_D5= Data.DT5;
	LCD_D4= Data.DT4;
	*/
	
	// Neu trinh bien dich nao khong dich duoc 4 
	// dong code duoi nay thi su dung
	// doan code ben tren va xoa 4 dong nay di
	LCD_D7= (b>>7)&0x01;
	LCD_D6= (b>>6)&0x01;
	LCD_D5= (b>>5)&0x01;
	LCD_D4= (b>>4)&0x01;
}

/*-------------------------------------*-
	Lcd_Write_High_Low - Local Function
-*-------------------------------------*/
void Lcd_Write_Low_Nibble(unsigned char b)
{
	/*
	byte Data;
	char dulieu[8]={0,0,0,0,0,0,0,0},i, du;
	i=0;
	while(b!=0)
	{
		du= b % 2;
		dulieu[i]= du;
		i++;
		b= b/2;
	}
	
	if (dulieu[3]==0) Data.DT3= 0; else Data.DT3=1;
	if (dulieu[2]==0) Data.DT2= 0; else Data.DT2=1;
	if (dulieu[1]==0) Data.DT1= 0; else Data.DT1=1;
	if (dulieu[0]==0) Data.DT0= 0; else Data.DT0=1;
	
	LCD_D7= Data.DT3;
	LCD_D6= Data.DT2;
	LCD_D5= Data.DT1;
	LCD_D4= Data.DT0;
	*/
	
	// Neu trinh bien dich nao khong dich duoc 4 
	// dong code duoi nay thi su dung
	// doan code ben tren va xoa 4 dong nay di
	LCD_D7= (b>>3)&0x01;
	LCD_D6= (b>>2)&0x01;
	LCD_D5= (b>>1)&0x01;
	LCD_D4= b&0x01;
		
}
#endif

//-------------------------------------------------------------------
// gui lenh ra lcd, neu dinh nghia FOUR thi 4 bit, khong thi 8 bit
//-------------------------------------------------------------------

#ifdef FOUR
void Cmd_Lcd(unsigned char a)
{

	#ifdef USE_RW
	RW= 0;
	#endif
	
	RS = 0;
	Lcd_Write_High_Nibble(a); 
	E = 1;
	E = 0;
	if (a< 0x02) delay_1_6ms();
	else delay_37us();
	Lcd_Write_Low_Nibble(a);
	E = 1;
	E = 0;
	if (a< 0x02) delay_1_6ms();
	else delay_37us();
}

#else
void Cmd_Lcd(unsigned char a)
{
	#ifdef USE_RW
	RW= 0;
	#endif
	
	RS=0;
	DATA= a;
	E=0; E=1;
	if (a> 0x02) delay_1_6ms();
	else delay_37us();

}
#endif

//----------------------------------------------------------------
// ham ghi du lieu, neu dinh nghia FOUR thi 4 bit, khong thi 8 bit
//----------------------------------------------------------------

#ifdef FOUR
void Write_Data(unsigned char b)
{
	#ifdef USE_RW
	RW=0;
	#endif
	
	RS = 1;
	Lcd_Write_High_Nibble(b);
	E = 1;
	E = 0;
	delay_37us();
	Lcd_Write_Low_Nibble(b);
	E = 1;
	E = 0;
	
	delay_37us(); 
}

#else
void Write_Data(unsigned char b)// ghi du lieu kieu 8 bit
{
	#ifdef USE_RW
	RW=0;
	#endif
	
	
	RS=1;// che do ghi du lieu
	DATA =b;
	E=0; E=1;
	delay_37us();
}

#endif

//---------------------------------------------------------------------
//	lcd init, neu dinh nghia FOUR thi che do 4 bit, khong thi 8 bit
//---------------------------------------------------------------------

#ifdef FOUR
/*--------------------------------------
khoi tao che do 4 bit, font 5x7
*/

void Lcd_Init(void)// co ham delay_2ms() delay_37us()
{
	char i;
	TRISEN =0;
	TRISRS=0;
	LCD_D7TRIS=0;
	LCD_D6TRIS=0;
	LCD_D5TRIS=0;
	LCD_D4TRIS=0;
	
	#ifdef USE_RW
	TRISRW=0;
	RW=0;
	#endif
	
	RS = 0;
	E = 0;
	
	for (i=0;i<=18;i++) delay_2ms();// delay 40ms
	Lcd_Write_Low_Nibble(0x03);
	E = 1;
	E = 0;
    delay_2ms(); delay_2ms(); delay_1ms();// delay 4.1 ms

	Lcd_Write_Low_Nibble(0x03);
	E = 1;
	E = 0;
    delay_37us();delay_37us(); delay_37us();// delay 100 us

	Lcd_Write_Low_Nibble(0x03);
	E = 1;
	E = 0;
//	#ifdef USE_RW
//	Busy_Lcd();
//	#else
	delay_1ms();// delay 1 ms
//	#endif
	
	Lcd_Write_Low_Nibble(0x02);
	E = 1;
	E = 0;
	delay_1ms();// delay 1 ms
		
	Cmd_Lcd(0x28);// 4bit 2dong. 5x7
	Cmd_Lcd(0x0C);// turn on lcd
	Cmd_Lcd(0x01);// clear
	Cmd_Lcd(0x06);// entry mode
	Cmd_Lcd(0x80);// 
}
#else

void Lcd_Init(void)
{
// che do 8 bit, 2 dong, khong bat con tro. 5x7
	DATATRIS=0;
	TRISRS=0;
	TRISRW=0;
	TRISEN =0;
	Cmd_Lcd(0x30);
	delay_2ms();
	delay_2ms(); delay_1ms();// delay 4.1 ms

	Cmd_Lcd(0x30);
	delay_37us(); delay_37us(); delay_37us();
	
	Cmd_Lcd(0x30);
	Cmd_Lcd(0x38);// 2dong 8bit 5x8
			

	Cmd_Lcd(0x0C);// cursor off,DON
	Cmd_Lcd(0x06);// blink on
	Cmd_Lcd(0x01);// clear
	Cmd_Lcd(0x80);// con tro ve dau dong 1
	
}

#endif


//------------------------------------------------------------------
// cac ham hien thi du lieu len lcd
//------------------------------------------------------------------

void Put_String(char a[])
{
	char i;
	for (i=0;i<strlen(a);i++)
	Write_Data(a[i]);

}

void lcd_gotoxy(unsigned char x, unsigned char y) //80us
{y==0?Cmd_Lcd(0x80+x-0):Cmd_Lcd(0xC0+x-0);}



void Put_String_Add(unsigned char x, unsigned char y, char *a)
{
	unsigned char i=0;
	lcd_gotoxy(x,y);
	while(a[i]!=0)
	{
		Write_Data(a[i]);
		i++;
		x++;
		lcd_gotoxy(x,y);
	}
	
}

void Put_Char_Add(unsigned char x, unsigned char y, char a)
{
	lcd_gotoxy(x,y);
	Write_Data(a);
}

void lcd_clear(void)
{
	Cmd_Lcd(0x01);
	delay_1_6ms();
}

void lcd_puts(char *string)
{
    while(*string)
	{
		Write_Data(*string);
		string++;
	}
}

void delay_ms(unsigned int time)
{
	int i;
	for(i=0;i<time;i++)
	{
		delay_1ms();
	}
}