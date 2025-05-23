#include "LCD.h"
#include "tm4c123gh6pm.h"
#include "GPIO.h"
#include "systickFunctions.h"
#include "uart.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <cstdlib>

#include "GPS_functions.h"
#include "Display.h"
uint8_t* nearest_place( float curLon,float curLat)  ;
 uint8_t* place_name(int index);
static const double latitudes[38] = {
    30.064172, 30.06365, 30.063742, 30.064051, 30.064302,
  30.064654, 30.065126, 30.065265, 30.065109, 30.063387,
  30.063229, 30.063087, 30.06391,  30.063789, 30.063562,
  30.063761, 30.063474, 30.063269, 30.064365, 30.064147,
  30.063924, 30.064144, 30.064408, 30.065569, 30.064534,
  30.064242, 30.064339, 30.064462, 30.06462,  30.064758,
  30.064534, 30.0649,   30.064951, 30.065062, 30.065216,
  30.064872, 30.064568,30.06496

};

static const double longitudes[38] = {
     31.280199, 31.28044,  31.280803, 31.280669, 31.280551,
  31.280371, 31.280247, 31.280183, 31.279902, 31.279931,
  31.279513, 31.279081, 31.279624, 31.27912,  31.279206,
  31.279807, 31.278262, 31.278385, 31.279716, 31.27904,
  31.278321, 31.277726, 31.277598, 31.278397, 31.277427,
  31.278148, 31.278582, 31.278974, 31.279389, 31.279821,
  31.277999, 31.278171, 31.278557, 31.278948, 31.279415,
  31.277854, 31.277995,31.277826

};

char ito_string[100];

char str[100];
uint32_t count = 20;
uint8_t first_gps = 1;
uint16_t acumm_dis;
float dis;
int main()
{
	
		  //char buffer[100] = "$GPRMC,203559.00,A,4717.11437,N,00833.91522,E,0.004,77.52,091202,,,A*57";
		  //char buffer[100] = "$GPRMC,203559.00,V,,,,,,,091202,,,V*57";
	    //char buffer[100] = "$GPRMC,,V,,,,,,,,,,V*57";
			char prev_location[] = "POOR";
			float prev_distance_long =0;
			float prev_distance_lat = 0;
			uint8_t sigstatus;
			acumm_dis=12366;
	GPIO_Init_PortC_PC4();
	SysTick_Init();
init_LCD();
  
	UART0_vInit(); 
	UART5_vInit(); 
	while(1)
	{
		UART_vReadString(UART5_ID, str, 100);   
		
///////for debuging/////////////////////
			UART_vWriteString(UART0_ID, str); 
				UART_vWrite(UART0_ID, '\r');   
				UART_vWrite(UART0_ID, '\n'); 				//UART_vWrite(UART0_ID, UART_u8Read(UART5_ID));
		

//////////////////////////////////////
			GPS_Spreading_Data(str);
		
		if (strlen(GPS_time)==0){
				error_display();
				GPIO_PORTC_DATA_R |= (1<<5);
				sigstatus=0;
			}
		else if(GPS_status=='V'){
			init_display();
			if (sigstatus==0) {
				GPIO_PORTC_DATA_R &= ~(1<<5);
							DelayMs(500);
				GPIO_PORTC_DATA_R |= (1<<5);
				DelayMs(100);
				GPIO_PORTC_DATA_R &= ~(1<<5);
				DelayMs(100);
				GPIO_PORTC_DATA_R |= (1<<5);
				DelayMs(100);
				GPIO_PORTC_DATA_R &= ~(1<<5);
				DelayMs(100);
				GPIO_PORTC_DATA_R |= (1<<5);
				DelayMs(100);
			}
			GPIO_PORTC_DATA_R &= ~(1<<5);
			sigstatus=1;
			error_signal_display();

			time_display();
			date_display();
			speed_display(" 0");
			location_display(prev_location);
			int_to_string(acumm_dis, ito_string);
			distance_display(ito_string);
			
		}
				else if(GPS_status=='A')
		{
			init_display();
			if (sigstatus==1) {
				GPIO_PORTC_DATA_R |= (1<<5);
				DelayMs(500);
			}
			GPIO_PORTC_DATA_R &= ~(1<<5);
			sigstatus=0;
		//	distance__ = GPS_Calculate_Distance(31.2211061, 30.0515606,31.2789716, 30.0652933); 
			time_display();
						int_to_string(acumm_dis, ito_string);
				distance_display(ito_string);
					conn_signal_display();
		
			date_display();
			speed_display(GPS_speed);
			location_display(nearest_place(lon, lat));
				
			
			if (first_gps == 1)
			{	
					prev_distance_long = lat;
					prev_distance_lat =	lon;
					first_gps = 0;
			}
			
			if (count==0)
			{
				dis = GPS_Calculate_Distance(lat, lon, prev_distance_long,prev_distance_lat );
				if (dis > 6.0f)
				acumm_dis+=dis;
		
				prev_distance_long = lat;
				prev_distance_lat =	lon;
				count=11;
			}
			
			count--;
		}
	}
}






/* Return name of place by index */
 uint8_t* place_name(int index) {
switch (index) {
    case 0:
      return "Hall A,B";
    case 1:
      return "Hall C,D";
    case 2:
    case 3:
    case 4:
      return "Arch building";
    case 5:
      return "mosque";
    case 6:
    case 7:
      return "Library";
    case 8:
      return "Tk3eba";
    case 9:
    case 10:
    case 11:
      return "Louban";
    case 12:
    case 13:
    case 14:
    case 15:
      return "Mal3ab";
    case 16:
    case 17:
      return "Credit";
    case 18:
    case 19:
    case 20:
      return "Wersh";
    case 21:
    case 22:
      return "Khrsana";
    case 23:
      return "Nafora";
    case 24:
      return "Gate 2";
    case 25:
    case 26:
    case 27:
    case 28:
    case 29:
    case 30:
    case 31:
    case 32:
    case 33:
    case 34:
    case 35:
    case 36:
      return "Mainstream";
    default:
      return "Unknown index";
  }
}

/* Find nearest place given current lat/lon */
uint8_t* nearest_place( float curLon,float curLat) {
		
		int i;
    int minDist = 1000000;
    int minIdx = -1;
		int d;
	/* Iterate over all points */
    for (i = 0; i < 38; i++) {
        d =  GPS_Calculate_Distance( curLon,curLat
                            , longitudes[i], latitudes[i]);
				
        if (d < minDist) {
            minDist = d;
            minIdx = i;
        }
    }

    return place_name(minIdx);
}
