#include "LCD.h"
#include "tm4c123gh6pm.h"
#include "GPIO.h"
#include "systickFunctions.h"
void data_LCD(char c){
GPIO_PORTB_DATA_R = c;
}

void control_LCD(char SW){
GPIO_PORTC_DATA_R |=SW;
}

void init_LCD(void){
GPIO_Init_PortB();
GPIO_Init_PortC_LCD();
data_LCD(init_lcd_functions);
control_LCD(clear_control);
	SysTick_DelayMs(3);
	data_LCD(display_control);
control_LCD(clear_control);
	SysTick_DelayMs(3);
		data_LCD(home);
control_LCD(clear_control);
	SysTick_DelayMs(3);
}
void clear(void){
	data_LCD(clear_char);
control_LCD(clear_control);
	SysTick_DelayMs(3);
			data_LCD(home);
control_LCD(clear_control);
	SysTick_DelayMs(3);
}
void shift_curser(void){
	data_LCD(shift);
control_LCD(clear_control);
	SysTick_DelayUs(60);
}
