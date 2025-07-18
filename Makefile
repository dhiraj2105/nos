CFLAGS := -std=gnu99 -ffreestanding -O2 -Wall -Wextra
LDFLAGS := -T linker.ld -nostdlib

SRC := kernel/kernel.c
OBJ := $(SRC:.c=.o)

all: os.iso

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

boot.o: boot/boot.asm
	nasm -f elf $< -o $@

kernel.bin: boot.o $(OBJ)
	$(LD) $(LDFLAGS) -o $@ $^

os.iso: kernel.bin
	mkdir -p isodir/boot/grub
	cp kernel.bin isodir/boot/kernel.bin
	echo 'set timeout=0\nset default=0\nmenuentry "My OS" {\nmultiboot /boot/kernel.bin\nboot\n}' > isodir/boot/grub/grub.cfg
	grub-mkrescue -o os.iso isodir

clean:
	rm -rf *.o kernel.bin isodir os.iso
