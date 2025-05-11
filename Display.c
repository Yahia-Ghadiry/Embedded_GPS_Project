#include "Display.h"
#include "GPS_functions.h"
#include "LCD.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
char distance[6];
void time_display(){
	int gps_time = 0;

	position_curser(2,10);
	
	gps_time = ((GPS_time[0]-'0')*10 + (GPS_time[0]-'0') + 4) % 24;
	display_char((gps_time / 10) + '0');
	
	display_char((gps_time % 10) + '0');
	
	display_char(':');
	display_char(GPS_time[2]);
	display_char(GPS_time[3]);



}
void init_display(void){
	  clear();
	display_String("Location ");
	position_curser(0,10);
		display_String(" Distance");
	position_curser(2,0);
		display_String("Speed");
	position_curser(2,16);
		display_String("SIG");
}

void date_display(void){
	position_curser(3,10);
	display_char(GPS_date[0]);
	display_char(GPS_date[1]);
	display_char('/');
	display_char(GPS_date[2]);
	display_char(GPS_date[3]);
		display_char('/');
	display_char('2');
	display_char('0');
		display_char(GPS_date[4]);
	display_char(GPS_date[5]);
}

void error_display(void){
	clear();
	position_curser(0,0);
		display_String("    NOCONNECTION");
position_curser(1,0);
		display_String("    NOCONNECTION");
position_curser(2,0);
		display_String("    NOCONNECTION");
position_curser(3,0);
		display_String("    NOCONNECTION");
}

void speed_display(uint8_t *str){
	position_curser(3,0);
	display_String(str);
	display_String("m/s");

}

void location_display(uint8_t *str){
	position_curser(1,0);
	display_String(str);

}

void int_to_string (uint16_t num, char * str)
{
	int i = 0;
	int dig = 0;
	int swap;
	int j = 0;
	if (num == 0)
	{
		str[0] = '0';
		str[1] = '\0';
			return;
	}
	
	while (num > 0)
	{
		dig = num % 10;
		
		num /= 10;
		str[i] = '0' + dig;
		i++;
	}
	str[i] = '\0';
	
	for (; j < i/2; j++)
	{
		swap = str[j];
		str[j] = str[i - j - 1];
		str[i - j -1] = swap;
	}
	
	}
void distance_display(uint8_t * str){
	
	position_curser(1,11);
	display_String(str);
	display_char('m');

}
void error_signal_display(void){
			position_curser(2,19);
	display_char('P');
}
void conn_signal_display(void){
			position_curser(2,19);
	display_char('G');
}