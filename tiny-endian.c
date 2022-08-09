#include <stdio.h>
#include <stdint.h>

int getBit(unsigned char byte, int position) // position in range 0-7
{
    return (byte >> position) & 0x1;
}
void tinyconv(uint8_t bytes[], size_t size) {
    for (int i = 0; i < size; ++i) {
        uint8_t sum = 0;
        for (uint8_t j = 0; j < 8; ++j) {
            sum += getBit(bytes[i], j) * (1 << (8 - j - 1));
        }
        bytes[i] = sum;
    }
}
//int main () {
//    unsigned char b = 0x04;
//    printf("%d", getBit(b, 0));
//    printf("%d", getBit(b, 1));
//    printf("%d", getBit(b, 2));
//    printf("%d", getBit(b, 3));
//    printf("%d", getBit(b, 4));
//    printf("%d", getBit(b, 5));
//    printf("%d", getBit(b, 6));
//    printf("%d\n", getBit(b, 7));
//    unsigned char sum = 0;
//    for (int i = 0; i < 8; ++i) {
//        sum += getBit(b, i) * (1 << (8 - i - 1));
//    }
//    printf("%d", sum);
//}