#include "uart.h"
#include "tm4c123gh6pm.h"
#include "bit_utilies.h"

void UART0_vInit(void)
{
	
	  // 1. Enable clock for UART0 and GPIOA
    SET(SYSCTL_RCGCUART_R, UART0_CLOCK_PIN);
    SET(SYSCTL_RCGCGPIO_R, GPIOA_CLOCK_PIN);
    while ((SYSCTL_PRGPIO_R & GPIOA_CLOCK_PIN) == CLOCK_READY_PIN);
	
    // 2. Disable UART0 before configuration
    CLR(UART0_CTL_R, UART_CTL_PIN);
 
    // 3. Set Baud Rate
    UART0_IBRD_R = BAUD_16_9600_I;
		UART0_FBRD_R = BAUD_16_9600_F;
	
    // 4. Configure line control for 8-bit, no parity, 1-stop bit, FIFO enabled
    UART0_LCRH_R = UART_8_n_1_FIFO;
	
    // 5. Select system clock as UART clock source
    UART0_CC_R = UART_SYSCLK_SOURCE;
	
    // 6. Enable UART0, TX and RX
    SET(UART0_CTL_R, UART_PIN );
		
    // 7. Enable alternate function on PA0, PA1
    SET(GPIO_PORTA_AFSEL_R, UART0_ALT_PA01);
		
    // 8. Configure PA0 and PA1 for UART
    GPIO_PORTA_PCTL_R = REV_MASK(GPIO_PORTA_PCTL_R,  UART0_PTL_PA01_MASK) | UART0_PTL_PA01;
 
    // 9. Enable digital I/O on PA0 and PA1
    SET(GPIO_PORTA_DEN_R, GPIO_PORTA_PIN01);
 
    // 10. Disable analog on PA0, PA1
    CLR(GPIO_PORTA_AMSEL_R, GPIO_PORTA_PIN01);
	
} 
<<<<<<< HEAD

void UART5_vInit(void)
{
    // 1. Enable clocks for UART5 and Port E
   SET(SYSCTL_RCGCUART_R, UART5_CLOCK_PIN);    // ox20
    SET(SYSCTL_RCGCGPIO_R, GPIOE_CLOCK_PIN);    
    while ((SYSCTL_PRGPIO_R & GPIOE_CLOCK_PIN) == CLOCK_READY_PIN);  

    // 2. Disable UART5 before configuration
     CLR(UART5_CTL_R, UART_CTL_PIN);

    // 3. Set Baud Rate (Assume 9600 baud, 16 MHz clock)
    UART5_IBRD_R = BAUD_16_9600_I;;   // Integer part
    UART5_FBRD_R =BAUD_16_9600_F ;    // Fractional part

    // 4. Configure line control: 8-bit, no parity, 1-stop bit, FIFO enabled
    UART5_LCRH_R = UART_8_n_1_FIFO ;

    // 5. Set system clock 
    UART5_CC_R = UART_SYSCLK_SOURCE;

    // 6. Enable UART5, TX and RX
     SET(UART5_CTL_R, UART_PIN );

    // 7. Enable alternate functions on PE4 (RX), PE5 (TX)
    SET(GPIO_PORTE_AFSEL_R, UART5_CLOCK_PIN);  //GPIO_PORTE_AFSEL_R |= (1 << 4) | (1 << 5);

    // 8. Configure PE4 and PE5 for UART5 in PCTL
		
     SET(GPIO_PORTE_PCTL_R, UART5_PTL_PE45);     //GPIO_PORTE_PCTL_R |= (0x1 << 20) | (0x1 << 24); // PE4 = U5RX, PE5 = U5TX

    // 9. Enable digital function
     SET(GPIO_PORTE_DEN_R,UART5_CLOCK_PIN ); // GPIO_PORTE_DEN_R |= (1 << 4) | (1 << 5);

    // 10. Disable analog function
    CLR(GPIO_PORTE_AMSEL_R,UART5_CLOCK_PIN ) ;
}


uint8_t UART_u8Read(uint8_t UART_ID) 
=======
void UART6_vInit(void)
{
    // 1. Enable clocks for UART5 and Port E
		SET(SYSCTL_RCGCUART_R, UART6_CLOCK_PIN);    // ox20
    SET(SYSCTL_RCGCGPIO_R, GPIOD_CLOCK_PIN);    
    while ((SYSCTL_PRGPIO_R & GPIOD_CLOCK_PIN) == CLOCK_READY_PIN);  

    // 2. Disable UART5 before configuration
     CLR(UART6_CTL_R, UART_CTL_PIN);

    // 3. Set Baud Rate (Assume 9600 baud, 16 MHz clock)
    UART6_IBRD_R = BAUD_16_9600_I;   // Integer part
    UART6_FBRD_R = BAUD_16_9600_F ;    // Fractional part

    // 4. Configure line control: 8-bit, no parity, 1-stop bit, FIFO enabled
    UART6_LCRH_R = UART_8_n_1_FIFO;

    // 5. Set system clock 
    UART6_CC_R = UART_SYSCLK_SOURCE;

    // 6. Enable UART5, TX and RX
     SET(UART6_CTL_R, UART_PIN);

    // 7. Enable alternate functions on PE4 (RX), PE5 (TX)
    SET(GPIO_PORTD_AFSEL_R, GPIOD_PIN45);  //GPIO_PORTE_AFSEL_R |= (1 << 4) | (1 << 5);

    // 8. Configure PE4 and PE5 for UART5 in PCTL //
		
    GPIO_PORTD_PCTL_R = REV_MASK(GPIO_PORTD_PCTL_R,  UART6_PTL_PD45_MASK) | UART6_PTL_PD45;
		
    // 9. Enable digital function
     SET(GPIO_PORTD_DEN_R, GPIOD_PIN45 ); // GPIO_PORTE_DEN_R |= (1 << 4) | (1 << 5);

    // 10. Disable analog function
    CLR(GPIO_PORTD_AMSEL_R, GPIOD_PIN45) ;
}

