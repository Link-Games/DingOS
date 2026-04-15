#include <stdbool.h>

#include "types.h"
#include "serial.h"
#include "port.h"
#include "vga.h"

#define TEXT_COLOR 0b00001111

void kernel() {
    initserial(COM1);
    serialwritechar(COM1, 'P');
    set_colour(TEXT_COLOR);
    print_char('P');
}

void _start() {
    kernel();
    for(;;) {}
}
