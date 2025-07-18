# === Cross-compiler tools ===
CC := i686-linux-gnu-gcc
LD := i686-linux-gnu-ld
AS := nasm

# === Build flags ===
CFLAGS := -std=gnu99 -ffreestanding -O2 -Wall -Wextra
LDFLAGS := -T linker.ld -nostdlib
ASFLAGS := -f elf32

# === Paths ===
KERNEL_SRC := kernel/kernel.c kernel/console.c
KERNEL_OBJ := $(SRC:.c=.o)
BOOT_OBJ := boot.o

# === Targets ===

all: myos.iso

# Assemble bootloader with multiboot header
$(BOOT_OBJ): boot/boot.asm
	$(AS) $(ASFLAGS) $< -o $@

# Compile C kernel
$(KERNEL_OBJ): $(KERNEL_SRC)
	$(CC) $(CFLAGS) -c $< -o $@

# Link to form the kernel ELF binary
kernel.bin: $(BOOT_OBJ) $(KERNEL_OBJ)
	$(LD) $(LDFLAGS) -o $@ $^

# Create GRUB bootable ISO image
myos.iso: kernel.bin
	mkdir -p isodir/boot/grub
	cp kernel.bin isodir/boot/kernel.bin
	echo 'set timeout=0\nset default=0\nmenuentry "MyOS" {\nmultiboot /boot/kernel.bin\nboot\n}' > isodir/boot/grub/grub.cfg
	grub-mkrescue -o myos.iso isodir

# === Cleanup ===

clean:
	rm -f *.o $(KERNEL_OBJ) kernel.bin

cleanall: clean
	rm -rf isodir myos.iso
