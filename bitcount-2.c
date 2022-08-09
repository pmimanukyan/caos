typedef int STYPE;
typedef unsigned int UTYPE;

int bitcount(STYPE value){
    int k = 0;
    UTYPE u_value = value;
    while (u_value != 0) {
        k += 1 & u_value;
        u_value >>= 1;
    }
    return k;
}