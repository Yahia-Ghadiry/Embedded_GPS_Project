// GPS_functions.h
#ifndef GPS_FUNCTIONS_H
#define GPS_FUNCTIONS_H

#include <stdint.h>
#include <stdbool.h>
#include <math.h>

#define PI 3.14159265358979323846f
#define R 6378137  // Earth radius in meters

extern char    GPS_time[11];   // HHMMSS.ss
extern char    GPS_status;     // 'A' = valid, 'V' = warning
extern float   lat;            // Latitude (ddmm.mmmm)
extern char    GPS_NS;         // 'N' or 'S'
extern float   lon;            // Longitude (dddmm.mmmm)
extern char    GPS_EW;         // 'E' or 'W'
extern float   GPS_speed;      // Speed in knots
extern float   GPS_course;     // Course in degrees
extern uint8_t GPS_date[7];    // DDMMYY
extern uint8_t mv[6];          // Magnetic variation
extern char    mvEW;           // 'E' or 'W'
extern char    posMode;        // Position mode (A/D)

void GPS_Spreading_Data(const char *gps_buffer);

float GPS_angle_format_to_degrees(float angle);
float GPS_angle_formate_to_rad(float angle);

float GPS_degree_to_radians(float degrees);
float GPS_radians_to_degree(float radians);

float GPS_Calculate_Distance(float lon, float lat, float lon_2, float lat_2);

#endif
