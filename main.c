#include "LCD.h"
#include "tm4c123gh6pm.h"
#include "GPIO.h"
#include "systickFunctions.h"
#include "uart.h"
int main(){
	

SysTick_Init();   
	UART0_vInit() ; 
		UART5_vInit() ; 
	while(1)
	{
		UART_vWrite(UART0_ID, UART_u8Read(UART5_ID));
	}

	
}

