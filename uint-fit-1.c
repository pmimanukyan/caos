#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

enum { MANTISSA = 23 };

int fits_into_float(uint32_t number) {
    if (number) {
        while ((number & 1) == 0) {
            number >>= 1;
        }
    }
    return !(number >> (1 + MANTISSA));
}

int main() {
    uint32_t number;
    int res;
    while ((res = scanf("%"SCNu32"\n", &number)) == 1) {
        printf("%d\n", fits_into_float(number));
    }
    if (res != EOF) {
        return 1;
    }
}