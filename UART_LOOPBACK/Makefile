CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
CFLAGS = -mcpu=cortex-m4 -mthumb -O0 -Wall -g -nostdlib -nostartfiles -T linker.ld

all: main.bin

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

startup.o: startup_stm32f401xe.s
	$(CC) $(CFLAGS) -c startup_stm32f401xe.s -o startup.o

main.elf: main.o startup.o
	$(CC) $(CFLAGS) main.o startup.o -o main.elf

main.bin: main.elf
	$(OBJCOPY) -O binary main.elf main.bin

flash: main.bin
	st-flash write main.bin 0x8000000

clean:
	rm -f *.o *.elf *.bin

