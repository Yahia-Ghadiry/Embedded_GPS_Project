#include "LCD.h"
#include "GPIO.h"
#include "tm4c123gh6pm.h"
#include "systickFunctions.h"
#include <stdint.h>
void data_LCD(char c){
GPIO_PORTB_DATA_R = c;
}

void set_control_LCD(void){
GPIO_PORTD_DATA_R |=0x02;
}
void set_E(void){
GPIO_PORTD_DATA_R |=(1<<2);
}
void clear_control_LCD(void){
GPIO_PORTD_DATA_R &=(~0x3);
}
void clear_E(void){
GPIO_PORTD_DATA_R &=~(1<<2);
}

void init_LCD(void){
GPIO_Init_PortB();
GPIO_Init_PortD_LCD();
	set_E();
				data_LCD(0x6);
clear_control_LCD();
		DelayUs(1);
	clear_E();
DelayMs(3);
	set_E();
data_LCD(init_lcd_functions);
clear_control_LCD();
	DelayUs(1);
	clear_E();
	DelayMs(3);
	set_E();
	data_LCD(display_control);
clear_control_LCD();
	DelayUs(1);
	clear_E();
	DelayMs(3);
		set_E();
		data_LCD(home);
clear_control_LCD();
		DelayUs(1);
	clear_E();
DelayMs(3);
	set_E();

}
void clear(void){
	data_LCD(clear_char);
clear_control_LCD();
	set_E();
  DelayUs(1);
	clear_E();
	DelayMs(3);
	set_E();
			data_LCD(home);
clear_control_LCD();
		set_E();
  DelayUs(1);
	clear_E();
	DelayMs(3);
	set_E();
}
void shift_curser(void){
	data_LCD(shift);
clear_control_LCD();
	set_E();
	  DelayUs(1);
	clear_E();
	DelayUs(60);
}

void position_curser(char row, char column){
    char address;
    switch(row) {
        case 0: address = 0x80 + column; break; 
        case 1: address = 0xC0 + column; break;  
        case 2: address = 0x94 + column; break;  
        case 3: address = 0xD4 + column; break;  
    }
		set_E();
    data_LCD(address);
		clear_control_LCD();
		DelayUs(1);
		clear_E();
		DelayUs(60);
		set_E();
}
void display_char(char c){
			set_E();
    data_LCD(c);
	set_control_LCD();
		DelayUs(1);
		clear_E();
		DelayUs(60);
		set_E();
}
void display_String(char *str) {
    while(*str) {
      display_char(*str++);
    }
}
