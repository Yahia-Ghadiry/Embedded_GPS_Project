#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "GPIO.h"
extern uint16_t acumm_dis;



//======== Port A =================
void GPIO_Init_PortA(void) {
   	
	  SYSCTL_RCGCUART_R |= 0x01;     
		while ((SYSCTL_PRUART_R & 0x01) == 0) 
    SYSCTL_RCGCGPIO_R |= 0x01;     
    while ((SYSCTL_PRGPIO_R & 0x01) == 0); 
    UART0_CTL_R &= ~0x01;          
    UART0_IBRD_R = 104;            
    UART0_FBRD_R = 11;             
    UART0_LCRH_R = 0x70;          
    UART0_CTL_R = 0x301;           

    GPIO_PORTA_AFSEL_R |= 0x03;    
    GPIO_PORTA_PCTL_R |= 0x11;     
    GPIO_PORTA_DEN_R |= 0x03;      
    GPIO_PORTA_AMSEL_R &= ~0x03;   
}

//======== Port B =================
void GPIO_Init_PortB(void){
	SYSCTL_RCGCGPIO_R |= 0x02;
	while((SYSCTL_PRGPIO_R & 0x02) == 0){}
	
	GPIO_PORTB_LOCK_R = 0x4C4F434B;
	GPIO_PORTB_CR_R |= 0xFF;
		 GPIO_PORTB_AFSEL_R =0;
	GPIO_PORTB_AMSEL_R = 0;
		
	GPIO_PORTB_DIR_R |= 0xFF;
	GPIO_PORTB_PUR_R = 0x00;
	GPIO_PORTB_DEN_R |= 0xFF;
}
//======== Port D =================
void GPIO_Init_PortD_LCD(void){
	SYSCTL_RCGCGPIO_R |= 0x08;
	while((SYSCTL_PRGPIO_R & 0x08) == 0){}
	
	GPIO_PORTD_LOCK_R = 0x4C4F434B;
  GPIO_PORTD_CR_R |= 0x07;
		
  GPIO_PORTD_AFSEL_R &= ~(0X07);
	GPIO_PORTD_AMSEL_R &= ~(0X07);
		
	
	GPIO_PORTD_DIR_R |= 0x07;
	GPIO_PORTD_PUR_R = 0x00;
	GPIO_PORTD_DEN_R |= 0x07;
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
		 // Interrupt Configuration for PC4
    GPIO_PORTC_IS_R &= ~0x11;                
    GPIO_PORTC_IBE_R &= ~0x11;               
    GPIO_PORTC_IEV_R &= ~0x11;               
    GPIO_PORTC_ICR_R = 0x11;                 
    GPIO_PORTC_IM_R |= 0x11;                 

    NVIC_EN0_R |= (1 << 5);                  
	




}

void GPIO_Init_A_B_F(void){
	GPIO_Init_PortA();
	GPIO_Init_PortB();
	GPIO_Init_PortF();
}

void GPIO_LED_RED_ON(void)   { GPIO_PORTF_DATA_R |= 0x02; }
void GPIO_LED_RED_OFF(void)  { GPIO_PORTF_DATA_R = ~0x02; }
void GPIO_LED_BLUE_ON(void)  { GPIO_PORTF_DATA_R |= 0x04; }
void GPIO_LED_BLUE_OFF(void) { GPIO_PORTF_DATA_R &= ~0x04; }
void GPIO_LED_GREEN_ON(void)  { GPIO_PORTF_DATA_R |= 0x08; }
void GPIO_LED_GREEN_OFF(void) { GPIO_PORTF_DATA_R &= ~0x08; }

void GPIO_LED_ALL_ON(void) 	  {	GPIO_PORTF_DATA_R |= 0x0E  ;}

void GPIO_LED_ALL_OFF(void) 	{ GPIO_PORTF_DATA_R &= ~0x0E ;}

//=================== PORT C Init & Interrupt Config ==================
void GPIO_Init_PortC_PC4(void) {
    SYSCTL_RCGCGPIO_R |= 0x04;              
    while ((SYSCTL_PRGPIO_R & 0x04) == 0) {} 

    GPIO_PORTC_LOCK_R = 0x4C4F434B;        
    GPIO_PORTC_CR_R |= 0x30;               
    GPIO_PORTC_AFSEL_R &= ~0x30;           
    GPIO_PORTC_AMSEL_R &= ~0x30;            
   
  GPIO_PORTC_DIR_R = (GPIO_PORTC_DIR_R & ~0x10) | 0x20;		
    GPIO_PORTC_PUR_R |= 0x10;               
    GPIO_PORTC_DEN_R |= 0x30;

    GPIO_PORTC_IS_R &= ~0x10;                
    GPIO_PORTC_IBE_R &= ~0x10;               
    GPIO_PORTC_IEV_R &= ~0x10;              
    GPIO_PORTC_ICR_R = 0x10;               
    GPIO_PORTC_IM_R |= 0x10;                
    NVIC_EN0_R |= (1 << 2);                 
		enableGlobalInterrupts();
}


void enableGlobalInterrupts(void) {
    __enable_irq(); 
}



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

void GPIOC_Handler(void) {
    if (GPIO_PORTC_RIS_R & 0x10) {
        GPIO_PORTC_ICR_R = 0x10;   // Clear the interrupt
        acumm_dis = 0;
    }
}

