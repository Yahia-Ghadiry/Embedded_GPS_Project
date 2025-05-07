// GPS_functions.h
#ifndef GPS_FUNCTIONS_H
#define GPS_FUNCTIONS_H

#include <stdint.h>
#include <stdbool.h>
#include <math.h>

#define PI 3.14159265358979323846f
#define R 6378137  // Earth radius in meters


// Function prototypes
void GPS_Spreading_Data(char* gps_buffer);

float GPS_angle_format_to_degrees(float angle);
float GPS_angle_formate_to_rad(float angle);

float GPS_degree_to_radians(float degrees);
float GPS_radians_to_degree(float radians);

float GPS_Calculate_Distance(float lon, float lat, float lon_2, float lat_2);

#endif