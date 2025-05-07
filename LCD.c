#include "LCD.h"
#include "GPIO.h"
#include "tm4c123gh6pm.h"
#include "systickFunctions.h"
#include <stdint.h>

// Set the Enable pin (E) high to latch the data
void set_E(void) {
    GPIO_PORTD_DATA_R |= (1 << 2);  // Set E high (pin PD2)
}

// Clear the Enable pin (E) low to finish the operation
void clear_E(void) {
    GPIO_PORTD_DATA_R &= ~(1 << 2);  // Set E low (pin PD2)
}

// Set the Register Select (RS) pin high for data mode
void set_control_LCD(void) {
    GPIO_PORTD_DATA_R |= 0x02;  // RS = 1 (data mode)
}

// Set the Register Select (RS) pin low for command mode
void clear_control_LCD(void) {
    GPIO_PORTD_DATA_R &= ~(0x03);  // RS = 0, RW = 0 (command mode)
}

// Helper function to send a 4-bit nibble over PB0–PB3
void send_nibble(uint8_t nibble) {
    GPIO_PORTB_DATA_R = (GPIO_PORTB_DATA_R & 0xF0) | (nibble & 0x0F);  // Mask and write nibble to PB0–PB3
    pulse_E();
}

// Helper function to send a byte (high nibble first, then low nibble)
void send_LCD(uint8_t byte, uint8_t is_data) {
    if (is_data) {
        set_control_LCD();  // RS = 1 (data mode)
    } else {
        clear_control_LCD();  // RS = 0 (command mode)
    }

    send_nibble(byte >> 4);  // Send high nibble first
    send_nibble(byte & 0x0F);  // Then send low nibble
    DelayUs(40);  // Wait for processing
}

// Pulse the Enable pin (E) to latch the data/nibble into the LCD
void pulse_E(void) {
    set_E();    // Set E high
    DelayUs(1); // Small delay
    clear_E();  // Set E low
    DelayUs(1); // Small delay
}

// Initialize LCD (4-bit mode)
void init_LCD(void) {
    GPIO_Init_PortB();
    GPIO_Init_PortD_LCD();
    DelayMs(50);

    // Function Set (4-bit mode)
    clear_control_LCD();               // RS = 0 for command
    send_LCD(0x28, 0);  // 4-bit mode, 2-line display, 5x8 dots
    DelayMs(5);  // Wait for LCD to process

    // Display ON, Cursor OFF
    send_LCD(0x0C, 0);  // Display on, cursor off
    DelayMs(3);

    // Clear Display
    clear();

    // Entry Mode
    send_LCD(0x06, 0);  // Auto increment cursor, no display shift
    DelayMs(3);
}

// Clear LCD display
void clear(void) {
    clear_control_LCD();
    send_LCD(0x01, 0);  // Clear display command
    DelayMs(3);
}

// Shift cursor
void shift_curser(void) {
    clear_control_LCD();
    send_LCD(0x18, 0);  // Shift cursor to the left
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
        default: return;  // Invalid row
    }

    clear_control_LCD();
    send_LCD(address, 0);  // Send address command
    DelayUs(60);
}

// Display a single character
void display_char(uint8_t c) {
    clear_control_LCD();
    send_LCD(c, 1);  // RS = 1 for data
    DelayUs(60);
}

// Display a string of characters
void display_String(uint8_t *str) {
    while(*str) {
        display_char(*str++);
    }
}
