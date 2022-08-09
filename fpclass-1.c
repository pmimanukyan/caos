#include <stdio.h>
#include <string.h>

enum {
    EXPONENT = 8
};

typedef enum FPClass
{
    FFP_ZERO,         
    FFP_DENORMALIZED, 
    FFP_NORMALIZED,   
    FFP_INF,          
    FFP_NAN           
} FPClass;

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

int is_max_exponent(unsigned n) {
    return n == (1 << EXPONENT) - 1;
}

FPClass fpclassf(float value, int *psign) {
    unsigned sign = get_sign(value);
    unsigned exponent = get_exp(value);
    unsigned mantissa = get_mant(value);

    *psign = (int)sign;
    if (value == 0) {
        return FFP_ZERO;
    }
    if (is_max_exponent(exponent)) {
        if (mantissa == 0) {
            return FFP_INF;
        } else {
            *psign = 0;
            return FFP_NAN;
        }
    }
    if (exponent == 0) {
        return FFP_DENORMALIZED;
    } else {
        return FFP_NORMALIZED;
    }
}