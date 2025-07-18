; -------------------------------
; FILE: boot.asm
; DESC: Multiboot header and kernel entry point
; NOTE: Calls C kernel_main after GRUB loads the image
; LAST CHANGE: Phase 2 - cleaned for proper handoff
; -------------------------------

section .multiboot
align 4
    dd 0x1BADB002          ; magic number
    dd 0x0                 ; flags
    dd -0x1BADB002         ; checksum

section .text
global _start
_start:
    extern kernel_main     ; declare symbol from C
    call kernel_main       ; call into the C kernel
    cli                    ; disable interrupts
    hlt                    ; halt forever
