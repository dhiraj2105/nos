// timer.c
#include "timer.h"
#include "isr.h"
#include "console.h"

static int ticks = 0;

static void timer_callback()
{
    ticks++;
    kprintf("Tick: %d\n", ticks);
}

void init_timer()
{
    register_irq_handler(0, timer_callback);
    outb(0x43, 0x36);
    outb(0x40, 1193180 / 20); // 20Hz
    outb(0x40, 0);
}
