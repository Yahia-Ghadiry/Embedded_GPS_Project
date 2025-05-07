#include "LCD.h"
#include "tm4c123gh6pm.h"
#include "GPIO.h"
#include "systickFunctions.h"
<<<<<<< HEAD
#include "GPS_functions.h"
#include <stdio.h>
#include <string.h>

int main() {

    char gps_buffer[100] = "$GPRMC,083559.00,A,4717.11437,N,00833.91522,E,0.004,77.52,091202,,,A*57";  // ?? move here

    SysTick_Init();
    init_LCD();

    GPS_Spreading_Data(gps_buffer);
		
    while(1); 
}
=======
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
>>>>>>> 1c27cebfb0c420c049d1406f17511a57a5f7b01c
