#include <stdint.h>
#include "tm4c123.h"
#include "GPIO.h"
#include "elements.h"


//======== Port A =================
void GPIO_Init_PortA(void) {
   	
	  SYSCTL_RCGCUART_R |= 0x01;     // Enable UART0 clock
		while ((SYSCTL_PRUART_R & 0x01) == 0) 
    SYSCTL_RCGCGPIO_R |= 0x01;     // Enable PORTA clock
    while ((SYSCTL_PRGPIO_R & 0x01) == 0); // Wait for GPIOA to be ready

    UART0_CTL_R &= ~0x01;          // Disable UART0 during config
    UART0_IBRD_R = 104;            // Integer part for 9600 baud
    UART0_FBRD_R = 11;             // Fractional part for 9600 baud
    UART0_LCRH_R = 0x70;           // 8-bit, no parity, 1 stop bit, enable FIFO
    UART0_CTL_R = 0x301;           // Enable UART0, TXE and RXE

    GPIO_PORTA_AFSEL_R |= 0x03;    // Enable alt function on PA0, PA1
    GPIO_PORTA_PCTL_R |= 0x11;     // Configure PA0, PA1 for UART
    GPIO_PORTA_DEN_R |= 0x03;      // Enable digital I/O on PA0, PA1
    GPIO_PORTA_AMSEL_R &= ~0x03;   // Disable analog on PA0, PA1
}

//======== Port B =================
void GPIO_Init_PortB(void){
	SYSCTL_RCGCGPIO_R |= 0x02;
	while((SYSCTL_PRGPIO_R&0x02) == 0){}
	
	GPIO_PORTB_LOCK_R = 0x4C4F434B;
	GPIO_PORTB_CR_R |= 0xFF;
	
	GPIO_PORTB_DIR_R |= 0xFF;
	GPIO_PORTB_PUR_R = 0x00;
	GPIO_PORTB_DEN_R |= 0xFF;
}

//======== Port F =================
void GPIO_Init_PortF(void){
    SYSCTL_RCGCGPIO_R |= 0x20; 
    while ((SYSCTL_PRGPIO_R & 0x20) == 0);

    GPIO_PORTF_LOCK_R = 0x4C4F434B;
    GPIO_PORTF_CR_R |= 0x1F;                

    GPIO_PORTF_DIR_R |= 0x0E;                
    GPIO_PORTF_DEN_R |= 0x1F; 
    GPIO_PORTF_PUR_R |= 0x11;  
	
		GPIO_LED_ALL_OFF();
}

void GPIO_Init_A_B_F(void){
	GPIO_Init_PortA();
	GPIO_Init_PortB();
	GPIO_Init_PortF();
}

// Red LED (PF1)
void GPIO_LED_RED_ON(void)   { GPIO_PORTF_DATA_R |= 0x02; }
void GPIO_LED_RED_OFF(void)  { GPIO_PORTF_DATA_R = ~0x02; }

// Blue LED (PF2)
void GPIO_LED_BLUE_ON(void)  { GPIO_PORTF_DATA_R |= 0x04; }
void GPIO_LED_BLUE_OFF(void) { GPIO_PORTF_DATA_R &= ~0x04; }

// Green LED (PF3)
void GPIO_LED_GREEN_ON(void)  { GPIO_PORTF_DATA_R |= 0x08; }
void GPIO_LED_GREEN_OFF(void) { GPIO_PORTF_DATA_R &= ~0x08; }

// All LEDs (PF1 | PF2 | PF3)
void GPIO_LED_ALL_ON(void) 	  {	GPIO_PORTF_DATA_R |= 0x0E  ;}

void GPIO_LED_ALL_OFF(void) 	{ GPIO_PORTF_DATA_R &= ~0x0E ;}



//=============== Functions ===============================
void GPIO_DATA_WRITE(uint8_t PORT, uint8_t VALUE){
    switch(PORT){
        case GPIOA: GPIO_PORTA_DATA_R = VALUE; break;
        case GPIOB: GPIO_PORTB_DATA_R = VALUE; break;
        case GPIOC: GPIO_PORTC_DATA_R = VALUE; break;
        case GPIOD: GPIO_PORTD_DATA_R = VALUE; break;
        case GPIOE: GPIO_PORTE_DATA_R = VALUE; break;
        case GPIOF: GPIO_PORTF_DATA_R = VALUE; break;
        default:                               break;
    }
}

int GPIO_DATA_READ(uint8_t PORT){
    uint8_t value = 0;
		switch(PORT){
			case GPIOA: value = GPIO_PORTA_DATA_R ; break;
			case GPIOB: value = GPIO_PORTB_DATA_R ; break;
			case GPIOC: value = GPIO_PORTC_DATA_R ; break;
			case GPIOD: value = GPIO_PORTD_DATA_R ; break;
			case GPIOE: value = GPIO_PORTE_DATA_R ; break;
			case GPIOF: value = GPIO_PORTF_DATA_R ; break;
			default:																break;
    }
    
    return value; 
}
void GPIO_DATA_SET(uint8_t PORT, uint8_t bit){
    switch(PORT){
        case GPIOA: SET_BIT(GPIO_PORTA_DATA_R, bit); break;
        case GPIOB: SET_BIT(GPIO_PORTB_DATA_R, bit); break;
        case GPIOC: SET_BIT(GPIO_PORTC_DATA_R, bit); break;
        case GPIOD: SET_BIT(GPIO_PORTD_DATA_R, bit); break;
        case GPIOE: SET_BIT(GPIO_PORTE_DATA_R, bit); break;
        case GPIOF: SET_BIT(GPIO_PORTF_DATA_R, bit); break;
    }
}

void GPIO_DATA_RESET(uint8_t PORT, uint8_t bit){
    switch(PORT){
        case GPIOA: CLR_BIT(GPIO_PORTA_DATA_R, bit); break;
        case GPIOB: CLR_BIT(GPIO_PORTB_DATA_R, bit); break;
        case GPIOC: CLR_BIT(GPIO_PORTC_DATA_R, bit); break;
        case GPIOD: CLR_BIT(GPIO_PORTD_DATA_R, bit); break;
        case GPIOE: CLR_BIT(GPIO_PORTE_DATA_R, bit); break;
        case GPIOF: CLR_BIT(GPIO_PORTF_DATA_R, bit); break;
        default:                                     break;
    }
}

void GPIO_DIR_SET(uint8_t PORT, uint8_t DIR){
    switch(PORT){
        case GPIOA: GPIO_PORTA_DIR_R = DIR; break;
        case GPIOB: GPIO_PORTB_DIR_R = DIR; break;
        case GPIOC: GPIO_PORTC_DIR_R = DIR; break;
        case GPIOD: GPIO_PORTD_DIR_R = DIR; break;
        case GPIOE: GPIO_PORTE_DIR_R = DIR; break;
        case GPIOF: GPIO_PORTF_DIR_R = DIR; break;
        default:                            break;
    }
}

void delay(long int period) {
    volatile long int i;
    for (i = 0; i < period; i++);
}



