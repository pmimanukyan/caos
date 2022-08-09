#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int return_val = 0;

int logto(char *cmd, char* out) {
    pid_t pid = fork();
    if (pid == -1) {
        return 0;
    } else if (pid == 0) {
        if (execlp(cmd, cmd, NULL) < 0) {
            exit(1);
        }
    } else {
        int cmd_status;
        waitpid(pid, &cmd_status, 0);
        if (WIFEXITED(cmd_status) && WEXITSTATUS(cmd_status) == 0) {
            return_val = 1;
        }
    }
    return return_val;
}

int main(int argc, char* argv[]) {
    char* cmd1 = argv[1];
    char* cmd2 = argv[2];
    char* out = argv[3];
    FILE * f = fopen(out, "a");
    dup2(fileno(f), fileno(stdout));
    if (logto(cmd1, out) || logto(cmd2, out) || return_val == 1) {
        return 0;
    } else {
        return 1;
    }
}