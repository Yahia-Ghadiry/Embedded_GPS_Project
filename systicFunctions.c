#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "systickFunctions.h"
#include "GPIO.h"



void SystemInit(void)
{
   
}

void SysTick_Init(void)
{
    NVIC_ST_CTRL_R = 0;              
    NVIC_ST_RELOAD_R = 0x00FFFFFF;    
    NVIC_ST_CURRENT_R = 0;            
    NVIC_ST_CTRL_R = 0x05;             
}

void DelayMs(uint32_t delay)
{
    uint32_t i;
    for(i = 0; i < delay; i++)
    {
        NVIC_ST_RELOAD_R = 16000 - 1; 
        NVIC_ST_CURRENT_R = 0;        
        while((NVIC_ST_CTRL_R & 0x00010000) == 0)
        {
           
        }
    }
}
void DelayUs(uint32_t delay)
{
    uint32_t i;
    for(i = 0; i < delay; i++)
    {
        NVIC_ST_RELOAD_R = 16 - 1;     
        NVIC_ST_CURRENT_R = 0;         
        while((NVIC_ST_CTRL_R & 0x00010000) == 0)
        {
         
        }
    }
}

