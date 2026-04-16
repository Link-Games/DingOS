#include <stdbool.h>

#include "types.h"
#include "serial.h"
#include "port.h"

void kernel() {
    initserial(COM1);
    serialwritechar(COM1, 'P');
}

void _start() {
    kernel();
    for(;;) {}
}
