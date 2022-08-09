#include <stdint.h>

int32_t satsum(int32_t v1, int32_t v2) {
    int result;
    if (__builtin_add_overflow(v1, v2, &result)) {
        uint32_t max = -1;
        if (result > 0) {
            max >>= 1;
            return -max - 1;
        } else {
            return max >> 1;
        }
    } else {
        return v1 + v2;
    }
}