#ifndef STRING_H
#define STRING_H

#include "stdint.h"

void strrev(char *s, uint8_t len);
uint8_t strlen(const char *buf);
char to_upper(char c);
void to_uppercase_str(char *s);

#endif