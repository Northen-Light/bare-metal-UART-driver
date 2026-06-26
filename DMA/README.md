# STM32 UART Communication Stack (DMA + Circular Buffer)

A bare-metal UART communication stack for STM32F103 featuring DMA-based reception using a circular buffer and a modular firmware architecture.

## Features

- USART1 initialization
- DMA-based UART RX
- Circular DMA buffer
- Continuous reception without per-byte interrupts
- Modular firmware architecture
- GNU Make build system
- Tested on STM32F103C8T6 (Blue Pill) using a CP2102 USB-UART adapter

## Architecture

```text
                USART1 RX
                    │
                    ▼
          DMA1 Channel 5
                    │
                    ▼
      Circular DMA Buffer (16 Bytes)
                    │
                    ▼
        usart1_read_char()
                    │
                    ▼
          Application Logic
                    │
                    ▼
              UART Output
```

## How It Works

- USART1 receives incoming serial data.
- DMA1 Channel 5 automatically transfers each received byte from `USART1_DR` to a circular buffer in SRAM.
- The CPU derives the current DMA write position from `DMA1_CNDTR5`.
- `usart1_read_char()` consumes unread bytes using its own software read pointer.
- No UART RX interrupt is generated for each received byte.

## Project Structure

```text
include/
├── uart.h
├── string.h
├── io.h
└── mmap-regs.h

drivers/
└── uart.c

utils/
└── string.c

libs/
└── io.c

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

## Current Limitations

- DMA buffer overflow detection is not implemented.
- The application must consume received data before DMA overwrites unread bytes.
- Buffer size is fixed at 16 bytes for demonstration purposes.