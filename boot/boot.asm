section .multiboot
align 4
    dd 0x1BADB002
    dd 0
    dd -0x1BADB002

section .text
global _start
_start:
    extern kernel_main
    call kernel_main
    cli
    hlt
