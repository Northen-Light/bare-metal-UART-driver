CC						= arm-none-eabi-gcc
LD						= arm-none-eabi-ld
OBJCOPY				= arm-none-eabi-objcopy

CFLAGS				= -Iinclude -mthumb -mcpu=cortex-m3 -O0 -ggdb
LDFLAGS				= -Tmain.ld -Map=main.map 

SRCS					= \
								startup.c \
								main.c \
								drivers/uart.c \
								utils/string.c \
								utils/ringbuffer.c \
								libs/io.c

OBJS					= $(SRCS:.c=.o)

all: main.bin

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

main.elf: $(OBJS)
	$(LD) $(LDFLAGS) $^ -o $@

main.bin: main.elf
	$(OBJCOPY) -O binary $< $@

clean: 
	rm -rf $(OBJS) main.bin main.elf main.map

flash:
	st-flash write main.bin 0x08000000 

.PHONY: all clean flash