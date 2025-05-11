#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "GPS_functions.h"
#include <stdint.h>
#include <math.h>  // For mathematical functions like sinf, cosf, sqrtf, etc.
#include "Display.h"
// Constants for GPS calculations
#define PI 3.141592653589793
#define R 6371.0f // Radius of Earth in kilometers
#define MAX_FIELD_LEN 20
char    GPS_time[11] = "";   // HHMMSS.ss
char    GPS_status   = 'V';
float   lat          = 0.0f;
char    GPS_NS       = 'N';
float   lon          = 0.0f;
char    GPS_EW       = 'E';
char   GPS_speed[8]    = "";
float   GPS_speed_v =0;
float   GPS_course   = 0.0f;
uint8_t GPS_date[7]  = "";   // DDMMYY
uint8_t mv[6]        = "";   // Magnetic variation
char    mvEW        = ' ';
char    posMode     = ' ';
float ratof(char *arr)
{
  float val = 0;
  int afterdot=0;
  float scale=1;
  int neg = 0; 

  if (*arr == '-') {
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
void GPS_Spreading_Data(const char *gps_buffer) {
    /* 1. Declarations first (C90) */
    char        field[MAX_FIELD_LEN];
    const char *p;
    uint8_t     idx;
    uint8_t     len;

    /* 2. Validate that buffer starts with "$GPRMC," */
    if (gps_buffer == NULL || strncmp(gps_buffer, "$GPRMC,", 7) != 0) {
        return;
    }

    /* 3. Initialize pointer—skip the "$GPRMC," prefix */
    p   = gps_buffer + 7;
    idx = 0;

    /* 4. Parse up to 12 fields separated by commas */
    while (*p != '\0' && idx <= 11) {
        len = 0;
        /* Copy characters into local field buffer */
        while (*p != '\0' && *p != ',' && len < (MAX_FIELD_LEN - 1)) {
            field[len++] = *p++;
        }
        field[len] = '\0';  /* Null-terminate */
        
        /* 5. Assign to globals based on field index */
        switch (idx) {
            case 0:
                /* UTC Time: hhmmss.sss */
                strncpy(GPS_time, field, sizeof(GPS_time) - 1);
                GPS_time[sizeof(GPS_time) - 1] = '\0';
                break;
            case 1:
                /* Status: A=active, V=void */
                GPS_status = field[0];
                break;
            case 2:
                /* Latitude: ddmm.mmmm format */
              lat = GPS_angle_format_to_degrees((float)ratof(field));
                break;
            case 3:
                /* North/South indicator */
                GPS_NS = field[0];
                break;
            case 4:
                /* Longitude: dddmm.mmmm format */
              lon = GPS_angle_format_to_degrees((float)ratof(field));
                break;
            case 5:
                /* East/West indicator */
                GPS_EW = field[0];
                break;
            case 6:
                /* Speed over ground in knots */
              GPS_speed_v = (float)ratof(field)*0.514444*18/5;
						int_to_string ((int)GPS_speed_v, GPS_speed);
                break;
            case 7:
                /* Course over ground in degrees */
               GPS_course = (float)ratof(field);
                break;
            case 8:
                /* Date: DDMMYY */
                strncpy((char*)GPS_date, field, sizeof(GPS_date) - 1);
                GPS_date[sizeof(GPS_date) - 1] = '\0';
                break;
            case 9:
                /* Magnetic variation */
                strncpy((char*)mv, field, sizeof(mv) - 1);
                mv[sizeof(mv) - 1] = '\0';
                break;
            case 10:
                /* Magnetic variation direction */
                mvEW = field[0];
                break;
            case 11:
                /* Mode indicator: A=autonomous, D=differential */
                posMode = field[0];
                break;
            default:
                break;
        }

        /* 6. Advance past comma if present */
        if (*p == ',') {
            p++;
        }
        idx++;
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
    return (((angle) * PI) / 180.0f);  // Convert degrees to radians
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
float GPS_Calculate_Distance(float currentLong, float currentLat, float destLong, float destLat) {
    // Get Radian Angle
    float currentLongRad = GPS_degree_to_radians(currentLong);
    float currentLatRad  = GPS_degree_to_radians(currentLat);
    float destLongRad    = GPS_degree_to_radians(destLong);
    float destLatRad     = GPS_degree_to_radians(destLat);

    // Get Difference
    float longDiff = destLongRad - currentLongRad;
    float latDiff  = destLatRad - currentLatRad;

    // Calculate Distance
    float a = pow(sin(latDiff / 2), 2) + cos(currentLatRad) * cos(destLatRad) * pow(sin(longDiff / 2), 2);  // Haversine formula
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    return R*c*1000;

}

// You can expand this function to calculate other values like bearing, etc.

