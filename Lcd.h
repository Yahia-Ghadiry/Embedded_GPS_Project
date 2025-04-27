#ifndef LCD_H

#define LCD_H
#include <stdint.h>
#endif
#define clear_char 1
#define	clear_control 0
void init_LCD(void);
void data_LCD(char c);
void control_LCD(char SW);
void clear(void);