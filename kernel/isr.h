// isr.h
#ifndef ISR_H
#define ISR_H

void isr_handler(int irq);
void register_irq_handler(int irq, void (*handler)());

#endif
