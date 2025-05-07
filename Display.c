#include "Display.h"
#include "GPS_functions.h"
#include "LCD.h"
void time_display(){

display_String("TIME");
	position_curser(1,0);
	display_char(GPS_time[0]);
	display_char(GPS_time[1]);
	display_char(':');
	display_char(GPS_time[2]);
	display_char(GPS_time[3]);



}
void display_error(void){



		display_String("ERROR");
position_curser(1,0);
		display_String("ERROR");
position_curser(2,0);
		display_String("ERROR");
position_curser(3,0);
		display_String("ERROR");
position_curser(0,10);
		display_String("ERROR");
position_curser(1,10);
		display_String("ERROR");
position_curser(2,10);
		display_String("ERROR");
position_curser(3,10);
		display_String("ERROR");
}