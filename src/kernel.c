#include <stdbool.h>

#include "types.h"
#include "serial.h"
#include "port.h"

void kernel() {
    initserial(COM1);
    serialwritechar(COM1, 'P');
}

__attribute__((section(".text._start")))
void _start() {
    kernel();
    for(;;) {}
}
