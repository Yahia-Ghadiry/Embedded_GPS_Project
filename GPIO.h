#ifndef GPIO_H
#define GPIO_H
#include <stdint.h>


//========= #define section ============
#define GPIOA 0
#define GPIOB 1
#define GPIOC 2
#define GPIOD 3
#define GPIOE 4
#define GPIOF 5

#define ON 1
#define OFF 0

#define GPIO_SW1_INPUT ((GPIO_PORTF_DATA_R & 0x10) == 0)
#define GPIO_SW2_INPUT ((GPIO_PORTF_DATA_R & 0x01) == 0)

#define SET_R(reg,val)	reg |= val
#define CLR_R(reg,val)	reg &= ~val

#define SET_BIT(reg,bit)	reg |= (1<<bit)
#define CLR_BIT(reg,bit)	reg &= ~(1<<bit)
#define GET_BIT(reg,bit)	((reg>>bit)&0x01)

//distance Accum
extern uint16_t acumm_dis;

// Function Prototype

//======== Port A =================
void GPIO_Init_PortA(void);

//======== Port B =================
void GPIO_Init_PortB(void);

//======== Port F =================
void GPIO_Init_PortF(void);
//---------------------------------
void GPIO_Init_PortA(void);

//======== Port C =================
void GPIO_Init_PortC_PC4(void);

//======== Port D_LCD =================
void GPIO_Init_PortD_LCD(void);


void GPIO_LED_RED_ON(void);
void GPIO_LED_RED_OFF(void);
void GPIO_LED_BLUE_ON(void);
void GPIO_LED_BLUE_OFF(void);
void GPIO_LED_GREEN_ON(void);
void GPIO_LED_GREEN_OFF(void);
void GPIO_LED_ALL_ON(void);
void GPIO_LED_ALL_OFF(void);
//-----------Init---------------------
void GPIO_Init_A_B_F(void);
void enableGlobalInterrupts(void);
//=============== Functions ===============================
void GPIO_DATA_WRITE(uint8_t PORT, uint8_t VALUE);
int  GPIO_DATA_READ(uint8_t PORT);
void GPIO_DATA_SET(uint8_t PORT, uint8_t bit);
void GPIO_DATA_SET(uint8_t PORT, uint8_t bit);
void GPIO_DIR_SET(uint8_t PORT, uint8_t DIR);
//------------------
void GPIOPortC_Handler(void);




void delay(long int period);

#endif 
