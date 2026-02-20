#include <stdbool.h>

void kernel() {
    
}

void _start() {
    kernel();
    for(;;) {}
}