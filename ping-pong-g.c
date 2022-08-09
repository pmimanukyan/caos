#include <sys/signalfd.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

__attribute__((noreturn)) void work(pid_t pid, int fd[],  int sfd, long int n, int id) {
    struct signalfd_siginfo fdsinfo;
    while (1) {
        if (read(sfd, &fdsinfo, sizeof(fdsinfo)) < 0) {
            exit(1);
        }
        int buf;
        if (fdsinfo.ssi_signo == SIGUSR1) {
            if (read(fd[0], &buf, sizeof(buf)) < 0) {
                exit(1);
            }
            printf("%d %d\n", id, buf);
            fflush(stdout);
            if (buf == n) {
                kill(pid, SIGINT);
                exit(0);
            }
            ++buf;
            if (write(fd[1], &buf, sizeof(buf)) < 0) {
                exit(1);
            }
            kill(pid, SIGUSR1);
        } else if (fdsinfo.ssi_signo == SIGINT) {
            exit(0);
        }
    }
}


int main(int argc, char *argv[]) {
    if (argc < 2) {
        return 1;
    }
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGUSR1);
    sigaddset(&set, SIGINT);
    sigprocmask(SIG_BLOCK, &set, NULL);

    int sfd = signalfd(-1, &set, 0);
    if (sfd == -1) {
        perror("signalfd");
        exit(1);
    }
    long int n = strtol(argv[1], NULL, 10);
    int fd[2];
    if (pipe(fd) == -1) {
        perror("pipe");
        close(sfd);
        exit(1);
    }

    pid_t pid1 = fork();
    if (pid1 == -1) {
        perror("pid1");
        exit(1);
    } else if (pid1 == 0) {
        int s;
        if (read(fd[0], &s, sizeof(s)) < 0) {
            exit(1);
        }
        work(s, fd, sfd, n, 1);
    }

    pid_t pid2 = fork();
    if (pid2 == -1) {
        perror("pid2");
        exit(1);
    } else if (pid2 == 0) {
        work(pid1, fd, sfd, n, 2);
    }
    if (write(fd[1], &pid2, sizeof(pid2)) < 0) {
        exit(1);
    }
    int num = 1;
    if (write(fd[1], &num, sizeof(num)) < 0) {
        exit(1);
    }
    kill(pid1, SIGUSR1);
    close(sfd);
    wait(NULL);
    wait(NULL);
}

// 1 1
// 2 2
// 1 3
// 2 4