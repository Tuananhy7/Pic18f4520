/*
 * Interfacing PIC16F887 microcontroller with DS18B20 temperature sensor.
 * C Code for MPLAB XC8 compiler.
 * Internal oscillator used @ 8MHz.
 * This is a free software with NO WARRANTY.
 * https://simple-circuit.com/
*/

#include"ds18b20.h" 

uint8_t temp1[8] = {1,2,3,4,5,6,7,8}; 
 
uint8_t ds18b20_start(void)
{
  DS18B20_PIN = 0;      // send reset pulse to the DS18B20 sensor
  DS18B20_PIN_Dir = 0;  // configure DS18B20_PIN pin as output
  Delay10TCYx(100);
  //__delay_us(500);      // wait 500 us
 
  DS18B20_PIN_Dir = 1;  // configure DS18B20_PIN pin as input
  Delay10TCYx(15); // 20
  //__delay_us(100);      // wait 100 us to read the DS18B20 sensor response
 
  if (!DS18B20_PIN)
  {
	  Delay10TCYx(20);		// when DS18B20_PIN = 0
    //__delay_us(400);    // wait 400 us ---80
    return 1;           // DS18B20 sensor is present
  }
 
  return 0;   // connection error
}

void ds18b20_config(uint8_t Temp_low, uint8_t Temp_high, uint8_t Resolution)
{
    ds18b20_write_byte(0x4E);      // Cho phep ghi 3 byte vao bo nho nhap:
    ds18b20_write_byte(Temp_high); // byte 2: Th
    ds18b20_write_byte(Temp_low);  // byte 3: Tl
    ds18b20_write_byte(Resolution);// byte 4: configuration register
    ds18b20_write_byte(0x48);      // Luu khoi tao vao EEPROM
    __delay_ms(1);
}
 
void ds18b20_write_bit(uint8_t value)
{
  DS18B20_PIN = 0;
  DS18B20_PIN_Dir = 0;  // configure DS18B20_PIN pin as output
  //Delay10TCYx(1);
  //__delay_us(2);        // wait 2 us
 
  DS18B20_PIN = (value&0x01);
  Delay10TCYx(10);
  //16 - 80us
  //__delay_us(80);       // wait 80 us
 
  DS18B20_PIN_Dir = 1;  // configure DS18B20_PIN pin as input
  //Delay10TCYx(1);
  //__delay_us(2);        // wait 2 us
}
 
void ds18b20_write_byte(uint8_t value)
{
	uint8_t i;
	DS18B20_PIN_Dir = 0;
	for(i = 0; i < 8; i++)
	{
		DS18B20_PIN = 0;
		DS18B20_PIN = (value&0x01);
		Delay10TCYx(12); // 60us
		DS18B20_PIN = 1;
		value >> i;
	}
		//ds18b20_write_bit(value >> i);
}
 
uint8_t ds18b20_read_bit(void)
{
	static uint8_t value = 0;
 
	DS18B20_PIN = 0;
	DS18B20_PIN_Dir = 0;  // configure DS18B20_PIN pin as output
	//Delay10TCYx(1);
	//__delay_us(2);

	DS18B20_PIN_Dir = 1;  // configure DS18B20_PIN pin as input
	//Delay10TCYx(1);
	//__delay_us(5);        // wait 5 us

	value = DS18B20_PIN;  // read and store DS18B20 state
	Delay10TCYx(20);
	//__delay_us(100);      // wait 100 us

	return value;
}
 
uint8_t ds18b20_read_byte(void)
{
  uint8_t value = 0;
  uint8_t i;
  DS18B20_PIN_Dir = 0;
  for(i = 0; i < 8; i++)
  {
	DS18B20_PIN = 0;
	value >>= 1;
	DS18B20_PIN = 1;
	DS18B20_PIN_Dir = 1;
	value |= DS18B20_PIN?0x80:0x00;
	Delay10TCYx(22);
	//__delay_us(100);      // wait 100 us
  }
    //value |= ds18b20_read_bit() << i;
 
  return value;
}

void out_console1(char array[], int index)
{
	int i=0;
	for(i=0;i<index;i++)
	{
		WriteUSART(array[i]);
		delay_ms(1);
	}
	WriteUSART('\r');
	delay_ms(500);
} 
 
uint8_t ds18b20_read(uint16_t *raw_temp_value)
{
	char lcd[16];
	
	
  if (!ds18b20_start())   // send start pulse
    return 0;             // return 0 if error
 
  ds18b20_write_byte(0xCC);   // send skip ROM command
  ds18b20_write_byte(0x44);   // send start conversion command
  Delay10TCYx(40); // 200us wait
  while(ds18b20_read_byte() == 0);  // wait for conversion complete
  
  if (!ds18b20_start())  // send start pulse
    return 0;            // return 0 if error
	
  ds18b20_write_byte(0xCC);  // send skip ROM command
  ds18b20_write_byte(0xBE);  // send read command
 
  // read temperature LSB byte and store it on raw_temp_value LSB byte
  *raw_temp_value  = ds18b20_read_byte();
  // read temperature MSB byte and store it on raw_temp_value MSB byte
  *raw_temp_value |= ((uint16_t)ds18b20_read_byte() << 8);
  temp1[0] = ds18b20_read_byte();
  temp1[1] = ds18b20_read_byte();
  temp1[2] = ds18b20_read_byte();
  temp1[3] = ds18b20_read_byte();
  temp1[4] = ds18b20_read_byte();
  temp1[5] = ds18b20_read_byte();
  temp1[6] = ds18b20_read_byte();
  
  //out_console1(raw_temp_value, 2);
  //*raw_temp_value = 6553;
  //*raw_temp_value |= 0xFF00;
  gotoxy(0,0);
  sprintf(&lcd[0], "read: %u", temp1[6]); lcd_puts(lcd);
 
  return 1;   // OK --> return 1
}