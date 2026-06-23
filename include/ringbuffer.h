#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include "stdint.h" 
#define RINGBUFFER_SIZE 128

typedef enum {
  RINGBUFFER_OK = 0,
  RINGBUFFER_FULL,
  RINGBUFFER_EMPTY
} ringbuffer_status_t;

void ringbuffer_init(void);
ringbuffer_status_t ringbuffer_put(char c);
ringbuffer_status_t ringbuffer_get(char *ch);

#endif