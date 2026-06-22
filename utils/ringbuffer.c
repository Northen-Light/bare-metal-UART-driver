#include "ringbuffer.h"
#include "stdint.h"

static char buffer[BUFFER_SIZE];
static uint8_t head;
static uint8_t tail;
static uint8_t ringbuffer_full(void);
static uint8_t ringbuffer_empty(void);

void ringbuffer_init(void) {
  head = 0;
  tail = 0;
}

ringbuffer_status_t ringbuffer_put(char c) {
  if (ringbuffer_full()) return RINGBUFFER_FULL;
  buffer[head] = c;
  head = (head + 1) % BUFFER_SIZE;
  return RINGBUFFER_OK;
}

ringbuffer_status_t ringbuffer_get(char *ch) {
  if (ringbuffer_empty()) return RINGBUFFER_EMPTY;
  *ch = buffer[tail];
  tail = (tail + 1) % BUFFER_SIZE;
  return RINGBUFFER_OK;
}

uint8_t ringbuffer_available(void) {
  return !ringbuffer_empty();
}

static uint8_t ringbuffer_full(void) {
  return (head + 1) % BUFFER_SIZE == tail;
}

static uint8_t ringbuffer_empty(void) {
  return head == tail;
}