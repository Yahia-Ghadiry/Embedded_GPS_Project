#include "interrupts.h"

void SysTick_InitPeriodic(uint32_t period) {
    NVIC_ST_CTRL_R = 0;
    NVIC_ST_RELOAD_R = period - 1;
    NVIC_ST_CURRENT_R = 0;
    NVIC_ST_CTRL_R = NVIC_ST_CTRL_ENABLE_Msk |
        NVIC_ST_CTRL_TICKINT_Msk |
        NVIC_ST_CTRL_CLKSOURCE_Msk;
}

void SysTick_Handler(void) {

    //  Function
}

void Switch_Init(void) {
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R5;
    volatile uint32_t delay = SYSCTL_RCGCGPIO_R;
    (void)delay;

    GPIO_PORTF_LOCK_R = 0x4C4F434B;
    GPIO_PORTF_CR_R |= 0x11;       // 0x11 = 0x1 | 0x10

    GPIO_PORTF_DIR_R &= ~0x11;      
    GPIO_PORTF_DEN_R |= 0x11;      

    GPIO_PORTF_IS_R &= ~0x11;      
    GPIO_PORTF_IBE_R &= ~0x11;      
    GPIO_PORTF_IEV_R |= 0x11;      

    GPIO_PORTF_ICR_R = 0x11;        

    GPIO_PORTF_IM_R |= 0x11;       

    NVIC_EN1_R |= 0x4000;           
}

void GPIOPortF_Handler(void) {
    uint32_t status = GPIO_PORTF_MIS_R;

    if (status & 0x1) {            
        GPIO_PORTF_ICR_R = 0x1;    
        // handle switch on PF0 pressed
    }
    if (status & 0x10) {           
        GPIO_PORTF_ICR_R = 0x10;   
        //  handle switch on PF4 pressed
    }
}
