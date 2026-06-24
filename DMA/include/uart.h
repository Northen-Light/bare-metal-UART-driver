#ifndef UART_H
#define UART_H

typedef void (*usart1_idle_callback_t)(const char *s);

void usart1_init(void);
void usart1_write_char(char c);
void set_usart1_idle_callback(usart1_idle_callback_t cb);
void USART1_IRQHandler(void);

#endif