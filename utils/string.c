#include "string.h"

void strrev(char *s, uint8_t len) {
  if (len == 0) return;
  uint8_t st = 0, end = len - 1;

  while (st < end) {
    char tmp = s[st];
    s[st] = s[end];
    s[end] = tmp;
    st++;
    end--;
  }
}

uint8_t strlen(const char *buf) {
  uint8_t len = 0;
  while(*buf++) len++;
  return len;
}

char to_upper(char c) {
  return (c >= 'a' && c <= 'z') ? c - ('a' - 'A') : c;
}

void to_uppercase_str(char *s) {
  while(*s) {
    *s = to_upper(*s);
    s++;
  }
}