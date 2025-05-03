#ifndef LCD_H

#define LCD_H


#define clear_char 1
#define	clear_control 0
#define	init_lcd_functions 0x3c
#define			display_control 0x0c
#define			entry 0x06
#define	shift 0x14				
void init_LCD(void);
void data_LCD(char c);
void set_control_LCD(void);
void clear_control_LCD(void);
void set_E(void);
void clear_E(void);
void clear(void);
void shift_curser(void);
void position_curser(char row, char column);
void display_char(char c);
void display_String(char *str);

#endif
