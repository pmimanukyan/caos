// cmd1 | cmd2 | ... | cmdN
// ./solution ls cat wc

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>

void wait_and_kill(int i, int* pids) {
    for (int j = 0; j < i; ++j) {
        if (pids[j] != 0) {
            kill(pids[j], SIGKILL);
            waitpid(pids[j], NULL, 0);
        }
    }
}

int main(int argc, char *argv[]) {
    int pfds[2];
    int prev_pipe;

    prev_pipe = -1;

    int* pids = calloc(argc, sizeof(*pids));
    if (pids == NULL) {
        return 1;
    }
    for (int i = 1; i < argc; i++) {
        if (pipe(pfds) < 0) {
            perror("pipe");
            wait_and_kill(i, pids);
            free(pids);
            return 1;
        }
        pid_t pid = fork();
        if (pid == -1) {
            wait_and_kill(i, pids);
            free(pids);
            return 1;
        } else if (pid == 0) {
            if (prev_pipe != STDIN_FILENO) {
                dup2(prev_pipe, STDIN_FILENO);
                close(prev_pipe);
            }
            if (i == argc - 1) {
                execlp(argv[i], argv[i], NULL);
                perror("exec in");
                free(pids);
                exit(1);
            }
            dup2(pfds[1], STDOUT_FILENO);
            close(pfds[1]);
            close(pfds[0]);
            execlp(argv[i], argv[i], NULL);
            perror("execlp failed");
            free(pids);
            exit(1);
        }
        pids[i] = pid;
        close(prev_pipe);
        close(pfds[1]);
        prev_pipe = pfds[0];
    }

    while (wait(NULL) != -1) {}
    free(pids);
    return 0;
}