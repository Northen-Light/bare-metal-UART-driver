#include "uart.h"
#include "stdint.h"
#include "mmap-regs.h"

#define DMA_BUFFER_SIZE 0x10

static volatile char dma_buffer[DMA_BUFFER_SIZE];
static uint8_t read_pos = 0;

void usart1_init(void) {
  RCC_APB2ENR |= (1 << 2);
  RCC_AHBENR |= (1 << 0);
  RCC_APB2ENR |= (1 << 14);

  GPIOA_CRH &= ~(0xF << 4);
  GPIOA_CRH |= (0xA << 4);

  GPIOA_CRH &= ~(0xF << 8);
  GPIOA_CRH |= (0x8 << 8);
  GPIOA_ODR |= (1 << 10);

  DMA1_CCR5 = 0;
  DMA1_CNDTR5 = DMA_BUFFER_SIZE;
  DMA1_CPAR5 = (volatile unsigned int)&USART1_DR;
  DMA1_CMAR5 = (volatile unsigned int)&dma_buffer[0];
  DMA1_CCR5 &= ~(1 << 4);
  DMA1_CCR5 |= (1 << 5);
  DMA1_CCR5 &= ~(1 << 6);
  DMA1_CCR5 |= (1 << 7);
  DMA1_CCR5 |= (1 << 0);

  USART1_CR1 = 0;
  // For STM32F103 @ 8 MHz, 115200 baud
  // USARTDIV = 8000000 / (16 × 115200)
  //          = 4.3403
  USART1_BRR = (4 << 4) | 5;
  USART1_CR1 |= (1 << 2);
  USART1_CR1 |= (1 << 3);
  USART1_CR3 |= (1 << 6);
  USART1_CR1 |= (1 << 13);
}

void usart1_write_char(char c) {
  while (!(USART1_SR & (1 << 7)));
  USART1_DR = c;
}

read_char_type_t usart1_read_char(char *ch) {
  uint32_t dma_write_pos = DMA_BUFFER_SIZE - DMA1_CNDTR5;

  if (dma_write_pos == read_pos) return READ_CHAR_EMPTY;

  *ch = dma_buffer[read_pos];
  read_pos = (read_pos + 1) & (DMA_BUFFER_SIZE - 1);

  return READ_CHAR_OK;
}