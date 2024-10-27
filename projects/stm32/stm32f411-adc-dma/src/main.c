#include "stm32f4xx.h"

// Define buffer to hold ADC values for PA1 and PA4
volatile uint16_t adc_values[2];

// Function Prototypes
void GPIO_Init(void);
void ADC_Init(void);
void ADC_Enable(void);
void ADC_Start(void);
void DMA_Init(void);
void DMA_Config(uint32_t srcAdd, uint32_t destAdd, uint16_t size);

// Main Function
int main(void) {
    // Initialize GPIO, DMA, and ADC
    GPIO_Init();
    DMA_Init();
    ADC_Init();
    ADC_Enable();

    // Configure DMA with source and destination addresses
    DMA_Config((uint32_t)&ADC1->DR, (uint32_t)adc_values, 2);

    // Start ADC conversions
    ADC_Start();

    // Main loop
    while (1) {
        // adc_values[0] = value from PA1 (ADC Channel 1)
        // adc_values[1] = value from PA4 (ADC Channel 4)

        // Add your logic here to process the ADC values as needed
    }
}

// GPIO Initialization (PA1 and PA4 as Analog Input)
void GPIO_Init(void) {
    RCC->AHB1ENR |= (1 << 0);  // Enable GPIOA clock

    // Set PA1 and PA4 to analog mode
    GPIOA->MODER |= (3 << (1 * 2)) | (3 << (4 * 2));  // Analog mode for PA1, PA4
}

// ADC Initialization
void ADC_Init(void) {
    // Enable ADC1 clock
    RCC->APB2ENR |= (1 << 8);  // ADC1 clock enabled

    // Clear ADC configuration registers before setup
    ADC1->CR1 = 0;
    ADC1->CR2 = 0;
    ADC1->SQR1 = 0;
    ADC1->SQR3 = 0;

    // Set the prescaler for the ADC (PCLK2 divided by 8)
    ADC->CCR |= (3 << 16);  // Set prescaler to divide by 8

    // Configure ADC scan mode and resolution
    ADC1->CR1 |= (1 << 8);  // Scan mode enabled (multiple channels)
    ADC1->CR1 &= ~(3 << 24);  // 12-bit resolution

    // Continuous conversion and DMA mode
    ADC1->CR2 |= (1 << 1);   // Continuous conversion mode
    ADC1->CR2 |= (1 << 10);  // End-of-conversion flag after each conversion
    ADC1->CR2 |= (1 << 8);   // Enable DMA
    ADC1->CR2 |= (1 << 9);   // Enable continuous DMA requests

    // Set the sampling time for channels 1 and 4 (use default time of 3 cycles)
    ADC1->SMPR2 &= ~((7 << 3) | (7 << 12));  // Set for channels 1 and 4 (PA1, PA4)

    // Set the sequence length for 2 conversions (PA1 and PA4)
    ADC1->SQR1 &= ~(0xF << 20);  // Clear sequence length bits
    ADC1->SQR1 |= (1 << 20);     // Sequence length: 2 conversions (L = 1 for 2 conversions)

    // Configure the sequence to read from PA1 (channel 1) and PA4 (channel 4)
    ADC1->SQR3 |= (1 << 0);  // First conversion: Channel 1 (PA1)
    ADC1->SQR3 |= (4 << 5);  // Second conversion: Channel 4 (PA4)
}

// ADC Enable (delay required for stabilization)
void ADC_Enable(void) {
    ADC1->CR2 |= (1 << 0);  // Enable ADC1
    for (volatile int i = 0; i < 10000; i++);  // Short delay for stabilization
}

// Start ADC Conversion
void ADC_Start(void) {
    ADC1->SR = 0;  // Clear status register
    ADC1->CR2 |= (1 << 30);  // Start conversion
}

// DMA Initialization
void DMA_Init(void) {
    RCC->AHB1ENR |= (1 << 22);  // Enable DMA2 clock

    // Disable DMA Stream 0 before configuring
    DMA2_Stream0->CR &= ~(1 << 0);  // Disable DMA stream

    // Configure DMA Stream
    DMA2_Stream0->CR &= ~(3 << 6);  // Data direction: Peripheral-to-memory
    DMA2_Stream0->CR |= (1 << 8);   // Circular mode
    DMA2_Stream0->CR |= (1 << 10);  // Memory increment mode
    DMA2_Stream0->CR |= (1 << 11) | (1 << 13);  // 16-bit data size for memory and peripheral
    DMA2_Stream0->CR &= ~(7 << 25);  // Select channel 0 for ADC1
}

// DMA Configuration (source and destination addresses)
void DMA_Config(uint32_t srcAdd, uint32_t destAdd, uint16_t size) {
    DMA2_Stream0->NDTR = size;   // Number of data items to transfer (2 conversions)
    DMA2_Stream0->PAR = srcAdd;  // Source address (ADC1 data register)
    DMA2_Stream0->M0AR = destAdd;  // Destination address (adc_values array)
    DMA2_Stream0->CR |= (1 << 0);  // Enable DMA stream
}
