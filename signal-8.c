#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

volatile int count;

void func(int s) {
    printf("%d\n", count);
    fflush(stdout);
    if (++count == 4) {
        exit(0);
    }
}
int main() {
    struct sigaction sa;
    sa.sa_handler = func;
    sa.sa_flags = SA_RESTART;
    sigaction(SIGINT, &sa, NULL);
    printf("%d\n", getpid());
    fflush(stdout);
    while (1) pause();
}