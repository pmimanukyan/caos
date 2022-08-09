#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        return 1;
    }
    int fd[2];
    if (pipe(fd) == -1) {
        return 1;
    }

    pid_t pid1 = fork();
    if (pid1 == -1) {
        perror("pid1");
        return 1;
    } else if (pid1 == 0) {
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        if (execlp(argv[1], argv[1], NULL) < 0) {
            return 1;
        }
    }

    close(fd[1]);
    pid_t pid2 = fork();
    if (pid2 == -1) {
        perror("pid2");
        return 1;
    } else if (pid2 == 0) {
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        if (execlp(argv[2], argv[2], NULL) < 0) {
            return 1;
        }
    }

    close(fd[0]);
    int status1, status2;
    waitpid(pid1, &status1, 0);
    waitpid(pid2, &status2, 0);
}