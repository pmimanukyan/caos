#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <sys/param.h>
#include <ctype.h>

int main(int argc, char **argv) {
    long long int sum = 0;
    char str[PATH_MAX];
    if (argc < 2) {
        printf("%d", 0);
        return 1;
    }
    DIR *dir = opendir(argv[1]);
    if (!dir) {
        return 1;
    }
    struct dirent *entry;

    int len = snprintf(str, sizeof(str), "%s/", argv[1]);
    if (len >= sizeof(str)) {
        return 1;
    }
    uid_t uid = getuid();
    while ((entry = readdir(dir))) {
        struct stat file_stat;
        if (snprintf(str + len, sizeof(str) - len, "%s", entry->d_name) >= sizeof(str) - len) {
            return 1;
        }
        if (stat(str, &file_stat) == -1) {
            continue;
        }
        if (S_ISREG(file_stat.st_mode) && isupper(entry->d_name[0]) && uid == file_stat.st_uid) {
            sum += file_stat.st_size;
        }
    }
    closedir(dir);
    printf("%lld\n", sum);
}