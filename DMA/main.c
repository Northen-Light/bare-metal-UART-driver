#include "uart.h"
#include "io.h"

void app(const char *s);

int main(void) {
  usart1_init();
  set_usart1_idle_callback(app);
  while(1);
}

void app(const char *s) {
  printstr(s);
  printstr("\r\n");
}
