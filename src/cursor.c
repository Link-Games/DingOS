#include "types.h"
#include "port.h"

// VGA ports
#define VGA_PORT_INDEX 0x3D4
#define VGA_PORT_DATA  0x3D5

// VGA Text Mode Screen Dimensions
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25

void setcursor(uint16_t x, uint16_t y){
    unsigned short position = (x * SCREEN_WIDTH) + y;
    outb(VGA_PORT_INDEX, 0x0E);
    outb(VGA_PORT_DATA, (unsigned char)(position >> 8));
    outb(VGA_PORT_INDEX, 0x0F);
    outb(VGA_PORT_DATA, (unsigned char)(position & 0xFF));
}
