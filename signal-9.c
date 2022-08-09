#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>

volatile sig_atomic_t last_signal = 0;

void handler1(int signal) {
    last_signal = signal;
}

int main() {
    volatile sig_atomic_t counter_usr1 = 0;
    volatile sig_atomic_t counter_usr2 = 0;

    sigset_t myset;
    sigemptyset(&myset);
    sigaddset(&myset, SIGUSR1);
    sigaddset(&myset, SIGUSR2);
    sigaddset(&myset, SIGTERM);
    sigprocmask(SIG_BLOCK, &myset, NULL);

    struct sigaction sa1 = { .sa_handler = handler1, .sa_flags = SA_RESTART };
    sigaction(SIGUSR1, &sa1, NULL);
    sigaction(SIGUSR2, &sa1, NULL);
    sigaction(SIGTERM, &sa1, NULL);
    printf("%d\n", getpid());
    fflush(stdout);

    sigset_t empty_set;
    sigemptyset(&empty_set);

    while (1) {
        sigsuspend(&empty_set);
        if (last_signal == SIGUSR1) {
            printf("%d\n", counter_usr1);
            fflush(stdout);
            printf("%d\n", counter_usr2);
            fflush(stdout);
            ++counter_usr1;
        } else if (last_signal == SIGUSR2) {
            ++counter_usr2;
        } else if (last_signal == SIGTERM) {
            exit(0);
        }
    }
}