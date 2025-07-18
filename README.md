# MyOS — A Minimal 32-bit Operating System

---

## 📦 About

**MyOS** is a small, fast, Linux-inspired hobby operating system written in **C** and **x86 Assembly**, targeting **32-bit x86 (i386)** architecture. It's designed to teach core OS concepts like bootloading, memory layout, interrupts, and console I/O — all from scratch.

This project is not a Linux distribution or kernel clone — it is a minimalist system that boots from GRUB and executes a kernel written in C. It's meant for educational purposes and for exploring how OSes really work under the hood.

---

## ✅ Current Features (as of Phase 2)

- ✅ GRUB-compatible Multiboot kernel
- ✅ Bootloader written in NASM
- ✅ Compiled using cross-compiler (`i686-linux-gnu-gcc`)
- ✅ Prints to screen via direct VGA text buffer (0xB8000)
- ✅ `kputchar()`, `kprint()`, and `kprintf()` for low-level console output

---

## 🚧 Roadmap (Phase-wise)

| Phase | Feature                                    | Status  |
| ----- | ------------------------------------------ | ------- |
| 0     | Toolchain & theory                         | ✅ Done |
| 1     | Bootloader + Kernel stub                   | ✅ Done |
| 2     | Console system, basic VGA text output      | ✅ Done |
| 3     | IDT setup, timer interrupt, keyboard input | 🔜 Next |
| 4     | Memory manager + malloc()                  | ⏳      |
| 5     | Process/task manager                       | ⏳      |
| 6     | Simple filesystem (FAT12 or EXT2)          | ⏳      |
| 7     | Shell and userland                         | ⏳      |
| 8     | Packaging + USB bootable                   | ⏳      |

---

## 🔧 Build Instructions

### 🛠 Prerequisites (Ubuntu/Debian):

```bash
sudo apt install gcc-i686-linux-gnu binutils-i686-linux-gnu \
                 grub-common xorriso nasm make
```

## 🧱 Build and Run

```
make clean
make # Builds the kernel
make iso # Generates GRUB bootable myos.iso
```

## 🧪 Test using QEMU (optional)

```
qemu-system-i386 -cdrom myos.iso
Or test with GNOME Boxes, VirtualBox, or write ISO to USB.
```
