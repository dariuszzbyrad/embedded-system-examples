UART, GPIO, and System Tick Example for STM32
=============================================

This example demonstrates the use of UART communication, GPIO pin configuration, and System Tick timing on an STM32 microcontroller. It allows control of an LED using both UART commands and a button, while also periodically reporting the LED's status over UART.

Hardware Requirements
---------------------

-   **Microcontroller**: STM32F4 series
-   **LED Pin**: PA5 configured as an output (connected to an onboard or external LED)
-   **Button Pin**: PC13 configured as an input with a pull-up resistor (connected to an onboard or external button)
-   **UART Pins**: PA2 for Tx (Transmit) and PA3 for Rx (Receive)

Overview
--------

In this example:

1.  **GPIO**: Initializes PA5 as an output pin to control an LED and PC13 as an input pin for button state detection.
2.  **UART**: Configures UART2 for communication at 9600 baud rate, 8 data bits, no parity, and 1 stop bit (8N1).
3.  **System Tick**: Sets up a system tick timer to keep track of time in milliseconds, providing a simple mechanism for software timing.

The example enables the following functionality:

-   **UART LED Control**: The LED can be controlled via UART commands:
    -   Sending `'1'` over UART turns the LED on.
    -   Sending `'0'` over UART turns the LED off.
-   **UART Status Reporting**: Every 2 seconds, the microcontroller sends the current LED status (`*` for on, `.` for off) via UART.
-   **Button LED Toggle**: Pressing the button toggles the LED state.

Code Structure
--------------

The project includes the following main functions:

-   **GPIO Configuration**:

    -   `config_PA5()`: Configures PA5 as an output pin for LED control.
    -   `config_PC13()`: Configures PC13 as an input pin with a pull-up resistor for button detection.
-   **UART Configuration and Communication**:

    -   `UART2_Config()`: Configures UART2 for 9600 baud communication and sets up PA2 and PA3 as Tx and Rx pins.
    -   `UART2_SendChar()`: Sends a single character over UART.
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

How to Use
----------

1.  Connect the LED to PA5 and the button to PC13 on your STM32 development board.
2.  Open a UART terminal on your computer at 9600 baud, 8N1, and connect to the STM32's UART2 interface.
3.  Compile and upload the code to the STM32 microcontroller.
4.  Use the following commands over UART:
    -   Send `'1'` to turn the LED on.
    -   Send `'0'` to turn the LED off.
5.  Press the button connected to PC13 to toggle the LED state.
6.  Observe the LED status messages (`*` for on, `.` for off) sent every 2 seconds in the UART terminal.

Notes
-----

-   **System Tick Timing**: The System Tick timer provides a simple and effective way to manage periodic tasks. Timers are checked for elapsed intervals without blocking, enabling efficient multitasking in the main loop.
-   **UART Command Pattern**: The UART receive function uses non-blocking polling to avoid stalling other tasks while waiting for input.
-   **Button Debouncing**: A basic debouncing technique is used, where the button state is checked every 100 ms.

This example demonstrates foundational skills for STM32 development, such as using UART communication for device control, implementing GPIO-based inputs and outputs, and managing timing with the system tick.