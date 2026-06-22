#include "uart.h"
#include "stdint.h"
#include "string.h"
#include "ringbuffer.h"
#include "io.h"

#define BUFFER_SIZE 128

static char buf[BUFFER_SIZE];
static uint8_t idx = 0;
static uint8_t bfull = 0;


int main(void) {
  usart1_init();
  ringbuffer_init();

  while(1) {
    if (ringbuffer_available()) {
      char ch;
      ringbuffer_get(&ch);
      if (!bfull) usart1_write_char(ch);

      if (ch == '\r') {
        buf[idx] = '\0';
        idx = 0;

        printstr("\r\n");

        if (bfull) {
          bfull = 0;
          printstr("\r\n");
          return 0;
        }

        printstr("str : ");
        printstr(buf);
        printstr("\r\n");

        to_uppercase_str(buf);
        printstr("upper case str : ");
        printstr(buf);
        printstr("\r\n");

        uint8_t len = strlen(buf);

        printstr("length of str : ");
        printnumber(len);
        printstr("\r\n");

        strrev(buf, len);
        printstr("reverse str : ");
        printstr(buf);
        printstr("\r\n");
        printstr("\r\n");

      } else {
        if (idx < BUFFER_SIZE - 1) {
          buf[idx++] = ch;
        } else {
          bfull = 1;
          printstr("\r\nBuffer full. Enter to continue...");
        }
      }
    }
  }
  
  return 0;
}
