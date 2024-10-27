ADC with DMA Example for STM32
==============================

This example demonstrates how to use Analog-to-Digital Conversion (ADC) with Direct Memory Access (DMA) on an STM32 microcontroller. The example reads analog values from GPIO pins PA1 and PA4, converts them to digital values via the ADC, and stores them directly into memory using DMA. This setup enables efficient, low-overhead data acquisition, suitable for applications requiring real-time data collection without CPU intervention.

Hardware Requirements
---------------------

-   **Microcontroller**: STM32F4 series
-   **Input Pins**: PA1 and PA4 configured as analog inputs
-   **ADC Channels**: Channel 1 for PA1 and Channel 4 for PA4

Overview
--------

In this example:

1.  **GPIO** is initialized to set up PA1 and PA4 as analog input pins.
2.  **ADC** is configured in scan mode to read multiple channels in sequence, set up for continuous conversions, and with DMA enabled to transfer results directly to memory.
3.  **DMA** is set up to handle transfers from the ADC data register to an array in memory, allowing automated data collection with minimal CPU load.

The converted data from the ADC is stored in an array, `adc_values`, where:

-   `adc_values[0]` holds the digital value for PA1.
-   `adc_values[1]` holds the digital value for PA4.

Code Structure
--------------

The project includes the following main functions:

-   **GPIO_Init()**: Initializes GPIOA with pins PA1 and PA4 as analog inputs.
-   **ADC_Init()**: Configures the ADC for 12-bit resolution, continuous conversion, and enables scan mode and DMA.
-   **ADC_Enable()**: Enables ADC1 with a short delay for stabilization.
-   **ADC_Start()**: Starts the ADC conversion process.
-   **DMA_Init()**: Initializes DMA2 Stream 0 to transfer data from ADC1 to memory.
-   **DMA_Config()**: Configures DMA for peripheral-to-memory data direction, circular mode, and enables the stream.

How to Use
----------

1.  Connect an analog signal to pins PA1 and PA4 on your STM32 development board.
2.  Compile and upload the code to the STM32 microcontroller.
3.  Monitor the values in the `adc_values` array to observe the converted digital values from PA1 and PA4.

Notes
-----

-   **Delay after ADC enable**: The delay in `ADC_Enable()` ensures the ADC stabilizes after being enabled.
-   **Circular DMA Mode**: Using circular mode for DMA allows continuous data transfer to memory without reconfiguring DMA after each transfer cycle.
