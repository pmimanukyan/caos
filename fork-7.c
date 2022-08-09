#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int number;
    int res;
    pid_t main_id = getpid();
    int k = 1;
    while ((res = scanf("%d", &number)) == 1) {
        pid_t id = fork();
        if (k) {
            k = 0;
            if (id == -1) {
                printf("-1\n");
                exit(0);
            }
        }
        if (id == -1) {
            exit(1);
        }
        if (id != 0) { // родитель
            int status;
            waitpid(id, &status, 0);
            if (WIFEXITED(status) == 1 && WEXITSTATUS(status) == 0) {
                printf("%d\n", number);
                exit(0);
            } else {
                pid_t cur_child_id = getpid();
                if (main_id == cur_child_id) {
                    printf("-1\n");
                    exit(0);
                } else {
                    exit(1);
                }
            }
        }

    }
    if (res != EOF) {
        return -1;
    }
}