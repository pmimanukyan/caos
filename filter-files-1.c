#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char **argv) {
    struct stat file_stat;
    long long int sum = 0;
    for (int i = 1; i < argc; ++i) {
        if (lstat(argv[i], &file_stat) == -1) {
            continue;
        }
        if (S_ISREG(file_stat.st_mode) && file_stat.st_nlink == 1) {
            sum += file_stat.st_size;
        }
    }
    printf("%lld\n", sum);
    return 0;
}