#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int status = 0;
    int wpid;
    int id = fork();
    if (id == 0) {
        int id1 = fork();
        if (id1 == 0) {
            printf("3 ");
            exit(0);
        }
        while ((wpid = wait(&status)) > 0);
        printf("2 ");
        exit(0);
    }
    while ((wpid = wait(&status)) > 0);
    printf("1\n");
    exit(0);
}