#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "GPS_functions.h"
#include <stdint.h>
#include <math.h>  // For mathematical functions like sinf, cosf, sqrtf, etc.

// Constants for GPS calculations
#define PI 3.141592653589793
#define R 6371.0f // Radius of Earth in kilometers

// Example buffer containing the GPS sentence
char GPS_time[11] = "";        // HHMMSS.ss
char GPS_status = 'V';         // 'A' = valid, 'V' = warning
float lat = 0.0f;              // Latitude
char GPS_NS = 'N';             // North/South
float lon = 0.0f;              // Longitude
char GPS_EW = 'E';             // East/West
float GPS_speed = 0.0f;        // Speed in knots
float GPS_course = 0.0f;       // Course in degrees
uint8_t GPS_date[7] = "";      // DDMMYY
uint8_t mv[6] = "";            // Magnetic variation (optional)
char mvEW = ' ';               // Magnetic variation direction
char posMode = ' ';            // Position mode

// Function to parse the GPS data from the NMEA sentence
void GPS_Spreading_Data(char* gps_buffer) {
    char *token;                 // Token used for parsing the sentence
    uint8_t field_index = 0;     // To keep track of the field we are processing

    if (!gps_buffer || strncmp(gps_buffer, "$GPRMC", 6) != 0) return;

    token = strtok(gps_buffer, ",");

    while (token != NULL) {
        switch (field_index) {
            case 1:
                strncpy(GPS_time, token, sizeof(GPS_time) - 1);
                GPS_time[sizeof(GPS_time) - 1] = '\0';  // Ensure null-termination
                break;
            case 2:
                GPS_status = token[0];
                break;
            case 3:
                lat = atof(token); // Latitude in ddmm.mmmmm format
                break;
            case 4:
                GPS_NS = token[0]; // North/South
                break;
            case 5:
                lon = atof(token); // Longitude in dddmm.mmmmm format
                break;
            case 6:
                GPS_EW = token[0]; // East/West
                break;
            case 7:
                GPS_speed = atof(token); // Speed in knots
                break;
            case 8:
                GPS_course = atof(token); // Course in degrees
                break;
            case 9:
                strncpy((char*)GPS_date, token, sizeof(GPS_date) - 1); // Date in DDMMYY format
                GPS_date[sizeof(GPS_date) - 1] = '\0';  // Ensure null-termination
                break;
            case 10:
                if (strlen(token) > 0) {
                    strncpy(mv, token, sizeof(mv) - 1); // Magnetic variation
                    mv[sizeof(mv) - 1] = '\0';  // Ensure null-termination
                }
                break;
            case 11:
                mvEW = token[0]; // Magnetic variation direction (E/W)
                break;
            case 12:
                posMode = token[0]; // Position mode (A = autonomous, D = differential)
                break;
            default:
                break;
        }
        token = strtok(NULL, ",");
        field_index++;
    }
}

// Convert GPS latitude/longitude in ddmm.mmmmm format to decimal degrees
float GPS_angle_format_to_degrees(float angle) {  
    int degrees = (int)angle / 100;  // Extract degrees (e.g., 47 from 4717.11437)
    float minutes = angle - (float)degrees * 100;  // Extract minutes (e.g., 17.11437 from 4717.11437)
    return (degrees + (minutes / 60.0f));  // Convert to decimal degrees
}

// Convert GPS angle in decimal degrees to radians
float GPS_angle_formate_to_rad(float angle) {
    return ((GPS_angle_format_to_degrees(angle) * PI) / 180.0f);  // Convert degrees to radians
}

// Convert degrees to radians
float GPS_degree_to_radians(float degrees) {         
    return ((degrees * PI) / 180.0f);
}

// Convert radians to degrees
float GPS_radians_to_degree(float radians) {         
    return ((radians * 180.0f) / PI);
}

// Calculate the distance between two points (Haversine formula)
float GPS_Calculate_Distance(float lon, float lat, float lon_2, float lat_2) {
    float delta_lon, delta_lat, a, c;

    lon  = GPS_angle_formate_to_rad(lon);
    lat  = GPS_angle_formate_to_rad(lat);
    lon_2 = GPS_angle_formate_to_rad(lon_2);
    lat_2 = GPS_angle_formate_to_rad(lat_2);

    delta_lon = fabs(lon - lon_2);
    delta_lat = fabs(lat - lat_2);

    a = sinf(delta_lat / 2.0f) * sinf(delta_lat / 2.0f) +
        cosf(lat) * cosf(lat_2) * sinf(delta_lon / 2.0f) * sinf(delta_lon / 2.0f);

    c = 2.0f * atanf(sqrtf(a) / sqrtf(1.0f - a));

    return R * c;  // Return distance in kilometers
}

// You can expand this function to calculate other values like bearing, etc.
