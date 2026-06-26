# Bare-Metal UART Advanced

A collection of bare-metal UART implementations for the STM32F103, written in C using direct register-level programming.

## Implementations

### 1. Interrupt + Ring Buffer

Location:

```text
interrupt-ringbuffer/
```

Features:

- USART1 interrupt-driven reception
- Software ring buffer
- Modular firmware architecture
- GNU Make build system

---

### 2. DMA + Circular Buffer

Location:

```text
DMA/
```

Features:

- DMA-based UART reception
- Circular DMA buffer
- Continuous reception without per-byte interrupts
- CPU-driven buffer consumption
- Modular firmware architecture
- GNU Make build system

---

## Hardware

- STM32F103C8T6 (Blue Pill)
- CP2102 USB-UART Adapter

## Toolchain

- arm-none-eabi-gcc
- GNU Make
- GDB
- ST-Link

## Learning Progression

```text
UART Polling
      ↓
UART Interrupts
      ↓
Interrupt + Ring Buffer
      ↓
DMA Normal Mode
      ↓
DMA Circular Mode
      ↓
CPU Consuming DMA Buffer
```

Each implementation is self-contained and includes its own README with architecture diagrams and implementation details.