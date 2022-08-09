#include <stdint.h>

uint32_t satsum(uint32_t v1, uint32_t v2) {
    uint32_t sum;
    if (-1 - v2 < v1) {
        sum = -1;
    } else {
        sum = v1 + v2;
    }
    return sum;
}