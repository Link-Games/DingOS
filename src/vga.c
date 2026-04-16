#include "types.h"
#include "cursor.h"
#include "vga.h"

#define VIDEO_ADDRESS 0xb8000
#define NEW_LINE_HEX 0xA0

uint16_t offset[] = {0,0};
uint16_t colour = 0x0f;

void crlf();
void scroll_screen();

void print_char(uint8_t charToPrint)
{
    if (charToPrint == '\n') {
        crlf();
        return;
    }
    if (offset[0] > 79) {
        offset[0] = 0;
        offset[1]++;
    }
    if (offset[1] > 24) {
        scroll_screen();
        offset[1] = 24;
    }
    int8_t* vmp = (char*) VIDEO_ADDRESS + offset[0] * 2 + offset[1] * 160;
    *vmp++ = charToPrint;
    *vmp = colour;
    ++offset[0];
    setcursor(offset[1], offset[0]);
}

void printf(uint8_t strtoPrint[])
{
    for(uint16_t i = 0; strtoPrint[i] != 0; i++){
        print_char(strtoPrint[i]);
    }
}

void crlf()
{
    offset[0] = 0;
    offset[1]++;
}

void clearscreen(){
    int8_t* vmp = (char*) VIDEO_ADDRESS;
    for(uint16_t i = 0; i < 80 * 25; i++){
        *vmp++ = ' ';
        *vmp++ = colour;
    }
    offset[0] = 0;
    offset[1] = 0;
    setcursor(0, 0);
}

void set_offset(uint16_t x, uint16_t y){
    offset[0] = x;
    offset[1] = y;
}

void set_colour(uint16_t color){
    colour = color;
}


void scroll_screen() {
    char* vmp = (char*) VIDEO_ADDRESS;
    // Copy each line up
    for (int row = 1; row < 25; row++) {
        for (int col = 0; col < 80; col++) {
            int from = row * 160 + col * 2;
            int to = (row - 1) * 160 + col * 2;
            vmp[to] = vmp[from];
            vmp[to + 1] = vmp[from + 1];
        }
    }
    // Clear the last line
    for (int col = 0; col < 80; col++) {
        int pos = 24 * 160 + col * 2;
        vmp[pos] = ' ';
        vmp[pos + 1] = colour;
    }
}
