# Embedded Systems Examples
Welcome to the **Embedded Systems Examples** repository! This repository contains a collection of code examples, tutorials, and snippets for working with embedded systems, including STM32 and Arduino projects. Each example focuses on different peripherals or functionalities, such as ADC (Analog-to-Digital Converters), GPIO (General Purpose Input/Output), UART (Universal Asynchronous Receiver-Transmitter), and more.

# About

This repository aims to provide useful examples and hands-on exercises for developers working with embedded systems. The code is written using register-level programming for STM32 microcontrollers and standard Arduino libraries.

Each folder contains a README specific to the example, detailing the project, the hardware setup, and instructions on how to compile and run the code.

# Projects

### 1\. ADC with DMA Example for STM32

This example demonstrates how to use the ADC with Direct Memory Access (DMA) on an STM32 microcontroller to read analog inputs on GPIO pins PA1 and PA4. The DMA transfers ADC values directly to memory, allowing for efficient, low-overhead data acquisition.

-   **File**: `projects/stm32/stm32f411-adc-dma`
-   **Main Features**:
    -   Configures PA1 and PA4 as analog inputs
    -   Sets up ADC for continuous conversion in scan mode
    -   Uses DMA to automatically transfer ADC values to memory
-   **Relevant Peripherals**: GPIO, ADC, DMA
-   **Target Microcontroller**: STM32F4 series

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
