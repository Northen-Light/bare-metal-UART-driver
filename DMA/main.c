#include "uart.h"
#include "stdint.h"
#include "string.h"
#include "io.h"

#define BUFFER_SIZE 128

static char buf[BUFFER_SIZE];
static uint8_t idx = 0;
static uint8_t bfull = 0;

int main(void) {
  usart1_init();
  while(1) {
    char ch = 0;
    if (usart1_read_char(&ch) == READ_CHAR_OK) {
      if (!bfull) usart1_write_char(ch);
      if (ch == '\r') {
        buf[idx] = '\0';
        idx = 0;

        printstr("\r\n");

        if (bfull) {
          bfull = 0;
          printstr("\r\n");
          continue;
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
}

/*  Note on execution speeds
CPU clocked 8MHz, time taken for an operation = 0.125 us

Based on baud rate of 115200 with 8N1 frame, each character
takes 10bits, so effectively 11520 bytes/sec.

For DMA to wrap around the buffer it will take 16 / 11520 = 1388us
For average time between 2 consecutive writes is 1388 us / 16 = 87us

DMA copy speed (less than 1us) is neglible compared to 87 us
*/
