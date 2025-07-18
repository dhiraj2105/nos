/*
 * FILE: idt.c
 * ABOUT: Initializes the Interrupt Descriptor Table (The IDT is a table that tells the CPU how to handle different interrupts (software or hardware events).) and remaps PIC (The PIC handles hardware interrupts (like keyboard input, timers, etc.).)
 * FEATURES: 256 IDT entries, remaps IRQ0–IRQ15 to IDT 32–47
 */

#include "idt.h"
#include "kernel.h"
#include <string.h>

#define IDT_ENTRIES 256

struct idt_entry
{
    uint16_t base_low;
    uint16_t selector;
    uint8_t always0;
    uint8_t flags;
    uint16_t base_high;
} __attribute__((packed));

struct idt_ptr
{
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

extern void idt_load(uint32_t); // From interrupt.asm
extern void isr_stub_table();   // Array of ISR/IRQ function stubs

struct idt_entry idt[IDT_ENTRIES];
struct idt_ptr idt_reg;

// Sets one entry in IDT
void set_idt_entry(int num, uint32_t base, uint16_t sel, uint8_t flags)
{
    idt[num].base_low = base & 0xFFFF;
    idt[num].selector = sel;
    idt[num].always0 = 0;
    idt[num].flags = flags;
    idt[num].base_high = (base >> 16) & 0xFFFF;
}

// Remap IRQs to IDT 32–47
void remap_pic()
{
    outb(0x20, 0x11);
    outb(0xA0, 0x11);
    outb(0x21, 0x20);
    outb(0xA1, 0x28);
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    outb(0x21, 0x0);
    outb(0xA1, 0x0);
}

// Install IDT
void idt_init()
{
    remap_pic();
    for (int i = 0; i < 256; i++)
        set_idt_entry(i, ((uint32_t *)isr_stub_table)[i], 0x08, 0x8E);

    idt_reg.base = (uint32_t)&idt;
    idt_reg.limit = sizeof(struct idt_entry) * IDT_ENTRIES - 1;

    idt_load((uint32_t)&idt_reg);
}
