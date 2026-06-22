#ifndef UART_H
#define UART_H

#include "stdint.h"

typedef enum {
  USART1_READ_OK = 0,
  USART1_READ_EMPTY
} usart1_read_char_t;

void usart1_init(void);
void usart1_write_char(char c);
void USART1_IRQHandler(void);
usart1_read_char_t usart1_read_char(char *ch);

#endif