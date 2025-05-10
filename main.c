#include "LCD.h"
#include "tm4c123gh6pm.h"
#include "GPIO.h"
#include "systickFunctions.h"
#include "uart.h"
#include <stdint.h>
#include "GPS_functions.h"
#include "Display.h"
volatile int kkk = 88888;
uint8_t aaa = '0';
char str[100];
int main()
{
		char buffer[100] = "$GPRMC,183559.00,A,4717.11437,N,00833.91522,E,0.004,77.52,091202,,,A*57";
	SysTick_Init();
init_LCD();
display_String("aaaaaaaaaa");

	SysTick_Init();   
	UART0_vInit(); 
	UART5_vInit(); 
	UART6_vInit(); 
	while(1)
	{
		kkk = 80;
		UART_vReadString(UART5_ID, str, 100);   
		
      UART_u8Read(UART5_ID)	;          //UART_vWrite(UART0_ID, UART_u8Read(UART5_ID));
//	//UART_vWrite(UART0_ID, '0');      //UART_vWrite(UART0_ID, UART_u8Read(UART5_ID));
//	//aaa = UART_u8Read(UART0_ID);
			GPS_Spreading_Data(buffer);
	if (GPS_status=='V'){
			display_error();
		}else{
time_display();
	}
		while (kkk != 0)
				{
					kkk--;
				}
			//UART_vWrite(UART5_ID, aaa7689
	   UART_vWriteString(UART0_ID, str); 
      UART_vWrite(UART0_ID, '\r');   
   UART_vWrite(UART0_ID, '\n'); 				//UART_vWrite(UART0_ID, UART_u8Read(UART5_ID));
				kkk = 80;
				while (kkk != 0)
				{
					kkk--;
				}
	}

	
}
