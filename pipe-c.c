#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int fd[2];
    if (pipe(fd) == -1) {
        return 1;
    }
    pid_t pid1 = fork();
    if (pid1 == -1) {
        perror("pid");
        return 1;
    } else if (pid1 == 0) {
        int pid2 = fork();
        if (pid2 == -1) {
            perror("pid2");
            return 1;
        } else if (pid2 == 0) {
            close(fd[1]);
            long long sum = 0;
            long number;
            while (read(fd[0], &number, sizeof(long)) > 0) {
                sum += number;
            }
            close(fd[0]);
            printf("%lld\n", sum);
            return 0;
        }
        close(fd[0]);
        close(fd[1]);
        waitpid(pid2, NULL, 0);
    } else {
        int res;
        long number;
        close(fd[0]);
        while ((res = scanf("%ld", &number)) == 1) {
            if(write(fd[1], &number, sizeof(number)) < 0) {
                return 1;
            }
        }
        int status;
        close(fd[1]);
        wait(&status);
        if (res != EOF) {
            return 1;
        }
    }
}