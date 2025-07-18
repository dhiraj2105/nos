# === Cross-compiler tools ===
CC := i686-linux-gnu-gcc
LD := i686-linux-gnu-ld
AS := nasm

# === Build flags ===
CFLAGS := -std=gnu99 -ffreestanding -O2 -Wall -Wextra
LDFLAGS := -T linker.ld -nostdlib
ASFLAGS := -f elf32

# === Source files ===
KERNEL_SRC := kernel/kernel.c \
              kernel/console.c \
              kernel/idt.c \
              kernel/isr.c \
              kernel/timer.c \
              kernel/keyboard.c

ASM_SRC := kernel/interrupt.asm
BOOT_SRC := boot/boot.asm

KERNEL_OBJ := $(KERNEL_SRC:.c=.o)
ASM_OBJ := $(ASM_SRC:.asm=.o)
BOOT_OBJ := $(BOOT_SRC:.asm=.o)

OBJ := $(BOOT_OBJ) $(KERNEL_OBJ) $(ASM_OBJ)

# === Targets ===

all: myos.iso

# Build .o from .c
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Build .o from .asm
%.o: %.asm
	$(AS) $(ASFLAGS) $< -o $@

# Link final kernel ELF binary
kernel.bin: $(OBJ)
	$(LD) $(LDFLAGS) -o $@ $^

# Build bootable ISO
myos.iso: kernel.bin
	mkdir -p isodir/boot/grub
	cp kernel.bin isodir/boot/kernel.bin
	echo 'set timeout=0\nset default=0\nmenuentry "NOS" {\nmultiboot /boot/kernel.bin\nboot\n}' > isodir/boot/grub/grub.cfg
	grub-mkrescue -o nos.iso isodir

# === Cleanup ===

clean:
	rm -f $(KERNEL_OBJ) $(ASM_OBJ) $(BOOT_OBJ) kernel.bin

cleanall: clean
	rm -rf isodir nos.iso
