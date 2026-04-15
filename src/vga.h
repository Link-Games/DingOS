#ifndef VGA_H
#define VGA_H

#include "types.h"

void print_char(uint8_t charToPrint);

void printf(uint8_t strtoPrint[]);

void crlf();

void clearscreen();

void set_offset(uint16_t x, uint16_t y);

void set_colour(uint16_t color);

void scroll_screen();

#endif //VGA_H
