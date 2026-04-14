#ifndef SERIAL_H
#define SERIAL_H

#include "types.h"

//Initialize serial port
//port: RANGE 0-65535, return: RANGE 0-1
int initserial(uint16_t port);

//Check if character is avaliable for read
//port: RANGE 0-65535, return: RANGE 0-1
int serialreceived(uint16_t port);

//Wait for character from serial port and read it
//port: RANGE 0-65535, return: RANGE 0-255
char serialread(uint16_t port);

//Check if transmit buffer is empty
//port: RANGE 0-65535, return: RANGE 0-1
int checktransmit(uint16_t port);

//Wait for empty transmit buffer, then send character
//port: RANGE 0-65535, c: RANGE 0-255
void serialwritechar(uint16_t port, uint8_t c);

//Wait for empty transmit buffer, then send string
//port: RANGE 0-65535, stringtoprint: RANGE 0-255
void serialwrite(uint16_t port, uint8_t strtoprint[]);

#endif //SERIAL_H
