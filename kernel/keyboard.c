// keyboard.c
#include "keyboard.h"
#include "isr.h"
#include "console.h"

static const char scancodes[128] = {
    0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0,
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0,
    '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,
    '*', 0, ' ', 0, // space = 57
};

static void keyboard_callback()
{
    uint8_t sc = inb(0x60);
    if (sc < 128 && scancodes[sc])
        kputchar(scancodes[sc]);
}

void init_keyboard()
{
    register_irq_handler(1, keyboard_callback);
}
