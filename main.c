#include "LCD.h"
#include "tm4c123gh6pm.h"
#include "GPIO.h"
#include "systickFunctions.h"
int main(){
	

SysTick_Init();   
	init_LCD();
	display_char('y');
	display_char('a');
		display_char('h');
	display_char('i');
		display_char('a');
	display_char(' ');
	display_char('z');
		display_char('i');
	display_char('a');
	display_char('d');
	
}
