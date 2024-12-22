# Reaction-Time-Game-Project
Embedded project (Reaction Time Game) By using the microcontroller TM4C123GH6PM:
This project aims to design a game using the TM4C123GH6PM microcontroller where players respond to randomly lit LEDs by pressing corresponding switches, with reaction times displayed on an LCD. An ADC slider is used to specify the difficulty of the game. A light sensor is used to turn the game on and off, and UART is used to transmit game statistics to a PC.

The TM4C123G is a member of the class of high performance 32 bit ARM cortex M4 microcontroller with a broad set of peripherals developed by Texas Instrumentals. The TIVA launchpad has a built-in processor clock frequency of up to 80MHz with a floating-point unit (FPU). The Cortex-M4F processor also supports the tail chaining functionality. It also includes a nested vector interrupt controller (NVIC). The debugging interface used is JTAG and SWD (serial wire debugger) for programming and debugging purposes.

![Tiva C tutorials | Embedded Lab](./assets/2.png)
<img src="./assets/9.png" alt="EK-TM4C123GXL_2" />

Without GPIOs we won’t have any other way to use a microcontroller and it will be nothing more different than a chunk of well-fabricated silicon. Through them we can interface both transducers or sensors and actuators. We can also connect other devices like a display, external devices and so on.The GPIOs of TM4C123 Tiva C ARM microcontrollers are very elaborate, having many options that are usually unavailable in common 8-bit microcontrollers and below we are providing a diagram for more ease in understanding it.

![img](./assets/TM4C123GH6PM.png) 
<img src="./assets/1.png" style="zoom: 70%;"/>

## Software Specifications

The project code consists of drivers files for GPIO, LCD, UART, Timers, Interrupts, and handlers for the game functionality.


Supervised by: 
Dr: Lamiaa El-refaey
Eng: Mahmoud Nawar
