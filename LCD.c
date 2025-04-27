#include "LCD.h"
#include "tm4c123gh6pm.h"

void data_LCD(char c){
GPIO_PORTB_DATA_R = c;
}

void control_LCD(char SW){
GPIO_PORTC_DATA_R |=SW;
}

void init_LCD(void){
GPIO_Init_PortB();
GPIO_Init_PortC_LCD();
data_LCD(clear_char);
control_LCD(clear_control);
	
}

void clear(void){}