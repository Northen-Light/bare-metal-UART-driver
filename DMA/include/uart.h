#ifndef UART_H
#define UART_H

typedef enum {
  READ_CHAR_OK = 0,
  READ_CHAR_EMPTY
} read_char_type_t;

void usart1_init(void);
void usart1_write_char(char c);
read_char_type_t usart1_read_char(char *ch);

#endif