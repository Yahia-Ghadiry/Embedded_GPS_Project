#include "uart.h"
#include "TM4C123.h"
#include "bit_utilies.h"

void UART_vInit(void)
{
	
	  // 1. Enable clock for UART0 and GPIOA
    SET(SYSCTL_RCGCUART_R, UART0_CLOCK_PIN);
    SET(SYSCTL_RCGCGPIO_R, GPIOA_CLOCK_PIN);
    while ((SYSCTL_PRGPIO_R & GPIOA_CLOCK_PIN) == CLOCK_READY_PIN);
	
    // 2. Disable UART0 before configuration
    CLR(UART0_CTL_R, UART0_CTL_PIN);
 
    // 3. Set Baud Rate
    UART0_IBRD_R = BAUD_16_9600_I;
		UART0_FBRD_R = BAUD_16_9600_F;
	
    // 4. Configure line control for 8-bit, no parity, 1-stop bit, FIFO enabled
    UART0_LCRH_R = UART0_8_n_1_FIFO;
	
    // 5. Select system clock as UART clock source
    UART0_CC_R = UART0_SYSCLK_SOURCE;
	
    // 6. Enable UART0, TX and RX
    SET(UART0_CTL_R, (UART0_TXE_PIN | UART0_RXE_PIN |UART0_UARTEN_PIN ));
		
    // 7. Enable alternate function on PA0, PA1
    SET(GPIO_PORTA_AFSEL_R, UART0_ALT_PA01);
		
    // 8. Configure PA0 and PA1 for UART
    GPIO_PORTA_PCTL_R = REV_MASK(GPIO_PORTA_PCTL_R,  UART0_PTL_PA01_MASK) | UART0_PTL_PA01;
 
    // 9. Enable digital I/O on PA0 and PA1
    SET(GPIO_PORTA_DEN_R, GPIO_PORTA_PIN01);
 
    // 10. Disable analog on PA0, PA1
    CLR(GPIO_PORTA_AMSEL_R, GPIO_PORTA_PIN01);
	
} 
uint8_t UART_u8Read(void) 
{  while(UART0_FR_R & UART_FR_RXFE) ;
  return (uint8_t )(UART0_DR_R &0XFF) ;
  
} 

	void UART0_Write(uint8_t data){
			while (UART0_FR_R & UART_FR_TXFF);        //Anas
			UART0_DR_R = data;      
	}
		
		
