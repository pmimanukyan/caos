#include <stdbool.h>

void normalize_path(char *buf) {
    bool found_slash = false;
    char *buf_copy_ptr = buf;
    while (*buf_copy_ptr) {
        if (*buf_copy_ptr == '/') {
            found_slash = true;
        } else {
            if (found_slash) {
                *buf++ = '/';
                found_slash = false;
            }
            *buf++ = *buf_copy_ptr;
        }
        ++buf_copy_ptr;
    }
    if (found_slash) {
        *buf++ = '/';
    }
    *buf = 0;
}