#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char **argv) {
    struct stat file_stat;
    for (int i = 1; i < argc; ++i) {
        stat(argv[i], &file_stat);
        if (lstat(argv[i], &file_stat) == -1) {
            printf("%s (missing)\n", argv[i]);
        } else if (S_ISLNK(file_stat.st_mode)) {
            printf("%s (broken symlink)\n", argv[i]);
        } else {
            printf("%s\n", argv[i]);
        }
    }
    return 0;
}