#include "types.h"
#include "bool.h"
#include "serial.h"
#include "port.h"
#include "vga.h"
#include "cursor.h"

#define TEXT_COLOUR 0b00001010

void kernel() {
    initserial(COM1);
    serialwritechar(COM1, 'P');
    set_colour(TEXT_COLOUR);
    clear_screen();
    enable_cursor(0, 15);
    printf("Dingers\n");
    printf("pingas\n\n\n");
    printf("mougger");
}

__attribute__((section(".text._start")))
void _start() {
    kernel();
    for(;;) {}
}
