#include "uart.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*
 * PA2: Tx, PA3: Rx
 */
void UART2_Config(void) {
    // 1. Enable clock for GPIOA (RM 6.3.9, p.117)
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    // 2. Configure PA2 as UART Tx (AF7) and PA3 as UART Rx (AF7)
    // Set PA2 (Tx) to Alternate Function Mode
    GPIOA->MODER &= ~GPIO_MODER_MODE2;          // Clear mode bits for PA2
    GPIOA->MODER |= GPIO_MODER_MODE2_1;         // Set PA2 to AF mode (10)

    // Set PA3 (Rx) to Alternate Function Mode
    GPIOA->MODER &= ~GPIO_MODER_MODE3;          // Clear mode bits for PA3
    GPIOA->MODER |= GPIO_MODER_MODE3_1;         // Set PA3 to AF mode (10)

    // Configure Alternate Function 7 (AF7) for PA2 and PA3 (USART2)
    GPIOA->AFR[0] |= (7 << GPIO_AFRL_AFSEL2_Pos) | (7 << GPIO_AFRL_AFSEL3_Pos);

    // Set PA3 as open-drain for Rx, keep PA2 as push-pull (default)
    GPIOA->OTYPER |= GPIO_OTYPER_OT3;

    // 3. Enable clock for USART2 (RM 6.3.11, p.118)
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

    // 4. Set baud rate to 9600 (assuming 16 MHz clock, BRR = 0x683)
    USART2->BRR = 0x683;

    // 5. Enable UART and its transmitter and receiver (RM 8.6.4, p.278)
    USART2->CR1 |= USART_CR1_UE | USART_CR1_TE | USART_CR1_RE;
}

// Transmit a single character over UART
void UART2_SendChar(uint8_t c) {
    USART2->DR = c;  // Load data into the Data Register
    while (!(USART2->SR & USART_SR_TXE)) {
        // Wait for transmission to complete
    }
}

// Transmit a string over UART
void UART2_SendString(const char* str) {
    while (*str) {
        UART2_SendChar((uint8_t)*str++);  // Send each character in the string
    }
}

// Receive a character from UART
uint8_t UART2_RecvChar(uint8_t *ch) {
    if (USART2->SR & USART_SR_RXNE) {   // Check if data is available to read
        *ch = (uint8_t)USART2->DR;      // Read received data
        return 0;                        // Return 0 for success
    }
    return 1;                            // Return 1 if no data is available
}

// Send a formatted string with a value over UART
void UART2_SendWithPattern(const char* pattern, uint8_t value) {
    char buffer[10];  // Buffer to hold the formatted output
    snprintf(buffer, sizeof(buffer), pattern, value);  // Format the string
    UART2_SendString(buffer);
    UART2_SendString("\r\n");
}
