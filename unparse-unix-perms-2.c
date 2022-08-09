#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int MIN(int a, int b) { return a > b ? b : a; }
enum {
    SIZE = 9,
    EXECUTE1 = 2,
    EXECUTE2 = 5,
    EXECUTE3 = 8,
};
const char *perms_to_str(char *buf, size_t size, int perms) {
    if (size == 0) {
        return buf;
    }
    size_t res_size = MIN(size - 1, SIZE);
    char str[SIZE] = "rwxrwxrwx";
    for (int i = 0; i < sizeof(str); ++i) {
        if (!(perms & (1 << i))) {
            str[sizeof(str) - i - 1] = '-';
        }
    }

    if (perms & S_ISUID) {
        if ((perms & S_IXOTH) || (perms & S_IXGRP)) {
            str[EXECUTE1] = 's';
        }
    }
    if (perms & S_ISGID) {
        if (perms & S_IXOTH) {
            str[EXECUTE2] = 's';
        }
    }
    if (perms & S_ISVTX) {
        if ((perms & S_IWOTH) && (perms & S_IXOTH)) {
            str[EXECUTE3] = 't';
        }
    }
    for (int i = 0; i < size - 1; ++i) {
        if (i >= SIZE) {
            break;
        }
        buf[i] = str[i];
    }

    *(buf + res_size) = '\0';
    return buf;
}