#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int mysys(const char *str) {
    pid_t pid = fork();
    int status = 0;
    if (pid == -1) {
        return -1;
    } else if (pid == 0) {
        execl("/bin/sh", "sh", "-c", str, NULL);
        _exit(127);
    } else {
        waitpid(pid, &status, 0);
        if (WIFSIGNALED(status)) {
            return 128 + WTERMSIG(status);
        }
        if (0 <= WEXITSTATUS(status) && WEXITSTATUS(status) <= 127) {
            return WEXITSTATUS(status);
        }
    }
    return 1;
}