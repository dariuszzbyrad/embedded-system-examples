# Embedded Systems Examples
Welcome to the **Embedded Systems Examples** repository! This repository contains a collection of code examples, tutorials, and snippets for working with embedded systems, including STM32 and Arduino projects. Each example focuses on different peripherals or functionalities, such as ADC (Analog-to-Digital Converters), GPIO (General Purpose Input/Output), UART (Universal Asynchronous Receiver-Transmitter), and more.

# About

This repository aims to provide useful examples and hands-on exercises for developers working with embedded systems. The code is written using register-level programming for STM32 microcontrollers and standard Arduino libraries.

Each folder contains a README specific to the example, detailing the project, the hardware setup, and instructions on how to compile and run the code.

# Projects

## 1\. ADC with DMA Example for STM32

This example demonstrates how to use the ADC with Direct Memory Access (DMA) on an STM32 microcontroller to read analog inputs on GPIO pins PA1 and PA4. The DMA transfers ADC values directly to memory, allowing for efficient, low-overhead data acquisition.

-   **File**: `projects/stm32/stm32f411-adc-dma`
-   **Main Features**:
    -   Configures PA1 and PA4 as analog inputs
    -   Sets up ADC for continuous conversion in scan mode
    -   Uses DMA to automatically transfer ADC values to memory
-   **Relevant Peripherals**: GPIO, ADC, DMA
-   **Target Microcontroller**: STM32F4 series

## 2\. UART, GPIO, and System Tick Example for STM32

This example demonstrates the use of UART communication, GPIO pin configuration, and System Tick timing on an STM32 microcontroller. It enables LED control via UART and a button, while also periodically reporting the LED's status.

-   **File**: `projects/stm32/stm32f411-uart-gpio-systick`
-   **Main Features**:
    -   Configures PA5 as an output for LED control and PC13 as an input for button press detection
    -   Sets up UART2 for 9600 baud communication (8N1 format)
    -   Implements a System Tick timer to manage timing for UART and button functions
    -   Allows LED control through UART commands and button toggling
-   **Relevant Peripherals**: GPIO, UART, System Tick
-   **Target Microcontroller**: STM32F4 series
    -   `UART2_SendString()`: Sends a string of characters over UART.
    -   `UART2_RecvChar()`: Receives a single character over UART (if available).
    -   `UART2_SendWithPattern()`: Sends a formatted message with a value over UART.
-   **System Tick Timer**:

    -   `SysTick_Handler()`: Increments a millisecond counter for time tracking.
    -   `GetSystemTick()`: Returns the current tick count.
-   **Main Loop**:

    -   Implements a non-blocking structure that checks and performs actions based on elapsed time:
        -   **UART Read (50 ms)**: Checks for incoming UART commands to control the LED.
        -   **UART Write (2 seconds)**: Sends the LED status.
        -   **Button (100 ms)**: Reads button state to toggle the LED.
        -   **LED Update (10 ms)**: Updates the LED based on the current state.

### How to Use
----------

1.  Connect the LED to PA5 and the button to PC13 on your STM32 development board.
2.  Open a UART terminal on your computer at 9600 baud, 8N1, and connect to the STM32's UART2 interface.
3.  Compile and upload the code to the STM32 microcontroller.
4.  Use the following commands over UART:
    -   Send `'1'` to turn the LED on.
    -   Send `'0'` to turn the LED off.
5.  Press the button connected to PC13 to toggle the LED state.
6.  Observe the LED status messages (`*` for on, `.` for off) sent every 2 seconds in the UART terminal.

### Notes
-----

-   **System Tick Timing**: The System Tick timer provides a simple and effective way to manage periodic tasks. Timers are checked for elapsed intervals without blocking, enabling efficient multitasking in the main loop.
-   **UART Command Pattern**: The UART receive function uses non-blocking polling to avoid stalling other tasks while waiting for input.
-   **Button Debouncing**: A basic debouncing technique is used, where the button state is checked every 100 ms.

This example demonstrates foundational skills for STM32 development, such as using UART communication for device control, implementing GPIO-based inputs and outputs, and managing timing with the system tick.Embedded Systems Examples

# Contributing

Feel free to contribute by submitting pull requests, reporting issues, or suggesting new examples!

- Fork the repository
- Create your feature branch (`git checkout -b feature/YourFeature`)
- Commit your changes (`git commit -m 'Add new feature'`)
- Push to the branch (`git push origin feature/YourFeature`)
- Open a pull request


# License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

*** 

Let me know if you need more examples or additional sections in this README!
