#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "systickFunctions.h"



// Dummy SystemInit to satisfy the linker
void SystemInit(void)
{
    // Normally, you can set the system clock here if you want
    // But for now, leave it empty or basic
}

// Initialize SysTick Timer
void SysTick_Init(void)
{
    NVIC_ST_CTRL_R = 0;              // 1) Disable SysTick during setup
    NVIC_ST_RELOAD_R = 0x00FFFFFF;    // 2) Maximum reload value (24-bit)
    NVIC_ST_CURRENT_R = 0;            // 3) Clear current value
    NVIC_ST_CTRL_R = 0x05;             // 4) Enable SysTick with core clock (no interrupts)
}

// Simple delay function (time in milliseconds)
void SysTick_DelayMs(uint32_t delay)
{
    // Assuming system clock = 16 MHz
    uint32_t i;
    for(i = 0; i < delay; i++)
    {
        NVIC_ST_RELOAD_R = 16000 - 1; // 1 ms delay (16,000 cycles at 16 MHz)
        NVIC_ST_CURRENT_R = 0;        // Clear current value
        while((NVIC_ST_CTRL_R & 0x00010000) == 0)
        {
            // Wait for COUNT flag to be set
        }
    }
}

