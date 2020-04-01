#ifndef __DS18B20_H
#define __DS18B20_H

#include <p18f4520.h>
#include "delay_timer0.h"
#include "LCD.h"

#define __delay_us(a) delay_timer0_us(a) //dong bo ham delay
#define __delay_ms(a) delay_ms(a) //dong bo ham delay

// DS18B20 data pin is connected to pin RD3
#define DS18B20_PIN      LATDbits.LATD3 //PORTDbits.RD3 
#define DS18B20_PIN_Dir  TRISDbits.TRISD3

//define cac gia tri cau hinh do phan giai
#define DS18B20_9BIT_RES    0x1F // Do phan giai 9bit
#define DS18B20_10BIT_RES   0x3F // Do phan giai 10bit
#define DS18B20_11BIT_RES   0x5F // Do phan giai 11bit
#define DS18B20_12BIT_RES   0x7F // Do phan giai 12bit

typedef float float32_t;
typedef unsigned char uint8_t;
typedef unsigned int uint16_t;

uint8_t ds18b20_start(void);
void ds18b20_config(uint8_t Temp_low, uint8_t Temp_high, uint8_t Resolution);
void ds18b20_write_bit(uint8_t value);
void ds18b20_write_byte(uint8_t value);
uint8_t ds18b20_read_bit(void);
uint8_t ds18b20_read_byte(void);
void out_console1(char array[], int index);
uint8_t ds18b20_read(uint16_t *raw_temp_value);


#endif