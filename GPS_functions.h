// GPS_functions.h
#ifndef GPS_FUNCTIONS_H
#define GPS_FUNCTIONS_H

#include <stdint.h>
#include <stdbool.h>
#include <math.h>

#define PI 3.14159265358979323846f
#define R 6378137  // Earth radius in meters

extern char    GPS_time[11];   // HHMMSS.ss
extern char    GPS_status;   
extern float   lat;            // Latitude (ddmm.mmmm)
extern char    GPS_NS;        
extern float   lon;            // Longitude (dddmm.mmmm)
extern char    GPS_EW;      
extern char   GPS_speed[8];     
extern float   GPS_course;    
extern uint8_t GPS_date[7];    
extern uint8_t mv[6];          
extern char    mvEW;           
extern char    posMode;        


void GPS_Spreading_Data(const char *gps_buffer);

float GPS_angle_format_to_degrees(float angle);
float GPS_angle_formate_to_rad(float angle);

float GPS_degree_to_radians(float degrees);
float GPS_radians_to_degree(float radians);

float GPS_Calculate_Distance(float currentLong, float currentLat, float destLong, float destLat) ;

#endif
