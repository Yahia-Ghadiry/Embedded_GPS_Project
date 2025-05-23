#ifndef UART_H
#define UART_H
#include "stdint.h"

#define UART0_CLOCK_PIN 0x01 
#define UART5_CLOCK_PIN 0x20  
#define UART6_CLOCK_PIN 0x40  
#define GPIOA_CLOCK_PIN 0x01  
#define GPIOC_CLOCK_PIN 0x04  
#define GPIOD_CLOCK_PIN 0x08
#define GPIOE_CLOCK_PIN 0x10

#define GPIOD_PIN45 0x30
#define GPIOE_PIN45 0x30

#define CLOCK_READY_PIN 0
#define UART_CTL_PIN 0x01
#define BAUD_16_9600_I 104
#define BAUD_16_9600_F 11

#define UART_8_n_1_FIFO 0x70
#define UART_SYSCLK_SOURCE 0x00
#define UART0_TXE_PIN 0x200
#define UART0_RXE_PIN 0x100
#define UART0_UARTEN_PIN 0x1 
#define   UART_PIN       0x301 


#define UART0_FR_TXFE 0x20 //Anas

#define UART0_ALT_PA01 0x03
#define UART0_PTL_PA01 0x00000011
#define UART0_PTL_PA01_MASK 0x000000FF 
#define UART5_PTL_PE45_MASK 0x00FF0000 
#define UART5_PTL_PE45 0x00110000
#define UART6_PTL_PD45_MASK 0x00FF0000 
#define UART6_PTL_PD45 0x00110000

#define GPIO_PORTA_PIN01 0x03

#define UART0_ID 0
#define UART5_ID 5
#define UART6_ID 6

void UART0_vInit(void) ;
void UART5_vInit(void) ;
void UART6_vInit(void) ;

char UART_u8Read(char UART_ID);
void UART_vReadString(uint8_t UART_ID, char* buffer, int maxLength) ;
void UART_vWrite(uint8_t UART_ID, uint8_t data); 
void UART_vWriteString(uint8_t UART_ID, const char* str) ;


#endif

