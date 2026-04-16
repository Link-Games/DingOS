#ifndef VGA_H
#define VGA_H

#include "types.h"

void print_char(char chartoPrint);

void printf(const char *strtoPrint);

void crlf();

void clear_screen();

void set_offset(uint16_t x, uint16_t y);

void set_colour(uint8_t color);

void scroll_screen();

#endif //VGA_H
