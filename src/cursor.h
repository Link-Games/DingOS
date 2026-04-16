#ifndef CURSOR_H
#define CURSOR_H

#include "types.h"

void set_cursor(uint16_t x, uint16_t y);

//Define cursor character
//cursor_start: scanline that cursor starts, RANGE 0-15; cursor_end: scanline that cursor starts, RANGE 0-15;
void enable_cursor(uint8_t cursor_start, uint8_t cursor_end);

//Disable cursor
//NULL
void disable_cursor();

#endif //CURSOR_H
