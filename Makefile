# MPLAB IDE generated this makefile for use with GNU make.
# Project: example.mcp
# Date: Sun Mar 29 18:29:35 2020

AS = MPASMWIN.exe
CC = mcc18.exe
LD = mplink.exe
AR = mplib.exe
RM = rm

example.cof : main.o LCD.o ds18b20.o delay_timer0.o
	$(LD) /l"C:\MCC18\lib" /k"C:\MCC18\lkr" "C:\MCC18\lkr\18f4520.lkr" "main.o" "LCD.o" "ds18b20.o" "delay_timer0.o" /z__MPLAB_BUILD=1 /z__MPLAB_DEBUG=1 /o"example.cof" /M"example.map" /W

main.o : main.c C:/MCC18/h/delays.h C:/MCC18/h/adc.h C:/MCC18/h/string.h C:/MCC18/h/math.h C:/MCC18/h/stdlib.h C:/MCC18/h/stdio.h C:/MCC18/h/usart.h LCD.h delay_timer0.h ds18b20.h main.c C:/MCC18/h/p18f4520.h C:/MCC18/h/p18cxxx.h C:/MCC18/h/stddef.h C:/MCC18/h/stdarg.h
	$(CC) -p=18F4520 "main.c" -fo="main.o" -D__DEBUG -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

LCD.o : LCD.c C:/MCC18/h/delays.h C:/MCC18/h/string.h LCD.h LCD.c C:/MCC18/h/p18f4520.h C:/MCC18/h/p18cxxx.h C:/MCC18/h/stddef.h
	$(CC) -p=18F4520 "LCD.c" -fo="LCD.o" -D__DEBUG -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

ds18b20.o : ds18b20.c C:/MCC18/h/math.h C:/MCC18/h/stdio.h delay_timer0.h ds18b20.h ds18b20.c C:/MCC18/h/p18f4520.h C:/MCC18/h/stdarg.h C:/MCC18/h/stddef.h
	$(CC) -p=18F4520 "ds18b20.c" -fo="ds18b20.o" -D__DEBUG -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

delay_timer0.o : delay_timer0.c C:/MCC18/h/math.h C:/MCC18/h/stdio.h delay_timer0.h delay_timer0.c C:/MCC18/h/p18f4520.h C:/MCC18/h/stdarg.h C:/MCC18/h/stddef.h
	$(CC) -p=18F4520 "delay_timer0.c" -fo="delay_timer0.o" -D__DEBUG -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

clean : 
	$(RM) "main.o" "LCD.o" "ds18b20.o" "delay_timer0.o" "example.cof" "example.hex"

