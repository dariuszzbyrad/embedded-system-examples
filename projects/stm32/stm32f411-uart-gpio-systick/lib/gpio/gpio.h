#include <stdint.h>
#include "stm32f4xx.h"

#define PA5_ON GPIOA->BSRR |= (1 << 5)  //Set PA5 with '1' (RM 8.4.7 s160)
#define PA5_OFF GPIOA->BSRR |= (1 << 21)  //Set PA5 with '0' (RM 8.4.7 s160)
#define PA5_TOGGLE GPIOA->ODR ^= (1 << 5)  //Toggle PA5

#define IS_BUTTON_PUSHED !(GPIOC->IDR & (1<<13))

void config_PC13(); //button on Nucleo board
void config_PA5();