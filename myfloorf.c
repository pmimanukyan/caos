#include <stdio.h>
#include <string.h>

enum {
    SIGN_BITS = 1,
    MANT_BITS = 23,
    EXP_BITS = 8,
    BIAS = 127
};

unsigned get_exp(float num) {
    unsigned exp;
    memcpy(&exp, &num, sizeof(num));

    return exp << SIGN_BITS >> (SIGN_BITS + MANT_BITS);
}

unsigned get_mant(float num) {
    unsigned mant;
    memcpy(&mant, &num, sizeof(num));
    int to_remove = SIGN_BITS + EXP_BITS;

    return mant << (to_remove) >> to_remove;
}

void myfloorf(float *arg) {
    unsigned *uptr_arg = (unsigned *)arg;
    unsigned mant = get_mant(*arg);
    unsigned exp = get_exp(*arg);

    if (exp < BIAS) {
        *arg = 0;
        return;
    }
    exp -= BIAS;
    for (int n = MANT_BITS - exp - 1; n >= 0; --n) {
        mant &= ~(1UL << n); // https://stackoverflow.com/questions/47981/how-do-you-set-clear-and-toggle-a-single-bit
    }
    *uptr_arg = mant + ((exp + BIAS) << MANT_BITS);
}