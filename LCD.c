#include "LCD.h"
#include "GPIO.h"
#include "tm4c123gh6pm.h"
#include "systickFunctions.h"
#include <stdint.h>

void set_E(void) {
    GPIO_PORTD_DATA_R |= (1 << 2);  
}

void clear_E(void) {
    GPIO_PORTD_DATA_R &= ~(1 << 2);  
}

void set_control_LCD(void) {
    GPIO_PORTD_DATA_R |= 0x02;  
}

void clear_control_LCD(void) {
    GPIO_PORTD_DATA_R &= ~(0x03); 
}

void send_nibble(uint8_t nibble) {
    GPIO_PORTB_DATA_R = (GPIO_PORTB_DATA_R & 0xF0) | (nibble & 0x0F);  
    pulse_E();
}

void send_LCD(uint8_t byte, uint8_t is_data) {
    if (is_data) {
        set_control_LCD();  
    } else {
        clear_control_LCD();  
    }

    send_nibble(byte >> 4);  
    send_nibble(byte & 0x0F);
    DelayUs(40);  
}

void pulse_E(void) {
    set_E();    
    DelayUs(1); 
    clear_E();  
    DelayUs(1); 
}

// Initialize LCD (4-bit mode)
void init_LCD(void) {
    GPIO_Init_PortB();
    GPIO_Init_PortD_LCD();
    DelayMs(50);

    clear_control_LCD();              
    send_LCD(0x28, 0);  
    DelayMs(5);  
    send_LCD(0x0C, 0);  
    DelayMs(3);

    clear();

    send_LCD(0x06, 0);  
    DelayMs(3);
}

// Clear LCD display
void clear(void) {
    clear_control_LCD();
    send_LCD(0x01, 0); 
    DelayMs(3);
}

// Shift cursor
void shift_curser(void) {
    clear_control_LCD();
    send_LCD(0x18, 0);  
    DelayUs(60);
}

// Set cursor position
void position_curser(uint8_t row, uint8_t col) {
    uint8_t address;

    switch(row) {
        case 0: address = 0x80 + col; break;  // Line 1
        case 1: address = 0xC0 + col; break;  // Line 2
        case 2: address = 0x94 + col; break;  // Line 3
        case 3: address = 0xD4 + col; break;  // Line 4
        default: return; 
    }

    clear_control_LCD();
    send_LCD(address, 0);  
    DelayUs(60);
}

// Display a single character
void display_char(uint8_t c) {
    clear_control_LCD();
    send_LCD(c, 1);  
    DelayUs(60);
}

// Display a string of characters
void display_String(uint8_t *str) {
    while(*str) {
        display_char(*str++);
    }
}
