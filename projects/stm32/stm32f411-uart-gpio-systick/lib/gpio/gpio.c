#include "gpio.h"

// Configure PC13 as input with pull-up
void config_PC13() {
	// 1. Enable GPIOC clock (RM 6.3.9, p.117)
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

	// 2. Configure PC13 as input (RM 8.4.1, p.157)
	GPIOC->MODER &= ~(GPIO_MODER_MODER13);  // Clear bits for PC13 (input mode is 00)

	// 3. Enable pull-up resistor for PC13 (RM 8.4.4, p.158)
	GPIOC->PUPDR &= ~(GPIO_PUPDR_PUPDR13);  // Clear bits for PUPDR13 first
	GPIOC->PUPDR |= GPIO_PUPDR_PUPDR13_0;   // Set bit to 01 for pull-up
}

// Configure PA5 as output with fast speed, push-pull, and no pull-up/pull-down
void config_PA5() {
	// 1. Enable GPIOA clock (RM 6.3.9, p.117)
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

	// 2. Configure PA5 as output (RM 8.4.1, p.157)
	GPIOA->MODER &= ~(GPIO_MODER_MODER5);    // Clear bits for PA5 first
	GPIOA->MODER |= GPIO_MODER_MODER5_0;     // Set bit to 01 for output mode

	// 3. Configure PA5 as push-pull output (RM 8.4.2, p.157)
	GPIOA->OTYPER &= ~(GPIO_OTYPER_OT5);     // Set bit to 0 for push-pull

	// 4. Set output speed for PA5 as fast (RM 8.4.3, p.158)
	GPIOA->OSPEEDR &= ~(GPIO_OSPEEDER_OSPEEDR5); // Clear speed bits first
	GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR5_0;  // Set bit to 1:0 for fast speed

	// 5. Configure PA5 with no pull-up/pull-down (RM 8.4.4, p.158)
	GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPDR5);       // Clear both bits for no pull-up/pull-down
}
