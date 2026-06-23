#include "uart.h"
#include "string.h"

void printstr (const char *s) {
  while (*s) {
    usart1_write_char(*s++);
  }
}

void printnumber(uint8_t num) {
  if (num == 0) {
    usart1_write_char('0');
    return;
  }

  char digits[3];
  uint8_t idx = 0, len;
  
  while (num) {
    digits[idx++] = num % 10 + '0';
    num /= 10;
  }

  digits[idx] = '\0';
  len = idx;
  strrev(digits, len);

  printstr(digits);
}