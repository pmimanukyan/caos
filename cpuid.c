#include <stdio.h>

enum {
    SIZE = 32,
    MODEL_ID_SIZE = 4,
    FAMILY_ID_SIZE = 4,
    EXTENDED_MODEL_ID_SIZE = 4,
    EXTENDED_FAMILY_ID_SIZE = 8,
    MODEL_ID_START_POS = 7,
    FAMILY_ID_START_POS = 11,
    EXTENDED_MODEL_ID_START_POS = 19,
    EXTENDED_FAMILY_ID_START_POS = 27
};
unsigned get_id(unsigned x, unsigned size, unsigned start, unsigned id_size) {
    return x << (size - start) >> (size - id_size + 1);
}
int main() {
    unsigned x, y, z;
    asm volatile("cpuid\n\t"
    : "=a"(x), "=c"(y), "=d"(z)
    : "a" (1)
    : "%ebx");

    unsigned Extended_Model_ID, Extended_Family_ID;
    unsigned Model_ID, Family_ID;

    Extended_Model_ID = get_id(x, SIZE, EXTENDED_MODEL_ID_START_POS, EXTENDED_MODEL_ID_SIZE);
    Extended_Family_ID = get_id(x, SIZE, EXTENDED_FAMILY_ID_START_POS, EXTENDED_FAMILY_ID_SIZE);

    Model_ID = get_id(x, SIZE, MODEL_ID_START_POS, MODEL_ID_SIZE);
    Family_ID = get_id(x, SIZE, FAMILY_ID_START_POS, FAMILY_ID_SIZE);

    unsigned res_Model_ID, res_Family_ID;
    if (!(Family_ID == 6 || Family_ID == 15)) {
        res_Model_ID = Model_ID;
    } else {
        res_Model_ID = (Extended_Model_ID << 4) + Model_ID;
    }

    if (Family_ID == 15) {
        res_Family_ID = Family_ID + Extended_Family_ID;
    } else {
        res_Family_ID = Family_ID;
    }
    printf("family=%d model=%d ecx=0x%x edx=0x%x\n", res_Family_ID, res_Model_ID, y, z);
}