#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/file.h>
#include <sys/stat.h>

int work(char* cmd) {
    pid_t pid = fork();
    if (pid == -1) {
        return 1;
    } else if (pid == 0) {
        if(execlp(cmd, cmd, NULL) < 0) {
            return 1;
        }
    } else {
        int status;
        waitpid(pid, &status, 0);
        if (!(WIFEXITED(status) && WEXITSTATUS(status) == 0)) {
            return 1;
        }
    }
    return 0;
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        return 1;
    }
    char* cmd1 = argv[1];
    char* cmd2 = argv[2];
    char* out = argv[3];

    int ret;
    if ((ret = work(cmd1))) {
        FILE* f = fopen(out, "w");
        if (f == NULL) {
            return 1;
        }
        dup2(fileno(f), fileno(stdout));
        return work(cmd2);
    }

    return ret;
}