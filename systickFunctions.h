#ifndef SYSTICKSIMPLE_H
#define SYSTICKSIMPLE_H

#include <stdint.h>

// Function prototypes
void SystemInit(void);
void SysTick_Init(void);
void SysTick_DelayMs(uint32_t delay);
void SysTick_DelayUs(uint32_t delay);
#endif // SYSTICKSIMPLE_H