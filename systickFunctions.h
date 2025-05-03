#ifndef SYSTICKSIMPLE_H

#define SYSTICKSIMPLE_H
#include <stdint.h>


// Function prototypes
void SystemInit(void);
void SysTick_Init(void);
void DelayMs(uint32_t delay);

void DelayUs(uint32_t delay);

#endif 
