#ifndef LCD_H

#define LCD_H

#include <stdint.h>
#define clear_char 1
#define	clear_control 0
#define	init_lcd_functions 0x38
#define			display_control 0x0c
#define			entry 0x06
#define	shift 0x14				
void pulse_E(void);
void init_LCD(void);
void data_LCD(uint8_t c);
void set_E(void);
	void clear_E(void);
void set_control_LCD(void);
void clear_control_LCD(void);
void set_E(void);
void clear_E(void);
void clear(void);
void shift_curser(void);
void position_curser(uint8_t row, uint8_t column);
void display_char(uint8_t c);
void display_String(uint8_t *str);

#endif
