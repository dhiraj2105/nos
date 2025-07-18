/*
 * FILE: console.h
 * ABOUT: Console (screen) text output functions for VGA text buffer
 * FEATURES: Low-level screen output API (kputchar, kprint, kprintf)
 * CHANGES: Added in Phase 2
 */

#ifndef CONSOLE_H
#define CONSOLE_H

#include <stdint.h>

void kputchar(char c);              // Print one character
void kprint(const char *str);       // Print a string
void kprintf(const char *fmt, ...); // Print formatted text

#endif
