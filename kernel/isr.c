/*
 * FILE: isr.c
 * ABOUT: Generic interrupt handler + IRQ handler hooks
 * FEATURES: Handles both CPU exceptions and hardware IRQs
 */

#include "isr.h"
#include "console.h"
#include "keyboard.h"
#include "timer.h"

void *irq_handlers[16] = {0};

// Registers custom IRQ handler
void register_irq_handler(int irq, void (*handler)())
{
    irq_handlers[irq] = handler;
}

// Common ISR/IRQ handler
void isr_handler(int irq)
{
    if (irq >= 32 && irq <= 47)
    {
        int irq_num = irq - 32;
        if (irq_handlers[irq_num])
            ((void (*)())irq_handlers[irq_num])();

        // Send EOI (End of Interrupt)
        if (irq_num >= 8)
            outb(0xA0, 0x20);
        outb(0x20, 0x20);
    }
}
