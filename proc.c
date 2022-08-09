#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>

int main(int argc, char** argv) {
    int index_of_coma = 0;
    for (int i = 1; i < argc - 1; ++i) {
        if (strcmp(argv[i], ";") == 0) {
            index_of_coma = i;
            argv[i] = NULL;
            break;
        }
    }
    char *cmd1 = argv[1];
    char *cmd2 = argv[index_of_coma + 1];

    pid_t pid1 = fork();
    if (pid1 == 0) {
        execvp(cmd1, &argv[1]);
        exit(1);
    }

    pid_t pid2 = fork();
    if (pid2 == 0) {
        execvp(cmd2, &argv[index_of_coma + 1]);
        exit(1);
    }

    int status;
    pid_t finished = wait(&status);
    if (finished != pid1) {
        kill(pid1, SIGKILL);
    } else {
        kill(pid2, SIGKILL);
    }
}