#include <stdio.h>
#include <string.h>

unsigned get_exp(float num) {
    const int sign_bits = 1;
    const int mant_bits = 23;
    unsigned exp;
    memcpy(&exp, &num, sizeof(num));

    return exp << sign_bits >> (sign_bits + mant_bits);
}

unsigned get_mant(float num) {
    const int sign_bits = 1;
    const int exp_bits = 8;
    unsigned mant;
    memcpy(&mant, &num, sizeof(num));
    int to_remove = sign_bits + exp_bits;

    return mant << (to_remove) >> to_remove;
}


unsigned get_sign(float num) {
    const int sign_bits = 1;
    const int all_bits = 32;
    unsigned sign;
    memcpy(&sign, &num, sizeof(num));

    return sign >> (all_bits - sign_bits);
}


int main(int argc, char *argv[]) {
    float number;
    int res;
    while ((res = scanf("%f", &number)) == 1) {
        printf("%u %u %x\n", get_sign(number), get_exp(number), get_mant(number));
    }
    if (res != EOF) {
        return 1;
    }
}