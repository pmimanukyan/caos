#include <stdio.h>
#include <unistd.h>
#include <signal.h>

char message[] = "We communicate on my terms.\n";
static void handler1(int signum, siginfo_t* siginfo, void* unused) {
    ssize_t res = write(STDOUT_FILENO, message, sizeof(message) - 1);
    (void)res;
}

int main(int argc, char** argv) {
    struct sigaction sa1 = { .sa_sigaction = handler1, .sa_flags = SA_RESTART | SA_SIGINFO};
    sigaction(SIGTERM, &sa1, NULL);

    int res;
    char reader[1000];
    while ((res = read(STDIN_FILENO, &reader, 1000)) > 0) {
        int write_res = write(STDOUT_FILENO, &reader, res);
        (void) write_res;
    }
}