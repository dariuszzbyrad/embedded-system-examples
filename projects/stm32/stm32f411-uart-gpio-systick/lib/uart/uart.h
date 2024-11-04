#ifndef UART_H
#define UART_H

#include <stdint.h>
#include "stm32f4xx.h"

void UART2_Config(void);
void UART2_SendChar(uint8_t c);
void UART2_SendString(char* str);
uint8_t UART2_RecvChar(uint8_t *ch);
void UART2_SendWithPattern(char* pattern, uint8_t value);

#endif