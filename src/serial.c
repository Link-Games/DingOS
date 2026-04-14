#include "types.h"
#include "string.h"
#include "port.h"
#include "serial.h"

int initserial(uint16_t port) {
   outb(port + 1, 0x00);    // Disable all interrupts
   outb(port + 3, 0x80);    // Enable DLAB (set baud rate divisor)
   outb(port + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
   outb(port + 1, 0x00);    //                  (hi byte)
   outb(port + 3, 0x03);    // 8 bits, no parity, one stop bit
   outb(port + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
   outb(port + 4, 0x0B);    // IRQs enabled, RTS/DSR set
   outb(port + 4, 0x1E);    // Set in loopback mode, test the serial chip
   outb(port + 0, 0xAE);    // Test serial chip (send byte 0xAE and check if serial returns same byte)

   // Check if serial is faulty (i.e: not same byte as sent)
   if(inb(port + 0) != 0xAE) {
      return 1;
   }

   // If serial is not faulty set it in normal operation mode
   // (not-loopback with IRQs enabled and OUT#1 and OUT#2 bits enabled)
   outb(port + 4, 0x0F);
   return 0;
}

int serialreceived(uint16_t port) {
   return inb(port + 5) & 1;
}

char serialread(uint16_t port) {
   while (serialreceived(port) == 0);

   return inb(port);
}

int checktransmit(uint16_t port) {
   return inb(port + 5) & 0x20;
}

void serialwritechar(uint16_t port, uint8_t c) {
   while (checktransmit(port) == 0);

   outb(port,c);
}

void serialwrite(uint16_t port, uint8_t strtoprint[]) {
   uint16_t len = strlen(strtoprint);
   for(uint16_t i = 0; i == len; i++) {
      serialwritechar(port, strtoprint[i]);
   }
}
