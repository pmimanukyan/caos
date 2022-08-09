#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

enum {
    USR1 = 1,
    USR2 = 2
};
volatile sig_atomic_t USR_TYPE = 1;

void handler1(int s) {
    USR_TYPE = USR1;
}
void handler2(int s) {
    USR_TYPE = USR2;
}

int main() {
    struct sigaction sa1 = { .sa_handler = handler1, .sa_flags = SA_RESTART };
    sigaction(SIGUSR1, &sa1, NULL);
    sa1.sa_handler = handler2;
    sa1.sa_flags = SA_RESTART;
    sigaction(SIGUSR2, &sa1, NULL);
    printf("%d\n", getpid());
    fflush(stdout);
    int res;
    long long int number;
    while ((res = scanf("%lld", &number)) == 1) {
        if (USR_TYPE == USR1) {
            printf("%lld\n", -number);
            fflush(stdout);
        } else {
            printf("%lld\n", number * number);
            fflush(stdout);
        }
    }
    if (res != EOF) {
        return 1;
    }
}