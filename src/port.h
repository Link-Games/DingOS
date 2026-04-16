#ifndef PORT_H
#define PORT_H

#include "types.h"

enum ports {
    COM1 = 0x3F8,
    COM2 = 0x2F8,
    COM3 = 0x3E8,
    COM4 = 0x2E8,
    COM5 = 0x5F8,
    COM6 = 0x4F8,
    COM7 = 0x5E8,
    COM8 = 0x4E8,
};

//Output to port
//port: RANGE 0-65535; value: RANGE 0-255;
void outb(uint16_t port, uint8_t value);

//Read port
//port: RANGE 0-65535;
uint8_t inb(uint16_t port);

#endif //PORT_H

