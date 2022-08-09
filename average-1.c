#include <stdio.h>

int main() {
    unsigned int a;
    unsigned int b;
    if (scanf("%u%u", &a, &b) == 2) {
        printf("%u\n", a / 2 + b / 2 + (a % 2) * (b % 2));
    } else {
        return 1;
    }
    return 0;
}