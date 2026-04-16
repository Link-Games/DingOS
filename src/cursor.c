#include "port.h"
#include "types.h"

// VGA ports
#define VGA_PORT_INDEX 0x3D4
#define VGA_PORT_DATA  0x3D5

// VGA Text Mode Screen Dimensions
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25

void set_cursor(int x, int y){
	uint16_t position = (y * SCREEN_WIDTH) + x;
	outb(VGA_PORT_INDEX, 0x0E);
	outb(VGA_PORT_DATA, (uint8_t)(position >> 8));
	outb(VGA_PORT_INDEX, 0x0F);
	outb(VGA_PORT_DATA, (uint8_t)(position & 0xFF));
}
