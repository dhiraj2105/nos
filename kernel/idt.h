/*
 * FILE: idt.h
 * ABOUT: Defines the Interrupt Descriptor Table (IDT) and setup functions
 * PHASE: 3 - Added in Phase 3 for interrupt handling
 */

#ifndef IDT_H
#define IDT_H

#include <stdint.h>

void idt_init();

#endif
