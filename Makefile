# Cross-compiler
CC := i686-linux-gnu-gcc
LD := i686-linux-gnu-ld
AS := nasm

# Flags
CFLAGS := -std=gnu99 -ffreestanding -O2 -Wall -Wextra
LDFLAGS := -T linker.ld -nostdlib
ASFLAGS := -f elf32

# Sources and Objects
SRC := kernel/kernel.c
OBJ := $(SRC:.c=.o)
BOOT_OBJ := boot.o

all: kernel.bin

boot.o: boot/boot.asm
	$(AS) $(ASFLAGS) $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

kernel.bin: $(BOOT_OBJ) $(OBJ)
	$(LD) $(LDFLAGS) -o $@ $^

clean:
	rm -f *.o kernel/*.o boot.o kernel.bin
