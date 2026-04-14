#include "types.h"

int strlen(uint8_t str[]) {
    uint16_t i = 0;
    while (str[i] != '\0') ++i;
    return i;
}
