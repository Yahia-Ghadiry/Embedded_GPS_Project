#ifndef UART_H
#define UART_H

#include "stdint.h"

#define UART0_CLOCK_PIN 0x01
#define GPIOA_CLOCK_PIN 0x01

#define CLOCK_READY_PIN 0

#define UART0_CTL_PIN 0x01

#define BAUD_16_9600_I 104
#define BAUD_16_9600_F 11

#define UART0_8_n_1_FIFO 0x70

#define UART0_SYSCLK_SOURCE 0x00

#define UART0_TXE_PIN 0x200
#define UART0_RXE_PIN 0x100
#define UART0_UARTEN_PIN 0x1


#define UART0_FR_TXFE 0x20 //Anas

#define UART0_ALT_PA01 0x03
#define UART0_PTL_PA01 0x00000011
#define UART0_PTL_PA01_MASK 0x000000FF

#define GPIO_PORTA_PIN01 0x03

void UART_vInit(void);

void UART0_Write(uint8_t data); //Anas
#endif
