/*
 * FILE: kernel.c
 * ABOUT: Main entry point for the kernel after bootloader
 * FEATURES: Prints initial messages using console system
 * CHANGES: Phase 2 - Uses kprintf() for better output
 */

#include "kernel.h"
#include "console.h"
#include "idt.h"
#include "timer.h"
#include "keyboard.h"

void kernel_main()
{
    kprint("NOS v0.1\n");
    kprintf("Welcome to DHRIAJ's NOS!\n");
    kprintf("Screen initialized at address: 0x%x\n", (uint32_t)0xB8000);

    idt_init();
    init_timer();
    init_keyboard();

    kprint("Interrupts enabled. Type to test keyboard.\n");

    while (1)
        ;
}
