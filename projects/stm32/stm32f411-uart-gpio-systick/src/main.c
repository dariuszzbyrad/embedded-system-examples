#include "main.h"
#include "uart.h"
#include "gpio.h"

// Constants for software timer intervals (in milliseconds)
#define UART2_READ_INTERVAL 50
#define UART2_WRITE_INTERVAL 2000
#define LED_UPDATE_INTERVAL 10
#define BUTTON_DEBOUNCE_INTERVAL 100

// System tick variable
__IO uint32_t Tick = 0;

// Software timer variables
uint32_t Timer_Read_UART2;
uint32_t Timer_Write_UART2;
uint32_t Timer_Led;
uint32_t Timer_Button;

// State variables
uint8_t led_status = 0;

// Function prototypes
void UpdateLedState(uint8_t state);
void ToggleLedState(void);
void InitTimers(void);
void CheckAndUpdateTimers(void);

// Main program
int main(void) {
	// Initialize system clock to generate 1ms tick interrupt
	SysTick_Config(SystemCoreClock / 1000);

	// Initialize peripherals
	UART2_Config();
	config_PC13();
	config_PA5();

	// Initialize timers
	InitTimers();

	// Send initial messages over UART
	UART2_SendString("START\r\n");

	while (1) {
		CheckAndUpdateTimers();
	}
}

// Initialize software timers with the current system tick
void InitTimers(void) {
	uint32_t currentTick = GetSystemTick();
	Timer_Read_UART2 = currentTick;
	Timer_Write_UART2 = currentTick;
	Timer_Led = currentTick;
	Timer_Button = currentTick;
}

// Function to check each timer and execute corresponding actions if the interval has elapsed
void CheckAndUpdateTimers(void) {
	uint32_t currentTick = GetSystemTick();
	uint8_t uart_data;

	// UART Write Timer - send status every 2 seconds
	if ((currentTick - Timer_Write_UART2) >= UART2_WRITE_INTERVAL) {
		Timer_Write_UART2 = currentTick;
		UART2_SendChar(led_status ? '1' : '0'); // Send LED status as '1' or '0'
	}

	// UART Read Timer - check for new UART commands every 50 ms
	if ((currentTick - Timer_Read_UART2) >= UART2_READ_INTERVAL) {
		Timer_Read_UART2 = currentTick;
		if (UART2_RecvChar(&uart_data) == 0) {
			// Update LED state based on received command
			if (uart_data == '1') {
				UpdateLedState(1);
			} else if (uart_data == '0') {
				UpdateLedState(0);
			}
		}
	}

	// LED Update Timer - refresh LED output based on state every 10 ms
	if ((currentTick - Timer_Led) >= LED_UPDATE_INTERVAL) {
		Timer_Led = currentTick;
		if (led_status) {
			PA5_ON;
		} else {
			PA5_OFF;
		}
	}

	// Button Timer - check button press every 100 ms
	if ((currentTick - Timer_Button) >= BUTTON_DEBOUNCE_INTERVAL) {
		Timer_Button = currentTick;
		if (IS_BUTTON_PUSHED) {
			ToggleLedState();
			// Debounce - wait until button is released
			while (IS_BUTTON_PUSHED);
		}
	}
}

// Toggle the LED state and update the led_status variable
void ToggleLedState(void) {
	led_status ^= 1;
}

// Update LED state based on UART or button input
void UpdateLedState(uint8_t state) {
	led_status = state;
}

// Interrupt handler for the system tick - increments the system tick variable
void SysTick_Handler(void) {
	Tick++;
}

// Get the current system tick count
uint32_t GetSystemTick(void) {
	return Tick;
}
