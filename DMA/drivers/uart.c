#include "uart.h"
#include "mmap-regs.h"
#include "stdint.h"

char dma_buffer[16];

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
  DMA1_CNDTR5 = 0x10;
  DMA1_CPAR5 = (volatile unsigned int)&USART1_DR;
  DMA1_CMAR5 = (volatile unsigned int)&dma_buffer[0];
  DMA1_CCR5 &= ~(1 << 4);
  DMA1_CCR5 &= ~(1 << 5);
  DMA1_CCR5 &= ~(1 << 6);
  DMA1_CCR5 |= (1 << 7);
  DMA1_CCR5 |= (1 << 1);
  DMA1_CCR5 |= (1 << 0);

  USART1_CR1 = 0;
  // For STM32F103 @ 8 MHz, 115200 baud
  // USARTDIV = 8000000 / (16 × 115200)
  //          = 4.3403
  USART1_BRR = (4 << 4) | 5;
  USART1_CR1 |= (1 << 2);
  USART1_CR1 |= (1 << 3);
  USART1_CR3 |= (1 << 6);
  NVIC_ISER0 |= (1 << 15);
  USART1_CR1 |= (1 << 13);
}

void usart1_write_char(char c) {
  while (!(USART1_SR & (1 << 7)));
  USART1_DR = c;
}

void DMA1_Channel5_IRQHandler() {}