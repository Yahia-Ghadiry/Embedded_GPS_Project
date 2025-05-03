#include "LCD.h"
#include "tm4c123gh6pm.h"
#include "GPIO.h"
#include "systickFunctions.h"
int main(){
	

SysTick_Init();   


	position_curser(0,0);
	display_String("yahia");
}
