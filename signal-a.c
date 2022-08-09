#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/file.h>
#include <stdlib.h>

enum SigTypes {
    NONE,
    TERM,
    SIGMIN
};

enum Constants {
    ARR_SIZE = 20,
    DESCRIPTOR_INIT = -10,
    CHUNK_SIZE = 16
};

volatile sig_atomic_t sig_type = NONE;
volatile sig_atomic_t file_index = 0;

void handler1(int s) {
    sig_type = TERM;
}
void handler2(int s) {
    sig_type = SIGMIN;
    file_index = s - SIGRTMIN;
}

int main(int argc, char *argv[]) {
    sigset_t set;
    sigemptyset(&set);
    struct sigaction sa1 = { .sa_handler = handler1};
    sigaction(SIGTERM, &sa1, NULL);
    sigaddset(&set, SIGTERM);

    // creating sum array
    long long int sum_arr[ARR_SIZE] = {0};

    // creating fd array
    int fds[ARR_SIZE];
    for (int i = 0; i < ARR_SIZE; ++i) {
        fds[i] = DESCRIPTOR_INIT;
    }
    sa1.sa_handler = handler2;
    for (int i = 0; i < argc - 1; ++i) {
        sigaction(SIGRTMIN + i, &sa1, NULL);
        sigaddset(&set, SIGRTMIN + i);
    }

    sigprocmask(SIG_BLOCK, &set, NULL);
    printf("%d\n", getpid());
    fflush(stdout);

    sigset_t empty_set;
    sigemptyset(&empty_set);

    while (1) {
        if (sig_type == NONE) {
            sigsuspend(&empty_set);
        }
        if (sig_type == TERM) {
            for (int i = 0; i < argc - 1; ++i) {
                printf("%lld\n", sum_arr[i]);
                fflush(stdout);
            }
            exit(0);
        } else if (sig_type == SIGMIN) {
            int index = file_index;
            sig_type = NONE;
            if (fds[index] == DESCRIPTOR_INIT) {
                fds[index] = open(argv[index + 1], O_RDONLY);
            }
            if (fds[index] == -1) {
                continue;
            } else {
                long long int sum = 0;
                char number[CHUNK_SIZE];
                ssize_t res;
                sigprocmask(SIG_UNBLOCK, &set, NULL);
                while ((res = read(fds[index], &number, CHUNK_SIZE)) > 0) {
                    long long num = strtoll(number, NULL, 10);
                    sum += num;
                    if (sig_type != NONE) {
                        break;
                    }
                }
                sum_arr[index] += sum;
                sigprocmask(SIG_BLOCK, &set, NULL);
                if (res == 0) {
                    close(fds[index]);// end of file
                    fds[index] = -1;
                }
            }
        }
    }
}