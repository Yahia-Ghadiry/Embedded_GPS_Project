#include "uart.h"
#include "TM4C123.h"
#include "bit_utilies.h"

void UART0_vInit(void)
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
    UART0_LCRH_R = UART_8_n_1_FIFO;
	
    // 5. Select system clock as UART clock source
    UART0_CC_R = UART_SYSCLK_SOURCE;
	
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

void UART5_vInit(void)
{
    // 1. Enable clocks for UART5 and Port E
   SET(SYSCTL_RCGCUART_R, UART5_CLOCK_PIN);    // Enable UART5 clock
    SET(SYSCTL_RCGCGPIO_R, GPIOE_CLOCK_PIN);     // Enable GPIOE clock
    while ((SYSCTL_PRGPIO_R & GPIOE_CLOCK_PIN) == CLOCK_READY_PIN); // Wait for GPIOE to be ready

    // 2. Disable UART5 before configuration
    UART5_CTL_R &= ~(1 << 0); // Disable UART

    // 3. Set Baud Rate (Assume 9600 baud, 16 MHz clock)
    UART5_IBRD_R = BAUD_16_9600_I;;   // Integer part
    UART5_FBRD_R =BAUD_16_9600_F ;    // Fractional part

    // 4. Configure line control: 8-bit, no parity, 1-stop bit, FIFO enabled
    UART5_LCRH_R = UART_8_n_1_FIFO ; // 8-bit, FIFO

    // 5. Set system clock as UART clock source
    UART5_CC_R = UART_SYSCLK_SOURCE;

    // 6. Enable UART5, TX and RX
    UART5_CTL_R |= (1 << 0) | (1 << 8) | (1 << 9);

    // 7. Enable alternate functions on PE4 (RX), PE5 (TX)
    GPIO_PORTE_AFSEL_R |= (1 << 4) | (1 << 5);

    // 8. Configure PE4 and PE5 for UART5 in PCTL
    GPIO_PORTE_PCTL_R &= ~0xFF000000;         // Clear bits for PE4/PE5
    GPIO_PORTE_PCTL_R |= (0x1 << 20) | (0x1 << 24); // PE4 = U5RX, PE5 = U5TX

    // 9. Enable digital function
    GPIO_PORTE_DEN_R |= (1 << 4) | (1 << 5);

    // 10. Disable analog function
    GPIO_PORTE_AMSEL_R &= ~((1 << 4) | (1 << 5));
}


uint8_t UART_u8Read(void) 
{  while(UART0_FR_R & UART_FR_RXFE) ;
  return (uint8_t )(UART0_DR_R &0XFF) ;
  
}  
void UART_ReadString(uint8_t* buffer, int maxLength) {
    int i = 0;
   uint8_t  c;
    while (i < (maxLength - 1)) {
        c = UART_u8Read();           // Custom function to receive a character
        if (c == '\r' || c == '\n') {  // Stop reading on Enter
            break;
        }
        buffer[i++] = c;
    }
    buffer[i] = '\0';  // Null-terminate the string
}


	void UART_Write(uint8_t data){
			while (UART0_FR_R & UART_FR_TXFF);  
			UART0_DR_R = data;      
	}
		
	void UART_WriteString(const uint8_t* str)
{
		     while (*str) 
			{
         UART_Write(*str++);
       } 
			
 } 

		
		