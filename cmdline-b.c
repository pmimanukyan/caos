#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>


int main(int argc, char **argv) {
    if (argc <= 3) {
        fprintf(stderr, "args\n");
        return 1;
    }

    char *cmd_exec = argv[1];
    char *in = argv[2];
    char *out = argv[3];

    pid_t main_pid = getpid();
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        return 1;
    } else if (pid == 0) {
        int in_fd = open(in, O_RDONLY);
        if (in_fd == -1) {
            perror("open in");
            return 1;
        }
        int out_fd = open(out, O_WRONLY | O_CREAT | O_TRUNC, 0666);
        if (out_fd == -1) {
            perror("open out");
            return 1;
        }
        dup2(in_fd, STDIN_FILENO);
        dup2(out_fd, STDOUT_FILENO);
        close(in_fd);
        close(out_fd);
        execlp(cmd_exec, cmd_exec, NULL);
        return 1;
    } else {
        int status;
        waitpid(pid, &status, 0);
    }
    return 0;
}