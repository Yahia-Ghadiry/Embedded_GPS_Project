#include "uart.h"
#include "TM4C123.h"
#include "bit_utilies.h"

void UART0_vInit(void)
{
	
    SET(SYSCTL_RCGCUART_R, UART0_CLOCK_PIN);
    SET(SYSCTL_RCGCGPIO_R, GPIOA_CLOCK_PIN);
    while ((SYSCTL_PRGPIO_R & GPIOA_CLOCK_PIN) == CLOCK_READY_PIN);
	
    CLR(UART0_CTL_R, UART_CTL_PIN);
 
    UART0_IBRD_R = BAUD_16_9600_I;
		UART0_FBRD_R = BAUD_16_9600_F;
	
    UART0_LCRH_R = UART_8_n_1_FIFO;
	
    UART0_CC_R = UART_SYSCLK_SOURCE;
	
    SET(UART0_CTL_R, UART_PIN );
		
    SET(GPIO_PORTA_AFSEL_R, UART0_ALT_PA01);
		
    GPIO_PORTA_PCTL_R = REV_MASK(GPIO_PORTA_PCTL_R,  UART0_PTL_PA01_MASK) | UART0_PTL_PA01;
 
    SET(GPIO_PORTA_DEN_R, GPIO_PORTA_PIN01);
 
    CLR(GPIO_PORTA_AMSEL_R, GPIO_PORTA_PIN01);
	
} 
void UART6_vInit(void)
{
		SET(SYSCTL_RCGCUART_R, UART6_CLOCK_PIN);    // ox20
    SET(SYSCTL_RCGCGPIO_R, GPIOD_CLOCK_PIN);    
    while ((SYSCTL_PRGPIO_R & GPIOD_CLOCK_PIN) == CLOCK_READY_PIN);  

     CLR(UART6_CTL_R, UART_CTL_PIN);

    UART6_IBRD_R = BAUD_16_9600_I;   
    UART6_FBRD_R = BAUD_16_9600_F ;  

    UART6_LCRH_R = UART_8_n_1_FIFO;

    UART6_CC_R = UART_SYSCLK_SOURCE;

     SET(UART6_CTL_R, UART_PIN);

    SET(GPIO_PORTD_AFSEL_R, GPIOD_PIN45);  

		
    GPIO_PORTD_PCTL_R = REV_MASK(GPIO_PORTD_PCTL_R,  UART6_PTL_PD45_MASK) | UART6_PTL_PD45;
		
     SET(GPIO_PORTD_DEN_R, GPIOD_PIN45 ); 

    CLR(GPIO_PORTD_AMSEL_R, GPIOD_PIN45) ;
}

void UART5_vInit(void)
{
   SET(SYSCTL_RCGCUART_R, UART5_CLOCK_PIN);    // ox20
    SET(SYSCTL_RCGCGPIO_R, GPIOE_CLOCK_PIN);    
    while ((SYSCTL_PRGPIO_R & GPIOE_CLOCK_PIN) == CLOCK_READY_PIN);  

     CLR(UART5_CTL_R, UART_CTL_PIN);

    UART5_IBRD_R = BAUD_16_9600_I;   // Integer part
    UART5_FBRD_R = BAUD_16_9600_F ;    // Fractional part

    UART5_LCRH_R = UART_8_n_1_FIFO ;

    UART5_CC_R = UART_SYSCLK_SOURCE;

     SET(UART5_CTL_R, UART_PIN );

    SET(GPIO_PORTE_AFSEL_R, GPIOE_PIN45);  

    GPIO_PORTE_PCTL_R = REV_MASK(GPIO_PORTE_PCTL_R,  UART5_PTL_PE45_MASK) | UART5_PTL_PE45;
		
     SET(GPIO_PORTE_DEN_R,GPIOE_PIN45); // GPIO_PORTE_DEN_R |= (1 << 4) | (1 << 5);

    CLR(GPIO_PORTE_AMSEL_R,GPIOE_PIN45) ;
}


char UART_u8Read(char UART_ID) 
                                     
{  
	switch (UART_ID)
	{
		case UART0_ID:
			while(UART0_FR_R & UART_FR_RXFE) ;
			return (uint8_t) (UART0_DR_R & 0XFF) ;
			
		case UART5_ID:
			while(UART5_FR_R & UART_FR_RXFE) ;
			return (uint8_t) (UART5_DR_R & 0XFF) ;
	
		case UART6_ID:
			while(UART6_FR_R & UART_FR_RXFE) ;
			return (uint8_t) (UART6_DR_R & 0XFF) ;
	} 
}


void UART_vReadString(uint8_t UART_ID, char* buffer, int maxLength) {
    int i = 0;
   uint8_t  c;
    while (i < (maxLength - 1)) {
        c = UART_u8Read(UART_ID);           
        if (c == '\r' || c == '\n') {  
            break;
        }
        buffer[i++] = c;
    }
    buffer[i] = '\0';  
}


	void UART_vWrite(uint8_t UART_ID, uint8_t data)
	{
		switch(UART_ID)
		{
			case UART0_ID:
				while (UART0_FR_R & UART_FR_TXFF);  
				UART0_DR_R = data;      
					break;
			case UART5_ID:
				while (UART5_FR_R & UART_FR_TXFF);  
				UART5_DR_R = data;      
					break;
			case UART6_ID:
				while (UART6_FR_R & UART_FR_TXFF);  
				UART6_DR_R = data;      
					break;
		}			
	}
		
void UART_vWriteString(uint8_t UART_ID, const char* str)
{
		  while (*str) 
			{
         UART_vWrite(UART_ID, *str++);
       } 
			
} 
			