void UART5_vInit(void)
{
    // 1. Enable clocks for UART5 and Port E
   SET(SYSCTL_RCGCUART_R, UART5_CLOCK_PIN);    // ox20
    SET(SYSCTL_RCGCGPIO_R, GPIOE_CLOCK_PIN);    
    while ((SYSCTL_PRGPIO_R & GPIOE_CLOCK_PIN) == CLOCK_READY_PIN);  

    // 2. Disable UART5 before configuration
     CLR(UART5_CTL_R, UART_CTL_PIN);

    // 3. Set Baud Rate (Assume 9600 baud, 16 MHz clock)
    UART5_IBRD_R = BAUD_16_9600_I;   // Integer part
    UART5_FBRD_R = BAUD_16_9600_F ;    // Fractional part

    // 4. Configure line control: 8-bit, no parity, 1-stop bit, FIFO enabled
    UART5_LCRH_R = UART_8_n_1_FIFO ;

    // 5. Set system clock 
    UART5_CC_R = UART_SYSCLK_SOURCE;

    // 6. Enable UART5, TX and RX
     SET(UART5_CTL_R, UART_PIN );

    // 7. Enable alternate functions on PE4 (RX), PE5 (TX)
    SET(GPIO_PORTE_AFSEL_R, GPIOE_PIN45);  //GPIO_PORTE_AFSEL_R |= (1 << 4) | (1 << 5);

    // 8. Configure PE4 and PE5 for UART5 in PCTL //
    GPIO_PORTE_PCTL_R = REV_MASK(GPIO_PORTE_PCTL_R,  UART5_PTL_PE45_MASK) | UART5_PTL_PE45;
		
    // 9. Enable digital function
     SET(GPIO_PORTE_DEN_R,GPIOE_PIN45); // GPIO_PORTE_DEN_R |= (1 << 4) | (1 << 5);

    // 10. Disable analog function
    CLR(GPIO_PORTE_AMSEL_R,GPIOE_PIN45) ;
}


uint8_t UART_u8Read(uint8_t UART_ID) //while(UART0_FR_R & UART_FR_RXFE) ;
                                      //return (uint8_t )(UART0_DR_R &0XFF) 
>>>>>>> 1c27cebfb0c420c049d1406f17511a57a5f7b01c
{  
	switch (UART_ID)
	{
		case UART0_ID:
			while(UART0_FR_R & UART_FR_RXFE) ;
<<<<<<< HEAD
			return (uint8_t )(UART0_DR_R &0XFF) ;
			break;
		case UART5_ID:
			while(UART5_FR_R & UART_FR_RXFE) ;
			return (uint8_t )(UART5_DR_R &0XFF) ;
			break;
	}
}  
=======
			return (uint8_t) (UART0_DR_R & 0XFF) ;
			
		case UART5_ID:
			while(UART5_FR_R & UART_FR_RXFE) ;
			return (uint8_t) (UART5_DR_R & 0XFF) ;
	
		case UART6_ID:
			while(UART6_FR_R & UART_FR_RXFE) ;
			return (uint8_t) (UART6_DR_R & 0XFF) ;
	} 
} 

>>>>>>> 1c27cebfb0c420c049d1406f17511a57a5f7b01c
void UART_vReadString(uint8_t UART_ID, uint8_t* buffer, int maxLength) {
    int i = 0;
   uint8_t  c;
    while (i < (maxLength - 1)) {
        c = UART_u8Read(UART_ID);           // Custom function to receive a character
        if (c == '\r' || c == '\n') {  // Stop reading on Enter
            break;
        }
        buffer[i++] = c;
    }
    buffer[i] = '\0';  // Null-terminate the string
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
<<<<<<< HEAD
=======
			case UART6_ID:
				while (UART6_FR_R & UART_FR_TXFF);  
				UART6_DR_R = data;      
					break;
>>>>>>> 1c27cebfb0c420c049d1406f17511a57a5f7b01c
		}			
	}
		
void UART_vWriteString(uint8_t UART_ID, const uint8_t* str)
{
		  while (*str) 
			{
         UART_vWrite(UART_ID, *str++);
       } 
			
} 
	
		