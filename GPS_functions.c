#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "GPS_functions.h"
#include <stdint.h>

// Example buffer containing the GPS sentence
uint8_t GPS_time[11] = "";     // HHMMSS.ss
char GPS_status = 'V';         // 'A' = valid, 'V' = warning
float lat = 0.0f;              // Latitude (raw format)
char GPS_NS = 'N';             // North/South
float lon = 0.0f;              // Longitude (raw format)
char GPS_EW = 'E';             // East/West
float GPS_speed = 0.0f;        // Speed in knots
float GPS_course = 0.0f;       // Course in degrees
uint8_t GPS_date[7] = "";      // DDMMYY
uint8_t mv[6] = "";            // Magnetic variation (optional)
char mvEW = ' ';               // Magnetic variation direction
char posMode = ' ';            // Position mode

void GPS_Spreading_Data(char* gps_buffer) {
    char *token;                 // ? Declaration at the top
    uint8_t field_index = 0;     // ? Declaration at the top

    if (!gps_buffer || strncmp(gps_buffer, "$GPRMC", 6) != 0) return;

    token = strtok(gps_buffer, ",");

    while (token != NULL) {
        switch (field_index) {
            case 1:
                strncpy(GPS_time, token, sizeof(GPS_time) - 1);
                GPS_time[sizeof(GPS_time) - 1] = '\0';  // ? ensure null-termination
                break;
            case 2:
                GPS_status = token[0];
                break;
            // ... Continue safely for all fields ...
        }

        token = strtok(NULL, ",");
        field_index++;
    }
}


float GPS_angle_format_to_degrees(float angle) {  // ddmm.mmmmm // 4717.11437
    int degrees = (int)angle/100;  // 47 (degree)
    float minutes = angle- (float)degrees*100;  // 17.11437 (min)
    return (degrees + (minutes / 60.0f));  // (total degree) 
}

float GPS_angle_formate_to_rad(float angle){

	return ((GPS_angle_format_to_degrees(angle)*PI)/180.0f);
}
float GPS_degree_to_radians(float degrees) {         
    return ((degrees * PI ) / 180.0f);
}

float GPS_radians_to_degree(float radians) {         
    return ((radians * 180.0f) / PI);
}
float GPS_Calculate_Distance(float lon , float lat , float lon_2 , float lat_2){
    float delta_lon, delta_lat, a, c;

    lon  = GPS_angle_formate_to_rad(lon);
    lat  = GPS_angle_formate_to_rad(lat);
    lon_2 = GPS_angle_formate_to_rad(lon_2);
    lat_2 = GPS_angle_formate_to_rad(lat_2);

    delta_lon = fabs(lon - lon_2);
    delta_lat = fabs(lat - lat_2);

    a = sinf(delta_lat/2.0f)*sinf(delta_lat/2.0f) +
        cosf(lat)*cosf(lat_2)*sinf(delta_lon/2.0f)*sinf(delta_lon/2.0f);

    c = 2.0f * atanf(sqrtf(a)/sqrtf(1.0f - a));

    return R * c;
}
