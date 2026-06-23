# STM32 UART Communication Stack

A bare-metal UART communication stack for STM32F103 featuring interrupt-driven reception, ring-buffered data handling, and a modular architecture.

## Features

* USART1 initialization
* Interrupt-driven UART RX
* Ring buffer for asynchronous reception
* Modular architecture
* GNU Make build system
* Tested on STM32F103C8T6 (Blue Pill) using a CP2102 USB-UART adapter

## Architecture

```text
USART1 RX
    |
    v
USART1_IRQHandler()
    |
    v
ringbuffer_put()
    |
    v
Return from ISR

-----------------------

Main Loop
    |
    v
usart1_read_char()
    |
    v
ringbuffer_get()
    |
    v
Application Logic
    |
    v
UART Output
```

## Project Structure

```text
include/
├── uart.h
├── ringbuffer.h
├── string.h
├── io.h
└── mmap-regs.h

drivers/
└── uart.c

utils/
├── ringbuffer.c
├── string.c

libs/
├── io.c

main.c
startup.c
Makefile
```

## Build

```bash
make
```

## Clean

```bash
make clean
```

## Demo

Input:

```text
hello world
```

Output:

```text
str : hello world
upper case str : HELLO WORLD
length of str : 11
reverse str : DLROW OLLEH
```
