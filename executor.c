#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <linux/limits.h>

int main() {
    int interactor_pid;
    if (read(STDIN_FILENO, &interactor_pid, sizeof(int)) < 0) {
        return 1;
    }

    char interactor_pid_str[100];
    sprintf(interactor_pid_str, "%d", interactor_pid);

    char path1[PATH_MAX];
    snprintf(path1, sizeof(path1), "/proc/%s/maps", interactor_pid_str);

    char *ptr1 = NULL;
    FILE *file1 = fopen(path1, "r");
    char *cur_part1 = NULL;
    char str[PATH_MAX + 1];
    while (fgets(str, sizeof(str), file1) != NULL) {
        char *first_subpart = strstr(str,  "libroutines.so");
        if (first_subpart != NULL) {
            cur_part1 = strtok(str, "-");
            break;
        }
    }
    char *address1 = cur_part1;
    uintptr_t long_address1 = strtol(address1, &ptr1, 16);
    fclose(file1);


    char *ptr2 = NULL;
    FILE *file2 = fopen("/proc/self/maps", "r");
    char *cur_part2 = NULL;
    char str2[PATH_MAX + 1];
    while (fgets(str2, sizeof(str2), file2) != NULL) {
        char *first_subpart2 = strstr(str2,  "libroutines.so");
        if (first_subpart2 != NULL) {
            cur_part2 = strtok(str2, "-");
            break;
        }
    }
    char *address2 = cur_part2;
    uintptr_t long_address2 = strtol(address2, &ptr2, 16);
    fclose(file2);

    uintptr_t uptr;
    int arg;
    while (read(STDIN_FILENO, &uptr, sizeof(uintptr_t)) > 0) {
        if (read(STDIN_FILENO, &arg, sizeof(int)) < 0) {
            return 1;
        }
        uintptr_t ufunc = long_address2 + (uptr - long_address1);
        typedef void func(int);
        func* f = (func*) ufunc;
        f(arg);
    }
    return 0;
}