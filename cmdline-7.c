#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int execute(char* cmd) {
    int cmd_status;
    pid_t cmd_pid = fork();
    if (cmd_pid == -1) {
        exit(1);
    } else if (cmd_pid == 0) {
        if (execlp(cmd, cmd, NULL) < 0) {
            perror("exec");
            exit(1);
        }
    }
    waitpid(cmd_pid, &cmd_status, 0);
    return WIFEXITED(cmd_status) && WEXITSTATUS(cmd_status) == 0;
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        perror("argc");
        return 1;
    }
    char* cmd1 = argv[1];
    char* cmd2 = argv[2];
    char* cmd3 = argv[3];
    return (execute(cmd1) || execute(cmd2)) && execute(cmd3) ? 0 : 1;
}

// прям кайфанул :) 