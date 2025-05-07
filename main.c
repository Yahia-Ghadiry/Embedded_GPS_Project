#include "LCD.h"
#include "tm4c123gh6pm.h"
#include "GPIO.h"
#include "systickFunctions.h"
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