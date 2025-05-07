#include "LCD.h"
#include "tm4c123gh6pm.h"
#include "GPIO.h"
#include "systickFunctions.h"
#include "uart.h"
#include <stdint.h>

volatile int kkk = 88888;
uint8_t aaa = '0';
int main()
{
	

	//SysTick_Init();   
	UART0_vInit(); 
	UART5_vInit(); 
	//UART6_vInit(); 
	while(1)
	{
		kkk = 88888;
		aaa = UART_u8Read(UART5_ID);       //UART_vWrite(UART0_ID, UART_u8Read(UART5_ID));
//	UART_vWrite(UART0_ID, '0');      //UART_vWrite(UART0_ID, UART_u8Read(UART5_ID));
	//aaa = UART_u8Read(UART0_ID);
		while (kkk != 0)
				{
					kkk--;
				}
			//UART_vWrite(UART5_ID, aaa7689
		   UART_vWrite(UART0_ID, aaa);      //UART_vWrite(UART0_ID, UART_u8Read(UART5_ID));
				kkk = 88888;
				while (kkk != 0)
				{
					kkk--;
				}
	}

	
}
