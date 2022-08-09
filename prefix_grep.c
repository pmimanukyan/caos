#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <limits.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        return 1;
    }
    char *name = argv[1];
    char *pref = argv[2];
    size_t pref_size = strlen(pref);

    DIR *dir = opendir(name);
    if (!dir) {
        perror("dir");
        return 1;
    }

    struct dirent *ent;
    struct stat st;

    while ((ent = readdir(dir))) {
        char* dir_name = ent->d_name;
        char path_name[PATH_MAX];
        sprintf(path_name, "%s/%s", name, dir_name);
        int sb = stat(path_name, &st);
        if (sb < 0 || S_ISDIR(st.st_mode)) {
            continue;
        }

        FILE* f = fopen(path_name, "r");
        if (f == NULL) {
            return 1;
        }

        int idx = 0;
        int flag = 1;
        for (int i = 0; i < pref_size; ++i) {
            int c;
            if (((c = fgetc(f)) == EOF) || (c != pref[idx])) {
                flag = 0;
                break;
            }
            ++idx;
        }
        if (flag == 1) {
            printf("%s\n", dir_name);
        }
    }
    closedir(dir);
}