#include "LCD.h"
#include "tm4c123gh6pm.h"
#include "GPIO.h"
#include "systickFunctions.h"
#include "uart.h"
#include <stdint.h>

volatile int kkk = 88888;
uint8_t aaa = '0';
uint8_t str[100];
int main()
{

	//SysTick_Init();   
	UART0_vInit(); 
	UART5_vInit(); 
	//UART6_vInit(); 
	while(1)
	{
		kkk = 80;
		UART_vReadString(UART5_ID, str, 100);   
      UART_vWrite(UART5_ID, '\n');      
      UART_u8Read(UART5_ID)	;          //UART_vWrite(UART0_ID, UART_u8Read(UART5_ID));
//	UART_vWrite(UART0_ID, '0');      //UART_vWrite(UART0_ID, UART_u8Read(UART5_ID));
	//aaa = UART_u8Read(UART0_ID);
		while (kkk != 0)
				{
					kkk--;
				}
			//UART_vWrite(UART5_ID, aaa7689
				UART_vWriteString(UART0_ID, str);    
				UART_vWrite(UART0_ID, '\r');    
				UART_vWrite(UART0_ID, '\n');
				kkk = 80;
				while (kkk != 0)
				{
					kkk--;
				}
	}

	
}
