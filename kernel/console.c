/*
 * FILE: console.c
 * ABOUT: Low-level VGA text output for printing debug/logs
 * FEATURES: Prints characters and strings to 0xB8000 video memory
 * BUGS: No scrolling or cursor handling yet
 * CHANGES: Initial version with kputchar, kprint, and basic kprintf
 */

#include "console.h"
#include <stdarg.h> // For variable argument list
#include <stdbool.h>

#define VGA_ADDRESS 0xB8000 // Start of video memory
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

static uint16_t *video_memory = (uint16_t *)VGA_ADDRESS;
static uint8_t cursor_x = 0;
static uint8_t cursor_y = 0;

// Writes a character to screen with default attribute (light gray on black)
void kputchar(char c)
{
    if (c == '\n')
    {
        cursor_x = 0;
        cursor_y++;
    }
    else
    {
        uint16_t pos = cursor_y * VGA_WIDTH + cursor_x;
        video_memory[pos] = ((uint8_t)0x07 << 8) | c; // 0x07 = light gray
        cursor_x++;
        if (cursor_x >= VGA_WIDTH)
        {
            cursor_x = 0;
            cursor_y++;
        }
    }

    // Reset to top if screen is full (no scrolling yet)
    if (cursor_y >= VGA_HEIGHT)
    {
        cursor_x = 0;
        cursor_y = 0;
    }
}

// Print a null-terminated string
void kprint(const char *str)
{
    while (*str)
        kputchar(*str++);
}

// Basic printf-style output (supports %s and %d)
void kprintf(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    for (const char *p = fmt; *p != '\0'; p++)
    {
        if (*p == '%' && *(p + 1))
        {
            p++;
            if (*p == 's')
            {
                char *val = va_arg(args, char *);
                kprint(val);
            }
            else if (*p == 'd')
            {
                int num = va_arg(args, int);
                char buf[32];
                int i = 30;
                buf[31] = '\0';
                if (num == 0)
                {
                    kputchar('0');
                    continue;
                }
                bool neg = false;
                if (num < 0)
                {
                    neg = true;
                    num = -num;
                }
                while (num > 0 && i)
                {
                    buf[i--] = '0' + (num % 10);
                    num /= 10;
                }
                if (neg)
                    buf[i--] = '-';
                kprint(&buf[i + 1]);
            }
            else
            {
                kputchar('%');
                kputchar(*p);
            }
        }
        else
        {
            kputchar(*p);
        }
    }

    va_end(args);
}
