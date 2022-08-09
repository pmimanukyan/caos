#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <strings.h>
#include <limits.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        return 1;
    }

    char path[PATH_MAX];
    pid_t main_pid = getpid();
    const char *dir = getenv("XDG_RUNTIME_DIR");
    if (!dir) { dir = getenv("TMPDIR"); }
    if (!dir) { dir = "/tmp"; }
    int len = snprintf(path, sizeof(path), "%s/%dtest.py", dir, main_pid);
    if (len >= PATH_MAX) {
        return 1;
    }
    FILE *f = fopen(path, "w");
    chmod(path, S_IRWXU);
    if (f == NULL) {
        printf("Error opening file!\n");
        return 1;
    }
    //"#!/usr/bin/env python3
    fprintf(f, "#!/usr/bin/env python3\n");
    fprintf(f, "import sys\n");
    fprintf(f, "import os\n");
    fprintf(f, "print(");
    fprintf(f, "%s  ", argv[1]);
    for (int i = 2; i < argc; ++i) {
        fprintf(f, "* %s", argv[i]);
    }
    fprintf(f, ")\n");
    fprintf(f, "os.remove(sys.argv[0])\n");
    fclose(f);
    execlp(path, path, NULL);
    return 1;
}