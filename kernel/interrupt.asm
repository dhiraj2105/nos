; FILE: interrupt.asm
; ABOUT: Assembly ISR/IRQ stubs and IDT loader for Phase 3
; NOTES: Calls C functions defined in isr.c

[BITS 32]
[GLOBAL idt_load]
[GLOBAL isr_stub_table]

SECTION .text

idt_load:
    mov eax, [esp+4]
    lidt [eax]
    ret

isr_stub_table:
%assign i 0
%rep 256
    extern isr_handler
    isr_stub_%+i:
        push dword i
        jmp isr_common_stub
    dd isr_stub_%+i
%assign i i+1
%endrep

isr_common_stub:
    pusha
    call isr_handler
    popa
    add esp, 4
    iret
