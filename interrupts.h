<<<<<<< HEAD
#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include <stdint.h>
#include "tm4c123gh6pm.h"    


void SysTick_InitPeriodic(uint32_t period);
void SysTick_Handler(void);


void Switch_Init(void);
void GPIOPortF_Handler(void);

#endif
=======
#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include <stdint.h>
#include "tm4c123gh6pm.h"    


void SysTick_InitPeriodic(uint32_t period);
void SysTick_Handler(void);


void Switch_Init(void);
void GPIOPortF_Handler(void);

#endif
>>>>>>> 9b8e08f62ca14b95d83abc4854daa54090471774
