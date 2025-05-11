#ifndef DISPLAY_H
#define DISPLAY_H

#include "Display.h"
#include "GPS_functions.h"
#include "LCD.h"

void time_display(void);
void error_display(void);
void init_display(void);
void date_display(void);
void speed_display(uint8_t *str);
void location_display(uint8_t *str);
void error_signal_display(void);
void conn_signal_display(void);
void distance_display(uint8_t * str);
void int_to_string (uint16_t num, char * str);
#endif
