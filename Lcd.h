#ifndef LCD_H

#define LCD_H
#include <stdint.h>

#define clear_char 1
#define	clear_control 0
#define	init_lcd_functions 0x28
#define			display_control 0x0c
#define			home 0x03
#define	shift 0x14				
void init_LCD(void);
void pulse_E(void);
void data_LCD(char c);
void set_control_LCD(void);
void clear_control_LCD(void);
void set_E(void);
void clear_E(void);
void clear(void);
void shift_curser(void);
void position_curser(uint8_t row, uint8_t col);
void display_char(uint8_t c);
void display_String(uint8_t *str);

#endif
