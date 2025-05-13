#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "GPS_functions.h"
#include <stdint.h>
#include <math.h>  
#include "Display.h"
#define PI 3.141592653589793
#define R 6371.0f // Radius of Earth in kilometers
#define MAX_FIELD_LEN 20

// GPS data variables
char    GPS_time[11] = "";   
char    GPS_status   = 'V';
float   lat          = 0.0f;
char    GPS_NS       = 'N';
float   lon          = 0.0f;
char    GPS_EW       = 'E';
char   GPS_speed[8]    = "";
float   GPS_speed_v =0;
float   GPS_course   = 0.0f;
uint8_t GPS_date[7]  = "";  
uint8_t mv[6]        = "";   // Magnetic variation
char    mvEW        = ' ';
char    posMode     = ' ';

// Convert string representation of a floating-point number to float
float ratof(char *arr)
{
  float val = 0;
  int afterdot=0;
  float scale=1;
  int neg = 0; 

  if (*arr == '-') { // Check for negative sign
    arr++;
    neg = 1;
  }
  while (*arr) {
    if (afterdot) {
      scale = scale/10;
      val = val + (*arr-'0')*scale;
    } else {
      if (*arr == '.') 
    afterdot++;
      else
    val = val * 10.0 + (*arr - '0');
    }
    arr++;
  }
  if(neg) return -val;
  else    return  val;
}

// Parse GPS buffer and extract relevant data
void GPS_Spreading_Data(const char *gps_buffer) {
    char        field[MAX_FIELD_LEN];
    const char *p;
    uint8_t     idx;
    uint8_t     len;

		// Ensure the buffer contains a valid $GPRMC sentence
    if (gps_buffer == NULL || strncmp(gps_buffer, "$GPRMC,", 7) != 0) {
        return;
    }

    p   = gps_buffer + 7;
    idx = 0;

    while (*p != '\0' && idx <= 11) {
        len = 0;
        while (*p != '\0' && *p != ',' && len < (MAX_FIELD_LEN - 1)) {
            field[len++] = *p++;
        }
        field[len] = '\0';  
        
				// Assign extracted data based on field index
        switch (idx) {
            case 0:
                strncpy(GPS_time, field, sizeof(GPS_time) - 1);
                GPS_time[sizeof(GPS_time) - 1] = '\0'; // git time
                break;
            case 1:
                GPS_status = field[0]; // statuse
                break;
            case 2:
              lat = GPS_angle_format_to_degrees((float)ratof(field));
                break;
            case 3:
                GPS_NS = field[0];
                break;
            case 4:
              lon = GPS_angle_format_to_degrees((float)ratof(field));
                break;
            case 5:
                GPS_EW = field[0];
                break;
            case 6:
              GPS_speed_v = (float)ratof(field)*0.514444*18/5;
						int_to_string ((int)GPS_speed_v, GPS_speed);
                break;
            case 7:
               GPS_course = (float)ratof(field);
                break;
            case 8:
                strncpy((char*)GPS_date, field, sizeof(GPS_date) - 1);
                GPS_date[sizeof(GPS_date) - 1] = '\0';
                break;
            case 9:
                strncpy((char*)mv, field, sizeof(mv) - 1); 
                mv[sizeof(mv) - 1] = '\0';
                break;
            case 10:
                mvEW = field[0];
                break;
            case 11:
                posMode = field[0];
                break;
            default:
                break;
        }

        if (*p == ',') {
            p++;
        }
        idx++;
    }
}
// Convert GPS latitude/longitude in ddmm.mmmmm format to decimal degrees
float GPS_angle_format_to_degrees(float angle) {  
    int degrees = (int)angle / 100;  
    float minutes = angle - (float)degrees * 100;  
    return (degrees + (minutes / 60.0f));  
}

// Convert GPS angle in decimal degrees to radians
float GPS_angle_formate_to_rad(float angle) {
    return (((angle) * PI) / 180.0f);  
}

// Convert degrees to radians
float GPS_degree_to_radians(float degrees) {         
    return ((degrees * PI) / 180.0f);
}

// Convert radians to degrees
float GPS_radians_to_degree(float radians) {         
    return ((radians * 180.0f) / PI);
}

// Calculate the distance between two points
float GPS_Calculate_Distance(float currentLong, float currentLat, float destLong, float destLat) {
    float currentLongRad = GPS_degree_to_radians(currentLong);
    float currentLatRad  = GPS_degree_to_radians(currentLat);
    float destLongRad    = GPS_degree_to_radians(destLong);
    float destLatRad     = GPS_degree_to_radians(destLat);

    float longDiff = destLongRad - currentLongRad;
    float latDiff  = destLatRad - currentLatRad;

		// Haversine formula for distance calculation
    float a = pow(sin(latDiff / 2), 2) + cos(currentLatRad) * cos(destLatRad) * pow(sin(longDiff / 2), 2);  // Haversine formula
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    return R*c*1000; // Convert distance from kilometers to meters

}


